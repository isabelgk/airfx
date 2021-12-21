#include "c74_min.h"

using namespace c74::min;

class tremosquare : public object<tremosquare>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a squarewave tremolo effect that only switches on zero crossings"};
	MIN_TAGS {"tremolo"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "frequency", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.5;
			B = 1.0;
			osc = 0.0;
			polarityL = false;
			muteL = false;	
			polarityR = false;
			muteR = false;	
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

		double overallscale = 1.0;
		overallscale /= 44100.0;
		overallscale *= samplerate();
		
		double increment = pow(A,4) / (50.0*overallscale);
		double wet = B;
		
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpd * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpd * 1.18e-43;
			long double drySampleL = inputSampleL;
			long double drySampleR = inputSampleR;
			
			osc += increment; if (osc > 1.0) osc = 0.0;
			//this is our little oscillator code
			
			if (inputSampleL < 0) {
				if (polarityL == true) muteL = (osc < 0.5);
				polarityL = false;
			} else {
				if (polarityL == false) muteL = (osc < 0.5);
				polarityL = true;
			}
			
			if (inputSampleR < 0) {
				if (polarityR == true) muteR = (osc < 0.5);
				polarityR = false;
			} else {
				if (polarityR == false) muteR = (osc < 0.5);
				polarityR = true;
			}
			
			if (muteL) inputSampleL = 0.0;
			if (muteR) inputSampleR = 0.0;
			
			if (wet !=1.0) {
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
    
	double osc;
	bool polarityL;
	bool muteL;
	bool polarityR;
	bool muteR;
	uint32_t fpd;
	//default stuff

};
MIN_EXTERNAL(tremosquare);

