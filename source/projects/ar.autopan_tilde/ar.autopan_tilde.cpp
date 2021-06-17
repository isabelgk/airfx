#include "c74_min.h"

using namespace c74::min;

class autopan : public object<autopan>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"for getting some organic stereo movement into your mix"};
	MIN_TAGS {"audio, effect"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "Rate", 0.1, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "Phase", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "Wide", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "Dry/Wet", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.1;
			B = 0.5;
			C = 0.0;
			D = 1.0;
			rate = 3.0;
			oldfpd = 429496.7295;
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
		double overallscale = 1.0;
		overallscale /= 44100.0;
		overallscale *= samplerate();

		long sampleFrames = _input.frame_count();
		
		double drift = (pow(A,4)*0.01)/overallscale;
		double offset = 3.141592653589793 + (B*6.283185307179586);
		double panlaw = 1.0-pow(C,2);
		double wet = D;
	
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpdL * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpdR * 1.18e-43;
			long double drySampleL = inputSampleL;
			long double drySampleR = inputSampleR;
			
			rate += (oldfpd*drift);
			if (rate > 6.283185307179586) {
				rate = 0.0;
				oldfpd = 0.4294967295+(fpdL*0.0000000000618);
			} else if (rate < 0.0) {
				rate = 6.283185307179586;
				oldfpd = 0.4294967295+(fpdL*0.0000000000618);
			}
			
			inputSampleL *= (sin(rate)+1.0);
			inputSampleR *= (sin(rate+offset)+1.0);
			
			long double mid = (inputSampleL + inputSampleR)*panlaw;
			long double side = inputSampleL - inputSampleR;
			//assign mid and side.Between these sections, you can do mid/side processing
			
			inputSampleL = (mid+side)/4.0;
			inputSampleR = (mid-side)/4.0;
			//unassign mid and side, and compensate for the sin()+1 volume boost
			
			if (wet != 1.0) {
				inputSampleL = (inputSampleL * wet) + (drySampleL * (1.0-wet));
				inputSampleR = (inputSampleR * wet) + (drySampleR * (1.0-wet));
			}
			//Dry/Wet control, defaults to the last slider
			
			//begin 64 bit stereo floating point dither
			int expon; frexp((double)inputSampleL, &expon);
			fpdL ^= fpdL << 13; fpdL ^= fpdL >> 17; fpdL ^= fpdL << 5;
			inputSampleL += ((double(fpdL)-uint32_t(0x7fffffff)) * 1.1e-44l * pow(2,expon+62));
			frexp((double)inputSampleR, &expon);
			fpdR ^= fpdR << 13; fpdR ^= fpdR >> 17; fpdR ^= fpdR << 5;
			inputSampleR += ((double(fpdR)-uint32_t(0x7fffffff)) * 1.1e-44l * pow(2,expon+62));
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
    
	double rate, oldfpd;
	
	uint32_t fpdL;
	uint32_t fpdR;
	//default stuff

};
MIN_EXTERNAL(autopan);

