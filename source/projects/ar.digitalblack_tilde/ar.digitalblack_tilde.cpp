#include "c74_min.h"

using namespace c74::min;

class digitalblack : public object<digitalblack>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a quick, staccato gate"};
	MIN_TAGS {"audio, effect"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "Thresh", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "Dry/Wet", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.0;
			B = 1.0;
			WasNegativeL = false;
			ZeroCrossL = 0;
			gaterollerL = 0.0;
			WasNegativeR = false;
			ZeroCrossR = 0;
			gaterollerR = 0.0;
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
		
		double threshold = (pow(A,4)/3)+0.00018;
		double release = 0.0064 / overallscale;
		double wet = B;
	    
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpd * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpd * 1.18e-43;
			long double drySampleL = inputSampleL;
			long double drySampleR = inputSampleR;
			
			
			if (inputSampleL > 0) {
				if (WasNegativeL == true) ZeroCrossL = 0;
				WasNegativeL = false;
			} else {
				ZeroCrossL += 1;
				WasNegativeL = true;
			}
			if (inputSampleR > 0) {
				if (WasNegativeR == true) ZeroCrossR = 0;
				WasNegativeR = false;
			} else {
				ZeroCrossR += 1;
				WasNegativeR = true;
			}
			
			if (ZeroCrossL > 6000) ZeroCrossL = 6000;
			if (ZeroCrossR > 6000) ZeroCrossR = 6000;
			
			if (fabs(inputSampleL) > threshold) {
				if (gaterollerL < ZeroCrossL) gaterollerL = ZeroCrossL;
			} else {
				gaterollerL -= release;
			}
			if (fabs(inputSampleR) > threshold) {
				if (gaterollerR < ZeroCrossR) gaterollerR = ZeroCrossR;
			} else {
				gaterollerR -= release;
			}
			
			if (gaterollerL < 0.0) gaterollerL = 0.0;
			if (gaterollerR < 0.0) gaterollerR = 0.0;
			
			double gate = 1.0;
			if (gaterollerL < 1.0) gate = gaterollerL;
			
			long double bridgerectifier = 1-cos(fabs(inputSampleL));
			
			if (inputSampleL > 0) inputSampleL = (inputSampleL*gate)+(bridgerectifier*(1-gate));
			else inputSampleL = (inputSampleL*gate)-(bridgerectifier*(1-gate));
			
			if ((gate == 0.0) && (fabs(inputSampleL*3) < threshold)) inputSampleL = 0.0;
			
			gate = 1.0;
			if (gaterollerR < 1.0) gate = gaterollerR;
			
			bridgerectifier = 1-cos(fabs(inputSampleR));
			
			if (inputSampleR > 0) inputSampleR = (inputSampleR*gate)+(bridgerectifier*(1-gate));
			else inputSampleR = (inputSampleR*gate)-(bridgerectifier*(1-gate));
			
			if ((gate == 0.0) && (fabs(inputSampleR*3) < threshold)) inputSampleR = 0.0;
			
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
    
	bool WasNegativeL;
	int ZeroCrossL;
	double gaterollerL;
	bool WasNegativeR;
	int ZeroCrossR;
	double gaterollerR;
	uint32_t fpd;
	//default stuff

};
MIN_EXTERNAL(digitalblack);

