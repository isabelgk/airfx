#include "c74_min.h"

using namespace c74::min;

class loud : public object<loud>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"distortion and demolition of air molecules, modeled"};
	MIN_TAGS {"audio, effect"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "Boost", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "Output Level", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "Dry/Wet", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.0;
			B = 1.0;
			C = 1.0;
			lastSampleL = 0.0;
			lastSampleR = 0.0;
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
		double boost = pow(A+1.0,5);
		double output = B;
		double wet = C;
		double dry = 1.0-wet;
		long double inputSampleL;
		long double inputSampleR;
		double drySampleL;
		double drySampleR;
		double clamp;
		
	    while (--sampleFrames >= 0)
	    {
			inputSampleL = *in1;
			inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpd * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpd * 1.18e-43;
	
			drySampleL = inputSampleL;
			drySampleR = inputSampleR;
			
			//begin L
			inputSampleL *= boost;
			clamp = inputSampleL - lastSampleL;
			
			if (clamp > 0)
			{
				inputSampleL = -(inputSampleL - 1.0);
				inputSampleL *= 1.2566108;
				if (inputSampleL < 0.0) inputSampleL = 0.0;
				if (inputSampleL > 3.141527) inputSampleL = 3.141527;
				inputSampleL = sin(inputSampleL) * overallscale;
				if (clamp > inputSampleL) clamp = inputSampleL;
			}
			
			if (clamp < 0)
			{
				inputSampleL += 1.0;
				inputSampleL *= 1.2566108;
				if (inputSampleL < 0.0) inputSampleL = 0.0;
				if (inputSampleL > 3.141527) inputSampleL = 3.141527;
				inputSampleL = -sin(inputSampleL) * overallscale;
				if (clamp < inputSampleL) clamp = inputSampleL;
			}
			
			inputSampleL = lastSampleL + clamp;
			lastSampleL = inputSampleL;
			//finished L
			
			//begin R
			inputSampleR *= boost;
			clamp = inputSampleR - lastSampleR;
			
			if (clamp > 0)
			{
				inputSampleR = -(inputSampleR - 1.0);
				inputSampleR *= 1.2566108;
				if (inputSampleR < 0.0) inputSampleR = 0.0;
				if (inputSampleR > 3.141527) inputSampleR = 3.141527;
				inputSampleR = sin(inputSampleR) * overallscale;
				if (clamp > inputSampleR) clamp = inputSampleR;
			}
			
			if (clamp < 0)
			{
				inputSampleR += 1.0;
				inputSampleR *= 1.2566108;
				if (inputSampleR < 0.0) inputSampleR = 0.0;
				if (inputSampleR > 3.141527) inputSampleR = 3.141527;
				inputSampleR = -sin(inputSampleR) * overallscale;
				if (clamp < inputSampleR) clamp = inputSampleR;
			}
			
			inputSampleR = lastSampleR + clamp;
			lastSampleR = inputSampleR;
			//finished R
			
			if (output < 1.0) {
				inputSampleL *= output;
				inputSampleR *= output;
			}
			if (wet < 1.0) {
				inputSampleL = (drySampleL*dry)+(inputSampleL*wet);
				inputSampleR = (drySampleR*dry)+(inputSampleR*wet);
			}
			//nice little output stage template: if we have another scale of floating point
			//number, we really don't want to meaninglessly multiply that by 1.0.
			
			//begin 64 bit stereo floating point dither
			int expon; frexp((double)inputSampleL, &expon);
			fpd ^= fpd << 13; fpd ^= fpd >> 17; fpd ^= fpd << 5;
			inputSampleL += static_cast<int32_t>(fpd) * 1.110223024625156e-44L * pow(2,expon+62);
			frexp((double)inputSampleR, &expon);
			fpd ^= fpd << 13; fpd ^= fpd >> 17; fpd ^= fpd << 5;
			inputSampleR += static_cast<int32_t>(fpd) * 1.110223024625156e-44L * pow(2,expon+62);
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
    
	double lastSampleL;
	double lastSampleR;
		uint32_t fpd;
	//default stuff

};
MIN_EXTERNAL(loud);

