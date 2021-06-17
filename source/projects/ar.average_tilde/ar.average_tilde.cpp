#include "c74_min.h"

using namespace c74::min;

class average : public object<average>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"distinctive sort of lowpass filter"};
	MIN_TAGS {"audio, effect"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1"};
	outlet<> out2 {this, "(signal) Output2"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "Average", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "Dry/Wet", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.0;
			B = 1.0;
			
			for(int count = 0; count < 11; count++) {bL[count] = 0.0; bR[count] = 0.0; f[count] = 0.0;}
			
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

		double correctionSample;
		double accumulatorSampleL;
		double accumulatorSampleR;
		double drySampleL;
		double drySampleR;
		double inputSampleL;
		double inputSampleR;
		
		double overallscale = (A * 9.0)+1.0;
		double wet = B;
		double dry = 1.0 - wet;
		double gain = overallscale;
		
		if (gain > 1.0) {f[0] = 1.0; gain -= 1.0;} else {f[0] = gain; gain = 0.0;}
		if (gain > 1.0) {f[1] = 1.0; gain -= 1.0;} else {f[1] = gain; gain = 0.0;}
		if (gain > 1.0) {f[2] = 1.0; gain -= 1.0;} else {f[2] = gain; gain = 0.0;}
		if (gain > 1.0) {f[3] = 1.0; gain -= 1.0;} else {f[3] = gain; gain = 0.0;}
		if (gain > 1.0) {f[4] = 1.0; gain -= 1.0;} else {f[4] = gain; gain = 0.0;}
		if (gain > 1.0) {f[5] = 1.0; gain -= 1.0;} else {f[5] = gain; gain = 0.0;}
		if (gain > 1.0) {f[6] = 1.0; gain -= 1.0;} else {f[6] = gain; gain = 0.0;}
		if (gain > 1.0) {f[7] = 1.0; gain -= 1.0;} else {f[7] = gain; gain = 0.0;}
		if (gain > 1.0) {f[8] = 1.0; gain -= 1.0;} else {f[8] = gain; gain = 0.0;}
		if (gain > 1.0) {f[9] = 1.0; gain -= 1.0;} else {f[9] = gain; gain = 0.0;}
		//there, now we have a neat little moving average with remainders
		
		if (overallscale < 1.0) overallscale = 1.0;
		f[0] /= overallscale;
		f[1] /= overallscale;
		f[2] /= overallscale;
		f[3] /= overallscale;
		f[4] /= overallscale;
		f[5] /= overallscale;
		f[6] /= overallscale;
		f[7] /= overallscale;
		f[8] /= overallscale;
		f[9] /= overallscale;
		//and now it's neatly scaled, too
		
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
			
			bL[9] = bL[8]; bL[8] = bL[7]; bL[7] = bL[6]; bL[6] = bL[5];
			bL[5] = bL[4]; bL[4] = bL[3]; bL[3] = bL[2]; bL[2] = bL[1];
			bL[1] = bL[0]; bL[0] = accumulatorSampleL = inputSampleL;
			
			bR[9] = bR[8]; bR[8] = bR[7]; bR[7] = bR[6]; bR[6] = bR[5];
			bR[5] = bR[4]; bR[4] = bR[3]; bR[3] = bR[2]; bR[2] = bR[1];
			bR[1] = bR[0]; bR[0] = accumulatorSampleR = inputSampleR;
			//primitive way of doing this: for larger batches of samples, you might
			//try using a circular buffer like in a reverb. If you add the new sample
			//and subtract the one on the end you can keep a running tally of the samples
			//between. Beware of tiny floating-point math errors eventually screwing up
			//your system, though!
			
			accumulatorSampleL *= f[0];
			accumulatorSampleL += (bL[1] * f[1]);
			accumulatorSampleL += (bL[2] * f[2]);
			accumulatorSampleL += (bL[3] * f[3]);
			accumulatorSampleL += (bL[4] * f[4]);
			accumulatorSampleL += (bL[5] * f[5]);
			accumulatorSampleL += (bL[6] * f[6]);
			accumulatorSampleL += (bL[7] * f[7]);
			accumulatorSampleL += (bL[8] * f[8]);
			accumulatorSampleL += (bL[9] * f[9]);
			
			accumulatorSampleR *= f[0];
			accumulatorSampleR += (bR[1] * f[1]);
			accumulatorSampleR += (bR[2] * f[2]);
			accumulatorSampleR += (bR[3] * f[3]);
			accumulatorSampleR += (bR[4] * f[4]);
			accumulatorSampleR += (bR[5] * f[5]);
			accumulatorSampleR += (bR[6] * f[6]);
			accumulatorSampleR += (bR[7] * f[7]);
			accumulatorSampleR += (bR[8] * f[8]);
			accumulatorSampleR += (bR[9] * f[9]);
			//we are doing our repetitive calculations on a separate value
			
			correctionSample = inputSampleL - accumulatorSampleL;
			//we're gonna apply the total effect of all these calculations as a single subtract
			inputSampleL -= correctionSample;
			
			correctionSample = inputSampleR - accumulatorSampleR;
			inputSampleR -= correctionSample;
			//our one math operation on the input data coming in
			
			if (wet < 1.0) {
				inputSampleL = (inputSampleL * wet) + (drySampleL * dry);
				inputSampleR = (inputSampleR * wet) + (drySampleR * dry);
			}
			//dry/wet control only applies if you're using it. We don't do a multiply by 1.0
			//if it 'won't change anything' but our sample might be at a very different scaling
			//in the floating point system.
			
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
    
	double bL[11];
	double f[11];		
	double bR[11];
	
	long double fpNShapeL;
	long double fpNShapeR;
	//default stuff

};
MIN_EXTERNAL(average);

