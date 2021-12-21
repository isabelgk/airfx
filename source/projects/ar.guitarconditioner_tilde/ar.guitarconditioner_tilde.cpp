#include "c74_min.h"

using namespace c74::min;

class guitarconditioner : public object<guitarconditioner>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"tone shaper"};
	MIN_TAGS {""};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};


	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			fpNShapeL = 0.0;
			fpNShapeR = 0.0;
			fpFlip = true;
			lastSampleTL = 0.0;
			lastSampleBL = 0.0; //for Slews. T for treble, B for bass
			iirSampleTAL = 0.0;
			iirSampleTBL = 0.0;
			iirSampleBAL = 0.0;
			iirSampleBBL = 0.0; //for Highpasses
			//this is reset: values being initialized only once. Startup values, whatever they are.
			lastSampleTR = 0.0;
			lastSampleBR = 0.0; //for Slews. T for treble, B for bass
			iirSampleTAR = 0.0;
			iirSampleTBR = 0.0;
			iirSampleBAR = 0.0;
			iirSampleBBR = 0.0; //for Highpasses
			//this is reset: values being initialized only once. Startup values, whatever they are.
			
			return {};
		}
	};

	void operator()(audio_bundle _input, audio_bundle _output) {
		double* in1 = _input.samples(0);
		double* in2 = _input.samples(1);
		double* out1 = _output.samples(0);
		double* out2 = _output.samples(1);
		long sampleFrames = _input.frame_count();

		double overallscale = 1.0;
		overallscale /= 44100.0;
		overallscale *= samplerate();
	
		long double inputSampleL;
		long double inputSampleR;
		long double trebleL;
		long double bassL;
		long double trebleR;
		long double bassR;
		
		double iirTreble = 0.287496/overallscale; //tight is -1
		double iirBass = 0.085184/overallscale; //tight is 1
		iirTreble += iirTreble;
		iirBass += iirBass; //simple double when tight is -1 or 1
		double tightBass = 0.6666666666;
		double tightTreble = -0.3333333333;
		double offset;
		double clamp;
		double threshTreble = 0.0081/overallscale;
		double threshBass = 0.0256/overallscale;
		
	
	    while (--sampleFrames >= 0)
	    {
			inputSampleL = *in1;
			inputSampleR = *in2;
			if (inputSampleL<1.2e-38 && -inputSampleL<1.2e-38) {
				static int noisesource = 0;
				//this declares a variable before anything else is compiled. It won't keep assigning
				//it to 0 for every sample, it's as if the declaration doesn't exist in this context,
				//but it lets me add this denormalization fix in a single place rather than updating
				//it in three different locations. The variable isn't thread-safe but this is only
				//a random seed and we can share it with whatever.
				noisesource = noisesource % 1700021; noisesource++;
				int residue = noisesource * noisesource;
				residue = residue % 170003; residue *= residue;
				residue = residue % 17011; residue *= residue;
				residue = residue % 1709; residue *= residue;
				residue = residue % 173; residue *= residue;
				residue = residue % 17;
				double applyresidue = residue;
				applyresidue *= 0.00000001;
				applyresidue *= 0.00000001;
				inputSampleL = applyresidue;
			}
			if (inputSampleR<1.2e-38 && -inputSampleR<1.2e-38) {
				static int noisesource = 0;
				noisesource = noisesource % 1700021; noisesource++;
				int residue = noisesource * noisesource;
				residue = residue % 170003; residue *= residue;
				residue = residue % 17011; residue *= residue;
				residue = residue % 1709; residue *= residue;
				residue = residue % 173; residue *= residue;
				residue = residue % 17;
				double applyresidue = residue;
				applyresidue *= 0.00000001;
				applyresidue *= 0.00000001;
				inputSampleR = applyresidue;
				//this denormalization routine produces a white noise at -300 dB which the noise
				//shaping will interact with to produce a bipolar output, but the noise is actually
				//all positive. That should stop any variables from going denormal, and the routine
				//only kicks in if digital black is input. As a final touch, if you save to 24-bit
				//the silence will return to being digital black again.
			}
			
			trebleL = bassL = inputSampleL;
			trebleR = bassR = inputSampleR;
			trebleL += trebleL; //+3dB on treble as the highpass is higher
			trebleR += trebleR; //+3dB on treble as the highpass is higher		
			
			offset = (1 + tightTreble) + ((1-fabs(trebleL))*tightTreble); //treble HP
			if (offset < 0) offset = 0;
			if (offset > 1) offset = 1; //made offset for HP
			if (fpFlip) {
				iirSampleTAL = (iirSampleTAL * (1 - (offset * iirTreble))) + (trebleL * (offset * iirTreble));
				trebleL = trebleL - iirSampleTAL;
			} else {
				iirSampleTBL = (iirSampleTBL * (1 - (offset * iirTreble))) + (trebleL * (offset * iirTreble));
				trebleL = trebleL - iirSampleTBL;
			} //done trebleL HP
			
			offset = (1 + tightTreble) + ((1-fabs(trebleR))*tightTreble); //treble HP
			if (offset < 0) offset = 0;
			if (offset > 1) offset = 1; //made offset for HP
			if (fpFlip) {
				iirSampleTAR = (iirSampleTAR * (1 - (offset * iirTreble))) + (trebleR * (offset * iirTreble));
				trebleR = trebleR - iirSampleTAR;
			} else {
				iirSampleTBR = (iirSampleTBR * (1 - (offset * iirTreble))) + (trebleR * (offset * iirTreble));
				trebleR = trebleR - iirSampleTBR;
			} //done trebleR HP
			
			offset = (1 - tightBass) + (fabs(bassL)*tightBass); //bass HP
			if (offset < 0) offset = 0;
			if (offset > 1) offset = 1;
			if (fpFlip) {
				iirSampleBAL = (iirSampleBAL * (1 - (offset * iirBass))) + (bassL * (offset * iirBass));
				bassL = bassL - iirSampleBAL;
			} else {
				iirSampleBBL = (iirSampleBBL * (1 - (offset * iirBass))) + (bassL * (offset * iirBass));
				bassL = bassL - iirSampleBBL;
			} //done bassL HP
			
			offset = (1 - tightBass) + (fabs(bassR)*tightBass); //bass HP
			if (offset < 0) offset = 0;
			if (offset > 1) offset = 1;
			if (fpFlip) {
				iirSampleBAR = (iirSampleBAR * (1 - (offset * iirBass))) + (bassR * (offset * iirBass));
				bassR = bassR - iirSampleBAR;
			} else {
				iirSampleBBR = (iirSampleBBR * (1 - (offset * iirBass))) + (bassR * (offset * iirBass));
				bassR = bassR - iirSampleBBR;
			} //done bassR HP
			
			inputSampleL = trebleL;
			clamp = inputSampleL - lastSampleTL;
			if (clamp > threshTreble)
				trebleL = lastSampleTL + threshTreble;
			if (-clamp > threshTreble)
				trebleL = lastSampleTL - threshTreble;
			lastSampleTL = trebleL; //trebleL slew
			
			inputSampleR = trebleR;
			clamp = inputSampleR - lastSampleTR;
			if (clamp > threshTreble)
				trebleR = lastSampleTR + threshTreble;
			if (-clamp > threshTreble)
				trebleR = lastSampleTR - threshTreble;
			lastSampleTR = trebleR; //trebleR slew
			
			inputSampleL = bassL;
			clamp = inputSampleL - lastSampleBL;
			if (clamp > threshBass)
				bassL = lastSampleBL + threshBass;
			if (-clamp > threshBass)
				bassL = lastSampleBL - threshBass;
			lastSampleBL = bassL; //bassL slew
			
			inputSampleR = bassR;
			clamp = inputSampleR - lastSampleBR;
			if (clamp > threshBass)
				bassR = lastSampleBR + threshBass;
			if (-clamp > threshBass)
				bassR = lastSampleBR - threshBass;
			lastSampleBR = bassR; //bassR slew
					
			inputSampleL = trebleL + bassL; //final merge
			inputSampleR = trebleR + bassR; //final merge	
			fpFlip = !fpFlip;
	
			//stereo 64 bit dither, made small and tidy.
			int expon; frexp((double)inputSampleL, &expon);
			long double dither = (rand()/(RAND_MAX*7.737125245533627e+25))*pow(2,expon+62);
			dither /= 536870912.0; //needs this to scale to 64 bit zone
			inputSampleL += (dither-fpNShapeL); fpNShapeL = dither;
			frexp((double)inputSampleR, &expon);
			dither = (rand()/(RAND_MAX*7.737125245533627e+25))*pow(2,expon+62);
			dither /= 536870912.0; //needs this to scale to 64 bit zone
			inputSampleR += (dither-fpNShapeR); fpNShapeR = dither;
			//end 64 bit dither
	
			*out1 = inputSampleL;
			*out2 = inputSampleR;
	
			*in1++;
			*in2++;
			*out1++;
			*out2++;
		}
	}
private:
    
	long double fpNShapeL;
	long double fpNShapeR;
	//default stuff
	bool fpFlip;
	double lastSampleTL;
	double lastSampleBL; //for Slews
	double iirSampleTAL;
	double iirSampleTBL;
	double iirSampleBAL;
	double iirSampleBBL; //for Highpasses
	
	double lastSampleTR;
	double lastSampleBR; //for Slews
	double iirSampleTAR;
	double iirSampleTBR;
	double iirSampleBAR;
	double iirSampleBBR; //for Highpasses
	
};

MIN_EXTERNAL(guitarconditioner);

