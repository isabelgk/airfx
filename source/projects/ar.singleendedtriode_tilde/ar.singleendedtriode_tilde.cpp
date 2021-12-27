#include "c74_min.h"

using namespace c74::min;

class singleendedtriode : public object<singleendedtriode>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"unusual analog modeling effects"};
	MIN_TAGS {"analog, character"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "triode", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "ab", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "b", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "mix", 0.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.0;
			B = 0.0;
			C = 0.0;
			D = 0.0;
		
			postsine = sin(0.5);
			
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

		double intensity = pow(A,2)*8.0;
		double triode = intensity;
		intensity +=0.001;
		double softcrossover = pow(B,3)/8.0;
		double hardcrossover = pow(C,7)/8.0;
		double wet = D;
		double dry = 1.0 - wet;
	
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
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
			double drySampleL = inputSampleL;
			double drySampleR = inputSampleR;
			
			if (triode > 0.0)
			{
				inputSampleL *= intensity;
				inputSampleR *= intensity;
				inputSampleL -= 0.5;
				inputSampleR -= 0.5;
				
				long double bridgerectifier = fabs(inputSampleL);
				if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
				bridgerectifier = sin(bridgerectifier);
				if (inputSampleL > 0) inputSampleL = bridgerectifier;
				else inputSampleL = -bridgerectifier;
				
				bridgerectifier = fabs(inputSampleR);
				if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
				bridgerectifier = sin(bridgerectifier);
				if (inputSampleR > 0) inputSampleR = bridgerectifier;
				else inputSampleR = -bridgerectifier;
				
				inputSampleL += postsine;
				inputSampleR += postsine;
				inputSampleL /= intensity;
				inputSampleR /= intensity;
			}
			
			if (softcrossover > 0.0)
			{
				long double bridgerectifier = fabs(inputSampleL);
				if (bridgerectifier > 0.0) bridgerectifier -= (softcrossover*(bridgerectifier+sqrt(bridgerectifier)));
				if (bridgerectifier < 0.0) bridgerectifier = 0;
				if (inputSampleL > 0.0) inputSampleL = bridgerectifier;
				else inputSampleL = -bridgerectifier;				
				
				bridgerectifier = fabs(inputSampleR);
				if (bridgerectifier > 0.0) bridgerectifier -= (softcrossover*(bridgerectifier+sqrt(bridgerectifier)));
				if (bridgerectifier < 0.0) bridgerectifier = 0;
				if (inputSampleR > 0.0) inputSampleR = bridgerectifier;
				else inputSampleR = -bridgerectifier;				
			}
			
			
			if (hardcrossover > 0.0)
			{
				long double bridgerectifier = fabs(inputSampleL);
				bridgerectifier -= hardcrossover;
				if (bridgerectifier < 0.0) bridgerectifier = 0.0;
				if (inputSampleL > 0.0) inputSampleL = bridgerectifier;
				else inputSampleL = -bridgerectifier;				
				
				bridgerectifier = fabs(inputSampleR);
				bridgerectifier -= hardcrossover;
				if (bridgerectifier < 0.0) bridgerectifier = 0.0;
				if (inputSampleR > 0.0) inputSampleR = bridgerectifier;
				else inputSampleR = -bridgerectifier;				
			}
			
			if (wet !=1.0) {
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
	//default stuff
	double postsine;

};
MIN_EXTERNAL(singleendedtriode);

