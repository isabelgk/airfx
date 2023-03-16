#include "c74_min.h"

using namespace c74::min;

class pressure5 : public object<pressure5>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"Pressure5 expands Pressure4 with after-boost and built-in ClipOnly2."};
	MIN_TAGS {"compressor"};
	MIN_AUTHOR {"Christopher Herb"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "pressure", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "speed", 0.25, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "mewiness", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "pawclaw", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> E {this, "output", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> F {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			muSpeedA = 10000;
			muSpeedB = 10000;
			muCoefficientA = 1;
			muCoefficientB = 1;
			muVary = 1;
			flip = false;
			for (int x = 0; x < fix_total; x++) {fixA[x] = 0.0; fixB[x] = 0.0;}
			lastSampleL = 0.0;
			wasPosClipL = false;
			wasNegClipL = false;
			lastSampleR = 0.0;
			wasPosClipR = false;
			wasNegClipR = false;
			for (int x = 0; x < 16; x++) {intermediateL[x] = 0.0; intermediateR[x] = 0.0;}
			slewMax = 0.0;

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
		int spacing = floor(overallscale); //should give us working basic scaling, usually 2 or 4
		if (spacing < 1) spacing = 1; if (spacing > 16) spacing = 16;
		
		double threshold = 1.0 - (A * 0.95);
		double muMakeupGain = 1.0 / threshold;
		//gain settings around threshold
		double release = pow((1.28-B),5)*32768.0;
		double fastest = sqrt(release);
		release /= overallscale;
		fastest /= overallscale;
		//speed settings around release
		double mewinessRef = C;
		double pawsClaws = -(D-0.5)*1.618033988749894848204586;
		// µ µ µ µ µ µ µ µ µ µ µ µ is the kitten song o/~
		double outputGain = pow(E*2.0,2); //max 4.0 gain
		double wet = F;
		
		fixA[fix_freq] = 24000.0 / samplerate();
		fixA[fix_reso] = 0.7071; //butterworth Q
		double K = tan(M_PI * fixA[fix_freq]);
		double norm = 1.0 / (1.0 + K / fixA[fix_reso] + K * K);
		fixA[fix_a0] = K * K * norm;
		fixA[fix_a1] = 2.0 * fixA[fix_a0];
		fixA[fix_a2] = fixA[fix_a0];
		fixA[fix_b1] = 2.0 * (K * K - 1.0) * norm;
		fixA[fix_b2] = (1.0 - K / fixA[fix_reso] + K * K) * norm;
		//for the fixed-position biquad filter
		for (int x = 0; x < fix_sL1; x++) fixB[x] = fixA[x];
		//make the second filter same as the first, don't use sample slots
		
		while (--sampleFrames >= 0)
		{
			double inputSampleL = *in1;
			double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
			if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;
			double drySampleL = inputSampleL;
			double drySampleR = inputSampleR;
			
			inputSampleL = inputSampleL * muMakeupGain;
			inputSampleR = inputSampleR * muMakeupGain;
			
			if (fixA[fix_freq] < 0.4999) {
				double temp = (inputSampleL * fixA[fix_a0]) + fixA[fix_sL1];
				fixA[fix_sL1] = (inputSampleL * fixA[fix_a1]) - (temp * fixA[fix_b1]) + fixA[fix_sL2];
				fixA[fix_sL2] = (inputSampleL * fixA[fix_a2]) - (temp * fixA[fix_b2]);
				inputSampleL = temp;
				temp = (inputSampleR * fixA[fix_a0]) + fixA[fix_sR1];
				fixA[fix_sR1] = (inputSampleR * fixA[fix_a1]) - (temp * fixA[fix_b1]) + fixA[fix_sR2];
				fixA[fix_sR2] = (inputSampleR * fixA[fix_a2]) - (temp * fixA[fix_b2]);
				inputSampleR = temp; //fixed biquad filtering ultrasonics before Pressure
			}
			
			double inputSense = fabs(inputSampleL);
			if (fabs(inputSampleR) > inputSense)
				inputSense = fabs(inputSampleR);
			//we will take the greater of either channel and just use that, then apply the result
			//to both stereo channels.
			
			double mewiness = sin(mewinessRef + (slewMax * pawsClaws));
			bool positivemu = true; if (mewiness < 0) {positivemu = false; mewiness = -mewiness;}
			
			if (flip)
			{
				if (inputSense > threshold)
				{
					muVary = threshold / inputSense;
					muAttack = sqrt(fabs(muSpeedA));
					muCoefficientA = muCoefficientA * (muAttack-1.0);
					if (muVary < threshold)
					{
						muCoefficientA = muCoefficientA + threshold;
					}
					else
					{
						muCoefficientA = muCoefficientA + muVary;
					}
					muCoefficientA = muCoefficientA / muAttack;
				}
				else
				{
					muCoefficientA = muCoefficientA * ((muSpeedA * muSpeedA)-1.0);
					muCoefficientA = muCoefficientA + 1.0;
					muCoefficientA = muCoefficientA / (muSpeedA * muSpeedA);
				}
				muNewSpeed = muSpeedA * (muSpeedA-1);
				muNewSpeed = muNewSpeed + fabs(inputSense*release)+fastest;
				muSpeedA = muNewSpeed / muSpeedA;
			}
			else
			{
				if (inputSense > threshold)
				{
					muVary = threshold / inputSense;
					muAttack = sqrt(fabs(muSpeedB));
					muCoefficientB = muCoefficientB * (muAttack-1);
					if (muVary < threshold)
					{
						muCoefficientB = muCoefficientB + threshold;
					}
					else
					{
						muCoefficientB = muCoefficientB + muVary;
					}
					muCoefficientB = muCoefficientB / muAttack;
				}
				else
				{
					muCoefficientB = muCoefficientB * ((muSpeedB * muSpeedB)-1.0);
					muCoefficientB = muCoefficientB + 1.0;
					muCoefficientB = muCoefficientB / (muSpeedB * muSpeedB);
				}
				muNewSpeed = muSpeedB * (muSpeedB-1);
				muNewSpeed = muNewSpeed + fabs(inputSense*release)+fastest;
				muSpeedB = muNewSpeed / muSpeedB;
			}
			//got coefficients, adjusted speeds
			
			double coefficient;
			if (flip) {
				if (positivemu) coefficient = pow(muCoefficientA,2);
				else coefficient = sqrt(muCoefficientA);
				coefficient = (coefficient*mewiness)+(muCoefficientA*(1.0-mewiness));
				inputSampleL *= coefficient;
				inputSampleR *= coefficient;
			} else {
				if (positivemu) coefficient = pow(muCoefficientB,2);
				else coefficient = sqrt(muCoefficientB);
				coefficient = (coefficient*mewiness)+(muCoefficientB*(1.0-mewiness));
				inputSampleL *= coefficient;
				inputSampleR *= coefficient;
			}
			//applied compression with vari-vari-µ-µ-µ-µ-µ-µ-is-the-kitten-song o/~
			//applied gain correction to control output level- tends to constrain sound rather than inflate it
			
			if (outputGain != 1.0) {
				inputSampleL *= outputGain;
				inputSampleR *= outputGain;
			}		
			
			flip = !flip;
			
			if (fixB[fix_freq] < 0.49999) {
				double temp = (inputSampleL * fixB[fix_a0]) + fixB[fix_sL1];
				fixB[fix_sL1] = (inputSampleL * fixB[fix_a1]) - (temp * fixB[fix_b1]) + fixB[fix_sL2];
				fixB[fix_sL2] = (inputSampleL * fixB[fix_a2]) - (temp * fixB[fix_b2]);
				inputSampleL = temp;
				temp = (inputSampleR * fixB[fix_a0]) + fixB[fix_sR1];
				fixB[fix_sR1] = (inputSampleR * fixB[fix_a1]) - (temp * fixB[fix_b1]) + fixB[fix_sR2];
				fixB[fix_sR2] = (inputSampleR * fixB[fix_a2]) - (temp * fixB[fix_b2]);
				inputSampleR = temp; //fixed biquad filtering ultrasonics between Pressure and ClipOnly
			}
			
			if (wet != 1.0) {
				inputSampleL = (inputSampleL * wet) + (drySampleL * (1.0-wet));
				inputSampleR = (inputSampleR * wet) + (drySampleR * (1.0-wet));
			}
			//Dry/Wet control, BEFORE ClipOnly
			
			slewMax = fabs(inputSampleL - lastSampleL);
			if (slewMax < fabs(inputSampleR - lastSampleR)) slewMax = fabs(inputSampleR - lastSampleR);
			//set up for fiddling with mewiness. Largest amount of slew in any direction
			
			//begin ClipOnly2 stereo as a little, compressed chunk that can be dropped into code
			if (inputSampleL > 4.0) inputSampleL = 4.0; if (inputSampleL < -4.0) inputSampleL = -4.0;
			if (wasPosClipL == true) { //current will be over
				if (inputSampleL<lastSampleL) lastSampleL=0.7058208+(inputSampleL*0.2609148);
				else lastSampleL = 0.2491717+(lastSampleL*0.7390851);
			} wasPosClipL = false;
			if (inputSampleL>0.9549925859) {wasPosClipL=true;inputSampleL=0.7058208+(lastSampleL*0.2609148);}
			if (wasNegClipL == true) { //current will be -over
				if (inputSampleL > lastSampleL) lastSampleL=-0.7058208+(inputSampleL*0.2609148);
				else lastSampleL=-0.2491717+(lastSampleL*0.7390851);
			} wasNegClipL = false;
			if (inputSampleL<-0.9549925859) {wasNegClipL=true;inputSampleL=-0.7058208+(lastSampleL*0.2609148);}
			intermediateL[spacing] = inputSampleL;
			inputSampleL = lastSampleL; //Latency is however many samples equals one 44.1k sample
			for (int x = spacing; x > 0; x--) intermediateL[x-1] = intermediateL[x];
			lastSampleL = intermediateL[0]; //run a little buffer to handle this
			
			if (inputSampleR > 4.0) inputSampleR = 4.0; if (inputSampleR < -4.0) inputSampleR = -4.0;
			if (wasPosClipR == true) { //current will be over
				if (inputSampleR<lastSampleR) lastSampleR=0.7058208+(inputSampleR*0.2609148);
				else lastSampleR = 0.2491717+(lastSampleR*0.7390851);
			} wasPosClipR = false;
			if (inputSampleR>0.9549925859) {wasPosClipR=true;inputSampleR=0.7058208+(lastSampleR*0.2609148);}
			if (wasNegClipR == true) { //current will be -over
				if (inputSampleR > lastSampleR) lastSampleR=-0.7058208+(inputSampleR*0.2609148);
				else lastSampleR=-0.2491717+(lastSampleR*0.7390851);
			} wasNegClipR = false;
			if (inputSampleR<-0.9549925859) {wasNegClipR=true;inputSampleR=-0.7058208+(lastSampleR*0.2609148);}
			intermediateR[spacing] = inputSampleR;
			inputSampleR = lastSampleR; //Latency is however many samples equals one 44.1k sample
			for (int x = spacing; x > 0; x--) intermediateR[x-1] = intermediateR[x];
			lastSampleR = intermediateR[0]; //run a little buffer to handle this
			//end ClipOnly2 stereo as a little, compressed chunk that can be dropped into code
			//final clip runs AFTER the Dry/Wet. It serves as a safety clip even if you're not full wet
			
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
	double muVary;
	double muAttack;
	double muNewSpeed;
	double muSpeedA;
	double muSpeedB;
	double muCoefficientA;
	double muCoefficientB;
	bool flip; //Pressure
	
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
		fix_lastSampleL,
		fix_lastSampleR,
		fix_total
	};
	double fixA[fix_total];
	double fixB[fix_total]; //fixed frequency biquad filter for ultrasonics, stereo
	
	double lastSampleL;
	double intermediateL[16];
	bool wasPosClipL;
	bool wasNegClipL;
	double lastSampleR;
	double intermediateR[16];
	bool wasPosClipR;
	bool wasNegClipR; //Stereo ClipOnly2
	
	double slewMax; //to adust mewiness
    
	uint32_t fpdL;
	uint32_t fpdR;
	//default stuff

};
MIN_EXTERNAL(pressure5);

