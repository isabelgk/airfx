#include "c74_min.h"

using namespace c74::min;

class stereofx : public object<stereofx>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"aggressive stereo widener"};
	MIN_TAGS {""};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "wide", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "monobass", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "centersquish", 0.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			iirSampleA = 0.0;
			iirSampleB = 0.0;
			fpNShapeL = 0.0;
			fpNShapeR = 0.0;
			flip = false;
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
		long double mid;
		long double side;
		//High Impact section
		double stereowide = A;
		double centersquish = C;
		double density = stereowide * 2.4;
		double sustain = 1.0 - (1.0/(1.0 + (density/7.0)));
		//this way, enhance increases up to 50% and then mid falls off beyond that
		double bridgerectifier;
		double count;
		//Highpass section
		double iirAmount = pow(B,3)/overallscale;
		double tight = -0.33333333333333;
		double offset;
		//we are setting it up so that to either extreme we can get an audible sound,
		//but sort of scaled so small adjustments don't shift the cutoff frequency yet.
		
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
			//assign working variables		
			mid = inputSampleL + inputSampleR;
			side = inputSampleL - inputSampleR;
			//assign mid and side. Now, High Impact code
			count = density;
			while (count > 1.0)
			{
				bridgerectifier = fabs(side)*1.57079633;
				if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
				//max value for sine function
				bridgerectifier = sin(bridgerectifier);
				if (side > 0.0) side = bridgerectifier;
				else side = -bridgerectifier;
				count = count - 1.0;
			}
			//we have now accounted for any really high density settings.
			bridgerectifier = fabs(side)*1.57079633;
			if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
			//max value for sine function
			bridgerectifier = sin(bridgerectifier);
			if (side > 0) side = (side*(1-count))+(bridgerectifier*count);
			else side = (side*(1-count))-(bridgerectifier*count);
			//blend according to density control
			//done first density. Next, sustain-reducer
			bridgerectifier = fabs(side)*1.57079633;
			if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
			bridgerectifier = (1-cos(bridgerectifier))*3.141592653589793;
			if (side > 0) side = (side*(1-sustain))+(bridgerectifier*sustain);
			else side = (side*(1-sustain))-(bridgerectifier*sustain);
			//done with High Impact code
			
			//now, Highpass code
			offset = 0.666666666666666 + ((1-fabs(side))*tight);
			if (offset < 0) offset = 0;
			if (offset > 1) offset = 1;
			if (flip)
			{
				iirSampleA = (iirSampleA * (1 - (offset * iirAmount))) + (side * (offset * iirAmount));
				side = side - iirSampleA;
			}
			else
			{
				iirSampleB = (iirSampleB * (1 - (offset * iirAmount))) + (side * (offset * iirAmount));
				side = side - iirSampleB;
			}
			//done with Highpass code
			
			bridgerectifier = fabs(mid)/1.273239544735162;
			if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
			bridgerectifier = sin(bridgerectifier)*1.273239544735162;
			if (mid > 0) mid = (mid*(1-centersquish))+(bridgerectifier*centersquish);
			else mid = (mid*(1-centersquish))-(bridgerectifier*centersquish);
			//done with the mid saturating section.
			
			inputSampleL = (mid+side)/2.0;
			inputSampleR = (mid-side)/2.0;
			
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
    
	double iirSampleA;
	double iirSampleB;
	long double fpNShapeL;
	long double fpNShapeR;
	bool flip;
	//default stuff

};
MIN_EXTERNAL(stereofx);

