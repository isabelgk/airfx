#include "c74_min.h"

using namespace c74::min;

class preponderant : public object<preponderant>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"Anti-Soothe, a strange tone intensifier and balancer."};
	MIN_TAGS {""};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "narrow", 0.25, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "medium", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "wide", 0.75, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "resonance", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> E {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.25;
			B = 0.5;
			C = 0.75;
			D = 0.5;
			E = 1.0;
			for (int x = 0; x < 15; x++) {biquadA[x] = 0.0; biquadB[x] = 0.0; biquadC[x] = 0.0;}
			bassBalanceL = midBalanceL = highBalanceL = 1.0;
			bassTrackL = midTrackL = highTrackL = 0.0;
			quicknessL = 0.0001;
			bassBalanceR = midBalanceR = highBalanceR = 1.0;
			bassTrackR = midTrackR = highTrackR = 0.0;
			quicknessR = 0.0001;
			
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
		
		double chase = 0.00005 / overallscale;
		
		biquadA[0] = pow(A,(3.0*cbrt(overallscale)))*0.42;
		if (biquadA[0] < 0.0001) biquadA[0] = 0.0001;
		
		biquadB[0] = pow(B,(3.0*cbrt(overallscale)))*0.42;
		if (biquadB[0] < 0.0001) biquadB[0] = 0.0001;
		
		biquadC[0] = pow(C,(3.0*cbrt(overallscale)))*0.42;
		if (biquadC[0] < 0.0001) biquadC[0] = 0.0001;
		
	    biquadA[1] = biquadB[1] = biquadC[1] = (pow(D,3)*8.0)+0.33;
		biquadB[1] /= 2.0; biquadC[1] /= 4.0;
		
		double volumeCompensation = sqrt(biquadA[1]);
		
		double wet = E;
		
		double K = tan(M_PI * biquadA[0]);
		double norm = 1.0 / (1.0 + K / biquadA[1] + K * K);
		biquadA[2] = K / biquadA[1] * norm;
		biquadA[3] = 0.0; //bandpass can simplify the biquad kernel: leave out this multiply
		biquadA[4] = -biquadA[2];
		biquadA[5] = 2.0 * (K * K - 1.0) * norm;
		biquadA[6] = (1.0 - K / biquadA[1] + K * K) * norm;
		
		K = tan(M_PI * biquadB[0]);
		norm = 1.0 / (1.0 + K / biquadB[1] + K * K);
		biquadB[2] = K / biquadB[1] * norm;
		biquadB[3] = 0.0; //bandpass can simplify the biquad kernel: leave out this multiply
		biquadB[4] = -biquadB[2];
		biquadB[5] = 2.0 * (K * K - 1.0) * norm;
		biquadB[6] = (1.0 - K / biquadB[1] + K * K) * norm;
		
		K = tan(M_PI * biquadC[0]);
		norm = 1.0 / (1.0 + K / biquadC[1] + K * K);
		biquadC[2] = K / biquadC[1] * norm;
		biquadC[3] = 0.0; //bandpass can simplify the biquad kernel: leave out this multiply
		biquadC[4] = -biquadC[2];
		biquadC[5] = 2.0 * (K * K - 1.0) * norm;
		biquadC[6] = (1.0 - K / biquadC[1] + K * K) * norm;
		
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpdL * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpdR * 1.18e-43;
			long double drySampleL = *in1;
			long double drySampleR = *in2;
			
			long double tempSampleL = (inputSampleL * biquadA[2]) + biquadA[7];
			biquadA[7] = -(tempSampleL * biquadA[5]) + biquadA[8]; //BANDPASS form
			biquadA[8] = (inputSampleL * biquadA[4]) - (tempSampleL * biquadA[6]);
			long double bassSampleL = tempSampleL; //like mono AU, 7 and 8 store L channel
			
			long double tempSampleR = (inputSampleR * biquadA[2]) + biquadA[9];
			biquadA[9] = -(tempSampleR * biquadA[5]) + biquadA[10]; //BANDPASS form
			biquadA[10] = (inputSampleR * biquadA[4]) - (tempSampleR * biquadA[6]);
			long double bassSampleR = tempSampleR; //note: 9 and 10 store the R channel
			
			tempSampleL = (inputSampleL * biquadB[2]) + biquadB[7];
			biquadB[7] = -(tempSampleL * biquadB[5]) + biquadB[8]; //BANDPASS form
			biquadB[8] = (inputSampleL * biquadB[4]) - (tempSampleL * biquadB[6]);
			long double midSampleL = tempSampleL; //like mono AU, 7 and 8 store L channel
			
			tempSampleR = (inputSampleR * biquadB[2]) + biquadB[9];
			biquadB[9] = -(tempSampleR * biquadB[5]) + biquadB[10]; //BANDPASS form
			biquadB[10] = (inputSampleR * biquadB[4]) - (tempSampleR * biquadB[6]);
			long double midSampleR = tempSampleR; //note: 9 and 10 store the R channel
			
			
			tempSampleL = (inputSampleL * biquadC[2]) + biquadC[7];
			biquadC[7] = -(tempSampleL * biquadC[5]) + biquadC[8]; //BANDPASS form
			biquadC[8] = (inputSampleL * biquadC[4]) - (tempSampleL * biquadC[6]);
			long double highSampleL = tempSampleL; //like mono AU, 7 and 8 store L channel
			
			tempSampleR = (inputSampleR * biquadC[2]) + biquadC[9];
			biquadC[9] = -(tempSampleR * biquadC[5]) + biquadC[10]; //BANDPASS form
			biquadC[10] = (inputSampleR * biquadC[4]) - (tempSampleR * biquadC[6]);
			long double highSampleR = tempSampleR; //note: 9 and 10 store the R channel
			
			if (bassBalanceL < 0.00125) bassBalanceL = 0.00125;
			if (bassBalanceL > 1.0) bassBalanceL = 1.0;
			
			if (bassBalanceR < 0.00125) bassBalanceR = 0.00125;
			if (bassBalanceR > 1.0) bassBalanceR = 1.0;
			
			if (midBalanceL < 0.00125) midBalanceL = 0.00125;
			if (midBalanceL > 1.0) midBalanceL = 1.0;
			
			if (midBalanceR < 0.00125) midBalanceR = 0.00125;
			if (midBalanceR > 1.0) midBalanceR = 1.0;
			
			if (highBalanceL < 0.00125) highBalanceL = 0.00125;
			if (highBalanceL > 1.0) highBalanceL = 1.0;
			
			if (highBalanceR < 0.00125) highBalanceR = 0.00125;
			if (highBalanceR > 1.0) highBalanceR = 1.0;
			
			bassSampleL *= bassBalanceL;
			midSampleL *= midBalanceL;
			highSampleL *= highBalanceL;
			if (bassTrackL < fabs(bassSampleL)) bassTrackL = fabs(bassSampleL);
			if (midTrackL < fabs(midSampleL)) midTrackL = fabs(midSampleL);
			if (highTrackL < fabs(highSampleL)) highTrackL = fabs(highSampleL);
			if (bassTrackL > quicknessL) bassTrackL -= quicknessL;
			if (midTrackL > quicknessL) midTrackL -= quicknessL;
			if (highTrackL > quicknessL) highTrackL -= quicknessL;
			
			double disparity = 0.0;
			if (disparity < fabs(bassTrackL - midTrackL)) disparity = fabs(bassTrackL - midTrackL);
			if (disparity < fabs(bassTrackL - highTrackL)) disparity = fabs(bassTrackL - highTrackL);
			if (disparity < fabs(midTrackL - highTrackL)) disparity = fabs(midTrackL - highTrackL);
			
			quicknessL *= (1.0-chase);
			quicknessL += ((1.0+disparity) * 0.0001 * chase);
			
			if (bassTrackL > midTrackL) {bassBalanceL -= quicknessL; midBalanceL += quicknessL;}
			else {bassBalanceL += quicknessL; midBalanceL -= quicknessL;}
			if (midTrackL > highTrackL) {midBalanceL -= quicknessL; highBalanceL += quicknessL;}
			else {midBalanceL += quicknessL; highBalanceL -= quicknessL;}
			if (highTrackL > bassTrackL) {highBalanceL -= quicknessL; bassBalanceL += quicknessL;}
			else {highBalanceL += quicknessL; bassBalanceL -= quicknessL;}
			
			if (highBalanceL > 0.618033988749894848204586) highBalanceL -= (quicknessL*0.001); else highBalanceL += (quicknessL*0.001);
			if (midBalanceL > 0.618033988749894848204586) midBalanceL -= (quicknessL*0.001); else midBalanceL += (quicknessL*0.001);
			if (bassBalanceL > 0.618033988749894848204586) bassBalanceL -= (quicknessL*0.001); else bassBalanceL += (quicknessL*0.001);
			
			bassSampleR *= bassBalanceR;
			midSampleR *= midBalanceR;
			highSampleR *= highBalanceR;
			if (bassTrackR < fabs(bassSampleR)) bassTrackR = fabs(bassSampleR);
			if (midTrackR < fabs(midSampleR)) midTrackR = fabs(midSampleR);
			if (highTrackR < fabs(highSampleR)) highTrackR = fabs(highSampleR);
			if (bassTrackR > quicknessR) bassTrackR -= quicknessR;
			if (midTrackR > quicknessR) midTrackR -= quicknessR;
			if (highTrackR > quicknessR) highTrackR -= quicknessR;
			
			disparity = 0.0;
			if (disparity < fabs(bassTrackR - midTrackR)) disparity = fabs(bassTrackR - midTrackR);
			if (disparity < fabs(bassTrackR - highTrackR)) disparity = fabs(bassTrackR - highTrackR);
			if (disparity < fabs(midTrackR - highTrackR)) disparity = fabs(midTrackR - highTrackR);
			
			quicknessR *= (1.0-chase);
			quicknessR += ((1.0+disparity) * 0.0001 * chase);
			
			if (bassTrackR > midTrackR) {bassBalanceR -= quicknessR; midBalanceR += quicknessR;}
			else {bassBalanceR += quicknessR; midBalanceR -= quicknessR;}
			if (midTrackR > highTrackR) {midBalanceR -= quicknessR; highBalanceR += quicknessR;}
			else {midBalanceR += quicknessR; highBalanceR -= quicknessR;}
			if (highTrackR > bassTrackR) {highBalanceR -= quicknessR; bassBalanceR += quicknessR;}
			else {highBalanceR += quicknessR; bassBalanceR -= quicknessR;}
			
			if (highBalanceR > 0.618033988749894848204586) highBalanceR -= (quicknessR*0.001); else highBalanceR += (quicknessR*0.001);
			if (midBalanceR > 0.618033988749894848204586) midBalanceR -= (quicknessR*0.001); else midBalanceR += (quicknessR*0.001);
			if (bassBalanceR > 0.618033988749894848204586) bassBalanceR -= (quicknessR*0.001); else bassBalanceR += (quicknessR*0.001);
			
			inputSampleL = (bassSampleL + midSampleL + highSampleL) * volumeCompensation;
			inputSampleR = (bassSampleR + midSampleR + highSampleR) * volumeCompensation;
			
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
	long double biquadC[15];
	
	long double bassBalanceL;
	long double midBalanceL;
	long double highBalanceL;
	long double bassTrackL;
	long double midTrackL;
	long double highTrackL;
	long double quicknessL;
	
	long double bassBalanceR;
	long double midBalanceR;
	long double highBalanceR;
	long double bassTrackR;
	long double midTrackR;
	long double highTrackR;
	long double quicknessR;
	
	uint32_t fpdL;
	uint32_t fpdR;
	//default stuff

};
MIN_EXTERNAL(preponderant);

