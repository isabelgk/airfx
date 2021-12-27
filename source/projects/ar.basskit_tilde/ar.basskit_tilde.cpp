#include "c74_min.h"

using namespace c74::min;

class basskit : public object<basskit>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a centered bass reinforcement with subs fill. Clean and controllable."};
	MIN_TAGS {"saturation, bass"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "drive", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "voicing", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "bass", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "sub", 0.5, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.5;
			B = 0.5;
			C = 0.5;
			D = 0.5;
			
			WasNegative = false;
			SubOctave = false;
			flip = false;
			bflip = 0;
			iirDriveSampleA = 0.0;
			iirDriveSampleB = 0.0;
			iirDriveSampleC = 0.0;
			iirDriveSampleD = 0.0;
			iirDriveSampleE = 0.0;
			iirDriveSampleF = 0.0;
			
			iirHeadBumpA = 0.0;
			iirHeadBumpB = 0.0;
			iirHeadBumpC = 0.0;
			
			iirSubBumpA = 0.0;
			iirSubBumpB = 0.0;
			iirSubBumpC = 0.0;
			
			lastHeadBump = 0.0;
			lastSubBump = 0.0;
			
			iirSampleA = 0.0;
			iirSampleB = 0.0;
			iirSampleC = 0.0;
			iirSampleD = 0.0;
			iirSampleE = 0.0;
			iirSampleF = 0.0;
			iirSampleG = 0.0;
			iirSampleH = 0.0;
			iirSampleI = 0.0;
			iirSampleJ = 0.0;
			iirSampleK = 0.0;
			iirSampleL = 0.0;
			iirSampleM = 0.0;
			iirSampleN = 0.0;
			iirSampleO = 0.0;
			iirSampleP = 0.0;
			iirSampleQ = 0.0;
			iirSampleR = 0.0;
			iirSampleS = 0.0;
			iirSampleT = 0.0;
			iirSampleU = 0.0;
			iirSampleV = 0.0;
			iirSampleW = 0.0;
			iirSampleX = 0.0;
			iirSampleY = 0.0;
			iirSampleZ = 0.0;	
			
			oscGate = 1.0;
				
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
		double overallscale = 1.0;
		overallscale /= 44100.0;
		overallscale *= samplerate();

		long sampleFrames = _input.frame_count();

		double ataLowpass;
		double randy;
		double invrandy;
		double HeadBump = 0.0;
		double BassGain = A * 0.1;
		double HeadBumpFreq = ((B*0.1)+0.02)/overallscale;
		double iirAmount = HeadBumpFreq/44.1;
		double BassOutGain = ((C*2.0)-1.0)*fabs(((C*2.0)-1.0));
		double SubBump = 0.0;
		double SubOutGain = ((D*2.0)-1.0)*fabs(((D*2.0)-1.0))*4.0;
		double clamp = 0.0;
		double fuzz = 0.111;
			
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
			
			ataLowpass = (inputSampleL + inputSampleR) / 2.0;
			iirDriveSampleA = (iirDriveSampleA * (1.0 - HeadBumpFreq)) + (ataLowpass * HeadBumpFreq); ataLowpass = iirDriveSampleA;
			iirDriveSampleB = (iirDriveSampleB * (1.0 - HeadBumpFreq)) + (ataLowpass * HeadBumpFreq); ataLowpass = iirDriveSampleB;
			
			
			oscGate += fabs(ataLowpass * 10.0);
			oscGate -= 0.001;
			if (oscGate > 1.0) oscGate = 1.0;
			if (oscGate < 0) oscGate = 0;
			//got a value that only goes down low when there's silence or near silence on input
			clamp = 1.0-oscGate;
			clamp *= 0.00001;
			//set up the thing to choke off oscillations- belt and suspenders affair
			
			if (ataLowpass > 0)
			{if (WasNegative){SubOctave = !SubOctave;} WasNegative = false;}
			else {WasNegative = true;}
			//set up polarities for sub-bass version
			randy = (rand()/(double)RAND_MAX)*fuzz; //0 to 1 the noise, may not be needed
			invrandy = (1.0-randy);
			randy /= 2.0;
			//set up the noise
			
			iirSampleA = (iirSampleA * (1.0 - iirAmount)) + (ataLowpass * iirAmount); ataLowpass -= iirSampleA;
			iirSampleB = (iirSampleB * (1.0 - iirAmount)) + (ataLowpass * iirAmount); ataLowpass -= iirSampleB;
			iirSampleC = (iirSampleC * (1.0 - iirAmount)) + (ataLowpass * iirAmount); ataLowpass -= iirSampleC;
			iirSampleD = (iirSampleD * (1.0 - iirAmount)) + (ataLowpass * iirAmount); ataLowpass -= iirSampleD;
			iirSampleE = (iirSampleE * (1.0 - iirAmount)) + (ataLowpass * iirAmount); ataLowpass -= iirSampleE;
			iirSampleF = (iirSampleF * (1.0 - iirAmount)) + (ataLowpass * iirAmount); ataLowpass -= iirSampleF;
			iirSampleG = (iirSampleG * (1.0 - iirAmount)) + (ataLowpass * iirAmount); ataLowpass -= iirSampleG;
			iirSampleH = (iirSampleH * (1.0 - iirAmount)) + (ataLowpass * iirAmount); ataLowpass -= iirSampleH;
			iirSampleI = (iirSampleI * (1.0 - iirAmount)) + (ataLowpass * iirAmount); ataLowpass -= iirSampleI;
			iirSampleJ = (iirSampleJ * (1.0 - iirAmount)) + (ataLowpass * iirAmount); ataLowpass -= iirSampleJ;
			iirSampleK = (iirSampleK * (1.0 - iirAmount)) + (ataLowpass * iirAmount); ataLowpass -= iirSampleK;
			iirSampleL = (iirSampleL * (1.0 - iirAmount)) + (ataLowpass * iirAmount); ataLowpass -= iirSampleL;
			iirSampleM = (iirSampleM * (1.0 - iirAmount)) + (ataLowpass * iirAmount); ataLowpass -= iirSampleM;
			iirSampleN = (iirSampleN * (1.0 - iirAmount)) + (ataLowpass * iirAmount); ataLowpass -= iirSampleN;
			iirSampleO = (iirSampleO * (1.0 - iirAmount)) + (ataLowpass * iirAmount); ataLowpass -= iirSampleO;
			iirSampleP = (iirSampleP * (1.0 - iirAmount)) + (ataLowpass * iirAmount); ataLowpass -= iirSampleP;
			iirSampleQ = (iirSampleQ * (1.0 - iirAmount)) + (ataLowpass * iirAmount); ataLowpass -= iirSampleQ;
			iirSampleR = (iirSampleR * (1.0 - iirAmount)) + (ataLowpass * iirAmount); ataLowpass -= iirSampleR;
			iirSampleS = (iirSampleS * (1.0 - iirAmount)) + (ataLowpass * iirAmount); ataLowpass -= iirSampleS;
			iirSampleT = (iirSampleT * (1.0 - iirAmount)) + (ataLowpass * iirAmount); ataLowpass -= iirSampleT;
			iirSampleU = (iirSampleU * (1.0 - iirAmount)) + (ataLowpass * iirAmount); ataLowpass -= iirSampleU;
			iirSampleV = (iirSampleV * (1.0 - iirAmount)) + (ataLowpass * iirAmount); ataLowpass -= iirSampleV;
			
			switch (bflip)
			{
				case 1:				
					iirHeadBumpA += (ataLowpass * BassGain);
					iirHeadBumpA -= (iirHeadBumpA * iirHeadBumpA * iirHeadBumpA * HeadBumpFreq);
					iirHeadBumpA = (invrandy * iirHeadBumpA) + (randy * iirHeadBumpB) + (randy * iirHeadBumpC);
					if (iirHeadBumpA > 0) iirHeadBumpA -= clamp;
					if (iirHeadBumpA < 0) iirHeadBumpA += clamp;
					HeadBump = iirHeadBumpA;
					break;
				case 2:
					iirHeadBumpB += (ataLowpass * BassGain);
					iirHeadBumpB -= (iirHeadBumpB * iirHeadBumpB * iirHeadBumpB * HeadBumpFreq);
					iirHeadBumpB = (randy * iirHeadBumpA) + (invrandy * iirHeadBumpB) + (randy * iirHeadBumpC);
					if (iirHeadBumpB > 0) iirHeadBumpB -= clamp;
					if (iirHeadBumpB < 0) iirHeadBumpB += clamp;
					HeadBump = iirHeadBumpB;
					break;
				case 3:
					iirHeadBumpC += (ataLowpass * BassGain);
					iirHeadBumpC -= (iirHeadBumpC * iirHeadBumpC * iirHeadBumpC * HeadBumpFreq);
					iirHeadBumpC = (randy * iirHeadBumpA) + (randy * iirHeadBumpB) + (invrandy * iirHeadBumpC);
					if (iirHeadBumpC > 0) iirHeadBumpC -= clamp;
					if (iirHeadBumpC < 0) iirHeadBumpC += clamp;
					HeadBump = iirHeadBumpC;
					break;
			}
			
			iirSampleW = (iirSampleW * (1.0 - iirAmount)) + (HeadBump * iirAmount); HeadBump -= iirSampleW;
			iirSampleX = (iirSampleX * (1.0 - iirAmount)) + (HeadBump * iirAmount); HeadBump -= iirSampleX;
			
			SubBump = HeadBump;
			iirSampleY = (iirSampleY * (1.0 - iirAmount)) + (SubBump * iirAmount); SubBump -= iirSampleY;
			
			iirDriveSampleC = (iirDriveSampleC * (1.0 - HeadBumpFreq)) + (SubBump * HeadBumpFreq); SubBump = iirDriveSampleC;
			iirDriveSampleD = (iirDriveSampleD * (1.0 - HeadBumpFreq)) + (SubBump * HeadBumpFreq); SubBump = iirDriveSampleD;
			
			
			SubBump = fabs(SubBump);
			if (SubOctave == false) {SubBump = -SubBump;}
			
			switch (bflip)
			{
				case 1:				
					iirSubBumpA += SubBump;// * BassGain);
					iirSubBumpA -= (iirSubBumpA * iirSubBumpA * iirSubBumpA * HeadBumpFreq);
					iirSubBumpA = (invrandy * iirSubBumpA) + (randy * iirSubBumpB) + (randy * iirSubBumpC);
					if (iirSubBumpA > 0) iirSubBumpA -= clamp;
					if (iirSubBumpA < 0) iirSubBumpA += clamp;
					SubBump = iirSubBumpA;
					break;
				case 2:
					iirSubBumpB += SubBump;// * BassGain);
					iirSubBumpB -= (iirSubBumpB * iirSubBumpB * iirSubBumpB * HeadBumpFreq);
					iirSubBumpB = (randy * iirSubBumpA) + (invrandy * iirSubBumpB) + (randy * iirSubBumpC);
					if (iirSubBumpB > 0) iirSubBumpB -= clamp;
					if (iirSubBumpB < 0) iirSubBumpB += clamp;
					SubBump = iirSubBumpB;
					break;
				case 3:
					iirSubBumpC += SubBump;// * BassGain);
					iirSubBumpC -= (iirSubBumpC * iirSubBumpC * iirSubBumpC * HeadBumpFreq);
					iirSubBumpC = (randy * iirSubBumpA) + (randy * iirSubBumpB) + (invrandy * iirSubBumpC);
					if (iirSubBumpC > 0) iirSubBumpC -= clamp;
					if (iirSubBumpC < 0) iirSubBumpC += clamp;
					SubBump = iirSubBumpC;
					break;
			}
			
			iirSampleZ = (iirSampleZ * (1.0 - HeadBumpFreq)) + (SubBump * HeadBumpFreq); SubBump = iirSampleZ;
			iirDriveSampleE = (iirDriveSampleE * (1.0 - iirAmount)) + (SubBump * iirAmount); SubBump = iirDriveSampleE;
			iirDriveSampleF = (iirDriveSampleF * (1.0 - iirAmount)) + (SubBump * iirAmount); SubBump = iirDriveSampleF;
			
			
			inputSampleL += (HeadBump * BassOutGain);
			inputSampleL += (SubBump * SubOutGain);
			
			inputSampleR += (HeadBump * BassOutGain);
			inputSampleR += (SubBump * SubOutGain);
			
			
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
   
	double iirDriveSampleA;
	double iirDriveSampleB;
	double iirDriveSampleC;
	double iirDriveSampleD;
	double iirDriveSampleE;
	double iirDriveSampleF;
	bool flip; //drive things
	
	int bflip;
	bool WasNegative;
	bool SubOctave;
	double iirHeadBumpA;
	double iirHeadBumpB;
	double iirHeadBumpC;
	
	double iirSubBumpA;
	double iirSubBumpB;
	double iirSubBumpC;
	
	double lastHeadBump;
	double lastSubBump;
	
	double iirSampleA;
	double iirSampleB;
	double iirSampleC;
	double iirSampleD;
	double iirSampleE;
	double iirSampleF;
	double iirSampleG;
	double iirSampleH;
	double iirSampleI;
	double iirSampleJ;
	double iirSampleK;
	double iirSampleL;
	double iirSampleM;
	double iirSampleN;
	double iirSampleO;
	double iirSampleP;
	double iirSampleQ;
	double iirSampleR;
	double iirSampleS;
	double iirSampleT;
	double iirSampleU;
	double iirSampleV;
	double iirSampleW;
	double iirSampleX;
	double iirSampleY;
	double iirSampleZ;		
	double oscGate;	
	
	long double fpNShapeL;
	long double fpNShapeR;
	//default stuff

};
MIN_EXTERNAL(basskit);

