#include "c74_min.h"

using namespace c74::min;

class avermatrix : public object<avermatrix>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"turns averaging into a full-featured EQ"};
	MIN_TAGS {"filter"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "average", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "depth", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.0;
			B = 0.0;
			C = 1.0;
			for(int x = 0; x < 11; x++) {
				f[x] = 0.0;
				for (int y = 0; y < 11; y++) {
					bL[x][y] = 0.0; bR[x][y] = 0.0;
				}
			}
		
			fpd = 17;
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

		
		double overalltaps = (A * 9.0)+1.0;
		double taps = overalltaps;
		//this is our averaging, which is not integer but continuous
		
		double overallpoles = (B * 9.0)+1.0;
		//this is the poles of the filter, also not integer but continuous
		int yLimit = floor(overallpoles)+1;
		double yPartial = overallpoles - floor(overallpoles);
		//now we can do a for loop, and also apply the final pole continuously
		
		double wet = (C * 2.0)-1.0;
		double dry = (1.0-wet);
		if (dry > 1.0) dry = 1.0;
		
		int xLimit = 1;
		for(int x = 0; x < 11; x++) {
			if (taps > 1.0) {
				f[x] = 1.0;
				taps -= 1.0;
				xLimit++;
			} else {
				f[x] = taps;
				taps = 0.0;
			}
		} //there, now we have a neat little moving average with remainders
		if (xLimit > 9) xLimit = 9;
		
		if (overalltaps < 1.0) overalltaps = 1.0;
		for(int x = 0; x < xLimit; x++) {
			f[x] /= overalltaps;
		} //and now it's neatly scaled, too	
		
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpd * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpd * 1.18e-43;
			long double drySampleL = inputSampleL;
			long double drySampleR = inputSampleR;
	
			long double previousPoleL = 0;		
			long double previousPoleR = 0;		
			for (int y = 0; y < yLimit; y++) {
				for (int x = xLimit; x >= 0; x--) {
					bL[x+1][y] = bL[x][y];
					bR[x+1][y] = bR[x][y];
				}
				bL[0][y] = previousPoleL = inputSampleL;
				bR[0][y] = previousPoleR = inputSampleR;
				inputSampleL = 0.0;
				inputSampleR = 0.0;
				for (int x = 0; x < xLimit; x++) {
					inputSampleL += (bL[x][y] * f[x]);
					inputSampleR += (bR[x][y] * f[x]);
				}
			}
			inputSampleL = (previousPoleL * (1.0-yPartial)) + (inputSampleL * yPartial);
			inputSampleR = (previousPoleR * (1.0-yPartial)) + (inputSampleR * yPartial);
			//in this way we can blend in the final pole
			
			inputSampleL = (inputSampleL * wet) + (drySampleL * dry);
			inputSampleR = (inputSampleR * wet) + (drySampleR * dry);
			//wet can be negative, in which case dry is always full volume and they cancel
			
			//begin 64 bit stereo floating point dither
			int expon; frexp((double)inputSampleL, &expon);
			fpd ^= fpd << 13; fpd ^= fpd >> 17; fpd ^= fpd << 5;
			inputSampleL += ((double(fpd)-uint32_t(0x7fffffff)) * 1.1e-44l * pow(2,expon+62));
			frexp((double)inputSampleR, &expon);
			fpd ^= fpd << 13; fpd ^= fpd >> 17; fpd ^= fpd << 5;
			inputSampleR += ((double(fpd)-uint32_t(0x7fffffff)) * 1.1e-44l * pow(2,expon+62));
			//end 64 bit stereo floating point dither
			
			*out1 = inputSampleL;
			*out2 = inputSampleR;
	
			*in1++;
			*in2++;
			*out1++;
			*out2++;
		}
	}
private:
    
	double bL[11][11];
	double bR[11][11];
	double f[11];		
	uint32_t fpd;
	//default stuff

};
MIN_EXTERNAL(avermatrix);

