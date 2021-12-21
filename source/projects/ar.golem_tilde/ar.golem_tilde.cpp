#include "c74_min.h"

using namespace c74::min;

class golem : public object<golem>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"blend a stereo track of two mics on an amp"};
	MIN_TAGS {""};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "balance", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "offset", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "phase", 0.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.5;
			B = 0.5;
			C = 0.0;
			for(count = 0; count < 4098; count++) {p[count] = 0.0;}
			count = 0;
			fpNShapeL = 0.0;
			fpNShapeR = 0.0;
			flip = true;
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

		int phase = (int)((C * 5.999)+1);
		double balance = ((A*2.0)-1.0) / 2.0;
		double gainL = 0.5 - balance;
		double gainR = 0.5 + balance;
		double range = 30.0;
		if (phase == 3) range = 700.0;
		if (phase == 4) range = 700.0;
		double offset = pow((B*2.0)-1.0,5) * range;
		if (phase > 4) offset = 0.0;
		if (phase > 5)
		{
			gainL = 0.5;
			gainR = 0.5;
		}
		int _near = (int)floor(fabs(offset));
		double farLevel = fabs(offset) - _near;
		int _far = _near + 1;
		double nearLevel = 1.0 - farLevel;
		
		long double inputSampleL;
		long double inputSampleR;
		
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
			
			if (phase == 2) inputSampleL = -inputSampleL;
			if (phase == 4) inputSampleL = -inputSampleL;
			
			inputSampleL *= gainL;
			inputSampleR *= gainR;
			
			if (count < 1 || count > 2048) {count = 2048;}
			
			if (offset > 0)
			{
				p[count+2048] = p[count] = inputSampleL;
				inputSampleL = p[count+_near]*nearLevel;
				inputSampleL += p[count+_far]*farLevel;
				
				//consider adding third sample just to bring out superhighs subtly, like old interpolation hacks
				//or third and fifth samples, ditto
				
			}
			
			if (offset < 0)
			{
				p[count+2048] = p[count] = inputSampleR;
				inputSampleR = p[count+_near]*nearLevel;
				inputSampleR += p[count+_far]*farLevel;
			}
			
			count -= 1;
			
			inputSampleL = inputSampleL + inputSampleR;
			inputSampleR = inputSampleL;
			//the output is totally mono
			
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
	bool flip;
	//default stuff
	double p[4099];
	int count;

};
MIN_EXTERNAL(golem);

