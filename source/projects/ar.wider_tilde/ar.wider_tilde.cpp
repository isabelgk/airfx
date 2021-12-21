#include "c74_min.h"

using namespace c74::min;

class wider : public object<wider>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"stereo space shaping"};
	MIN_TAGS {""};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "width", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "center", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.5;
			B = 0.5;
			C = 1.0;
			for(int fcount = 0; fcount < 4098; fcount++) {p[fcount] = 0.0;}
			count = 0;
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
		
		long double inputSampleL;
		long double inputSampleR;
		double drySampleL;
		double drySampleR;
		long double mid;
		long double side;
		double out;
		double densityside = (A*2.0)-1.0;
		double densitymid = (B*2.0)-1.0;
		double wet = C;
		double dry = 1.0 - wet;
		wet *= 0.5; //we make mid-side by adding/subtracting both channels into each channel
		//and that's why we gotta divide it by 2: otherwise everything's doubled. So, premultiply it to save an extra 'math'
		double offset = (densityside-densitymid)/2;
		if (offset > 0) offset = sin(offset);
		if (offset < 0) offset = -sin(-offset);
		offset = -(pow(offset,4) * 20 * overallscale);
		int _near = (int)floor(fabs(offset));
		double _farLevel = fabs(offset) - _near;
		int _far = _near + 1;
		double _nearLevel = 1.0 - _farLevel;
		double bridgerectifier;
		//interpolating the sample
	    
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
			//assign working variables		
			mid = inputSampleL + inputSampleR;
			side = inputSampleL - inputSampleR;
			//assign mid and side. Now, High Impact code
			
			if (densityside != 0.0)
			{
				out = fabs(densityside);
				bridgerectifier = fabs(side)*1.57079633;
				if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
				//max value for sine function
				if (densityside > 0) bridgerectifier = sin(bridgerectifier);
				else bridgerectifier = 1-cos(bridgerectifier);
				//produce either boosted or starved version
				if (side > 0) side = (side*(1-out))+(bridgerectifier*out);
				else side = (side*(1-out))-(bridgerectifier*out);
				//blend according to density control
			}
			
			if (densitymid != 0.0)
			{
				out = fabs(densitymid);
				bridgerectifier = fabs(mid)*1.57079633;
				if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
				//max value for sine function
				if (densitymid > 0) bridgerectifier = sin(bridgerectifier);
				else bridgerectifier = 1-cos(bridgerectifier);
				//produce either boosted or starved version
				if (mid > 0) mid = (mid*(1-out))+(bridgerectifier*out);
				else mid = (mid*(1-out))-(bridgerectifier*out);
				//blend according to density control
			}
			
			if (count < 1 || count > 2048) {count = 2048;}
			if (offset > 0)
			{
				p[count+2048] = p[count] = mid;
				mid = p[count+_near]*_nearLevel;
				mid += p[count+_far]*_farLevel;
			}
			
			if (offset < 0)
			{
				p[count+2048] = p[count] = side;
				side = p[count+_near]*_nearLevel;
				side += p[count+_far]*_farLevel;
			}
			count -= 1;
			
			inputSampleL = (drySampleL * dry) + ((mid+side) * wet);
			inputSampleR = (drySampleR * dry) + ((mid-side) * wet);
			
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

	double p[4099];
	int count;

};
MIN_EXTERNAL(wider);

