#include "c74_min.h"

using namespace c74::min;

class acceleration2 : public object<acceleration2>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"Second gen acceleration limiter that tames edge, leaves brightness. Updated for high sample rate and more extreme effect."};
	MIN_TAGS {"audio, effect"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "Limit", 0.32, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "Dry/Wet", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.32;
			B = 1.0;
			
			lastSampleL = lastSampleR = 0.0;
			for(int count = 0; count < 33; count++) {sL[count] = sR[count] = 0.0;}
			m1L = m2L = m1R = m2R = 0.0;
			for (int x = 0; x < 11; x++) {biquadA[x] = 0.0;biquadB[x] = 0.0;}
		
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
		
		double intensity = pow(A,3)*32;
		double wet = B;	
		int spacing = (int)(1.73*overallscale)+1;
		if (spacing > 16) spacing = 16;
		
		biquadA[0] = (20000.0 * (1.0-(A*0.618033988749894848204586))) / samplerate();
		biquadB[0] = 20000.0 / samplerate();
	    biquadA[1] = 0.7071;
		biquadB[1] = 0.7071;
		
		double K = tan(M_PI * biquadA[0]);
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
			long double drySampleL = inputSampleL;
			long double drySampleR = inputSampleR;
			
			long double tempSample = (inputSampleL * biquadA[2]) + biquadA[7];
			biquadA[7] = (inputSampleL * biquadA[3]) - (tempSample * biquadA[5]) + biquadA[8];
			biquadA[8] = (inputSampleL * biquadA[4]) - (tempSample * biquadA[6]);
			double smoothL = tempSample; //like mono AU, 7 and 8 store L channel
			
			tempSample = (inputSampleR * biquadA[2]) + biquadA[9];
			biquadA[9] = (inputSampleR * biquadA[3]) - (tempSample * biquadA[5]) + biquadA[10];
			biquadA[10] = (inputSampleR * biquadA[4]) - (tempSample * biquadA[6]);
			double smoothR = tempSample; //note: 9 and 10 store the R channel
			
			for(int count = spacing*2; count >= 0; count--) {sL[count+1] = sL[count]; sR[count+1] = sR[count];}
			sL[0] = inputSampleL; sR[0] = inputSampleR;
			
			m1L = (sL[0]-sL[spacing])*(fabs(sL[0]-sL[spacing]));
			m2L = (sL[spacing]-sL[spacing*2])*(fabs(sL[spacing]-sL[spacing*2]));
			double senseL = (intensity*intensity*fabs(m1L-m2L));
			if (senseL > 1.0) senseL = 1.0;
			inputSampleL = (inputSampleL * (1.0-senseL)) + (smoothL*senseL);
			
			m1R = (sR[0]-sR[spacing])*(fabs(sR[0]-sR[spacing]));
			m2R = (sR[spacing]-sR[spacing*2])*(fabs(sR[spacing]-sR[spacing*2]));
			double senseR = (intensity*intensity*fabs(m1R-m2R));
			if (senseR > 1.0) senseR = 1.0;
			inputSampleR = (inputSampleR * (1.0-senseR)) + (smoothR*senseR);		
			
			tempSample = (inputSampleL * biquadB[2]) + biquadB[7];
			biquadB[7] = (inputSampleL * biquadB[3]) - (tempSample * biquadB[5]) + biquadB[8];
			biquadB[8] = (inputSampleL * biquadB[4]) - (tempSample * biquadB[6]);
			inputSampleL = tempSample; //like mono AU, 7 and 8 store L channel
			
			tempSample = (inputSampleR * biquadB[2]) + biquadB[9];
			biquadB[9] = (inputSampleR * biquadB[3]) - (tempSample * biquadB[5]) + biquadB[10];
			biquadB[10] = (inputSampleR * biquadB[4]) - (tempSample * biquadB[6]);
			inputSampleR = tempSample; //note: 9 and 10 store the R channel
			
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
    
	
	double lastSampleL;
	double sL[34];
	double m1L;
	double m2L;
	
	double lastSampleR;
	double sR[34];
	double m1R;
	double m2R;
	
	long double biquadA[11];
	long double biquadB[11]; //note that this stereo form doesn't require L and R forms!
	//This is because so much of it is coefficients etc. that are the same on both channels.
	//So the stored samples are in 7-8 and 9-10, and freq/res/coefficients serve both.
	
	uint32_t fpdL;
	uint32_t fpdR;
	//default stuff

};
MIN_EXTERNAL(acceleration2);

