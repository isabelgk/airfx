#include "c74_min.h"

using namespace c74::min;

class surgetide : public object<surgetide>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"surge and flow dynamics"};
	MIN_TAGS {""};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "surgenode", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "surgerate", 0.3, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.5;
			B = 0.3;
			C = 1.0;
			fpNShapeL = 0.0;
			fpNShapeR = 0.0;
			flip = true;
			chaseA = 0.0;
			chaseB = 0.0;
			chaseC = 0.0;	
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
		long double drySampleL;
		long double drySampleR;
		
		double intensity = A;
		double attack = ((B+0.1)*0.0005)/overallscale;
		double decay = ((B+0.001)*0.00005)/overallscale;
		double wet = C;
		double dry = 1.0 - wet;
		double inputSense;
		
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
	
			inputSampleL *= 8.0;
			inputSampleR *= 8.0;
			inputSampleL *= intensity;
			inputSampleR *= intensity;
			
			inputSense = fabs(inputSampleL);
			if (fabs(inputSampleR) > inputSense)
				inputSense = fabs(inputSampleR);
			
			if (chaseC < inputSense) chaseA += attack;
			if (chaseC > inputSense) chaseA -= decay;
			
			if (chaseA > decay) chaseA = decay;
			if (chaseA < -attack) chaseA = -attack;
			
			chaseB += (chaseA/overallscale);
			
			if (chaseB > decay) chaseB = decay;
			if (chaseB < -attack) chaseB = -attack;
			
			chaseC += (chaseB/overallscale);
			if (chaseC > 1.0) chaseC = 1.0;
			if (chaseC < 0.0) chaseC = 0.0;
			
			inputSampleL *= chaseC;
			inputSampleL = drySampleL - (inputSampleL * intensity);
			inputSampleL = (drySampleL * dry) + (inputSampleL * wet);
			
			inputSampleR *= chaseC;
			inputSampleR = drySampleR - (inputSampleR * intensity);
			inputSampleR = (drySampleR * dry) + (inputSampleR * wet);		
	
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
	long double chaseA;
	long double chaseB;
	long double chaseC;
	
};
MIN_EXTERNAL(surgetide);

