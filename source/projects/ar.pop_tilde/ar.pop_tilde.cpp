#include "c74_min.h"

using namespace c74::min;

class pop : public object<pop>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a crazy overcompressor with a very exaggerated sound"};
	MIN_TAGS {"compressor"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "intensity", 0.3, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "output", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
            fpd = 17;
			
			for(int count = 0; count < 10000; count++) {dL[count] = 0; dR[count] = 0;}
			delay = 0;
			flip = false;
			
			muSpeedAL = 10000;
			muSpeedBL = 10000;
			muCoefficientAL = 1;
			muCoefficientBL = 1;
			thickenL = 1;
			muVaryL = 1;
			previousL = 0.0;
			previous2L = 0.0;
			previous3L = 0.0;
			previous4L = 0.0;
			previous5L = 0.0;
		
			muSpeedAR = 10000;
			muSpeedBR = 10000;
			muCoefficientAR = 1;
			muCoefficientBR = 1;
			thickenR = 1;
			muVaryR = 1;
			previousR = 0.0;
			previous2R = 0.0;
			previous3R = 0.0;
			previous4R = 0.0;
			previous5R = 0.0;
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
		
		double highGainOffset = pow(A,2)*0.023;
		double threshold = 1.001 - (1.0-pow(1.0-A,5));
		double muMakeupGain = sqrt(1.0 / threshold);
		//gain settings around threshold
		double release = (A*100000.0) + 300000.0;
		int maxdelay = (int)(1450.0 * overallscale);
		if (maxdelay > 9999) maxdelay = 9999;
		release /= overallscale;
		double fastest = sqrt(release);
		//speed settings around release
		double output = B;
		double wet = C;
		// µ µ µ µ µ µ µ µ µ µ µ µ is the kitten song o/~
	    
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
	
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpd * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpd * 1.18e-43;
	
			long double drySampleL = inputSampleL;
			long double drySampleR = inputSampleR;
			
			dL[delay] = inputSampleL;
			dR[delay] = inputSampleR;
			delay--;
			if (delay < 0 || delay > maxdelay) {delay = maxdelay;}
			//yes this is a second bounds check. it's cheap, check EVERY time
			inputSampleL = (inputSampleL * thickenL) + (dL[delay] * (1.0-thickenL));
			inputSampleR = (inputSampleR * thickenR) + (dR[delay] * (1.0-thickenR));
			
			long double lowestSampleL = inputSampleL;
			if (fabs(inputSampleL) > fabs(previousL)) lowestSampleL = previousL;
			if (fabs(lowestSampleL) > fabs(previous2L)) lowestSampleL = (lowestSampleL + previous2L) / 1.99;
			if (fabs(lowestSampleL) > fabs(previous3L)) lowestSampleL = (lowestSampleL + previous3L) / 1.98;
			if (fabs(lowestSampleL) > fabs(previous4L)) lowestSampleL = (lowestSampleL + previous4L) / 1.97;
			if (fabs(lowestSampleL) > fabs(previous5L)) lowestSampleL = (lowestSampleL + previous5L) / 1.96;
			previous5L = previous4L;
			previous4L = previous3L;
			previous3L = previous2L;
			previous2L = previousL;
			previousL = inputSampleL;
			inputSampleL *= muMakeupGain;
			double punchinessL = 0.95-fabs(inputSampleL*0.08);
			if (punchinessL < 0.65) punchinessL = 0.65;
			
			long double lowestSampleR = inputSampleR;
			if (fabs(inputSampleR) > fabs(previousR)) lowestSampleR = previousR;
			if (fabs(lowestSampleR) > fabs(previous2R)) lowestSampleR = (lowestSampleR + previous2R) / 1.99;
			if (fabs(lowestSampleR) > fabs(previous3R)) lowestSampleR = (lowestSampleR + previous3R) / 1.98;
			if (fabs(lowestSampleR) > fabs(previous4R)) lowestSampleR = (lowestSampleR + previous4R) / 1.97;
			if (fabs(lowestSampleR) > fabs(previous5R)) lowestSampleR = (lowestSampleR + previous5R) / 1.96;
			previous5R = previous4R;
			previous4R = previous3R;
			previous3R = previous2R;
			previous2R = previousR;
			previousR = inputSampleR;
			inputSampleR *= muMakeupGain;
			double punchinessR = 0.95-fabs(inputSampleR*0.08);
			if (punchinessR < 0.65) punchinessR = 0.65;
			
			//adjust coefficients for L
			if (flip)
			{
				if (fabs(lowestSampleL) > threshold)
				{
					muVaryL = threshold / fabs(lowestSampleL);
					muAttackL = sqrt(fabs(muSpeedAL));
					muCoefficientAL = muCoefficientAL * (muAttackL-1.0);
					if (muVaryL < threshold)
					{
						muCoefficientAL = muCoefficientAL + threshold;
					}
					else
					{
						muCoefficientAL = muCoefficientAL + muVaryL;
					}
					muCoefficientAL = muCoefficientAL / muAttackL;
				}
				else
				{
					muCoefficientAL = muCoefficientAL * ((muSpeedAL * muSpeedAL)-1.0);
					muCoefficientAL = muCoefficientAL + 1.0;
					muCoefficientAL = muCoefficientAL / (muSpeedAL * muSpeedAL);
				}
				muNewSpeedL = muSpeedAL * (muSpeedAL-1);
				muNewSpeedL = muNewSpeedL + fabs(lowestSampleL*release)+fastest;
				muSpeedAL = muNewSpeedL / muSpeedAL;
			}
			else
			{
				if (fabs(lowestSampleL) > threshold)
				{
					muVaryL = threshold / fabs(lowestSampleL);
					muAttackL = sqrt(fabs(muSpeedBL));
					muCoefficientBL = muCoefficientBL * (muAttackL-1);
					if (muVaryL < threshold)
					{
						muCoefficientBL = muCoefficientBL + threshold;
					}
					else
					{
						muCoefficientBL = muCoefficientBL + muVaryL;
					}
					muCoefficientBL = muCoefficientBL / muAttackL;
				}
				else
				{
					muCoefficientBL = muCoefficientBL * ((muSpeedBL * muSpeedBL)-1.0);
					muCoefficientBL = muCoefficientBL + 1.0;
					muCoefficientBL = muCoefficientBL / (muSpeedBL * muSpeedBL);
				}
				muNewSpeedL = muSpeedBL * (muSpeedBL-1);
				muNewSpeedL = muNewSpeedL + fabs(lowestSampleL*release)+fastest;
				muSpeedBL = muNewSpeedL / muSpeedBL;
			}
			//got coefficients, adjusted speeds for L
			
			//adjust coefficients for R
			if (flip)
			{
				if (fabs(lowestSampleR) > threshold)
				{
					muVaryR = threshold / fabs(lowestSampleR);
					muAttackR = sqrt(fabs(muSpeedAR));
					muCoefficientAR = muCoefficientAR * (muAttackR-1.0);
					if (muVaryR < threshold)
					{
						muCoefficientAR = muCoefficientAR + threshold;
					}
					else
					{
						muCoefficientAR = muCoefficientAR + muVaryR;
					}
					muCoefficientAR = muCoefficientAR / muAttackR;
				}
				else
				{
					muCoefficientAR = muCoefficientAR * ((muSpeedAR * muSpeedAR)-1.0);
					muCoefficientAR = muCoefficientAR + 1.0;
					muCoefficientAR = muCoefficientAR / (muSpeedAR * muSpeedAR);
				}
				muNewSpeedR = muSpeedAR * (muSpeedAR-1);
				muNewSpeedR = muNewSpeedR + fabs(lowestSampleR*release)+fastest;
				muSpeedAR = muNewSpeedR / muSpeedAR;
			}
			else
			{
				if (fabs(lowestSampleR) > threshold)
				{
					muVaryR = threshold / fabs(lowestSampleR);
					muAttackR = sqrt(fabs(muSpeedBR));
					muCoefficientBR = muCoefficientBR * (muAttackR-1);
					if (muVaryR < threshold)
					{
						muCoefficientBR = muCoefficientBR + threshold;
					}
					else
					{
						muCoefficientBR = muCoefficientBR + muVaryR;
					}
					muCoefficientBR = muCoefficientBR / muAttackR;
				}
				else
				{
					muCoefficientBR = muCoefficientBR * ((muSpeedBR * muSpeedBR)-1.0);
					muCoefficientBR = muCoefficientBR + 1.0;
					muCoefficientBR = muCoefficientBR / (muSpeedBR * muSpeedBR);
				}
				muNewSpeedR = muSpeedBR * (muSpeedBR-1);
				muNewSpeedR = muNewSpeedR + fabs(lowestSampleR*release)+fastest;
				muSpeedBR = muNewSpeedR / muSpeedBR;
			}
			//got coefficients, adjusted speeds for R
			
			long double coefficientL = highGainOffset;
			if (flip) coefficientL += pow(muCoefficientAL,2);
			else coefficientL += pow(muCoefficientBL,2);
			inputSampleL *= coefficientL;
			thickenL = (coefficientL/5)+punchinessL;//0.80;
			thickenL = (1.0-wet)+(wet*thickenL);
			
			long double coefficientR = highGainOffset;
			if (flip) coefficientR += pow(muCoefficientAR,2);
			else coefficientR += pow(muCoefficientBR,2);
			inputSampleR *= coefficientR;
			thickenR = (coefficientR/5)+punchinessR;//0.80;
			thickenR = (1.0-wet)+(wet*thickenR);
			//applied compression with vari-vari-µ-µ-µ-µ-µ-µ-is-the-kitten-song o/~
			//applied gain correction to control output level- tends to constrain sound rather than inflate it
			
			long double bridgerectifier = fabs(inputSampleL);
			if (bridgerectifier > 1.2533141373155) bridgerectifier = 1.2533141373155;
			bridgerectifier = sin(bridgerectifier * fabs(bridgerectifier)) / ((fabs(bridgerectifier) == 0.0) ?1:fabs(bridgerectifier));
			//using Spiral instead of Density algorithm
			if (inputSampleL > 0) inputSampleL = (inputSampleL*coefficientL)+(bridgerectifier*(1-coefficientL));
			else inputSampleL = (inputSampleL*coefficientL)-(bridgerectifier*(1-coefficientL));
			//second stage of overdrive to prevent overs and allow bloody loud extremeness
			
			bridgerectifier = fabs(inputSampleR);
			if (bridgerectifier > 1.2533141373155) bridgerectifier = 1.2533141373155;
			bridgerectifier = sin(bridgerectifier * fabs(bridgerectifier)) / ((fabs(bridgerectifier) == 0.0) ?1:fabs(bridgerectifier));
			//using Spiral instead of Density algorithm
			if (inputSampleR > 0) inputSampleR = (inputSampleR*coefficientR)+(bridgerectifier*(1-coefficientR));
			else inputSampleR = (inputSampleR*coefficientR)-(bridgerectifier*(1-coefficientR));
			//second stage of overdrive to prevent overs and allow bloody loud extremeness
			
			flip = !flip;
			
			if (output < 1.0) {inputSampleL *= output;inputSampleR *= output;}
			if (wet<1.0) {
				inputSampleL = (drySampleL*(1.0-wet))+(inputSampleL*wet);
				inputSampleR = (drySampleR*(1.0-wet))+(inputSampleR*wet);
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
	
	double muVaryL;
	double muAttackL;
	double muNewSpeedL;
	double muSpeedAL;
	double muSpeedBL;
	double muCoefficientAL;
	double muCoefficientBL;
	long double thickenL;
	long double previousL;
	long double previous2L;
	long double previous3L;
	long double previous4L;
	long double previous5L;
	double dL[10001];
	
	double muVaryR;
	double muAttackR;
	double muNewSpeedR;
	double muSpeedAR;
	double muSpeedBR;
	double muCoefficientAR;
	double muCoefficientBR;
	long double thickenR;
	long double previousR;
	long double previous2R;
	long double previous3R;
	long double previous4R;
	long double previous5R;
	double dR[10001];
	
	int delay;
	bool flip;	

};
MIN_EXTERNAL(pop);

