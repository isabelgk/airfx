#include "c74_min.h"

using namespace c74::min;

class distance : public object<distance>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a reverb"};
	MIN_TAGS {"audio, effect, reverb"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "distance", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.0;
			B = 1.0;
			thirdresultL = prevresultL = lastclampL = clampL = changeL = lastL = 0.0;
			thirdresultR = prevresultR = lastclampR = clampR = changeR = lastR = 0.0;
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
		
		double softslew = (pow(A*2.0,3.0)*12.0)+0.6;
		softslew *= overallscale;
		double filtercorrect = softslew / 2.0;
		double thirdfilter = softslew / 3.0;
		double levelcorrect = 1.0 + (softslew / 6.0);
		double postfilter;
		double wet = B;
		double dry = 1.0-wet;
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
	
			inputSampleL *= softslew;
			lastclampL = clampL;
			clampL = inputSampleL - lastL;
			postfilter = changeL = fabs(clampL - lastclampL);
			postfilter += filtercorrect;
			if (changeL > 1.5707963267949) changeL = 1.5707963267949;
			bridgerectifier = (1.0-sin(changeL));
			if (bridgerectifier < 0.0) bridgerectifier = 0.0;
			inputSampleL = lastL + (clampL * bridgerectifier);
			lastL = inputSampleL;
			inputSampleL /= softslew;
			inputSampleL += (thirdresultL * thirdfilter);
			inputSampleL /= (thirdfilter + 1.0);
			inputSampleL += (prevresultL * postfilter);
			inputSampleL /= (postfilter + 1.0);
			//do an IIR like thing to further squish superdistant stuff
			thirdresultL = prevresultL;
			prevresultL = inputSampleL;
			inputSampleL *= levelcorrect;
			
			inputSampleR *= softslew;
			lastclampR = clampR;
			clampR = inputSampleR - lastR;
			postfilter = changeR = fabs(clampR - lastclampR);
			postfilter += filtercorrect;
			if (changeR > 1.5707963267949) changeR = 1.5707963267949;
			bridgerectifier = (1.0-sin(changeR));
			if (bridgerectifier < 0.0) bridgerectifier = 0.0;
			inputSampleR = lastR + (clampR * bridgerectifier);
			lastR = inputSampleR;
			inputSampleR /= softslew;
			inputSampleR += (thirdresultR * thirdfilter);
			inputSampleR /= (thirdfilter + 1.0);
			inputSampleR += (prevresultR * postfilter);
			inputSampleR /= (postfilter + 1.0);
			//do an IIR like thing to further squish superdistant stuff
			thirdresultR = prevresultR;
			prevresultR = inputSampleR;
			inputSampleR *= levelcorrect;
			
			if (wet < 1.0) {
				inputSampleL = (drySampleL * dry)+(inputSampleL*wet);
				inputSampleR = (drySampleR * dry)+(inputSampleR*wet);
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
    
	double lastclampL;
	double clampL;
	double changeL;
	double thirdresultL;
	double prevresultL;
	double lastL;

	double lastclampR;
	double clampR;
	double changeR;
	double thirdresultR;
	double prevresultR;
	double lastR;
	
	long double fpNShapeL;
	long double fpNShapeR;
	//default stuff

};
MIN_EXTERNAL(distance);

