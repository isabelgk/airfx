#include "c74_min.h"

using namespace c74::min;

class remap : public object<remap>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"puts the guts back into overloudenated audio"};
	MIN_TAGS {""};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "remap", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "output", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.5;
			B = 1.0;
			C = 1.0;
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
		long sampleFrames = _input.frame_count();

		double drive = A * 0.5;
		double gain = (drive+0.2)*8;
		double out = B;
		double wet = C;
		
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpd * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpd * 1.18e-43;
			long double drySampleL = inputSampleL;
			long double drySampleR = inputSampleR;
			
			long double gaintrimL = fabs(inputSampleL);
			long double gaintrimR = fabs(inputSampleR);
			
			long double bridgerectifierL = gaintrimL*gain;
			long double bridgerectifierR = gaintrimR*gain;
			
			if (gaintrimL > 1.0) gaintrimL = 1.0;
			else gaintrimL *= gaintrimL;
			
			if (gaintrimR > 1.0) gaintrimR = 1.0;
			else gaintrimR *= gaintrimR;
			
			if (inputSampleL > 1.57079633) bridgerectifierL = 1.0-(1.0-sin(bridgerectifierL));
			else bridgerectifierL = sin(bridgerectifierL);
			
			if (inputSampleR > 1.57079633) bridgerectifierR = 1.0-(1.0-sin(bridgerectifierR));
			else bridgerectifierR = sin(bridgerectifierR);
			
			if (inputSampleL > 0) inputSampleL -= (bridgerectifierL*gaintrimL*drive);
			else inputSampleL += (bridgerectifierL*gaintrimL*drive);
			
			if (inputSampleR > 0) inputSampleR -= (bridgerectifierR*gaintrimR*drive);
			else inputSampleR += (bridgerectifierR*gaintrimR*drive);
			
			if (out < 1.0) {
				inputSampleL *= out;
				inputSampleR *= out;
			}
			
			if (wet < 1.0) {
				inputSampleL = (inputSampleL * wet) + (drySampleL * (1.0-wet));
				inputSampleR = (inputSampleR * wet) + (drySampleR * (1.0-wet));
			}
			
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
    
	uint32_t fpd;
	//default stuff

};
MIN_EXTERNAL(remap);

