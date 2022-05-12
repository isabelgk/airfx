#include "c74_min.h"

using namespace c74::min;

class coils2 : public object<coils2>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a transformer overdrive emulator"};
	MIN_TAGS {"drive, saturation"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "saturation", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "cheapness", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			for (int x = 0; x < 15; x++) {biquadA[x] = 0.0; biquadB[x] = 0.0;}
			hysteresisL = hysteresisR = 0.0;
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
		
		double distScaling = pow(1.0-A,2);
		if (distScaling < 0.0001) distScaling = 0.0001;
		biquadA[0] = 600.0/samplerate();
		biquadA[1] = 0.01+(pow(B,2)*0.5);
		long double iirAmount = biquadA[1]/overallscale;
		double K = tan(M_PI * biquadA[0]);
		double norm = 1.0 / (1.0 + K / biquadA[1] + K * K);
		biquadA[2] = K / biquadA[1] * norm;
		biquadA[4] = -biquadA[2];
		biquadA[5] = 2.0 * (K * K - 1.0) * norm;
		biquadA[6] = (1.0 - K / biquadA[1] + K * K) * norm;
		biquadB[0] = (21890.0-(biquadA[1]*890.0))/samplerate();
		biquadB[1] = 0.89;
		K = tan(M_PI * biquadB[0]);
		norm = 1.0 / (1.0 + K / biquadB[1] + K * K);
		biquadB[2] = K * K * norm;
		biquadB[3] = 2.0 * biquadB[2];
		biquadB[4] = biquadB[2];
		biquadB[5] = 2.0 * (K * K - 1.0) * norm;
		biquadB[6] = (1.0 - K / biquadB[1] + K * K) * norm;
		double wet = C;
		
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpdL * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpdR * 1.18e-43;
			long double drySampleL = inputSampleL;
			long double drySampleR = inputSampleR;
			
			if (biquadA[0] < 0.49999) {
				long double tempSample = (inputSampleL * biquadA[2]) + biquadA[7];
				biquadA[7] = -(tempSample * biquadA[5]) + biquadA[8];
				biquadA[8] = (inputSampleL * biquadA[4]) - (tempSample * biquadA[6]);
				inputSampleL = tempSample;			
				tempSample = (inputSampleR * biquadA[2]) + biquadA[9];
				biquadA[9] = -(tempSample * biquadA[5]) + biquadA[10];
				biquadA[10] = (inputSampleR * biquadA[4]) - (tempSample * biquadA[6]);
				inputSampleR = tempSample; //create bandpass of clean tone
			}
			long double diffSampleL = (drySampleL-inputSampleL)/distScaling;
			long double diffSampleR = (drySampleR-inputSampleR)/distScaling; //mids notched out		
			if (biquadB[0] < 0.49999) {
				long double tempSample = (diffSampleL * biquadB[2]) + biquadB[7];
				biquadB[7] = (diffSampleL * biquadB[3]) - (tempSample * biquadB[5]) + biquadB[8];
				biquadB[8] = (diffSampleL * biquadB[4]) - (tempSample * biquadB[6]);
				diffSampleL = tempSample;
				tempSample = (diffSampleR * biquadB[2]) + biquadB[9];
				biquadB[9] = (diffSampleR * biquadB[3]) - (tempSample * biquadB[5]) + biquadB[10];
				biquadB[10] = (diffSampleR * biquadB[4]) - (tempSample * biquadB[6]);
				diffSampleR = tempSample;
			}		
			hysteresisL = (hysteresisL * (1.0-iirAmount)) + (diffSampleL * iirAmount);
			if (fabs(hysteresisL)<1.18e-37) hysteresisL = 0.0; else diffSampleL -= hysteresisL;
			if (diffSampleL > 1.571) diffSampleL = 1.571; else if (diffSampleL < -1.571) diffSampleL = -1.571;
			if (hysteresisL > 1.571) hysteresisL = 1.571; else if (hysteresisL < -1.571) hysteresisL = -1.571;
			hysteresisR = (hysteresisR * (1.0-iirAmount)) + (diffSampleR * iirAmount);
			if (fabs(hysteresisR)<1.18e-37) hysteresisR = 0.0; else diffSampleR -= hysteresisR;
			if (diffSampleR > 1.571) diffSampleR = 1.571; else if (diffSampleR < -1.571) diffSampleR = -1.571;
			if (hysteresisR > 1.571) hysteresisR = 1.571; else if (hysteresisR < -1.571) hysteresisR = -1.571;
			inputSampleL += (sin(diffSampleL)-sin(hysteresisL))*distScaling;
			inputSampleR += (sin(diffSampleR)-sin(hysteresisR))*distScaling; //apply transformer distortions
	
			if (wet !=1.0) {
				inputSampleL = (inputSampleL * wet) + (drySampleL * (1.0-wet));
				inputSampleR = (inputSampleR * wet) + (drySampleR * (1.0-wet));
			}
					
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
    
	long double biquadA[15];
	long double biquadB[15];
	long double hysteresisL;
	long double hysteresisR;
	uint32_t fpdL;
	uint32_t fpdR;
	//default stuff

};
MIN_EXTERNAL(coils2);

