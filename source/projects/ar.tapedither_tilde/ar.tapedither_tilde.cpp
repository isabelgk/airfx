#include "c74_min.h"

using namespace c74::min;

class tapedither : public object<tapedither>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"TPDF dither with noise like reel-to-reel tape"};
	MIN_TAGS {"tape"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "quant", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "derez", 0.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			fpd = 17;
			previousDither1L = 0.0;
			previousDither2L = 0.0;
			previousDither3L = 0.0;
			previousDither4L = 0.0;
			previousDither1R = 0.0;
			previousDither2R = 0.0;
			previousDither3R = 0.0;
			previousDither4R = 0.0;
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

		double currentDitherL;
		double currentDitherR;
		int processing = (uint32_t)( A * 1.999 );
		bool highres = false;
		if (processing == 1) highres = true;
		float scaleFactor;
		if (highres) scaleFactor = 8388608.0;
		else scaleFactor = 32768.0;
		float derez = B;
		if (derez > 0.0) scaleFactor *= pow(1.0-derez,6);
		if (scaleFactor < 0.0001) scaleFactor = 0.0001;
		float outScale = scaleFactor;
		if (outScale < 8.0) outScale = 8.0;
	    
		
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpd * 1.18e-43;
			fpd ^= fpd << 13; fpd ^= fpd >> 17; fpd ^= fpd << 5;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpd * 1.18e-43;
			fpd ^= fpd << 13; fpd ^= fpd >> 17; fpd ^= fpd << 5;
			
			inputSampleL *= scaleFactor;
			inputSampleR *= scaleFactor;
			//0-1 is now one bit, now we dither
			
			currentDitherL = (rand()/(double)RAND_MAX);
			currentDitherR = (rand()/(double)RAND_MAX);
			
			inputSampleL += currentDitherL;
			inputSampleR += currentDitherR;
			inputSampleL -= previousDither4L;
			inputSampleR -= previousDither4R;
			
			inputSampleL = floor(inputSampleL);
			inputSampleR = floor(inputSampleR);
			
			previousDither4L = previousDither3L;
			previousDither3L = previousDither2L;
			previousDither2L = previousDither1L;
			previousDither1L = currentDitherL;
			
			previousDither4R = previousDither3R;
			previousDither3R = previousDither2R;
			previousDither2R = previousDither1R;
			previousDither1R = currentDitherR;
			
			inputSampleL /= outScale;
			inputSampleR /= outScale;
			
			*out1 = inputSampleL;
			*out2 = inputSampleR;
			
			*in1++;
			*in2++;
			*out1++;
			*out2++;
		}
	}
private:
    
	double previousDither1L;
	double previousDither2L;
	double previousDither3L;
	double previousDither4L;
	double previousDither1R;
	double previousDither2R;
	double previousDither3R;
	double previousDither4R;
	uint32_t fpd;
	//default stuff
	
};
MIN_EXTERNAL(tapedither);

