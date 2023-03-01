#include "c74_min.h"

using namespace c74::min;

class console8litechannel : public object<console8litechannel>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"Console8LiteChannel is simplified Console8, working with just a single mix buss."};
	MIN_TAGS {"analog"};
	MIN_AUTHOR {"Christopher Herb"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "fader", 0.5, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			inTrimA = 0.5; inTrimB = 0.5;
			iirAL = 0.0; iirBL = 0.0; iirAR = 0.0; iirBR = 0.0;
			for (int x = 0; x < fix_total; x++) {fix[x] = 0.0;fixB[x] = 0.0;}
			for (int x = 0; x < 10; x++) {softL[x] = 0.0; softR[x] = 0.0;}

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
		double iirAmountA = 12.66/samplerate();
		//this is our distributed unusual highpass, which is
		//adding subtle harmonics to the really deep stuff to define it
		if (fabs(iirAL)<1.18e-37) iirAL = 0.0;
		if (fabs(iirBL)<1.18e-37) iirBL = 0.0;
		if (fabs(iirAR)<1.18e-37) iirAR = 0.0;
		if (fabs(iirBR)<1.18e-37) iirBR = 0.0;
		//catch denormals early and only check once per buffer
		if (samplerate() > 49000.0) hsr = true; else hsr = false;
		fix[fix_freq] = 24000.0 / samplerate();
		fix[fix_reso] = 2.24697960;
		double K = tan(M_PI * fix[fix_freq]); //lowpass
		double norm = 1.0 / (1.0 + K / fix[fix_reso] + K * K);
		fix[fix_a0] = K * K * norm;
		fix[fix_a1] = 2.0 * fix[fix_a0];
		fix[fix_a2] = fix[fix_a0];
		fix[fix_b1] = 2.0 * (K * K - 1.0) * norm;
		fix[fix_b2] = (1.0 - K / fix[fix_reso] + K * K) * norm;
		//this is the fixed biquad distributed anti-aliasing filter
		
		inTrimA = inTrimB; inTrimB = A*2.0;
		//0.5 is unity gain, and we can attenuate to silence or boost slightly over 12dB
		//into softclipping overdrive.
		fixB[fix_freq] = 24000.0 / samplerate();
		fixB[fix_reso] = 0.80193774;
		K = tan(M_PI * fixB[fix_freq]); //lowpass
		norm = 1.0 / (1.0 + K / fixB[fix_reso] + K * K);
		fixB[fix_a0] = K * K * norm;
		fixB[fix_a1] = 2.0 * fixB[fix_a0];
		fixB[fix_a2] = fixB[fix_a0];
		fixB[fix_b1] = 2.0 * (K * K - 1.0) * norm;
		fixB[fix_b2] = (1.0 - K / fixB[fix_reso] + K * K) * norm;
		//this is the fixed biquad distributed anti-aliasing filter
		
		double overallscale = 1.0;
		overallscale /= 44100.0;
		overallscale *= samplerate();
		cycleEnd = floor(overallscale);
		if (cycleEnd < 1) cycleEnd = 1;
		if (cycleEnd == 3) cycleEnd = 4;
		if (cycleEnd > 4) cycleEnd = 4;
		//this is going to be 2 for 88.1 or 96k, 4 for 176 or 192k
		
		while (--sampleFrames >= 0)
		{
			double inputSampleL = *in1;
			double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
			if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;
			
			double position = (double)sampleFrames/inFramesToProcess;
			double inTrim = (inTrimA*position)+(inTrimB*(1.0-position));
			//input trim smoothed to cut out zipper noise
			
			iirAL = (iirAL * (1.0 - iirAmountA)) + (inputSampleL * iirAmountA);
			double iirAmountBL = fabs(iirAL)+0.00001;
			iirBL = (iirBL * (1.0 - iirAmountBL)) + (iirAL * iirAmountBL);
			inputSampleL -= iirBL;
			iirAR = (iirAR * (1.0 - iirAmountA)) + (inputSampleR * iirAmountA);
			double iirAmountBR = fabs(iirAR)+0.00001;
			iirBR = (iirBR * (1.0 - iirAmountBR)) + (iirAR * iirAmountBR);
			inputSampleR -= iirBR;
			//Console8 highpass
			if (cycleEnd == 4) {
				softL[8] = softL[7]; softL[7] = softL[6]; softL[6] = softL[5]; softL[5] = softL[4];
				softL[4] = softL[3]; softL[3] = softL[2]; softL[2] = softL[1]; softL[1] = softL[0];
				softL[0] = inputSampleL;
				softR[8] = softR[7]; softR[7] = softR[6]; softR[6] = softR[5]; softR[5] = softR[4];
				softR[4] = softR[3]; softR[3] = softR[2]; softR[2] = softR[1]; softR[1] = softR[0];
				softR[0] = inputSampleR;
			}
			if (cycleEnd == 2) {
				softL[8] = softL[6]; softL[6] = softL[4];
				softL[4] = softL[2]; softL[2] = softL[0];
				softL[0] = inputSampleL;
				softR[8] = softR[6]; softR[6] = softR[4];
				softR[4] = softR[2]; softR[2] = softR[0];
				softR[0] = inputSampleR;
			}
			if (cycleEnd == 1) {
				softL[8] = softL[4];
				softL[4] = softL[0];
				softL[0] = inputSampleL;
				softR[8] = softR[4];
				softR[4] = softR[0];
				softR[0] = inputSampleR;
			}
			softL[9] = ((softL[0]-softL[4])-(softL[4]-softL[8]));
			if (softL[9] > 0.91416342) inputSampleL = softL[4]+(fabs(softL[4])*sin(softL[9]-0.91416342)*0.08583658);
			if (-softL[9] > 0.91416342) inputSampleL = softL[4]-(fabs(softL[4])*sin(-softL[9]-0.91416342)*0.08583658);
			//Console8 slew soften: must be clipped or it can generate NAN out of the full system
			if (inputSampleL > 1.57079633) inputSampleL = 1.57079633; if (inputSampleL < -1.57079633) inputSampleL = -1.57079633;
			softR[9] = ((softR[0]-softR[4])-(softR[4]-softR[8]));
			if (softR[9] > 0.91416342) inputSampleR = softR[4]+(fabs(softR[4])*sin(softR[9]-0.91416342)*0.08583658);
			if (-softR[9] > 0.91416342) inputSampleR = softR[4]-(fabs(softR[4])*sin(-softR[9]-0.91416342)*0.08583658);
			//Console8 slew soften: must be clipped or it can generate NAN out of the full system
			if (inputSampleR > 1.57079633) inputSampleR = 1.57079633; if (inputSampleR < -1.57079633) inputSampleR = -1.57079633;
			if (hsr){
				double outSample = (inputSampleL * fix[fix_a0]) + fix[fix_sL1];
				fix[fix_sL1] = (inputSampleL * fix[fix_a1]) - (outSample * fix[fix_b1]) + fix[fix_sL2];
				fix[fix_sL2] = (inputSampleL * fix[fix_a2]) - (outSample * fix[fix_b2]);
				inputSampleL = outSample;
				outSample = (inputSampleR * fix[fix_a0]) + fix[fix_sR1];
				fix[fix_sR1] = (inputSampleR * fix[fix_a1]) - (outSample * fix[fix_b1]) + fix[fix_sR2];
				fix[fix_sR2] = (inputSampleR * fix[fix_a2]) - (outSample * fix[fix_b2]);
				inputSampleR = outSample;
			} //fixed biquad filtering ultrasonics		
			//we can go directly into the first distortion stage of ChannelOut
			//with a filtered signal, so its biquad is between stages
			//on the input channel we have direct signal, not Console8 decode
			
			inputSampleL *= inTrim;
			if (inputSampleL > 1.57079633) inputSampleL = 1.57079633; if (inputSampleL < -1.57079633) inputSampleL = -1.57079633;
			inputSampleL = sin(inputSampleL);
			//Console8 gain stage clips at exactly 1.0 post-sin()
			inputSampleR *= inTrim;
			if (inputSampleR > 1.57079633) inputSampleR = 1.57079633; if (inputSampleR < -1.57079633) inputSampleR = -1.57079633;
			inputSampleR = sin(inputSampleR);
			//Console8 gain stage clips at exactly 1.0 post-sin()
			if (hsr){
				double outSample = (inputSampleL * fixB[fix_a0]) + fixB[fix_sL1];
				fixB[fix_sL1] = (inputSampleL * fixB[fix_a1]) - (outSample * fixB[fix_b1]) + fixB[fix_sL2];
				fixB[fix_sL2] = (inputSampleL * fixB[fix_a2]) - (outSample * fixB[fix_b2]);
				inputSampleL = outSample;
				outSample = (inputSampleR * fixB[fix_a0]) + fixB[fix_sR1];
				fixB[fix_sR1] = (inputSampleR * fixB[fix_a1]) - (outSample * fixB[fix_b1]) + fixB[fix_sR2];
				fixB[fix_sR2] = (inputSampleR * fixB[fix_a2]) - (outSample * fixB[fix_b2]);
				inputSampleR = outSample;
			} //fixed biquad filtering ultrasonics
			inputSampleL *= inTrim;
			if (inputSampleL > 1.57079633) inputSampleL = 1.57079633; if (inputSampleL < -1.57079633) inputSampleL = -1.57079633;
			inputSampleL = sin(inputSampleL);
			//Console8 gain stage clips at exactly 1.0 post-sin()
			inputSampleR *= inTrim;
			if (inputSampleR > 1.57079633) inputSampleR = 1.57079633; if (inputSampleR < -1.57079633) inputSampleR = -1.57079633;
			inputSampleR = sin(inputSampleR);
			//Console8 gain stage clips at exactly 1.0 post-sin()
			
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
	double iirAL;
	double iirBL;
	double iirAR;
	double iirBR;
	double inTrimA;
	double inTrimB;
	bool hsr;
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
	double fix[fix_total];
	double fixB[fix_total];
	double softL[11];
	double softR[11];
	int cycleEnd;
	
	uint32_t fpdL;
	uint32_t fpdR;
	//default stuff

};
MIN_EXTERNAL(console8litechannel);

