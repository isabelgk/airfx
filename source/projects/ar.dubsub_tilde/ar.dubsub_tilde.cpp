#include "c74_min.h"

using namespace c74::min;

class dubsub : public object<dubsub>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a fully featured bass doctor"};
	MIN_TAGS {"audio, effect"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "TGrind", 0.9, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "Grd/Out", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "XOver", 0.74, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "BsDrive", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> E {this, "BsVoice", 0.95, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> F {this, "BassOut", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> G {this, "SbDrive", 0.2, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> H {this, "SbVoice", 0.2, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> I {this, "SubOut", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> J {this, "Dry/Wet", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.9;
			B = 0.5;
			C = 0.74;
			D = 1.0;
			E = 0.95;
			F = 0.5;
			G = 0.2;
			H = 0.2;
			I = 0.5;
			J = 1.0;
			
			WasNegativeL = false;
			SubOctaveL = false;
			WasNegativeR = false;
			SubOctaveR = false;
			flip = false;
			bflip = 0;
			
			iirDriveSampleAL = 0.0;
			iirDriveSampleBL = 0.0;
			iirDriveSampleCL = 0.0;
			iirDriveSampleDL = 0.0;
			iirDriveSampleEL = 0.0;
			iirDriveSampleFL = 0.0;
			iirDriveSampleAR = 0.0;
			iirDriveSampleBR = 0.0;
			iirDriveSampleCR = 0.0;
			iirDriveSampleDR = 0.0;
			iirDriveSampleER = 0.0;
			iirDriveSampleFR = 0.0;
			
			iirHeadBumpAL = 0.0;
			iirHeadBumpBL = 0.0;
			iirHeadBumpCL = 0.0;
			iirHeadBumpAR = 0.0;
			iirHeadBumpBR = 0.0;
			iirHeadBumpCR = 0.0;
			
			iirSubBumpAL = 0.0;
			iirSubBumpBL = 0.0;
			iirSubBumpCL = 0.0;
			iirSubBumpAR = 0.0;
			iirSubBumpBR = 0.0;
			iirSubBumpCR = 0.0;
			
			lastHeadBumpL = 0.0;
			lastSubBumpL = 0.0;
			lastHeadBumpR = 0.0;
			lastSubBumpR = 0.0;
			
			iirSampleAL = 0.0;
			iirSampleBL = 0.0;
			iirSampleCL = 0.0;
			iirSampleDL = 0.0;
			iirSampleEL = 0.0;
			iirSampleFL = 0.0;
			iirSampleGL = 0.0;
			iirSampleHL = 0.0;
			iirSampleIL = 0.0;
			iirSampleJL = 0.0;
			iirSampleKL = 0.0;
			iirSampleLL = 0.0;
			iirSampleML = 0.0;
			iirSampleNL = 0.0;
			iirSampleOL = 0.0;
			iirSamplePL = 0.0;
			iirSampleQL = 0.0;
			iirSampleRL = 0.0;
			iirSampleSL = 0.0;
			iirSampleTL = 0.0;
			iirSampleUL = 0.0;
			iirSampleVL = 0.0;
			iirSampleWL = 0.0;
			iirSampleXL = 0.0;
			iirSampleYL = 0.0;
			iirSampleZL = 0.0;	
			iirSampleAR = 0.0;
			iirSampleBR = 0.0;
			iirSampleCR = 0.0;
			iirSampleDR = 0.0;
			iirSampleER = 0.0;
			iirSampleFR = 0.0;
			iirSampleGR = 0.0;
			iirSampleHR = 0.0;
			iirSampleIR = 0.0;
			iirSampleJR = 0.0;
			iirSampleKR = 0.0;
			iirSampleLR = 0.0;
			iirSampleMR = 0.0;
			iirSampleNR = 0.0;
			iirSampleOR = 0.0;
			iirSamplePR = 0.0;
			iirSampleQR = 0.0;
			iirSampleRR = 0.0;
			iirSampleSR = 0.0;
			iirSampleTR = 0.0;
			iirSampleUR = 0.0;
			iirSampleVR = 0.0;
			iirSampleWR = 0.0;
			iirSampleXR = 0.0;
			iirSampleYR = 0.0;
			iirSampleZR = 0.0;	
			
			oscGateL = 1.0;
			oscGateR = 1.0;	
			
			fpNShapeL = 0.0;
			fpNShapeR = 0.0;
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
		
		double driveone = pow(A*3.0,2);
		double driveoutput = pow(B,2);
		double iirAmount = ((C*0.33)+0.1)/overallscale;
		double ataLowpassL;
		double ataLowpassR;
		double randyL;
		double invrandyL;
		double randyR;
		double invrandyR;
		double HeadBumpL = 0.0;
		double HeadBumpR = 0.0;
		double BassGain = D * 0.1;
		double HeadBumpFreq = ((E*0.1)+0.0001)/overallscale;
		double iirBmount = HeadBumpFreq/44.1;
		double altBmount = 1.0 - iirBmount;
		double BassOutGain = pow(F,2) * 0.5;
		double SubBumpL = 0.0;
		double SubBumpR = 0.0;
		double SubGain = G * 0.1;
		double SubBumpFreq = ((H*0.1)+0.0001)/overallscale;
		double iirCmount = SubBumpFreq/44.1;
		double altCmount = 1.0 - iirCmount;
		double SubOutGain = pow(I,2) * 0.45;
		double clampL = 0.0;
		double clampR = 0.0;
		double out;
		double fuzz = 0.111;
		double wet = J;
		double dry = 1.0-wet;
		double glitch = 0.60;
		double tempSampleL;
		double tempSampleR;
		
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
			//effectively digital black, we'll subtract it aDubSub. We want a 'air' hiss
			double drySampleL = inputSampleL;
			double drySampleR = inputSampleR;
			
			// here's the plan.
			// Grind Boost
			// Grind Output Level
			// Bass Split Freq
			// Bass Drive
			// Bass Voicing
			// Bass Output Level
			// Sub Oct Drive
			// Sub Voicing
			// Sub Output Level
			// Dry/Wet
			
			oscGateL += fabs(inputSampleL * 10.0);
			oscGateL -= 0.001;
			if (oscGateL > 1.0) oscGateL = 1.0;
			if (oscGateL < 0) oscGateL = 0;
			oscGateR += fabs(inputSampleR * 10.0);
			oscGateR -= 0.001;
			if (oscGateR > 1.0) oscGateR = 1.0;
			if (oscGateR < 0) oscGateR = 0;
			//got a value that only goes down low when there's silence or _near silence on input
			clampL = 1.0-oscGateL;
			clampL *= 0.00001;
			clampR = 1.0-oscGateR;
			clampR *= 0.00001;
			//set up the thing to choke off oscillations- belt and suspenders affair
			
			if (flip)
			{
				tempSampleL = inputSampleL;
				iirDriveSampleAL = (iirDriveSampleAL * (1 - iirAmount)) + (inputSampleL * iirAmount);
				inputSampleL -= iirDriveSampleAL;
				iirDriveSampleCL = (iirDriveSampleCL * (1 - iirAmount)) + (inputSampleL * iirAmount);
				inputSampleL -= iirDriveSampleCL;
				iirDriveSampleEL = (iirDriveSampleEL * (1 - iirAmount)) + (inputSampleL * iirAmount);
				inputSampleL -= iirDriveSampleEL;
				ataLowpassL = tempSampleL - inputSampleL;
				
				tempSampleR = inputSampleR;
				iirDriveSampleAR = (iirDriveSampleAR * (1 - iirAmount)) + (inputSampleR * iirAmount);
				inputSampleR -= iirDriveSampleAR;
				iirDriveSampleCR = (iirDriveSampleCR * (1 - iirAmount)) + (inputSampleR * iirAmount);
				inputSampleR -= iirDriveSampleCR;
				iirDriveSampleER = (iirDriveSampleER * (1 - iirAmount)) + (inputSampleR * iirAmount);
				inputSampleR -= iirDriveSampleER;
				ataLowpassR = tempSampleR - inputSampleR;
			}
			else
			{
				tempSampleL = inputSampleL;
				iirDriveSampleBL = (iirDriveSampleBL * (1 - iirAmount)) + (inputSampleL * iirAmount);
				inputSampleL -= iirDriveSampleBL;
				iirDriveSampleDL = (iirDriveSampleDL * (1 - iirAmount)) + (inputSampleL * iirAmount);
				inputSampleL -= iirDriveSampleDL;
				iirDriveSampleFL = (iirDriveSampleFL * (1 - iirAmount)) + (inputSampleL * iirAmount);
				inputSampleL -= iirDriveSampleFL;
				ataLowpassL = tempSampleL - inputSampleL;
				
				tempSampleR = inputSampleR;
				iirDriveSampleBR = (iirDriveSampleBR * (1 - iirAmount)) + (inputSampleR * iirAmount);
				inputSampleR -= iirDriveSampleBR;
				iirDriveSampleDR = (iirDriveSampleDR * (1 - iirAmount)) + (inputSampleR * iirAmount);
				inputSampleR -= iirDriveSampleDR;
				iirDriveSampleFR = (iirDriveSampleFR * (1 - iirAmount)) + (inputSampleR * iirAmount);
				inputSampleR -= iirDriveSampleFR;
				ataLowpassR = tempSampleR - inputSampleR;
			}
			//highpass section
			if (inputSampleL > 1.0) {inputSampleL = 1.0;}
			if (inputSampleL < -1.0) {inputSampleL = -1.0;}
			if (inputSampleR > 1.0) {inputSampleR = 1.0;}
			if (inputSampleR < -1.0) {inputSampleR = -1.0;}
			
			out = driveone;
			while (out > glitch)
			{
				out -= glitch;
				inputSampleL -= (inputSampleL * (fabs(inputSampleL) * glitch) * (fabs(inputSampleL) * glitch) );
				inputSampleR -= (inputSampleR * (fabs(inputSampleR) * glitch) * (fabs(inputSampleR) * glitch) );
				inputSampleL *= (1.0+glitch);
				inputSampleR *= (1.0+glitch);
			}
			//that's taken care of the really high gain stuff
			
			inputSampleL -= (inputSampleL * (fabs(inputSampleL) * out) * (fabs(inputSampleL) * out) );
			inputSampleR -= (inputSampleR * (fabs(inputSampleR) * out) * (fabs(inputSampleR) * out) );
			inputSampleL *= (1.0+out);
			inputSampleR *= (1.0+out);
			
			if (ataLowpassL > 0)
			{if (WasNegativeL){SubOctaveL = !SubOctaveL;} WasNegativeL = false;}
			else {WasNegativeL = true;}
			
			if (ataLowpassR > 0)
			{if (WasNegativeR){SubOctaveR = !SubOctaveR;} WasNegativeR = false;}
			else {WasNegativeR = true;}
			//set up polarities for sub-bass version
			
			randyL = (rand()/(double)RAND_MAX)*fuzz; //0 to 1 the noise, may not be needed
			invrandyL = (1.0-randyL);
			randyL /= 2.0;
			
			randyR = (rand()/(double)RAND_MAX)*fuzz; //0 to 1 the noise, may not be needed
			invrandyR = (1.0-randyR);
			randyR /= 2.0;
			//set up the noise
			
			iirSampleAL = (iirSampleAL * altBmount) + (ataLowpassL * iirBmount); ataLowpassL -= iirSampleAL;
			iirSampleBL = (iirSampleBL * altBmount) + (ataLowpassL * iirBmount); ataLowpassL -= iirSampleBL;
			iirSampleCL = (iirSampleCL * altBmount) + (ataLowpassL * iirBmount); ataLowpassL -= iirSampleCL;
			iirSampleDL = (iirSampleDL * altBmount) + (ataLowpassL * iirBmount); ataLowpassL -= iirSampleDL;
			iirSampleEL = (iirSampleEL * altBmount) + (ataLowpassL * iirBmount); ataLowpassL -= iirSampleEL;
			iirSampleFL = (iirSampleFL * altBmount) + (ataLowpassL * iirBmount); ataLowpassL -= iirSampleFL;
			iirSampleGL = (iirSampleGL * altBmount) + (ataLowpassL * iirBmount); ataLowpassL -= iirSampleGL;
			iirSampleHL = (iirSampleHL * altBmount) + (ataLowpassL * iirBmount); ataLowpassL -= iirSampleHL;
			iirSampleIL = (iirSampleIL * altBmount) + (ataLowpassL * iirBmount); ataLowpassL -= iirSampleIL;
			iirSampleJL = (iirSampleJL * altBmount) + (ataLowpassL * iirBmount); ataLowpassL -= iirSampleJL;
			iirSampleKL = (iirSampleKL * altBmount) + (ataLowpassL * iirBmount); ataLowpassL -= iirSampleKL;
			iirSampleLL = (iirSampleLL * altBmount) + (ataLowpassL * iirBmount); ataLowpassL -= iirSampleLL;
			iirSampleML = (iirSampleML * altBmount) + (ataLowpassL * iirBmount); ataLowpassL -= iirSampleML;
			iirSampleNL = (iirSampleNL * altBmount) + (ataLowpassL * iirBmount); ataLowpassL -= iirSampleNL;
			iirSampleOL = (iirSampleOL * altBmount) + (ataLowpassL * iirBmount); ataLowpassL -= iirSampleOL;
			iirSamplePL = (iirSamplePL * altBmount) + (ataLowpassL * iirBmount); ataLowpassL -= iirSamplePL;
			iirSampleQL = (iirSampleQL * altBmount) + (ataLowpassL * iirBmount); ataLowpassL -= iirSampleQL;
			iirSampleRL = (iirSampleRL * altBmount) + (ataLowpassL * iirBmount); ataLowpassL -= iirSampleRL;
			iirSampleSL = (iirSampleSL * altBmount) + (ataLowpassL * iirBmount); ataLowpassL -= iirSampleSL;
			iirSampleTL = (iirSampleTL * altBmount) + (ataLowpassL * iirBmount); ataLowpassL -= iirSampleTL;
			iirSampleUL = (iirSampleUL * altBmount) + (ataLowpassL * iirBmount); ataLowpassL -= iirSampleUL;
			iirSampleVL = (iirSampleVL * altBmount) + (ataLowpassL * iirBmount); ataLowpassL -= iirSampleVL;
			
			iirSampleAR = (iirSampleAR * altBmount) + (ataLowpassR * iirBmount); ataLowpassR -= iirSampleAR;
			iirSampleBR = (iirSampleBR * altBmount) + (ataLowpassR * iirBmount); ataLowpassR -= iirSampleBR;
			iirSampleCR = (iirSampleCR * altBmount) + (ataLowpassR * iirBmount); ataLowpassR -= iirSampleCR;
			iirSampleDR = (iirSampleDR * altBmount) + (ataLowpassR * iirBmount); ataLowpassR -= iirSampleDR;
			iirSampleER = (iirSampleER * altBmount) + (ataLowpassR * iirBmount); ataLowpassR -= iirSampleER;
			iirSampleFR = (iirSampleFR * altBmount) + (ataLowpassR * iirBmount); ataLowpassR -= iirSampleFR;
			iirSampleGR = (iirSampleGR * altBmount) + (ataLowpassR * iirBmount); ataLowpassR -= iirSampleGR;
			iirSampleHR = (iirSampleHR * altBmount) + (ataLowpassR * iirBmount); ataLowpassR -= iirSampleHR;
			iirSampleIR = (iirSampleIR * altBmount) + (ataLowpassR * iirBmount); ataLowpassR -= iirSampleIR;
			iirSampleJR = (iirSampleJR * altBmount) + (ataLowpassR * iirBmount); ataLowpassR -= iirSampleJR;
			iirSampleKR = (iirSampleKR * altBmount) + (ataLowpassR * iirBmount); ataLowpassR -= iirSampleKR;
			iirSampleLR = (iirSampleLR * altBmount) + (ataLowpassR * iirBmount); ataLowpassR -= iirSampleLR;
			iirSampleMR = (iirSampleMR * altBmount) + (ataLowpassR * iirBmount); ataLowpassR -= iirSampleMR;
			iirSampleNR = (iirSampleNR * altBmount) + (ataLowpassR * iirBmount); ataLowpassR -= iirSampleNR;
			iirSampleOR = (iirSampleOR * altBmount) + (ataLowpassR * iirBmount); ataLowpassR -= iirSampleOR;
			iirSamplePR = (iirSamplePR * altBmount) + (ataLowpassR * iirBmount); ataLowpassR -= iirSamplePR;
			iirSampleQR = (iirSampleQR * altBmount) + (ataLowpassR * iirBmount); ataLowpassR -= iirSampleQR;
			iirSampleRR = (iirSampleRR * altBmount) + (ataLowpassR * iirBmount); ataLowpassR -= iirSampleRR;
			iirSampleSR = (iirSampleSR * altBmount) + (ataLowpassR * iirBmount); ataLowpassR -= iirSampleSR;
			iirSampleTR = (iirSampleTR * altBmount) + (ataLowpassR * iirBmount); ataLowpassR -= iirSampleTR;
			iirSampleUR = (iirSampleUR * altBmount) + (ataLowpassR * iirBmount); ataLowpassR -= iirSampleUR;
			iirSampleVR = (iirSampleVR * altBmount) + (ataLowpassR * iirBmount); ataLowpassR -= iirSampleVR;
			
			switch (bflip)
			{
				case 1:				
					iirHeadBumpAL += (ataLowpassL * BassGain);
					iirHeadBumpAL -= (iirHeadBumpAL * iirHeadBumpAL * iirHeadBumpAL * HeadBumpFreq);
					iirHeadBumpAL = (invrandyL * iirHeadBumpAL) + (randyL * iirHeadBumpBL) + (randyL * iirHeadBumpCL);
					if (iirHeadBumpAL > 0) iirHeadBumpAL -= clampL;
					if (iirHeadBumpAL < 0) iirHeadBumpAL += clampL;
					HeadBumpL = iirHeadBumpAL;
					
					iirHeadBumpAR += (ataLowpassR * BassGain);
					iirHeadBumpAR -= (iirHeadBumpAR * iirHeadBumpAR * iirHeadBumpAR * HeadBumpFreq);
					iirHeadBumpAR = (invrandyR * iirHeadBumpAR) + (randyR * iirHeadBumpBR) + (randyR * iirHeadBumpCR);
					if (iirHeadBumpAR > 0) iirHeadBumpAR -= clampR;
					if (iirHeadBumpAR < 0) iirHeadBumpAR += clampR;
					HeadBumpR = iirHeadBumpAR;
					break;
				case 2:
					iirHeadBumpBL += (ataLowpassL * BassGain);
					iirHeadBumpBL -= (iirHeadBumpBL * iirHeadBumpBL * iirHeadBumpBL * HeadBumpFreq);
					iirHeadBumpBL = (randyL * iirHeadBumpAL) + (invrandyL * iirHeadBumpBL) + (randyL * iirHeadBumpCL);
					if (iirHeadBumpBL > 0) iirHeadBumpBL -= clampL;
					if (iirHeadBumpBL < 0) iirHeadBumpBL += clampL;
					HeadBumpL = iirHeadBumpBL;
					
					iirHeadBumpBR += (ataLowpassR * BassGain);
					iirHeadBumpBR -= (iirHeadBumpBR * iirHeadBumpBR * iirHeadBumpBR * HeadBumpFreq);
					iirHeadBumpBR = (randyR * iirHeadBumpAR) + (invrandyR * iirHeadBumpBR) + (randyR * iirHeadBumpCR);
					if (iirHeadBumpBR > 0) iirHeadBumpBR -= clampR;
					if (iirHeadBumpBR < 0) iirHeadBumpBR += clampR;
					HeadBumpR = iirHeadBumpBR;
					break;
				case 3:
					iirHeadBumpCL += (ataLowpassL * BassGain);
					iirHeadBumpCL -= (iirHeadBumpCL * iirHeadBumpCL * iirHeadBumpCL * HeadBumpFreq);
					iirHeadBumpCL = (randyL * iirHeadBumpAL) + (randyL * iirHeadBumpBL) + (invrandyL * iirHeadBumpCL);
					if (iirHeadBumpCL > 0) iirHeadBumpCL -= clampL;
					if (iirHeadBumpCL < 0) iirHeadBumpCL += clampL;
					HeadBumpL = iirHeadBumpCL;
					
					iirHeadBumpCR += (ataLowpassR * BassGain);
					iirHeadBumpCR -= (iirHeadBumpCR * iirHeadBumpCR * iirHeadBumpCR * HeadBumpFreq);
					iirHeadBumpCR = (randyR * iirHeadBumpAR) + (randyR * iirHeadBumpBR) + (invrandyR * iirHeadBumpCR);
					if (iirHeadBumpCR > 0) iirHeadBumpCR -= clampR;
					if (iirHeadBumpCR < 0) iirHeadBumpCR += clampR;
					HeadBumpR = iirHeadBumpCR;
					break;
			}
			
			iirSampleWL = (iirSampleWL * altBmount) + (HeadBumpL * iirBmount); HeadBumpL -= iirSampleWL;
			iirSampleXL = (iirSampleXL * altBmount) + (HeadBumpL * iirBmount); HeadBumpL -= iirSampleXL;
			
			iirSampleWR = (iirSampleWR * altBmount) + (HeadBumpR * iirBmount); HeadBumpR -= iirSampleWR;
			iirSampleXR = (iirSampleXR * altBmount) + (HeadBumpR * iirBmount); HeadBumpR -= iirSampleXR;
			
			SubBumpL = HeadBumpL;
			iirSampleYL = (iirSampleYL * altCmount) + (SubBumpL * iirCmount); SubBumpL -= iirSampleYL;
			
			SubBumpR = HeadBumpR;
			iirSampleYR = (iirSampleYR * altCmount) + (SubBumpR * iirCmount); SubBumpR -= iirSampleYR;
			
			SubBumpL = fabs(SubBumpL);
			if (SubOctaveL == false) {SubBumpL = -SubBumpL;}
			
			SubBumpR = fabs(SubBumpR);
			if (SubOctaveR == false) {SubBumpR = -SubBumpR;}
			
			switch (bflip)
			{
				case 1:				
					iirSubBumpAL += (SubBumpL * SubGain);
					iirSubBumpAL -= (iirSubBumpAL * iirSubBumpAL * iirSubBumpAL * SubBumpFreq);
					iirSubBumpAL = (invrandyL * iirSubBumpAL) + (randyL * iirSubBumpBL) + (randyL * iirSubBumpCL);
					if (iirSubBumpAL > 0) iirSubBumpAL -= clampL;
					if (iirSubBumpAL < 0) iirSubBumpAL += clampL;
					SubBumpL = iirSubBumpAL;
					
					iirSubBumpAR += (SubBumpR * SubGain);
					iirSubBumpAR -= (iirSubBumpAR * iirSubBumpAR * iirSubBumpAR * SubBumpFreq);
					iirSubBumpAR = (invrandyR * iirSubBumpAR) + (randyR * iirSubBumpBR) + (randyR * iirSubBumpCR);
					if (iirSubBumpAR > 0) iirSubBumpAR -= clampR;
					if (iirSubBumpAR < 0) iirSubBumpAR += clampR;
					SubBumpR = iirSubBumpAR;
					break;
				case 2:
					iirSubBumpBL += (SubBumpL * SubGain);
					iirSubBumpBL -= (iirSubBumpBL * iirSubBumpBL * iirSubBumpBL * SubBumpFreq);
					iirSubBumpBL = (randyL * iirSubBumpAL) + (invrandyL * iirSubBumpBL) + (randyL * iirSubBumpCL);
					if (iirSubBumpBL > 0) iirSubBumpBL -= clampL;
					if (iirSubBumpBL < 0) iirSubBumpBL += clampL;
					SubBumpL = iirSubBumpBL;
					
					iirSubBumpBR += (SubBumpR * SubGain);
					iirSubBumpBR -= (iirSubBumpBR * iirSubBumpBR * iirSubBumpBR * SubBumpFreq);
					iirSubBumpBR = (randyR * iirSubBumpAR) + (invrandyR * iirSubBumpBR) + (randyR * iirSubBumpCR);
					if (iirSubBumpBR > 0) iirSubBumpBR -= clampR;
					if (iirSubBumpBR < 0) iirSubBumpBR += clampR;
					SubBumpR = iirSubBumpBR;
					break;
				case 3:
					iirSubBumpCL += (SubBumpL * SubGain);
					iirSubBumpCL -= (iirSubBumpCL * iirSubBumpCL * iirSubBumpCL * SubBumpFreq);
					iirSubBumpCL = (randyL * iirSubBumpAL) + (randyL * iirSubBumpBL) + (invrandyL * iirSubBumpCL);
					if (iirSubBumpCL > 0) iirSubBumpCL -= clampL;
					if (iirSubBumpCL < 0) iirSubBumpCL += clampL;
					SubBumpL = iirSubBumpCL;
					
					iirSubBumpCR += (SubBumpR * SubGain);
					iirSubBumpCR -= (iirSubBumpCR * iirSubBumpCR * iirSubBumpCR * SubBumpFreq);
					iirSubBumpCR = (randyR * iirSubBumpAR) + (randyR * iirSubBumpBR) + (invrandyR * iirSubBumpCR);
					if (iirSubBumpCR > 0) iirSubBumpCR -= clampR;
					if (iirSubBumpCR < 0) iirSubBumpCR += clampR;
					SubBumpR = iirSubBumpCR;
					break;
			}
			
			iirSampleZL = (iirSampleZL * altCmount) + (SubBumpL * iirCmount); SubBumpL -= iirSampleZL;
			iirSampleZR = (iirSampleZR * altCmount) + (SubBumpR * iirCmount); SubBumpR -= iirSampleZR;
			
			inputSampleL *= driveoutput; //start with the drive section then add lows and subs
			inputSampleR *= driveoutput; //start with the drive section then add lows and subs
			
			inputSampleL += ((HeadBumpL + lastHeadBumpL) * BassOutGain);
			inputSampleL += ((SubBumpL + lastSubBumpL) * SubOutGain);
			
			inputSampleR += ((HeadBumpR + lastHeadBumpR) * BassOutGain);
			inputSampleR += ((SubBumpR + lastSubBumpR) * SubOutGain);
			
			lastHeadBumpL = HeadBumpL;
			lastSubBumpL = SubBumpL;
			lastHeadBumpR = HeadBumpR;
			lastSubBumpR = SubBumpR;
			
			if (wet !=1.0) {
				inputSampleL = (inputSampleL * wet) + (drySampleL * dry);
				inputSampleR = (inputSampleR * wet) + (drySampleR * dry);
			}
			//Dry/Wet control, defaults to the last slider
			
			flip = !flip;
			bflip++;
			if (bflip < 1 || bflip > 3) bflip = 1;
			
			//stereo 64 bit dither, made small and tidy.
			int expon; frexp((double)inputSampleL, &expon);
			long double dither = (rand()/(RAND_MAX*7.737125245533627e+25))*pow(2,expon+62);
			dither /= 536870912.0; //needs this to scale to 64 bit zone
			inputSampleL += (dither-fpNShapeL); fpNShapeL = dither;
			frexp((double)inputSampleR, &expon);
			dither = (rand()/(RAND_MAX*7.737125245533627e+25))*pow(2,expon+62);
			dither /= 536870912.0; //needs this to scale to 64 bit zone
			inputSampleR += (dither-fpNShapeR); fpNShapeR = dither;
			//end 64 bit dither
			
			*out1 = inputSampleL;
			*out2 = inputSampleR;
	
			*in1++;
			*in2++;
			*out1++;
			*out2++;
		}
	}
private:
    
	
private:		
	double iirDriveSampleAL;
	double iirDriveSampleBL;
	double iirDriveSampleCL;
	double iirDriveSampleDL;
	double iirDriveSampleEL;
	double iirDriveSampleFL;
	double iirDriveSampleAR;
	double iirDriveSampleBR;
	double iirDriveSampleCR;
	double iirDriveSampleDR;
	double iirDriveSampleER;
	double iirDriveSampleFR;
	bool flip; //drive things
	
	int bflip;
	bool WasNegativeL;
	bool SubOctaveL;
	bool WasNegativeR;
	bool SubOctaveR;
	
	double iirHeadBumpAL;
	double iirHeadBumpBL;
	double iirHeadBumpCL;
	double iirHeadBumpAR;
	double iirHeadBumpBR;
	double iirHeadBumpCR;
	
	double iirSubBumpAL;
	double iirSubBumpBL;
	double iirSubBumpCL;
	double iirSubBumpAR;
	double iirSubBumpBR;
	double iirSubBumpCR;
	
	double lastHeadBumpL;
	double lastSubBumpL;
	double lastHeadBumpR;
	double lastSubBumpR;
	
	double iirSampleAL;
	double iirSampleBL;
	double iirSampleCL;
	double iirSampleDL;
	double iirSampleEL;
	double iirSampleFL;
	double iirSampleGL;
	double iirSampleHL;
	double iirSampleIL;
	double iirSampleJL;
	double iirSampleKL;
	double iirSampleLL;
	double iirSampleML;
	double iirSampleNL;
	double iirSampleOL;
	double iirSamplePL;
	double iirSampleQL;
	double iirSampleRL;
	double iirSampleSL;
	double iirSampleTL;
	double iirSampleUL;
	double iirSampleVL;
	double iirSampleWL;
	double iirSampleXL;
	double iirSampleYL;
	double iirSampleZL;
	double iirSampleAR;
	double iirSampleBR;
	double iirSampleCR;
	double iirSampleDR;
	double iirSampleER;
	double iirSampleFR;
	double iirSampleGR;
	double iirSampleHR;
	double iirSampleIR;
	double iirSampleJR;
	double iirSampleKR;
	double iirSampleLR;
	double iirSampleMR;
	double iirSampleNR;
	double iirSampleOR;
	double iirSamplePR;
	double iirSampleQR;
	double iirSampleRR;
	double iirSampleSR;
	double iirSampleTR;
	double iirSampleUR;
	double iirSampleVR;
	double iirSampleWR;
	double iirSampleXR;
	double iirSampleYR;
	double iirSampleZR;
	
	double oscGateL;
	double oscGateR;
	
	
	long double fpNShapeL;
	long double fpNShapeR;
	//default stuff

};
MIN_EXTERNAL(dubsub);

