#include "c74_min.h"

using namespace c74::min;

class density : public object<density>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a Swiss Army Knife of saturation/antisaturation"};
	MIN_TAGS {"saturation"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "density", 0.2, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "highpass", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "output", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.2; //equivalent of 0.0 in VST 0-1 scale for 'Density' control
			B = 0.0;
			C = 1.0;
			D = 1.0;
			iirSampleAL = 0.0;
			iirSampleBL = 0.0;
			iirSampleAR = 0.0;
			iirSampleBR = 0.0;
			fpFlip = true;
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

		double overallscale = 1.0;
		overallscale /= 44100.0;
		overallscale *= samplerate();
		double density = (A*5.0)-1.0;
		double iirAmount = pow(B,3)/overallscale;
		double output = C;
		double wet = D;
		double dry = 1.0-wet;
		double bridgerectifier;
		double out = fabs(density);
		density = density * fabs(density);
		double count;
		
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
	
			if (fpFlip)
			{
				iirSampleAL = (iirSampleAL * (1.0 - iirAmount)) + (inputSampleL * iirAmount);
				inputSampleL -= iirSampleAL;
				iirSampleAR = (iirSampleAR * (1.0 - iirAmount)) + (inputSampleR * iirAmount);
				inputSampleR -= iirSampleAR;
			}
			else
			{
				iirSampleBL = (iirSampleBL * (1.0 - iirAmount)) + (inputSampleL * iirAmount);
				inputSampleL -= iirSampleBL;
				iirSampleBR = (iirSampleBR * (1.0 - iirAmount)) + (inputSampleR * iirAmount);
				inputSampleR -= iirSampleBR;
			}
			//highpass section
			fpFlip = !fpFlip;
			
			count = density;
			while (count > 1.0)
			{
				bridgerectifier = fabs(inputSampleL)*1.57079633;
				if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
				//max value for sine function
				bridgerectifier = sin(bridgerectifier);
				if (inputSampleL > 0.0) inputSampleL = bridgerectifier;
				else inputSampleL = -bridgerectifier;
				
				bridgerectifier = fabs(inputSampleR)*1.57079633;
				if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
				//max value for sine function
				bridgerectifier = sin(bridgerectifier);
				if (inputSampleR > 0.0) inputSampleR = bridgerectifier;
				else inputSampleR = -bridgerectifier;			
				
				count = count - 1.0;
			}
			//we have now accounted for any really high density settings.
			
			while (out > 1.0) out = out - 1.0;
			
			bridgerectifier = fabs(inputSampleL)*1.57079633;
			if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
			//max value for sine function
			if (density > 0) bridgerectifier = sin(bridgerectifier);
			else bridgerectifier = 1-cos(bridgerectifier);
			//produce either boosted or starved version
			if (inputSampleL > 0) inputSampleL = (inputSampleL*(1-out))+(bridgerectifier*out);
			else inputSampleL = (inputSampleL*(1-out))-(bridgerectifier*out);
			//blend according to density control
			
			bridgerectifier = fabs(inputSampleR)*1.57079633;
			if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
			//max value for sine function
			if (density > 0) bridgerectifier = sin(bridgerectifier);
			else bridgerectifier = 1-cos(bridgerectifier);
			//produce either boosted or starved version
			if (inputSampleR > 0) inputSampleR = (inputSampleR*(1.0-out))+(bridgerectifier*out);
			else inputSampleR = (inputSampleR*(1.0-out))-(bridgerectifier*out);
			//blend according to density control
			
			if (output < 1.0) {
				inputSampleL *= output;
				inputSampleR *= output;
			}
			if (wet < 1.0) {
				inputSampleL = (drySampleL * dry)+(inputSampleL * wet);
				inputSampleR = (drySampleR * dry)+(inputSampleR * wet);
			}
			//nice little output stage template: if we have another scale of floating point
			//number, we really don't want to meaninglessly multiply that by 1.0.		
			
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
	double iirSampleAL;
	double iirSampleBL;
	double iirSampleAR;
	double iirSampleBR;
	bool fpFlip;
};
MIN_EXTERNAL(density);

