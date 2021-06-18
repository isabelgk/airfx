#include "c74_min.h"

using namespace c74::min;

class spiral2 : public object<spiral2>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"more smooth distortion"};
	MIN_TAGS {"audio, effect"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "Input", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "Highpass", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "Presence", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "Output", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> E {this, "Dry/Wet", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.5;
			B = 0.0;
			C = 0.5;
			D = 1.0;
			E = 1.0;
			iirSampleAL = 0.0;
			iirSampleBL = 0.0;
			prevSampleL = 0.0;
			fpd = 17;
		
			iirSampleAR = 0.0;
			iirSampleBR = 0.0;
			prevSampleR = 0.0;
			flip = true;
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
		
		double gain = pow(A*2.0,2.0);
		double iirAmount = pow(B,3.0)/overallscale;
		double presence = C;
		double output = D;
		double wet = E;
		
		
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
	
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpd * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpd * 1.18e-43;
	
			long double drySampleL = inputSampleL;
			long double drySampleR = inputSampleR;
			
			if (gain != 1.0) {
				inputSampleL *= gain;
				inputSampleR *= gain;
				prevSampleL *= gain;
				prevSampleR *= gain;
			}
			
			if (flip)
			{
				iirSampleAL = (iirSampleAL * (1 - iirAmount)) + (inputSampleL * iirAmount);
				iirSampleAR = (iirSampleAR * (1 - iirAmount)) + (inputSampleR * iirAmount);
				inputSampleL -= iirSampleAL;
				inputSampleR -= iirSampleAR;
			}
			else
			{
				iirSampleBL = (iirSampleBL * (1 - iirAmount)) + (inputSampleL * iirAmount);
				iirSampleBR = (iirSampleBR * (1 - iirAmount)) + (inputSampleR * iirAmount);
				inputSampleL -= iirSampleBL;
				inputSampleR -= iirSampleBR;
			}
			//highpass section
			
			long double presenceSampleL = sin(inputSampleL * fabs(prevSampleL)) / ((prevSampleL == 0.0) ?1:fabs(prevSampleL));
			long double presenceSampleR = sin(inputSampleR * fabs(prevSampleR)) / ((prevSampleR == 0.0) ?1:fabs(prevSampleR));
			//change from first Spiral: delay of one sample on the scaling factor.
			inputSampleL = sin(inputSampleL * fabs(inputSampleL)) / ((fabs(inputSampleL) == 0.0) ?1:fabs(inputSampleL));
			inputSampleR = sin(inputSampleR * fabs(inputSampleR)) / ((fabs(inputSampleR) == 0.0) ?1:fabs(inputSampleR));
			
			if (output < 1.0) {
				inputSampleL *= output;
				inputSampleR *= output;
				presenceSampleL *= output;
				presenceSampleR *= output;
			}
			if (presence > 0.0) {
				inputSampleL = (inputSampleL * (1.0-presence)) + (presenceSampleL * presence);
				inputSampleR = (inputSampleR * (1.0-presence)) + (presenceSampleR * presence);
			}
			if (wet < 1.0) {
				inputSampleL = (drySampleL * (1.0-wet)) + (inputSampleL * wet);
				inputSampleR = (drySampleR * (1.0-wet)) + (inputSampleR * wet);
			}
			//nice little output stage template: if we have another scale of floating point
			//number, we really don't want to meaninglessly multiply that by 1.0.
			
			prevSampleL = drySampleL;
			prevSampleR = drySampleR;
			flip = !flip;
			
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
    
	long double iirSampleAL;
	long double iirSampleBL;
	long double prevSampleL;
		uint32_t fpd;

	long double iirSampleAR;
	long double iirSampleBR;
	long double prevSampleR;
	bool flip;
	//default stuff

};
MIN_EXTERNAL(spiral2);

