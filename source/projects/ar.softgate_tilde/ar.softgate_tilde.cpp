#include "c74_min.h"

using namespace c74::min;

class softgate : public object<softgate>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a gate that can mute hiss and smooth sample tails"};
	MIN_TAGS {"audio, effect"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "Thresh", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "Darken", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "Silence", 0.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.5;
			B = 0.5;
			C = 0.0;
			storedL[0] = storedL[1] = 0.0;
			diffL = 0.0;
			storedR[0] = storedR[1] = 0.0;
			diffR = 0.0;
			gate = 1.1;
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
		
		double threshold = pow(A,6);
		double recovery = pow((B*0.5),6);
		recovery /= overallscale;
		double baseline = pow(C,6);
		double invrec = 1.0 - recovery;
		
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpd * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpd * 1.18e-43;
	
			storedL[1] = storedL[0];
			storedL[0] = inputSampleL;
			diffL = storedL[0] - storedL[1];
			
			storedR[1] = storedR[0];
			storedR[0] = inputSampleR;
			diffR = storedR[0] - storedR[1];
			
			if (gate > 0) {gate = ((gate-baseline) * invrec) + baseline;}
			
			if ((fabs(diffR) > threshold) || (fabs(diffL) > threshold)) {gate = 1.1;}
			else {gate = (gate * invrec); if (threshold > 0) {gate += ((fabs(inputSampleL)/threshold) * recovery);gate += ((fabs(inputSampleR)/threshold) * recovery);}}
			
			if (gate < 0) gate = 0;
			
			if (gate < 1.0)
			{
				storedL[0] = storedL[1] + (diffL * gate);		
				storedR[0] = storedR[1] + (diffR * gate);
			}
			
			if (gate < 1) {
				inputSampleL = (inputSampleL * gate) + (storedL[0] * (1.0-gate));
				inputSampleR = (inputSampleR * gate) + (storedR[0] * (1.0-gate));
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
	double storedL[2];
	double diffL;
	double storedR[2];
	double diffR;
	double gate;

};
MIN_EXTERNAL(softgate);

