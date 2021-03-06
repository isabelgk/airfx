#include "c74_min.h"

using namespace c74::min;

class pyewacket : public object<pyewacket>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"An old school compressor for high definition transients. Adds no fatness, just energy."};
	MIN_TAGS {"compressor"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "inputgain", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "release", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "output", 0.5, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			chase = 1.0;
			lastrectifierL = 0.0;
			lastrectifierR = 0.0;
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
		double overallscale = 1.0;
		overallscale /= 44100.0;
		overallscale *= samplerate();

		long sampleFrames = _input.frame_count();
		
		long double fpOld = 0.618033988749894848204586; //golden ratio!
		long double fpNew = 1.0 - fpOld;
		long double inputSampleL;
		long double inputSampleR;
		long double drySampleL;
		long double drySampleR;
		double bridgerectifier;
		double temprectifier;
		double inputSense;
		
		double inputGain = pow(10.0,((A*24.0)-12.0)/20.0);
		double attack = ((B+0.5)*0.006)/overallscale;
		double decay = ((B+0.01)*0.0004)/overallscale;
		double outputGain = pow(10.0,((C*24.0)-12.0)/20.0);
		double wet;
		double maxblur;
		double blurdry;
		double out;
		double dry;	
	
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
			
			if (inputGain != 1.0) {
				inputSampleL *= inputGain;
				inputSampleR *= inputGain;
			}
			drySampleL = inputSampleL;
			drySampleR = inputSampleR;
			inputSense = fabs(inputSampleL);
			if (fabs(inputSampleR) > inputSense)
				inputSense = fabs(inputSampleR);
			//we will take the greater of either channel and just use that, then apply the result
			//to both stereo channels.
			if (chase < inputSense) chase += attack;
			if (chase > 1.0) chase = 1.0;
			if (chase > inputSense) chase -= decay;
			if (chase < 0.0) chase = 0.0;
			//chase will be between 0 and ? (if input is super hot)
			out = wet = chase;
			if (wet > 1.0) wet = 1.0;
			maxblur = wet * fpNew;
			blurdry = 1.0 - maxblur;
			//scaled back so that blur remains balance of both
			if (out > fpOld) out = fpOld - (out - fpOld);
			if (out < 0.0) out = 0.0;
			dry = 1.0 - wet;
			
			if (inputSampleL > 1.57079633) inputSampleL = 1.57079633;
			if (inputSampleL < -1.57079633) inputSampleL = -1.57079633;
			if (inputSampleR > 1.57079633) inputSampleR = 1.57079633;
			if (inputSampleR < -1.57079633) inputSampleR = -1.57079633;
			
			bridgerectifier = fabs(inputSampleL);
			if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
			temprectifier = 1-cos(bridgerectifier);
			bridgerectifier = ((lastrectifierL*maxblur) + (temprectifier*blurdry));
			lastrectifierL = temprectifier;
			//starved version is also blurred by one sample
			if (inputSampleL > 0) inputSampleL = (inputSampleL*dry)+(bridgerectifier*out);
			else inputSampleL = (inputSampleL*dry)-(bridgerectifier*out);
			
			bridgerectifier = fabs(inputSampleR);
			if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
			temprectifier = 1-cos(bridgerectifier);
			bridgerectifier = ((lastrectifierR*maxblur) + (temprectifier*blurdry));
			lastrectifierR = temprectifier;
			//starved version is also blurred by one sample
			if (inputSampleR > 0) inputSampleR = (inputSampleR*dry)+(bridgerectifier*out);
			else inputSampleR = (inputSampleR*dry)-(bridgerectifier*out);
			
			if (outputGain != 1.0) {
				inputSampleL *= outputGain;
				inputSampleR *= outputGain;
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
	double chase;
	double lastrectifierL;
	double lastrectifierR;
	
};
MIN_EXTERNAL(pyewacket);

