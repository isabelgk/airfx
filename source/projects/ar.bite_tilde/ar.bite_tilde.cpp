#include "c74_min.h"

using namespace c74::min;

class bite : public object<bite>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"an unusual edge-maker"};
	MIN_TAGS {"destruction, lofi"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "bite", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "output", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			sampleAL = 0.0;
			sampleBL = 0.0;
			sampleCL = 0.0;
			sampleDL = 0.0;
			sampleEL = 0.0;
			sampleFL = 0.0;
			sampleGL = 0.0;
			sampleHL = 0.0;
			sampleIL = 0.0;
			
			sampleAR = 0.0;
			sampleBR = 0.0;
			sampleCR = 0.0;
			sampleDR = 0.0;
			sampleER = 0.0;
			sampleFR = 0.0;
			sampleGR = 0.0;
			sampleHR = 0.0;
			sampleIR = 0.0;
			
			fpNShapeL = 0.0;
			fpNShapeR = 0.0;
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

		double overallscale = 1.3;
		overallscale /= 44100.0;
		overallscale *= samplerate();
	
		double gain = ((A*2.0)-1.0)*overallscale;
		double outputgain = B;
		double midA;
		double midB;
		double midC;
		double midD;
		double trigger;
		double inputSampleL;
		double inputSampleR;	
	
	    while (--sampleFrames >= 0)
	    {		
			sampleIL = sampleHL;
			sampleHL = sampleGL;
			sampleGL = sampleFL;
			sampleFL = sampleEL;
			sampleEL = sampleDL;
			sampleDL = sampleCL;
			sampleCL = sampleBL;
			sampleBL = sampleAL;
			sampleAL = *in1;
	
			sampleIR = sampleHR;
			sampleHR = sampleGR;
			sampleGR = sampleFR;
			sampleFR = sampleER;
			sampleER = sampleDR;
			sampleDR = sampleCR;
			sampleCR = sampleBR;
			sampleBR = sampleAR;
			sampleAR = *in2;
			//rotate the buffer in primitive fashion
			if (sampleAL<1.2e-38 && -sampleAL<1.2e-38) {
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
				sampleAL = applyresidue;
			}
			if (sampleAR<1.2e-38 && -sampleAR<1.2e-38) {
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
				sampleAR = applyresidue;
				//this denormalization routine produces a white noise at -300 dB which the noise
				//shaping will interact with to produce a bipolar output, but the noise is actually
				//all positive. That should stop any variables from going denormal, and the routine
				//only kicks in if digital black is input. As a final touch, if you save to 24-bit
				//the silence will return to being digital black again.
			}
			
			midA = sampleAL - sampleEL;
			midB = sampleIL - sampleEL;
			midC = sampleCL - sampleEL;
			midD = sampleGL - sampleEL;
			midA *= ((((sampleBL + sampleCL + sampleDL)/3) - ((sampleAL + sampleEL)/2.0))*gain);
			midB *= ((((sampleFL + sampleGL + sampleHL)/3) - ((sampleEL + sampleIL)/2.0))*gain);		
			midC *= ((sampleDL - ((sampleCL + sampleEL)/2.0))*gain);
			midD *= ((sampleFL - ((sampleEL + sampleGL)/2.0))*gain);
			trigger = sin(midA + midB + midC + midD);		
			inputSampleL = sampleEL + (trigger*8.0);
			
			midA = sampleAR - sampleER;
			midB = sampleIR - sampleER;
			midC = sampleCR - sampleER;
			midD = sampleGR - sampleER;
			midA *= ((((sampleBR + sampleCR + sampleDR)/3) - ((sampleAR + sampleER)/2.0))*gain);
			midB *= ((((sampleFR + sampleGR + sampleHR)/3) - ((sampleER + sampleIR)/2.0))*gain);		
			midC *= ((sampleDR - ((sampleCR + sampleER)/2.0))*gain);
			midD *= ((sampleFR - ((sampleER + sampleGR)/2.0))*gain);
			trigger = sin(midA + midB + midC + midD);		
			inputSampleR = sampleER + (trigger*8.0);
			
			if (outputgain != 1.0) {
				inputSampleL *= outputgain;
				inputSampleR *= outputgain;
			}
			
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
	double sampleAL;
	double sampleBL;
	double sampleCL;
	double sampleDL;
	double sampleEL;
	double sampleFL;
	double sampleGL;
	double sampleHL;
	double sampleIL;
	
	double sampleAR;
	double sampleBR;
	double sampleCR;
	double sampleDR;
	double sampleER;
	double sampleFR;
	double sampleGR;
	double sampleHR;
	double sampleIR;
	
};
MIN_EXTERNAL(bite);

