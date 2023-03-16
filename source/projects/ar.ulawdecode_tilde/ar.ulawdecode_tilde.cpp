#include "c74_min.h"

using namespace c74::min;

class ulawdecode : public object<ulawdecode>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"uLawDecode is a Console-like encode/decode pair, but much more extreme."};
	MIN_TAGS {"compansion"};
	MIN_AUTHOR {"Christopher Herb"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "gain", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			fpdL = 1.0; while (fpdL < 16386) fpdL = rand()*UINT32_MAX;
			fpdR = 1.0; while (fpdR < 16386) fpdR = rand()*UINT32_MAX;
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
		
		double gain = A;
		double wet = B;
		//removed extra dry variable

		while (--sampleFrames >= 0)
		{
			double inputSampleL = *in1;
			double inputSampleR = *in2;

			if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
			if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;
			double drySampleL = inputSampleL;
			double drySampleR = inputSampleR;
			
			if (gain != 1.0) {
				inputSampleL *= gain;
				inputSampleR *= gain;
			}
			
			if (inputSampleL > 1.0) inputSampleL = 1.0;
			if (inputSampleL < -1.0) inputSampleL = -1.0;
			
			if (inputSampleR > 1.0) inputSampleR = 1.0;
			if (inputSampleR < -1.0) inputSampleR = -1.0;
			
			if (inputSampleL > 0) inputSampleL = (pow(256,fabs(inputSampleL))-1.0) / 255;
			if (inputSampleL < 0) inputSampleL = -(pow(256,fabs(inputSampleL))-1.0) / 255;
			
			if (inputSampleR > 0) inputSampleR = (pow(256,fabs(inputSampleR))-1.0) / 255;
			if (inputSampleR < 0) inputSampleR = -(pow(256,fabs(inputSampleR))-1.0) / 255;
			
			if (wet != 1.0) {
				inputSampleL = (inputSampleL * wet) + (drySampleL * (1.0-wet));
				inputSampleR = (inputSampleR * wet) + (drySampleR * (1.0-wet));
			}
			
			//begin 64 bit stereo floating point dither
			//int expon; frexp((double)inputSampleL, &expon);
			fpdL ^= fpdL << 13; fpdL ^= fpdL >> 17; fpdL ^= fpdL << 5;
			//inputSampleL += ((double(fpdL)-uint32_t(0x7fffffff)) * 1.1e-44l * pow(2,expon+62));
			//frexp((double)inputSampleR, &expon);
			fpdR ^= fpdR << 13; fpdR ^= fpdR >> 17; fpdR ^= fpdR << 5;
			//inputSampleR += ((double(fpdR)-uint32_t(0x7fffffff)) * 1.1e-44l * pow(2,expon+62));
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
	uint32_t fpdL;
	uint32_t fpdR;
	//default stuff
};

MIN_EXTERNAL(ulawdecode);
