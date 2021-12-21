#include "c74_min.h"

using namespace c74::min;

class tapedust : public object<tapedust>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"special treble-erode noise, a 'slew noise' effect"};
	MIN_TAGS {"tape"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "dust", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.0;
			B = 1.0;
			
			for(int count = 0; count < 11; count++) {
				bL[count] = 0.0;
				fL[count] = 0.0;
				bR[count] = 0.0;
				fR[count] = 0.0;
			}
			
			fpNShapeL = 0.0;
			fpNShapeR = 0.0;
			fpFlip = true;
			//this is reset: values being initialized only once. Startup values, whatever they are.
			
			return {};
		}
	};

	void operator()(audio_bundle _input, audio_bundle _output) {
		double* in1 = _input.samples(0);
		double* in2 = _input.samples(1);
		double* out1 = _output.samples(0);
		double* out2 = _output.samples(1);
		double overallscale = 1.0;
		overallscale /= 44100.0;
		overallscale *= samplerate();

		long sampleFrames = _input.frame_count();

		long double inputSampleL;
		long double inputSampleR;
	
		double drySampleL;
		double drySampleR;
		double rRange = pow(A,2)*5.0;
		double xfuzz = rRange * 0.002;
		double rOffset = (rRange*0.4) + 1.0;
		double rDepthL; //the randomly fluctuating value
		double rDepthR; //the randomly fluctuating value
		double gainL;
		double gainR;
		double wet = B;
		double dry = 1.0 - wet;
		
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
			drySampleL = inputSampleL;
			drySampleR = inputSampleR;
			
			for(int count = 9; count < 0; count--) {
				bL[count+1] = bL[count];
				bR[count+1] = bR[count];
			}
			
			bL[0] = inputSampleL;
			bR[0] = inputSampleR;
			inputSampleL = rand() / (double)RAND_MAX;
			inputSampleR = rand() / (double)RAND_MAX;
			gainL = rDepthL = (inputSampleL * rRange) + rOffset;
			gainR = rDepthR = (inputSampleR * rRange) + rOffset;
			inputSampleL *= ((1.0-fabs(bL[0]-bL[1]))*xfuzz);
			inputSampleR *= ((1.0-fabs(bR[0]-bR[1]))*xfuzz);
			if (fpFlip) {
				inputSampleL = -inputSampleL;
				inputSampleR = -inputSampleR;
			}
			fpFlip = !fpFlip;
			
			for(int count = 0; count < 9; count++) {			
				if (gainL > 1.0) {
					fL[count] = 1.0;
					gainL -= 1.0;
				} else {
					fL[count] = gainL;
					gainL = 0.0;
				}
				if (gainR > 1.0) {
					fR[count] = 1.0;
					gainR -= 1.0;
				} else {
					fR[count] = gainR;
					gainR = 0.0;
				}
				fL[count] /= rDepthL;
				fR[count] /= rDepthR;
				inputSampleL += (bL[count] * fL[count]);
				inputSampleR += (bR[count] * fR[count]);
			}
			
			if (wet < 1.0) {
				inputSampleL = (inputSampleL * wet) + (drySampleL * dry);
				inputSampleR = (inputSampleR * wet) + (drySampleR * dry);
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
	bool fpFlip;
	//default stuff

	double bL[11];
	double fL[11];		
	double bR[11];
	double fR[11];		

};
MIN_EXTERNAL(tapedust);

