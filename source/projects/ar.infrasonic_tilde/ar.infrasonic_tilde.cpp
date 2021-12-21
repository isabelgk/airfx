#include "c74_min.h"

using namespace c74::min;

class infrasonic : public object<infrasonic>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a very steep subsonic filter"};
	MIN_TAGS {"filter"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};


	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			for (int x = 0; x < 15; x++) {biquadA[x] = 0.0; biquadB[x] = 0.0; biquadC[x] = 0.0; biquadD[x] = 0.0; biquadE[x] = 0.0;}
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

		biquadE[0] = biquadD[0] = biquadC[0] = biquadB[0] = biquadA[0] = 20.0 / samplerate();
	    biquadA[1] = 0.50623256;
		biquadB[1] = 0.56116312;
		biquadC[1] = 0.70710678;
		biquadD[1] = 1.10134463;
		biquadE[1] = 3.19622661; //tenth order Butterworth out of five biquads
		
		double K = tan(M_PI * biquadA[0]); //lowpass
		double norm = 1.0 / (1.0 + K / biquadA[1] + K * K);
		biquadA[2] = norm;
		biquadA[3] = -2.0 * biquadA[2];
		biquadA[4] = biquadA[2];
		biquadA[5] = 2.0 * (K * K - 1.0) * norm;
		biquadA[6] = (1.0 - K / biquadA[1] + K * K) * norm;
		
		K = tan(M_PI * biquadA[0]);
		norm = 1.0 / (1.0 + K / biquadB[1] + K * K);
		biquadB[2] = norm;
		biquadB[3] = -2.0 * biquadB[2];
		biquadB[4] = biquadB[2];
		biquadB[5] = 2.0 * (K * K - 1.0) * norm;
		biquadB[6] = (1.0 - K / biquadB[1] + K * K) * norm;
		
		K = tan(M_PI * biquadC[0]);
		norm = 1.0 / (1.0 + K / biquadC[1] + K * K);
		biquadC[2] = norm;
		biquadC[3] = -2.0 * biquadC[2];
		biquadC[4] = biquadC[2];
		biquadC[5] = 2.0 * (K * K - 1.0) * norm;
		biquadC[6] = (1.0 - K / biquadC[1] + K * K) * norm;
		
		K = tan(M_PI * biquadD[0]);
		norm = 1.0 / (1.0 + K / biquadD[1] + K * K);
		biquadD[2] = norm;
		biquadD[3] = -2.0 * biquadD[2];
		biquadD[4] = biquadD[2];
		biquadD[5] = 2.0 * (K * K - 1.0) * norm;
		biquadD[6] = (1.0 - K / biquadD[1] + K * K) * norm;
		
		K = tan(M_PI * biquadE[0]);
		norm = 1.0 / (1.0 + K / biquadE[1] + K * K);
		biquadE[2] = norm;
		biquadE[3] = -2.0 * biquadE[2];
		biquadE[4] = biquadE[2];
		biquadE[5] = 2.0 * (K * K - 1.0) * norm;
		biquadE[6] = (1.0 - K / biquadE[1] + K * K) * norm;
		
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpd * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpd * 1.18e-43;
			
			long double outSampleL = biquadA[2]*inputSampleL+biquadA[3]*biquadA[7]+biquadA[4]*biquadA[8]-biquadA[5]*biquadA[9]-biquadA[6]*biquadA[10];
			biquadA[8] = biquadA[7]; biquadA[7] = inputSampleL; inputSampleL = outSampleL; biquadA[10] = biquadA[9]; biquadA[9] = inputSampleL; //DF1 left
			
			outSampleL = biquadB[2]*inputSampleL+biquadB[3]*biquadB[7]+biquadB[4]*biquadB[8]-biquadB[5]*biquadB[9]-biquadB[6]*biquadB[10];
			biquadB[8] = biquadB[7]; biquadB[7] = inputSampleL; inputSampleL = outSampleL; biquadB[10] = biquadB[9]; biquadB[9] = inputSampleL; //DF1 left
			
			outSampleL = biquadC[2]*inputSampleL+biquadC[3]*biquadC[7]+biquadC[4]*biquadC[8]-biquadC[5]*biquadC[9]-biquadC[6]*biquadC[10];
			biquadC[8] = biquadC[7]; biquadC[7] = inputSampleL; inputSampleL = outSampleL; biquadC[10] = biquadC[9]; biquadC[9] = inputSampleL; //DF1 left
			
			outSampleL = biquadD[2]*inputSampleL+biquadD[3]*biquadD[7]+biquadD[4]*biquadD[8]-biquadD[5]*biquadD[9]-biquadD[6]*biquadD[10];
			biquadD[8] = biquadD[7]; biquadD[7] = inputSampleL; inputSampleL = outSampleL; biquadD[10] = biquadD[9]; biquadD[9] = inputSampleL; //DF1 left
			
			outSampleL = biquadE[2]*inputSampleL+biquadE[3]*biquadE[7]+biquadE[4]*biquadE[8]-biquadE[5]*biquadE[9]-biquadE[6]*biquadE[10];
			biquadE[8] = biquadE[7]; biquadE[7] = inputSampleL; inputSampleL = outSampleL; biquadE[10] = biquadE[9]; biquadE[9] = inputSampleL; //DF1 left
			
			long double outSampleR = biquadA[2]*inputSampleR+biquadA[3]*biquadA[11]+biquadA[4]*biquadA[12]-biquadA[5]*biquadA[13]-biquadA[6]*biquadA[14];
			biquadA[12] = biquadA[11]; biquadA[11] = inputSampleR; inputSampleR = outSampleR; biquadA[14] = biquadA[13]; biquadA[13] = inputSampleR; //DF1 right
			
			outSampleR = biquadB[2]*inputSampleR+biquadB[3]*biquadB[11]+biquadB[4]*biquadB[12]-biquadB[5]*biquadB[13]-biquadB[6]*biquadB[14];
			biquadB[12] = biquadB[11]; biquadB[11] = inputSampleR; inputSampleR = outSampleR; biquadB[14] = biquadB[13]; biquadB[13] = inputSampleR; //DF1 right
			
			outSampleR = biquadC[2]*inputSampleR+biquadC[3]*biquadC[11]+biquadC[4]*biquadC[12]-biquadC[5]*biquadC[13]-biquadC[6]*biquadC[14];
			biquadC[12] = biquadC[11]; biquadC[11] = inputSampleR; inputSampleR = outSampleR; biquadC[14] = biquadC[13]; biquadC[13] = inputSampleR; //DF1 right
			
			outSampleR = biquadD[2]*inputSampleR+biquadD[3]*biquadD[11]+biquadD[4]*biquadD[12]-biquadD[5]*biquadD[13]-biquadD[6]*biquadD[14];
			biquadD[12] = biquadD[11]; biquadD[11] = inputSampleR; inputSampleR = outSampleR; biquadD[14] = biquadD[13]; biquadD[13] = inputSampleR; //DF1 right
			
			outSampleR = biquadE[2]*inputSampleR+biquadE[3]*biquadE[11]+biquadE[4]*biquadE[12]-biquadE[5]*biquadE[13]-biquadE[6]*biquadE[14];
			biquadE[12] = biquadE[11]; biquadE[11] = inputSampleR; inputSampleR = outSampleR; biquadE[14] = biquadE[13]; biquadE[13] = inputSampleR; //DF1 right
			
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
	
	long double biquadA[15];
	long double biquadB[15];
	long double biquadC[15];
	long double biquadD[15];
	long double biquadE[15]; //note that this stereo form doesn't require L and R forms!
	//This is because so much of it is coefficients etc. that are the same on both channels.
	//So the stored samples are in 7-8-9-10 and 11-12-13-14, and freq/res/coefficients serve both.
    
	uint32_t fpd;
	//default stuff
};

MIN_EXTERNAL(infrasonic);

