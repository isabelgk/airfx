#include "c74_min.h"

using namespace c74::min;

class phasenudge : public object<phasenudge>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a phase rotator/allpass filter"};
	MIN_TAGS {"allpass, filter"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "phasenudge", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			for(int count = 0; count < 1502; count++) {dL[count] = 0.0; dR[count] = 0.0;}
			one = 1; maxdelay = 9001;
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

		
		int allpasstemp;
		double outallpass = 0.618033988749894848204586; //golden ratio!
		//if you see 0.6180 it's not a wild stretch to wonder whether you are working with a constant
		int maxdelayTarget = (int)(pow(A,3)*1501.0);
		double wet = B;
		double dry = 1.0 - wet;
		double bridgerectifier;	
		
		long double inputSampleL;
		long double inputSampleR;
		long double drySampleL;
		long double drySampleR;
		
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
			
			inputSampleL /= 4.0;
			inputSampleR /= 4.0;
			
			bridgerectifier = fabs(inputSampleL);
			bridgerectifier = sin(bridgerectifier);
			if (inputSampleL > 0) inputSampleL = bridgerectifier;
			else inputSampleL = -bridgerectifier;
			
			bridgerectifier = fabs(inputSampleR);
			bridgerectifier = sin(bridgerectifier);
			if (inputSampleR > 0) inputSampleR = bridgerectifier;
			else inputSampleR = -bridgerectifier;
			
			if (fabs(maxdelay - maxdelayTarget) > 1500) maxdelay = maxdelayTarget;
			
			if (maxdelay < maxdelayTarget) {
				maxdelay++;
				dL[maxdelay] = (dL[0]+dL[maxdelay-1]) / 2.0;
				dR[maxdelay] = (dR[0]+dR[maxdelay-1]) / 2.0;
			}
			
			if (maxdelay > maxdelayTarget) {
				maxdelay--;
				dL[maxdelay] = (dL[0]+dL[maxdelay]) / 2.0;
				dR[maxdelay] = (dR[0]+dR[maxdelay]) / 2.0;
			}
			
			allpasstemp = one - 1;
			
			if (allpasstemp < 0 || allpasstemp > maxdelay) allpasstemp = maxdelay;
			
			inputSampleL -= dL[allpasstemp]*outallpass;
			inputSampleR -= dR[allpasstemp]*outallpass;
			dL[one] = inputSampleL;
			dR[one] = inputSampleR;
			inputSampleL *= outallpass;
			inputSampleR *= outallpass;
			one--; if (one < 0 || one > maxdelay) {one = maxdelay;}
			inputSampleL += (dL[one]);
			inputSampleR += (dR[one]);
			
			bridgerectifier = fabs(inputSampleL);
			bridgerectifier = 1.0-cos(bridgerectifier);
			if (inputSampleL > 0) inputSampleL -= bridgerectifier;
			else inputSampleL += bridgerectifier;
			
			bridgerectifier = fabs(inputSampleR);
			bridgerectifier = 1.0-cos(bridgerectifier);
			if (inputSampleR > 0) inputSampleR -= bridgerectifier;
			else inputSampleR += bridgerectifier;
			
			inputSampleL *= 4.0;
			inputSampleR *= 4.0;
			
			if (wet < 1.0) {
				inputSampleL = (drySampleL * dry)+(inputSampleL * wet);
				inputSampleR = (drySampleR * dry)+(inputSampleR * wet);
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
    
	double dL[1503];
	double dR[1503];
	int one, maxdelay;

	long double fpNShapeL;
	long double fpNShapeR;
	//default stuff

};
MIN_EXTERNAL(phasenudge);

