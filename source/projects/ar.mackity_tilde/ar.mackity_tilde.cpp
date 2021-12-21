#include "c74_min.h"

using namespace c74::min;

class mackity : public object<mackity>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"an emulation of the input stage of a vintage Mackie 1202"};
	MIN_TAGS {""};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "intrim", 0.1, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "outpad", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.1;
			B = 1.0;
			
			iirSampleAL = 0.0;
			iirSampleBL = 0.0;
			iirSampleAR = 0.0;
			iirSampleBR = 0.0;
			for (int x = 0; x < 15; x++) {biquadA[x] = 0.0; biquadB[x] = 0.0;}
		
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
		
		double inTrim = A*10.0;
		double outPad = B;
		inTrim *= inTrim;
		
		double iirAmountA = 0.001860867/overallscale;
		double iirAmountB = 0.000287496/overallscale;
		
		biquadB[0] = biquadA[0] = 19160.0 / samplerate();
	    biquadA[1] = 0.431684981684982;
		biquadB[1] = 1.1582298;
		
		double K = tan(M_PI * biquadA[0]); //lowpass
		double norm = 1.0 / (1.0 + K / biquadA[1] + K * K);
		biquadA[2] = K * K * norm;
		biquadA[3] = 2.0 * biquadA[2];
		biquadA[4] = biquadA[2];
		biquadA[5] = 2.0 * (K * K - 1.0) * norm;
		biquadA[6] = (1.0 - K / biquadA[1] + K * K) * norm;
		
		K = tan(M_PI * biquadB[0]);
		norm = 1.0 / (1.0 + K / biquadB[1] + K * K);
		biquadB[2] = K * K * norm;
		biquadB[3] = 2.0 * biquadB[2];
		biquadB[4] = biquadB[2];
		biquadB[5] = 2.0 * (K * K - 1.0) * norm;
		biquadB[6] = (1.0 - K / biquadB[1] + K * K) * norm;
		
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpdL * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpdR * 1.18e-43;
			
			if (fabs(iirSampleAL)<1.18e-37) iirSampleAL = 0.0;
			iirSampleAL = (iirSampleAL * (1.0 - iirAmountA)) + (inputSampleL * iirAmountA);
			inputSampleL -= iirSampleAL;
			if (fabs(iirSampleAR)<1.18e-37) iirSampleAR = 0.0;
			iirSampleAR = (iirSampleAR * (1.0 - iirAmountA)) + (inputSampleR * iirAmountA);
			inputSampleR -= iirSampleAR;
			
			if (inTrim != 1.0) {inputSampleL *= inTrim; inputSampleR *= inTrim;}
			
			long double outSampleL = biquadA[2]*inputSampleL+biquadA[3]*biquadA[7]+biquadA[4]*biquadA[8]-biquadA[5]*biquadA[9]-biquadA[6]*biquadA[10];
			biquadA[8] = biquadA[7]; biquadA[7] = inputSampleL; inputSampleL = outSampleL; biquadA[10] = biquadA[9]; biquadA[9] = inputSampleL; //DF1 left
			
			long double outSampleR = biquadA[2]*inputSampleR+biquadA[3]*biquadA[11]+biquadA[4]*biquadA[12]-biquadA[5]*biquadA[13]-biquadA[6]*biquadA[14];
			biquadA[12] = biquadA[11]; biquadA[11] = inputSampleR; inputSampleR = outSampleR; biquadA[14] = biquadA[13]; biquadA[13] = inputSampleR; //DF1 right
			
			if (inputSampleL > 1.0) inputSampleL = 1.0;
			if (inputSampleL < -1.0) inputSampleL = -1.0;
			inputSampleL -= pow(inputSampleL,5)*0.1768;
			if (inputSampleR > 1.0) inputSampleR = 1.0;
			if (inputSampleR < -1.0) inputSampleR = -1.0;
			inputSampleR -= pow(inputSampleR,5)*0.1768;
			
			outSampleL = biquadB[2]*inputSampleL+biquadB[3]*biquadB[7]+biquadB[4]*biquadB[8]-biquadB[5]*biquadB[9]-biquadB[6]*biquadB[10];
			biquadB[8] = biquadB[7]; biquadB[7] = inputSampleL; inputSampleL = outSampleL; biquadB[10] = biquadB[9]; biquadB[9] = inputSampleL; //DF1 left
			
			outSampleR = biquadB[2]*inputSampleR+biquadB[3]*biquadB[11]+biquadB[4]*biquadB[12]-biquadB[5]*biquadB[13]-biquadB[6]*biquadB[14];
			biquadB[12] = biquadB[11]; biquadB[11] = inputSampleR; inputSampleR = outSampleR; biquadB[14] = biquadB[13]; biquadB[13] = inputSampleR; //DF1 right
			
			if (fabs(iirSampleBL)<1.18e-37) iirSampleBL = 0.0;
			iirSampleBL = (iirSampleBL * (1.0 - iirAmountB)) + (inputSampleL * iirAmountB);
			inputSampleL -= iirSampleBL;
			if (fabs(iirSampleBR)<1.18e-37) iirSampleBR = 0.0;
			iirSampleBR = (iirSampleBR * (1.0 - iirAmountB)) + (inputSampleR * iirAmountB);
			inputSampleR -= iirSampleBR;
			
			if (outPad != 1.0) {inputSampleL *= outPad; inputSampleR *= outPad;}
			
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
    
	
	long double iirSampleAL;
	long double iirSampleBL;
	long double iirSampleAR;
	long double iirSampleBR;
	long double biquadA[15];
	long double biquadB[15];
	
	uint32_t fpdL;
	uint32_t fpdR;
	//default stuff

};
MIN_EXTERNAL(mackity);

