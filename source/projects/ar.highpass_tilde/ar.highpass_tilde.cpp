#include "c74_min.h"

using namespace c74::min;

class highpass : public object<highpass>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a time warp, for retro midrangey sounds"};
	MIN_TAGS {""};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "highpass", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "tightness", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			iirSampleAL = 0.0;
			iirSampleBL = 0.0;
			iirSampleAR = 0.0;
			iirSampleBR = 0.0;
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
		long sampleFrames = _input.frame_count();

		double overallscale = 1.0;
		overallscale /= 44100.0;
		overallscale *= samplerate();
		double iirAmount = pow(A,3)/overallscale;
		double tight = (B*2.0)-1.0;
		double wet = C;
		double dry = 1.0 - wet;
		double offset;
		double inputSampleL;
		double inputSampleR;
		double outputSampleL;
		double outputSampleR;
		
		iirAmount += (iirAmount * tight * tight);
		if (tight > 0) tight /= 1.5;
		else tight /= 3.0;
		//we are setting it up so that to either extreme we can get an audible sound,
		//but sort of scaled so small adjustments don't shift the cutoff frequency yet.
		if (iirAmount <= 0.0) iirAmount = 0.0;
		if (iirAmount > 1.0) iirAmount = 1.0;
		//handle the change in cutoff frequency
	    
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
			outputSampleL = inputSampleL;
			outputSampleR = inputSampleR;
			
			if (tight > 0) offset = (1 - tight) + (fabs(inputSampleL)*tight);
			else offset = (1 + tight) + ((1-fabs(inputSampleL))*tight);
			if (offset < 0) offset = 0;
			if (offset > 1) offset = 1;
			if (fpFlip)
			{
				iirSampleAL = (iirSampleAL * (1 - (offset * iirAmount))) + (inputSampleL * (offset * iirAmount));
				outputSampleL = outputSampleL - iirSampleAL;
			}
			else
			{
				iirSampleBL = (iirSampleBL * (1 - (offset * iirAmount))) + (inputSampleL * (offset * iirAmount));
				outputSampleL = outputSampleL - iirSampleBL;
			}
			
			
			if (tight > 0) offset = (1 - tight) + (fabs(inputSampleR)*tight);
			else offset = (1 + tight) + ((1-fabs(inputSampleR))*tight);
			if (offset < 0) offset = 0;
			if (offset > 1) offset = 1;
			if (fpFlip)
			{
				iirSampleAR = (iirSampleAR * (1 - (offset * iirAmount))) + (inputSampleR * (offset * iirAmount));
				outputSampleR = outputSampleR - iirSampleAR;
			}
			else
			{
				iirSampleBR = (iirSampleBR * (1 - (offset * iirAmount))) + (inputSampleR * (offset * iirAmount));
				outputSampleR = outputSampleR - iirSampleBR;
			}
			fpFlip = !fpFlip;
			
			
			
			if (wet < 1.0) outputSampleL = (outputSampleL * wet) + (inputSampleL * dry);
			if (wet < 1.0) outputSampleR = (outputSampleR * wet) + (inputSampleR * dry);
			
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
			
			*out1 = outputSampleL;
			*out2 = outputSampleR;
			
			*in1++;
			*in2++;
			*out1++;
			*out2++;
		}
	}
private:
	double iirSampleAL;
	double iirSampleBL;
	double iirSampleAR;
	double iirSampleBR;
	bool fpFlip;
	long double fpNShapeL;
	long double fpNShapeR;
	//default stuff

};
MIN_EXTERNAL(highpass);

