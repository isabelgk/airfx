#include "c74_min.h"

using namespace c74::min;

class desk : public object<desk>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"subtle analog modeling"};
	MIN_TAGS {"audio, effect"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};


	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			lastSampleL = 0.0;
			lastOutSampleL = 0.0;
			lastSlewL = 0.0;
			lastSampleR = 0.0;
			lastOutSampleR = 0.0;
			lastSlewR = 0.0;
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

		double gain = 0.135;
		double slewgain = 0.208;	
		double prevslew = 0.333;
		double balanceB = 0.0001;
		double overallscale = 1.0;
		overallscale /= 44100.0;
		overallscale *= samplerate();
		slewgain *= overallscale;
		prevslew *= overallscale;
		balanceB /= overallscale;
		double balanceA = 1.0 - balanceB;
		double slew;
		double bridgerectifier;
		double combsample;
		
	
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
	
			//begin L
			slew = inputSampleL - lastSampleL;
			lastSampleL = inputSampleL;
			//Set up direct reference for slew
			
			bridgerectifier = fabs(slew*slewgain);
			if (bridgerectifier > 1.57079633) bridgerectifier = 1.0;
			else bridgerectifier = sin(bridgerectifier);
			if (slew > 0) slew = bridgerectifier/slewgain;
			else slew = -(bridgerectifier/slewgain);
			
			inputSampleL = (lastOutSampleL*balanceA) + (lastSampleL*balanceB) + slew;
			//go from last slewed, but include some raw values
			lastOutSampleL = inputSampleL;
			//Set up slewed reference
			
			combsample = fabs(drySampleL*lastSampleL);
			if (combsample > 1.0) combsample = 1.0;
			//bailout for very high input gains
			inputSampleL -= (lastSlewL * combsample * prevslew);
			lastSlewL = slew;
			//slew interaction with previous slew
			
			inputSampleL *= gain;
			bridgerectifier = fabs(inputSampleL);
			if (bridgerectifier > 1.57079633) bridgerectifier = 1.0;
			else bridgerectifier = sin(bridgerectifier);
			
			if (inputSampleL > 0) inputSampleL = bridgerectifier;
			else inputSampleL = -bridgerectifier;
			//drive section
			inputSampleL /= gain;
			//end L
			
			//begin R
			slew = inputSampleR - lastSampleR;
			lastSampleR = inputSampleR;
			//Set up direct reference for slew
			
			bridgerectifier = fabs(slew*slewgain);
			if (bridgerectifier > 1.57079633) bridgerectifier = 1.0;
			else bridgerectifier = sin(bridgerectifier);
			if (slew > 0) slew = bridgerectifier/slewgain;
			else slew = -(bridgerectifier/slewgain);
			
			inputSampleR = (lastOutSampleR*balanceA) + (lastSampleR*balanceB) + slew;
			//go from last slewed, but include some raw values
			lastOutSampleR = inputSampleR;
			//Set up slewed reference
			
			combsample = fabs(drySampleR*lastSampleR);
			if (combsample > 1.0) combsample = 1.0;
			//bailout for very high input gains
			inputSampleR -= (lastSlewR * combsample * prevslew);
			lastSlewR = slew;
			//slew interaction with previous slew
			
			inputSampleR *= gain;
			bridgerectifier = fabs(inputSampleR);
			if (bridgerectifier > 1.57079633) bridgerectifier = 1.0;
			else bridgerectifier = sin(bridgerectifier);
			
			if (inputSampleR > 0) inputSampleR = bridgerectifier;
			else inputSampleR = -bridgerectifier;
			//drive section
			inputSampleR /= gain;
			//end R
	
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

	long double lastSampleL;
	long double lastOutSampleL;
	double lastSlewL;
	long double lastSampleR;
	long double lastOutSampleR;
	double lastSlewR;
	
};

MIN_EXTERNAL(desk);

