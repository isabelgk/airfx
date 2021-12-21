#include "c74_min.h"

using namespace c74::min;

class compresaturator : public object<compresaturator>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"fades between compressing and soft clipping"};
	MIN_TAGS {"compressor, saturation, softclipper"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "drive", 0.5, range {0.0, 1.0} };  // todo: scale to dB
	attribute<number, threadsafe::no, limit::clamp> B {this, "clamp", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "expand", 0.5, range {0.0, 1.0} }; // todo: scale to samples
	attribute<number, threadsafe::no, limit::clamp> D {this, "output", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> E {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.5; //-12 to +12 dB
			B = 0.5; //0 to 100%
			C = 0.5; //50 to 5000 samples, default 500
			D = 1.0;
			E = 1.0;
			
			for(int count = 0; count < 10990; count++) {dL[count] = 0.0; dR[count] = 0.0;}
			dCount = 0;
			lastWidthL = 500;
			padFactorL = 0;
			lastWidthR = 500;
			padFactorR = 0;
			
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

		double inputgain = pow(10.0,((A*24.0)-12.0)/20.0);
		double satComp = B*2.0;
		int widestRange = C*C*5000;
		if (widestRange < 50) widestRange = 50;
		satComp += (((double)widestRange/3000.0)*satComp);
		//set the max wideness of comp zone, minimum range boosted (too much?)
		double output = D;
		double wet = E;
		
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
	
			static int noisesourceL = 0;
			static int noisesourceR = 850010;
			int residue;
			double applyresidue;
			
			noisesourceL = noisesourceL % 1700021; noisesourceL++;
			residue = noisesourceL * noisesourceL;
			residue = residue % 170003; residue *= residue;
			residue = residue % 17011; residue *= residue;
			residue = residue % 1709; residue *= residue;
			residue = residue % 173; residue *= residue;
			residue = residue % 17;
			applyresidue = residue;
			applyresidue *= 0.00000001;
			applyresidue *= 0.00000001;
			inputSampleL += applyresidue;
			if (inputSampleL<1.2e-38 && -inputSampleL<1.2e-38) {
				inputSampleL -= applyresidue;
			}
			
			noisesourceR = noisesourceR % 1700021; noisesourceR++;
			residue = noisesourceR * noisesourceR;
			residue = residue % 170003; residue *= residue;
			residue = residue % 17011; residue *= residue;
			residue = residue % 1709; residue *= residue;
			residue = residue % 173; residue *= residue;
			residue = residue % 17;
			applyresidue = residue;
			applyresidue *= 0.00000001;
			applyresidue *= 0.00000001;
			inputSampleR += applyresidue;
			if (inputSampleR<1.2e-38 && -inputSampleR<1.2e-38) {
				inputSampleR -= applyresidue;
			}
			//for live air, we always apply the dither noise. Then, if our result is 
			//effectively digital black, we'll subtract it again. We want a 'air' hiss
			long double drySampleL = inputSampleL;
			long double drySampleR = inputSampleR;
			
			if (dCount < 1 || dCount > 5000) {dCount = 5000;}
			
			//begin L
			long double temp = inputSampleL;
			double variSpeed = 1.0 + ((padFactorL/lastWidthL)*satComp);
			if (variSpeed < 1.0) variSpeed = 1.0;
			double totalgain = inputgain / variSpeed;
			if (totalgain != 1.0) {
				inputSampleL *= totalgain;
				if (totalgain < 1.0) {
					temp *= totalgain;
					//no boosting beyond unity please
				}
			}
			
			long double bridgerectifier = fabs(inputSampleL);
			double overspill = 0;
			int targetWidth = widestRange;
			//we now have defaults and an absolute input value to work with
			if (bridgerectifier < 0.01) padFactorL *= 0.9999;
			//in silences we bring back padFactor if it got out of hand		
			if (bridgerectifier > 1.57079633) {
				bridgerectifier = 1.57079633;
				targetWidth = 8;
			}
			//if our output's gone beyond saturating to distorting, we begin chasing the
			//buffer size smaller. Anytime we don't have that, we expand (smoothest sound, only adding to an increasingly subdivided buffer)
			
			bridgerectifier = sin(bridgerectifier);
			if (inputSampleL > 0) {
				inputSampleL = bridgerectifier;
				overspill = temp - bridgerectifier;
			}
			
			if (inputSampleL < 0) {
				inputSampleL = -bridgerectifier;
				overspill = (-temp) - bridgerectifier;
			} 
			//drive section
			
			dL[dCount + 5000] = dL[dCount] = overspill * satComp;
			//we now have a big buffer to draw from, which is always positive amount of overspill
			
			padFactorL += dL[dCount];
			double randy = (rand()/(double)RAND_MAX);
			if ((targetWidth*randy) > lastWidthL) {
				//we are expanding the buffer so we don't remove this trailing sample
				lastWidthL += 1;
			} else {
				padFactorL -= dL[dCount+lastWidthL];
				//zero change, or target is smaller and we are shrinking
				if (targetWidth < lastWidthL) {
					lastWidthL -= 1;
					if (lastWidthL < 2) lastWidthL = 2;
					//sanity check as randy can give us target zero
					padFactorL -= dL[dCount+lastWidthL];
				}
			}
			//variable attack/release speed more rapid as comp intensity increases
			//implemented in a way where we're repeatedly not altering the buffer as it expands, which makes the comp artifacts smoother
			if (padFactorL < 0) padFactorL = 0;
			//end L
			
			//begin R
			temp = inputSampleR;
			variSpeed = 1.0 + ((padFactorR/lastWidthR)*satComp);
			if (variSpeed < 1.0) variSpeed = 1.0;
			totalgain = inputgain / variSpeed;
			if (totalgain != 1.0) {
				inputSampleR *= totalgain;
				if (totalgain < 1.0) {
					temp *= totalgain;
					//no boosting beyond unity please
				}
			}
			
			bridgerectifier = fabs(inputSampleR);
			overspill = 0;
			targetWidth = widestRange;
			//we now have defaults and an absolute input value to work with
			if (bridgerectifier < 0.01) padFactorR *= 0.9999;
			//in silences we bring back padFactor if it got out of hand		
			if (bridgerectifier > 1.57079633) {
				bridgerectifier = 1.57079633;
				targetWidth = 8;
			}
			//if our output's gone beyond saturating to distorting, we begin chasing the
			//buffer size smaller. Anytime we don't have that, we expand (smoothest sound, only adding to an increasingly subdivided buffer)
			
			bridgerectifier = sin(bridgerectifier);
			if (inputSampleR > 0) {
				inputSampleR = bridgerectifier;
				overspill = temp - bridgerectifier;
			}
			
			if (inputSampleR < 0) {
				inputSampleR = -bridgerectifier;
				overspill = (-temp) - bridgerectifier;
			} 
			//drive section
			
			dR[dCount + 5000] = dR[dCount] = overspill * satComp;
			//we now have a big buffer to draw from, which is always positive amount of overspill
			
			padFactorR += dR[dCount];
			randy = (rand()/(double)RAND_MAX);
			if ((targetWidth*randy) > lastWidthR) {
				//we are expanding the buffer so we don't remove this trailing sample
				lastWidthR += 1;
			} else {
				padFactorR -= dR[dCount+lastWidthR];
				//zero change, or target is smaller and we are shrinking
				if (targetWidth < lastWidthR) {
					lastWidthR -= 1;
					if (lastWidthR < 2) lastWidthR = 2;
					//sanity check as randy can give us target zero
					padFactorR -= dR[dCount+lastWidthR];
				}
			}
			//variable attack/release speed more rapid as comp intensity increases
			//implemented in a way where we're repeatedly not altering the buffer as it expands, which makes the comp artifacts smoother
			if (padFactorR < 0) padFactorR = 0;
			//end R
			
			dCount--;
			
			if (output < 1.0) {
				inputSampleL *= output;
				inputSampleR *= output;
			}
			
			if (wet < 1.0) {
				inputSampleL = (inputSampleL * wet) + (drySampleL * (1.0-wet));
				inputSampleR = (inputSampleR * wet) + (drySampleR * (1.0-wet));
			}
			
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
    
		uint32_t fpd;
	//default stuff

	int dCount;

	float dL[11000];
	int lastWidthL;
	double padFactorL;
	
	float dR[11000];
	int lastWidthR;
	double padFactorR;
	
};
MIN_EXTERNAL(compresaturator);

