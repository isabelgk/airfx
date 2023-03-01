#include "c74_min.h"

using namespace c74::min;

class ybandpass : public object<ybandpass>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"YBandpass is soft and smooth to nasty, edgy texture-varying filtering."};
	MIN_TAGS {"filter"};
	MIN_AUTHOR {"Christopher Herb"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "gain", 0.1, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "freq", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "reson8", 0.1, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "resedge", 0.1, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> E {this, "output", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> F {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			for (int x = 0; x < biq_total; x++) {biquad[x] = 0.0;}
			powFactorA = 1.0; powFactorB = 1.0;
			inTrimA = 0.1; inTrimB = 0.1;
			outTrimA = 1.0; outTrimB = 1.0;
			for (int x = 0; x < fix_total; x++) {fixA[x] = 0.0; fixB[x] = 0.0;}
			
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
		auto inFramesToProcess = sampleFrames; //vst doesn't give us this as a separate variable so we'll make it

		double overallscale = 1.0;
		overallscale /= 44100.0;
		overallscale *= samplerate();
		
		inTrimA = inTrimB;
		inTrimB = A*10.0;
		
		biquad[biq_freq] = pow(B,3)*20000.0;
		if (biquad[biq_freq] < 15.0) biquad[biq_freq] = 15.0;
		biquad[biq_freq] /= samplerate();
		biquad[biq_reso] = (pow(C,2)*15.0)+0.5571;
		biquad[biq_aA0] = biquad[biq_aB0];
		//biquad[biq_aA1] = biquad[biq_aB1];
		biquad[biq_aA2] = biquad[biq_aB2];
		biquad[biq_bA1] = biquad[biq_bB1];
		biquad[biq_bA2] = biquad[biq_bB2];
		//previous run through the buffer is still in the filter, so we move it
		//to the A section and now it's the new starting point.
		double K = tan(M_PI * biquad[biq_freq]);
		double norm = 1.0 / (1.0 + K / biquad[biq_reso] + K * K);
		biquad[biq_aB0] = K / biquad[biq_reso] * norm;
		//biquad[biq_aB1] = 0.0; //bandpass can simplify the biquad kernel: leave out this multiply
		biquad[biq_aB2] = -biquad[biq_aB0];
		biquad[biq_bB1] = 2.0 * (K * K - 1.0) * norm;
		biquad[biq_bB2] = (1.0 - K / biquad[biq_reso] + K * K) * norm;
		//for the coefficient-interpolated biquad filter
		
		powFactorA = powFactorB;
		powFactorB = pow(D+0.9,4);
		
		//1.0 == target neutral
		
		outTrimA = outTrimB;
		outTrimB = E;
		
		double wet = F;
		
		fixA[fix_freq] = fixB[fix_freq] = 20000.0 / samplerate();
		fixA[fix_reso] = fixB[fix_reso] = 0.7071; //butterworth Q
		
		K = tan(M_PI * fixA[fix_freq]);
		norm = 1.0 / (1.0 + K / fixA[fix_reso] + K * K);
		fixA[fix_a0] = fixB[fix_a0] = K * K * norm;
		fixA[fix_a1] = fixB[fix_a1] = 2.0 * fixA[fix_a0];
		fixA[fix_a2] = fixB[fix_a2] = fixA[fix_a0];
		fixA[fix_b1] = fixB[fix_b1] = 2.0 * (K * K - 1.0) * norm;
		fixA[fix_b2] = fixB[fix_b2] = (1.0 - K / fixA[fix_reso] + K * K) * norm;
		//for the fixed-position biquad filter
		
		while (--sampleFrames >= 0)
		{
			double inputSampleL = *in1;
			double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
			if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;
			double drySampleL = inputSampleL;
			double drySampleR = inputSampleR;
			
			double temp = (double)sampleFrames/inFramesToProcess;
			biquad[biq_a0] = (biquad[biq_aA0]*temp)+(biquad[biq_aB0]*(1.0-temp));
			//biquad[biq_a1] = (biquad[biq_aA1]*temp)+(biquad[biq_aB1]*(1.0-temp));
			biquad[biq_a2] = (biquad[biq_aA2]*temp)+(biquad[biq_aB2]*(1.0-temp));
			biquad[biq_b1] = (biquad[biq_bA1]*temp)+(biquad[biq_bB1]*(1.0-temp));
			biquad[biq_b2] = (biquad[biq_bA2]*temp)+(biquad[biq_bB2]*(1.0-temp));
			//this is the interpolation code for the biquad
			double powFactor = (powFactorA*temp)+(powFactorB*(1.0-temp));
			double inTrim = (inTrimA*temp)+(inTrimB*(1.0-temp));
			double outTrim = (outTrimA*temp)+(outTrimB*(1.0-temp));
			
			inputSampleL *= inTrim;
			inputSampleR *= inTrim;
			
			temp = (inputSampleL * fixA[fix_a0]) + fixA[fix_sL1];
			fixA[fix_sL1] = (inputSampleL * fixA[fix_a1]) - (temp * fixA[fix_b1]) + fixA[fix_sL2];
			fixA[fix_sL2] = (inputSampleL * fixA[fix_a2]) - (temp * fixA[fix_b2]);
			inputSampleL = temp; //fixed biquad filtering ultrasonics
			temp = (inputSampleR * fixA[fix_a0]) + fixA[fix_sR1];
			fixA[fix_sR1] = (inputSampleR * fixA[fix_a1]) - (temp * fixA[fix_b1]) + fixA[fix_sR2];
			fixA[fix_sR2] = (inputSampleR * fixA[fix_a2]) - (temp * fixA[fix_b2]);
			inputSampleR = temp; //fixed biquad filtering ultrasonics
			
			//encode/decode courtesy of torridgristle under the MIT license
			if (inputSampleL > 1.0) inputSampleL = 1.0;
			else if (inputSampleL > 0.0) inputSampleL = 1.0 - pow(1.0-inputSampleL,powFactor);
			if (inputSampleL < -1.0) inputSampleL = -1.0;
			else if (inputSampleL < 0.0) inputSampleL = -1.0 + pow(1.0+inputSampleL,powFactor);
			if (inputSampleR > 1.0) inputSampleR = 1.0;
			else if (inputSampleR > 0.0) inputSampleR = 1.0 - pow(1.0-inputSampleR,powFactor);
			if (inputSampleR < -1.0) inputSampleR = -1.0;
			else if (inputSampleR < 0.0) inputSampleR = -1.0 + pow(1.0+inputSampleR,powFactor);
			
			temp = (inputSampleL * biquad[biq_a0]) + biquad[biq_sL1];
			biquad[biq_sL1] = -(temp * biquad[biq_b1]) + biquad[biq_sL2];
			biquad[biq_sL2] = (inputSampleL * biquad[biq_a2]) - (temp * biquad[biq_b2]);
			inputSampleL = temp; //coefficient interpolating biquad filter
			temp = (inputSampleR * biquad[biq_a0]) + biquad[biq_sR1];
			biquad[biq_sR1] = -(temp * biquad[biq_b1]) + biquad[biq_sR2];
			biquad[biq_sR2] = (inputSampleR * biquad[biq_a2]) - (temp * biquad[biq_b2]);
			inputSampleR = temp; //coefficient interpolating biquad filter
			
			//encode/decode courtesy of torridgristle under the MIT license
			if (inputSampleL > 1.0) inputSampleL = 1.0;
			else if (inputSampleL > 0.0) inputSampleL = 1.0 - pow(1.0-inputSampleL,(1.0/powFactor));
			if (inputSampleL < -1.0) inputSampleL = -1.0;
			else if (inputSampleL < 0.0) inputSampleL = -1.0 + pow(1.0+inputSampleL,(1.0/powFactor));
			if (inputSampleR > 1.0) inputSampleR = 1.0;
			else if (inputSampleR > 0.0) inputSampleR = 1.0 - pow(1.0-inputSampleR,(1.0/powFactor));
			if (inputSampleR < -1.0) inputSampleR = -1.0;
			else if (inputSampleR < 0.0) inputSampleR = -1.0 + pow(1.0+inputSampleR,(1.0/powFactor));
			
			inputSampleL *= outTrim;
			inputSampleR *= outTrim;
			
			temp = (inputSampleL * fixB[fix_a0]) + fixB[fix_sL1];
			fixB[fix_sL1] = (inputSampleL * fixB[fix_a1]) - (temp * fixB[fix_b1]) + fixB[fix_sL2];
			fixB[fix_sL2] = (inputSampleL * fixB[fix_a2]) - (temp * fixB[fix_b2]);
			inputSampleL = temp; //fixed biquad filtering ultrasonics
			temp = (inputSampleR * fixB[fix_a0]) + fixB[fix_sR1];
			fixB[fix_sR1] = (inputSampleR * fixB[fix_a1]) - (temp * fixB[fix_b1]) + fixB[fix_sR2];
			fixB[fix_sR2] = (inputSampleR * fixB[fix_a2]) - (temp * fixB[fix_b2]);
			inputSampleR = temp; //fixed biquad filtering ultrasonics
			
			if (wet < 1.0) {
				inputSampleL = (inputSampleL*wet) + (drySampleL*(1.0-wet));
				inputSampleR = (inputSampleR*wet) + (drySampleR*(1.0-wet));
			}
			
			//begin 64 bit stereo floating point dither
			//int expon; frexp((double)inputSampleL, &expon);
			fpdL ^= fpdL << 13; fpdL ^= fpdL >> 17; fpdL ^= fpdL << 5;
			//inputSampleL += ((double(fpdL)-uint32_t(0x7fffffff)) * 1.1e-44l * pow(2,expon+62));
			//frexp((double)inputSampleR, &expon);
			fpdR ^= fpdR << 13; fpdR ^= fpdR >> 17; fpdR ^= fpdR << 5;
			//inputSampleR += ((double(fpdR)-uint32_t(0x7fffffff)) * 1.1e-44l * pow(2,expon+62));
			//end 64 bit stereo floating point dither
			
			*out1 = inputSampleL;
			*out2 = inputSampleR;

			in1++;
			in2++;
			out1++;
			out2++;
		}
	}
private:
    enum {
		biq_freq,
		biq_reso,
		biq_a0,
		biq_a1,
		biq_a2,
		biq_b1,
		biq_b2,
		biq_aA0,
		biq_aA1,
		biq_aA2,
		biq_bA1,
		biq_bA2,
		biq_aB0,
		biq_aB1,
		biq_aB2,
		biq_bB1,
		biq_bB2,
		biq_sL1,
		biq_sL2,
		biq_sR1,
		biq_sR2,
		biq_total
	}; //coefficient interpolating biquad filter, stereo
	double biquad[biq_total];
	
	double powFactorA;
	double powFactorB;
	double inTrimA;
	double inTrimB;
	double outTrimA;
	double outTrimB;
	
	enum {
		fix_freq,
		fix_reso,
		fix_a0,
		fix_a1,
		fix_a2,
		fix_b1,
		fix_b2,
		fix_sL1,
		fix_sL2,
		fix_sR1,
		fix_sR2,
		fix_total
	}; //fixed frequency biquad filter for ultrasonics, stereo
	double fixA[fix_total];
	double fixB[fix_total];
    
	uint32_t fpdL;
	uint32_t fpdR;
	//default stuff

};
MIN_EXTERNAL(ybandpass);

