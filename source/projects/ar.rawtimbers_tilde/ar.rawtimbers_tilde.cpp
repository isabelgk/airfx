#include "c74_min.h"

using namespace c74::min;

class rawtimbers : public object<rawtimbers>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"add brightness with quantization"};
	MIN_TAGS {"audio, effect"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "Quant", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "DeRez", 0.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 1.0;
			B = 0.0;
			fpd = 17;
			lastSampleL = 0.0;
			lastSample2L = 0.0;
			lastSampleR = 0.0;
			lastSample2R = 0.0;
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
			double outputSampleL;
			double outputSampleR;
			
			inputSampleL += 0.381966011250105;
			inputSampleR += 0.381966011250105;
			
			if ((lastSampleL+lastSampleL) >= (inputSampleL+lastSample2L)) outputSampleL = floor(lastSampleL);
			else outputSampleL = floor(lastSampleL+1.0); //round down or up based on whether it softens treble angles
			
			if ((lastSampleR+lastSampleR) >= (inputSampleR+lastSample2R)) outputSampleR = floor(lastSampleR);
			else outputSampleR = floor(lastSampleR+1.0); //round down or up based on whether it softens treble angles
			
			lastSample2L = lastSampleL;
			lastSampleL = inputSampleL; //we retain three samples in a row
			
			lastSample2R = lastSampleR;
			lastSampleR = inputSampleR; //we retain three samples in a row
			
			*out1 = outputSampleL / outScale;
			*out2 = outputSampleR / outScale;
			
			*in1++;
			*in2++;
			*out1++;
			*out2++;
		}
	}
private:
    
	double lastSampleL;
	double lastSample2L;
	double lastSampleR;
	double lastSample2R;
	uint32_t fpd;
	//default stuff
	
};
MIN_EXTERNAL(rawtimbers);

