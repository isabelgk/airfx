#include "c74_min.h"

using namespace c74::min;

class bassamp : public object<bassamp>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"gives some bass guitar tones"};
	MIN_TAGS {"saturation"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "high", 0.75, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "dry", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "dub", 0.75, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "sub", 0.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.75;
			B = 0.0;
			C = 0.75;
			D = 0.0;
			
			LataLast6Sample = 0.0;
			LataLast5Sample = 0.0;
			LataLast4Sample = 0.0;
			LataLast3Sample = 0.0;
			LataLast2Sample = 0.0;
			LataLast1Sample = 0.0;
			LataHalfwaySample = 0.0;
			LataHalfDrySample = 0.0;
			LataHalfDiffSample = 0.0;
			LataLastDiffSample = 0.0;
			LataDrySample = 0.0;
			LataDiffSample = 0.0;
			LataPrevDiffSample = 0.0;
			LWasNegative = false;
			LSubOctave = false;
			LiirDriveSampleA = 0.0;
			LiirDriveSampleB = 0.0;
			LiirDriveSampleC = 0.0;
			LiirDriveSampleD = 0.0;
			LiirDriveSampleE = 0.0;
			LiirDriveSampleF = 0.0;
			LiirHeadBumpA = 0.0;
			LiirHeadBumpB = 0.0;
			LiirHeadBumpC = 0.0;
			LiirSubBumpA = 0.0;
			LiirSubBumpB = 0.0;
			LiirSubBumpC = 0.0;
			LiirSampleA = 0.0;
			LiirSampleB = 0.0;
			LiirSampleC = 0.0;
			LiirSampleD = 0.0;
			LiirSampleE = 0.0;
			LiirSampleF = 0.0;
			LiirSampleG = 0.0;
			LiirSampleH = 0.0;
			LiirSampleI = 0.0;
			LiirSampleJ = 0.0;
			LiirSampleK = 0.0;
			LiirSampleL = 0.0;
			LiirSampleM = 0.0;
			LiirSampleN = 0.0;
			LiirSampleO = 0.0;
			LiirSampleP = 0.0;
			LiirSampleQ = 0.0;
			LiirSampleR = 0.0;
			LiirSampleS = 0.0;
			LiirSampleT = 0.0;
			LiirSampleU = 0.0;
			LiirSampleV = 0.0;
			LiirSampleW = 0.0;
			LiirSampleX = 0.0;
			LiirSampleY = 0.0;
			LiirSampleZ = 0.0;	
			
			RataLast6Sample = 0.0;
			RataLast5Sample = 0.0;
			RataLast4Sample = 0.0;
			RataLast3Sample = 0.0;
			RataLast2Sample = 0.0;
			RataLast1Sample = 0.0;
			RataHalfwaySample = 0.0;
			RataHalfDrySample = 0.0;
			RataHalfDiffSample = 0.0;
			RataLastDiffSample = 0.0;
			RataDrySample = 0.0;
			RataDiffSample = 0.0;
			RataPrevDiffSample = 0.0;
			RWasNegative = false;
			RSubOctave = false;
			RiirDriveSampleA = 0.0;
			RiirDriveSampleB = 0.0;
			RiirDriveSampleC = 0.0;
			RiirDriveSampleD = 0.0;
			RiirDriveSampleE = 0.0;
			RiirDriveSampleF = 0.0;
			RiirHeadBumpA = 0.0;
			RiirHeadBumpB = 0.0;
			RiirHeadBumpC = 0.0;
			RiirSubBumpA = 0.0;
			RiirSubBumpB = 0.0;
			RiirSubBumpC = 0.0;
			RiirSampleA = 0.0;
			RiirSampleB = 0.0;
			RiirSampleC = 0.0;
			RiirSampleD = 0.0;
			RiirSampleE = 0.0;
			RiirSampleF = 0.0;
			RiirSampleG = 0.0;
			RiirSampleH = 0.0;
			RiirSampleI = 0.0;
			RiirSampleJ = 0.0;
			RiirSampleK = 0.0;
			RiirSampleL = 0.0;
			RiirSampleM = 0.0;
			RiirSampleN = 0.0;
			RiirSampleO = 0.0;
			RiirSampleP = 0.0;
			RiirSampleQ = 0.0;
			RiirSampleR = 0.0;
			RiirSampleS = 0.0;
			RiirSampleT = 0.0;
			RiirSampleU = 0.0;
			RiirSampleV = 0.0;
			RiirSampleW = 0.0;
			RiirSampleX = 0.0;
			RiirSampleY = 0.0;
			RiirSampleZ = 0.0;	
			
			flip = false;
			bflip = 0;
			ataK1 = -0.646; //first FIR shaping of interpolated sample, brightens
			ataK2 = 0.311; //second FIR shaping of interpolated sample, thickens
			ataK6 = -0.093; //third FIR shaping of interpolated sample, brings air
			ataK7 = 0.057; //fourth FIR shaping of interpolated sample, thickens
			ataK8 = -0.023; //fifth FIR shaping of interpolated sample, brings air
			ataK3 = 0.114; //add raw to interpolated dry, toughens
			ataK4 = 0.886; //remainder of interpolated dry, adds up to 1.0
			ataK5 = 0.122; //subtract this much prev. diff sample, brightens
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
		double overallscale = 1.0;
		overallscale /= 44100.0;
		overallscale *= samplerate();

		long sampleFrames = _input.frame_count();
		
		double contHigh = A;
		double dry = B;
		double contDub = C*1.3;
		double contSub = D/2.0;
		
		double driveone = pow(contHigh*3.0,2);
		double driveoutput = contHigh;
		double iirAmount = 0.344/overallscale;
		double BassGain = contDub * 0.1;
		double HeadBumpFreq = (BassGain+0.0001)/overallscale;
		double BassOutGain = contDub * 0.2;
		double SubGain = contSub * 0.1;
		double SubBumpFreq = (SubGain+0.0001)/overallscale;
		double SubOutGain = contSub * 0.3;
		double iirHPAmount = 0.0000014/overallscale;
	    
	    while (--sampleFrames >= 0)
	    {
			long double LinputSample = *in1;
			long double RinputSample = *in2;
			if (fabs(LinputSample)<1.18e-43) LinputSample = fpd * 1.18e-43;
			if (fabs(RinputSample)<1.18e-43) RinputSample = fpd * 1.18e-43;
			
			LataDrySample = LinputSample;
			LataHalfDrySample = LataHalfwaySample = (LinputSample + LataLast1Sample + (LataLast2Sample*ataK1) + (LataLast3Sample*ataK2) + (LataLast4Sample*ataK6) + (LataLast5Sample*ataK7) + (LataLast6Sample*ataK8)) / 2.0;
			LataLast6Sample = LataLast5Sample; LataLast5Sample = LataLast4Sample; LataLast4Sample = LataLast3Sample; LataLast3Sample = LataLast2Sample; LataLast2Sample = LataLast1Sample; LataLast1Sample = LinputSample;
			//setting up oversampled special antialiasing
			RataDrySample = RinputSample;
			RataHalfDrySample = RataHalfwaySample = (RinputSample + RataLast1Sample + (RataLast2Sample*ataK1) + (RataLast3Sample*ataK2) + (RataLast4Sample*ataK6) + (RataLast5Sample*ataK7) + (RataLast6Sample*ataK8)) / 2.0;
			RataLast6Sample = RataLast5Sample; RataLast5Sample = RataLast4Sample; RataLast4Sample = RataLast3Sample; RataLast3Sample = RataLast2Sample; RataLast2Sample = RataLast1Sample; RataLast1Sample = RinputSample;
			//setting up oversampled special antialiasing
			
			double correction;
			double subtractSample;
			double tempSample; //used repeatedly in different places
			
			//begin first half- change inputSample -> ataHalfwaySample, ataDrySample -> ataHalfDrySample
			
			double LataHalfwayLowpass;
			double RataHalfwayLowpass;
			if (flip)
			{
				tempSample = subtractSample = LataHalfwaySample;
				LiirDriveSampleA = (LiirDriveSampleA * (1.0-iirAmount)) + (tempSample * iirAmount); tempSample -= LiirDriveSampleA; correction = LiirDriveSampleA;
				LiirDriveSampleC = (LiirDriveSampleC * (1.0-iirAmount)) + (tempSample * iirAmount); tempSample -= LiirDriveSampleC; correction += LiirDriveSampleC;
				LiirDriveSampleE = (LiirDriveSampleE * (1.0-iirAmount)) + (tempSample * iirAmount); tempSample -= LiirDriveSampleE; correction += LiirDriveSampleE;
				LataHalfwaySample -= correction;
				LataHalfwayLowpass = subtractSample - LataHalfwaySample;
				
				tempSample = subtractSample = RataHalfwaySample;
				RiirDriveSampleA = (RiirDriveSampleA * (1.0-iirAmount)) + (tempSample * iirAmount); tempSample -= RiirDriveSampleA; correction = RiirDriveSampleA;
				RiirDriveSampleC = (RiirDriveSampleC * (1.0-iirAmount)) + (tempSample * iirAmount); tempSample -= RiirDriveSampleC; correction += RiirDriveSampleC;
				RiirDriveSampleE = (RiirDriveSampleE * (1.0-iirAmount)) + (tempSample * iirAmount); tempSample -= RiirDriveSampleE; correction += RiirDriveSampleE;
				RataHalfwaySample -= correction;
				RataHalfwayLowpass = subtractSample - RataHalfwaySample;
			}
			else
			{
				tempSample = subtractSample = LataHalfwaySample;
				LiirDriveSampleB = (LiirDriveSampleB * (1.0-iirAmount)) + (tempSample * iirAmount); tempSample -= LiirDriveSampleB; correction = LiirDriveSampleB;
				LiirDriveSampleD = (LiirDriveSampleD * (1.0-iirAmount)) + (tempSample * iirAmount); tempSample -= LiirDriveSampleD; correction += LiirDriveSampleD;
				LiirDriveSampleF = (LiirDriveSampleF * (1.0-iirAmount)) + (tempSample * iirAmount); tempSample -= LiirDriveSampleF; correction += RiirDriveSampleF;
				LataHalfwaySample -= correction;			
				LataHalfwayLowpass = subtractSample - LataHalfwaySample;
				
				tempSample = subtractSample = RataHalfwaySample;
				RiirDriveSampleB = (RiirDriveSampleB * (1.0-iirAmount)) + (tempSample * iirAmount); tempSample -= RiirDriveSampleB; correction = RiirDriveSampleB;
				RiirDriveSampleD = (RiirDriveSampleD * (1.0-iirAmount)) + (tempSample * iirAmount); tempSample -= RiirDriveSampleD; correction += RiirDriveSampleD;
				RiirDriveSampleF = (RiirDriveSampleF * (1.0-iirAmount)) + (tempSample * iirAmount); tempSample -= RiirDriveSampleF; correction += RiirDriveSampleF;
				RataHalfwaySample -= correction;			
				RataHalfwayLowpass = subtractSample - RataHalfwaySample;
			}
			//highpass section
			if (LataHalfwaySample > 1.0) {LataHalfwaySample = 1.0;}
			if (LataHalfwaySample < -1.0) {LataHalfwaySample = -1.0;}
			if (RataHalfwaySample > 1.0) {RataHalfwaySample = 1.0;}
			if (RataHalfwaySample < -1.0) {RataHalfwaySample = -1.0;}
			double drivetwo = driveone;
			while (drivetwo > 0.60)
			{
				drivetwo -= 0.60;
				LataHalfwaySample -= (LataHalfwaySample * (fabs(LataHalfwaySample) * 0.60) * (fabs(LataHalfwaySample) * 0.60) );
				RataHalfwaySample -= (RataHalfwaySample * (fabs(RataHalfwaySample) * 0.60) * (fabs(RataHalfwaySample) * 0.60) );
				LataHalfwaySample *= (1.0+0.60);
				RataHalfwaySample *= (1.0+0.60);
			}
			//that's taken care of the really high gain stuff
			
			LataHalfwaySample -= (LataHalfwaySample * (fabs(LataHalfwaySample) * drivetwo) * (fabs(LataHalfwaySample) * drivetwo) );
			RataHalfwaySample -= (RataHalfwaySample * (fabs(RataHalfwaySample) * drivetwo) * (fabs(RataHalfwaySample) * drivetwo) );
			LataHalfwaySample *= (1.0+drivetwo);
			RataHalfwaySample *= (1.0+drivetwo);
			
			
			//end first half
			//begin second half- inputSample and ataDrySample handled separately here
			
			double LataLowpass;
			double RataLowpass;
			if (flip)
			{
				tempSample = subtractSample = LinputSample;
				LiirDriveSampleA = (LiirDriveSampleA * (1.0-iirAmount)) + (tempSample * iirAmount); tempSample -= LiirDriveSampleA; correction = LiirDriveSampleA;
				LiirDriveSampleC = (LiirDriveSampleC * (1.0-iirAmount)) + (tempSample * iirAmount); tempSample -= LiirDriveSampleC; correction += LiirDriveSampleC;
				LiirDriveSampleE = (LiirDriveSampleE * (1.0-iirAmount)) + (tempSample * iirAmount); tempSample -= LiirDriveSampleE; correction += LiirDriveSampleE;
				LinputSample -= correction;
				LataLowpass = subtractSample - LinputSample;
				
				tempSample = subtractSample = RinputSample;
				RiirDriveSampleA = (RiirDriveSampleA * (1.0-iirAmount)) + (tempSample * iirAmount); tempSample -= RiirDriveSampleA; correction = RiirDriveSampleA;
				RiirDriveSampleC = (RiirDriveSampleC * (1.0-iirAmount)) + (tempSample * iirAmount); tempSample -= RiirDriveSampleC; correction += RiirDriveSampleC;
				RiirDriveSampleE = (RiirDriveSampleE * (1.0-iirAmount)) + (tempSample * iirAmount); tempSample -= RiirDriveSampleE; correction += RiirDriveSampleE;
				RinputSample -= correction;
				RataLowpass = subtractSample - RinputSample;
			}
			else
			{
				tempSample = subtractSample = LinputSample;
				LiirDriveSampleB = (LiirDriveSampleB * (1.0-iirAmount)) + (tempSample * iirAmount); tempSample -= LiirDriveSampleB; correction = LiirDriveSampleB;
				LiirDriveSampleD = (LiirDriveSampleD * (1.0-iirAmount)) + (tempSample * iirAmount); tempSample -= LiirDriveSampleD; correction += LiirDriveSampleD;
				LiirDriveSampleF = (LiirDriveSampleF * (1.0-iirAmount)) + (tempSample * iirAmount); tempSample -= LiirDriveSampleF; correction += LiirDriveSampleF;
				LinputSample -= correction;
				LataLowpass = subtractSample - LinputSample;
				
				tempSample = subtractSample = RinputSample;
				RiirDriveSampleB = (RiirDriveSampleB * (1.0-iirAmount)) + (tempSample * iirAmount); tempSample -= RiirDriveSampleB; correction = RiirDriveSampleB;
				RiirDriveSampleD = (RiirDriveSampleD * (1.0-iirAmount)) + (tempSample * iirAmount); tempSample -= RiirDriveSampleD; correction += RiirDriveSampleD;
				RiirDriveSampleF = (RiirDriveSampleF * (1.0-iirAmount)) + (tempSample * iirAmount); tempSample -= RiirDriveSampleF; correction += RiirDriveSampleF;
				RinputSample -= correction;
				RataLowpass = subtractSample - RinputSample;
			}
			//highpass section
			if (LinputSample > 1.0) {LinputSample = 1.0;}
			if (LinputSample < -1.0) {LinputSample = -1.0;}
			if (RinputSample > 1.0) {RinputSample = 1.0;}
			if (RinputSample < -1.0) {RinputSample = -1.0;}
			drivetwo = driveone;
			while (drivetwo > 0.60)
			{
				drivetwo -= 0.60;
				LinputSample -= (LinputSample * (fabs(LinputSample) * 0.60) * (fabs(LinputSample) * 0.60) );
				RinputSample -= (RinputSample * (fabs(RinputSample) * 0.60) * (fabs(RinputSample) * 0.60) );
				LinputSample *= (1.0+0.60);
				RinputSample *= (1.0+0.60);
			}
			//that's taken care of the really high gain stuff
			
			LinputSample -= (LinputSample * (fabs(LinputSample) * drivetwo) * (fabs(LinputSample) * drivetwo) );
			RinputSample -= (RinputSample * (fabs(RinputSample) * drivetwo) * (fabs(RinputSample) * drivetwo) );
			LinputSample *= (1.0+drivetwo);
			RinputSample *= (1.0+drivetwo);
			//end second half
			
			
			LataHalfDrySample = (LataDrySample*ataK3)+(LataHalfDrySample*ataK4);
			LataHalfDiffSample = (LataHalfwaySample - LataHalfDrySample)/2.0;
			LataLastDiffSample = LataDiffSample*ataK5;
			LataDiffSample = (LinputSample - LataDrySample)/2.0;
			LataDiffSample += LataHalfDiffSample;
			LataDiffSample -= LataLastDiffSample;
			LinputSample = LataDrySample;
			LinputSample += LataDiffSample;
			//apply processing as difference to non-oversampled raw input
			RataHalfDrySample = (RataDrySample*ataK3)+(RataHalfDrySample*ataK4);
			RataHalfDiffSample = (RataHalfwaySample - RataHalfDrySample)/2.0;
			RataLastDiffSample = RataDiffSample*ataK5;
			RataDiffSample = (RinputSample - RataDrySample)/2.0;
			RataDiffSample += RataHalfDiffSample;
			RataDiffSample -= RataLastDiffSample;
			RinputSample = RataDrySample;
			RinputSample += RataDiffSample;
			//apply processing as difference to non-oversampled raw input
			
			//now we've got inputSample as the Drive top-end output, and we have ataLowpass and ataHalfwayLowpass
			LataLowpass += LataHalfwayLowpass; //and combined them. Now we make sub-octaves
			RataLowpass += RataHalfwayLowpass; //and combined them. Now we make sub-octaves
			
			double randy = (rand()/(double)RAND_MAX)*0.0555; //0 to 1 the noise, may not be needed		
			
			switch (bflip)
			{
				case 1:				
					LiirHeadBumpA += (LataLowpass * BassGain);
					LiirHeadBumpA -= (LiirHeadBumpA * LiirHeadBumpA * LiirHeadBumpA * HeadBumpFreq);
					LiirHeadBumpA = ((1.0-randy) * LiirHeadBumpA) + (randy * LiirHeadBumpB) + (randy * LiirHeadBumpC);
					
					RiirHeadBumpA += (RataLowpass * BassGain);
					RiirHeadBumpA -= (RiirHeadBumpA * RiirHeadBumpA * RiirHeadBumpA * HeadBumpFreq);
					RiirHeadBumpA = ((1.0-randy) * RiirHeadBumpA) + (randy * RiirHeadBumpB) + (randy * RiirHeadBumpC);
					break;
				case 2:
					LiirHeadBumpB += (LataLowpass * BassGain);
					LiirHeadBumpB -= (LiirHeadBumpB * LiirHeadBumpB * LiirHeadBumpB * HeadBumpFreq);
					LiirHeadBumpB = (randy * LiirHeadBumpA) + ((1.0-randy) * LiirHeadBumpB) + (randy * LiirHeadBumpC);
					
					RiirHeadBumpB += (RataLowpass * BassGain);
					RiirHeadBumpB -= (RiirHeadBumpB * RiirHeadBumpB * RiirHeadBumpB * HeadBumpFreq);
					RiirHeadBumpB = (randy * RiirHeadBumpA) + ((1.0-randy) * RiirHeadBumpB) + (randy * RiirHeadBumpC);
					break;
				case 3:
					LiirHeadBumpC += (LataLowpass * BassGain);
					LiirHeadBumpC -= (LiirHeadBumpC * LiirHeadBumpC * LiirHeadBumpC * HeadBumpFreq);
					LiirHeadBumpC = (randy * LiirHeadBumpA) + (randy * LiirHeadBumpB) + ((1.0-randy) * LiirHeadBumpC);
					
					RiirHeadBumpC += (RataLowpass * BassGain);
					RiirHeadBumpC -= (RiirHeadBumpC * RiirHeadBumpC * RiirHeadBumpC * HeadBumpFreq);
					RiirHeadBumpC = (randy * RiirHeadBumpA) + (randy * RiirHeadBumpB) + ((1.0-randy) * RiirHeadBumpC);
					break;
			}
			double LHeadBump = LiirHeadBumpA + LiirHeadBumpB + LiirHeadBumpC;
			double RHeadBump = RiirHeadBumpA + RiirHeadBumpB + RiirHeadBumpC;
			
			double LSubBump = fabs(LHeadBump);
			double RSubBump = fabs(RHeadBump);
			
			if (LHeadBump > 0)
			{if (LWasNegative){LSubOctave = !LSubOctave;} LWasNegative = false;}
			else {LWasNegative = true;}
			//set up polarities for sub-bass version
			if (RHeadBump > 0)
			{if (RWasNegative){RSubOctave = !RSubOctave;} RWasNegative = false;}
			else {RWasNegative = true;}
			//set up polarities for sub-bass version
			
			if (LSubOctave == false) {LSubBump = -LSubBump;}
			if (RSubOctave == false) {RSubBump = -RSubBump;}
			
			switch (bflip)
			{
				case 1:				
					LiirSubBumpA += (LSubBump * SubGain);
					LiirSubBumpA -= (LiirSubBumpA * LiirSubBumpA * LiirSubBumpA * SubBumpFreq);
					LiirSubBumpA = ((1.0-randy) * LiirSubBumpA) + (randy * LiirSubBumpB) + (randy * LiirSubBumpC);
					
					RiirSubBumpA += (RSubBump * SubGain);
					RiirSubBumpA -= (RiirSubBumpA * RiirSubBumpA * RiirSubBumpA * SubBumpFreq);
					RiirSubBumpA = ((1.0-randy) * RiirSubBumpA) + (randy * RiirSubBumpB) + (randy * RiirSubBumpC);
					break;
				case 2:
					LiirSubBumpB += (LSubBump * SubGain);
					LiirSubBumpB -= (LiirSubBumpB * LiirSubBumpB * LiirSubBumpB * SubBumpFreq);
					LiirSubBumpB = (randy * LiirSubBumpA) + ((1.0-randy) * LiirSubBumpB) + (randy * LiirSubBumpC);
					
					RiirSubBumpB += (RSubBump * SubGain);
					RiirSubBumpB -= (RiirSubBumpB * RiirSubBumpB * RiirSubBumpB * SubBumpFreq);
					RiirSubBumpB = (randy * RiirSubBumpA) + ((1.0-randy) * RiirSubBumpB) + (randy * RiirSubBumpC);
					break;
				case 3:
					LiirSubBumpC += (LSubBump * SubGain);
					LiirSubBumpC -= (LiirSubBumpC * LiirSubBumpC * LiirSubBumpC * SubBumpFreq);
					LiirSubBumpC = (randy * LiirSubBumpA) + (randy * LiirSubBumpB) + ((1.0-randy) * LiirSubBumpC);
					
					RiirSubBumpC += (RSubBump * SubGain);
					RiirSubBumpC -= (RiirSubBumpC * RiirSubBumpC * RiirSubBumpC * SubBumpFreq);
					RiirSubBumpC = (randy * RiirSubBumpA) + (randy * RiirSubBumpB) + ((1.0-randy) * RiirSubBumpC);
					break;
			}
			LSubBump = LiirSubBumpA + LiirSubBumpB + LiirSubBumpC;
			RSubBump = RiirSubBumpA + RiirSubBumpB + RiirSubBumpC;
			
			flip = !flip;
			bflip++;
			if (bflip < 1 || bflip > 3) bflip = 1;
			
			LinputSample *= driveoutput;
			RinputSample *= driveoutput;
			
			
			correction = LataDrySample*dry;
			correction += (LHeadBump * BassOutGain);
			correction += (LSubBump * SubOutGain);
			LinputSample += correction;
			
			correction = RataDrySample*dry;
			correction += (RHeadBump * BassOutGain);
			correction += (RSubBump * SubOutGain);
			RinputSample += correction;
			
			tempSample = LinputSample;		
			LiirSampleA = (LiirSampleA * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= LiirSampleA; correction = LiirSampleA;
			LiirSampleB = (LiirSampleB * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= LiirSampleB; correction += LiirSampleB;
			LiirSampleC = (LiirSampleC * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= LiirSampleC; correction += LiirSampleC;
			LiirSampleD = (LiirSampleD * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= LiirSampleD; correction += LiirSampleD;
			LiirSampleE = (LiirSampleE * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= LiirSampleE; correction += LiirSampleE;
			LiirSampleF = (LiirSampleF * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= LiirSampleF; correction += LiirSampleF;
			LiirSampleG = (LiirSampleG * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= LiirSampleG; correction += LiirSampleG;
			LiirSampleH = (LiirSampleH * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= LiirSampleH; correction += LiirSampleH;
			LiirSampleI = (LiirSampleI * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= LiirSampleI; correction += LiirSampleI;
			LiirSampleJ = (LiirSampleJ * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= LiirSampleJ; correction += LiirSampleJ;
			LiirSampleK = (LiirSampleK * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= LiirSampleK; correction += LiirSampleK;
			LiirSampleL = (LiirSampleL * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= LiirSampleL; correction += LiirSampleL;
			LiirSampleM = (LiirSampleM * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= LiirSampleM; correction += LiirSampleM;
			LiirSampleN = (LiirSampleN * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= LiirSampleN; correction += LiirSampleN;
			LiirSampleO = (LiirSampleO * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= LiirSampleO; correction += LiirSampleO;
			LiirSampleP = (LiirSampleP * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= LiirSampleP; correction += LiirSampleP;
			LiirSampleQ = (LiirSampleQ * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= LiirSampleQ; correction += LiirSampleQ;
			LiirSampleR = (LiirSampleR * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= LiirSampleR; correction += LiirSampleR;
			LiirSampleS = (LiirSampleS * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= LiirSampleS; correction += LiirSampleS;
			LiirSampleT = (LiirSampleT * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= LiirSampleT; correction += LiirSampleT;
			LiirSampleU = (LiirSampleU * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= LiirSampleU; correction += LiirSampleU;
			LiirSampleV = (LiirSampleV * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= LiirSampleV; correction += LiirSampleV;
			LiirSampleW = (LiirSampleW * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= LiirSampleW; correction += LiirSampleW;
			LiirSampleX = (LiirSampleX * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= LiirSampleX; correction += LiirSampleX;
			LiirSampleY = (LiirSampleY * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= LiirSampleY; correction += LiirSampleY;
			LiirSampleZ = (LiirSampleZ * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= LiirSampleZ; correction += LiirSampleZ;
			//do the IIR on a dummy sample, and store up the correction in a variable at the same scale as the very low level
			//numbers being used. Don't keep doing it against the possibly high level signal number.
			LinputSample -= correction;
			//apply stored up tiny corrections
			
			tempSample = RinputSample;		
			RiirSampleA = (RiirSampleA * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= RiirSampleA; correction = RiirSampleA;
			RiirSampleB = (RiirSampleB * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= RiirSampleB; correction += RiirSampleB;
			RiirSampleC = (RiirSampleC * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= RiirSampleC; correction += RiirSampleC;
			RiirSampleD = (RiirSampleD * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= RiirSampleD; correction += RiirSampleD;
			RiirSampleE = (RiirSampleE * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= RiirSampleE; correction += RiirSampleE;
			RiirSampleF = (RiirSampleF * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= RiirSampleF; correction += RiirSampleF;
			RiirSampleG = (RiirSampleG * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= RiirSampleG; correction += RiirSampleG;
			RiirSampleH = (RiirSampleH * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= RiirSampleH; correction += RiirSampleH;
			RiirSampleI = (RiirSampleI * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= RiirSampleI; correction += RiirSampleI;
			RiirSampleJ = (RiirSampleJ * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= RiirSampleJ; correction += RiirSampleJ;
			RiirSampleK = (RiirSampleK * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= RiirSampleK; correction += RiirSampleK;
			RiirSampleL = (RiirSampleL * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= RiirSampleL; correction += RiirSampleL;
			RiirSampleM = (RiirSampleM * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= RiirSampleM; correction += RiirSampleM;
			RiirSampleN = (RiirSampleN * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= RiirSampleN; correction += RiirSampleN;
			RiirSampleO = (RiirSampleO * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= RiirSampleO; correction += RiirSampleO;
			RiirSampleP = (RiirSampleP * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= RiirSampleP; correction += RiirSampleP;
			RiirSampleQ = (RiirSampleQ * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= RiirSampleQ; correction += RiirSampleQ;
			RiirSampleR = (RiirSampleR * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= RiirSampleR; correction += RiirSampleR;
			RiirSampleS = (RiirSampleS * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= RiirSampleS; correction += RiirSampleS;
			RiirSampleT = (RiirSampleT * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= RiirSampleT; correction += RiirSampleT;
			RiirSampleU = (RiirSampleU * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= RiirSampleU; correction += RiirSampleU;
			RiirSampleV = (RiirSampleV * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= RiirSampleV; correction += RiirSampleV;
			RiirSampleW = (RiirSampleW * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= RiirSampleW; correction += RiirSampleW;
			RiirSampleX = (RiirSampleX * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= RiirSampleX; correction += RiirSampleX;
			RiirSampleY = (RiirSampleY * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= RiirSampleY; correction += RiirSampleY;
			RiirSampleZ = (RiirSampleZ * (1.0-iirHPAmount)) + (tempSample * iirHPAmount); tempSample -= RiirSampleZ; correction += RiirSampleZ;
			//do the IIR on a dummy sample, and store up the correction in a variable at the same scale as the very low level
			//numbers being used. Don't keep doing it against the possibly high level signal number.
			RinputSample -= correction;
			//apply stored up tiny corrections
			
			//begin 64 bit stereo floating point dither
			int expon; frexp((double)LinputSample, &expon);
			fpd ^= fpd << 13; fpd ^= fpd >> 17; fpd ^= fpd << 5;
			LinputSample += ((double(fpd)-uint32_t(0x7fffffff)) * 1.1e-44l * pow(2,expon+62));
			frexp((double)RinputSample, &expon);
			fpd ^= fpd << 13; fpd ^= fpd >> 17; fpd ^= fpd << 5;
			RinputSample += ((double(fpd)-uint32_t(0x7fffffff)) * 1.1e-44l * pow(2,expon+62));
			//end 64 bit stereo floating point dither
			
			*out1 = LinputSample;
			*out2 = RinputSample;
	
			*in1++;
			*in2++;
			*out1++;
			*out2++;
		}
	}
private:
    
	double LataLast6Sample;
	double LataLast5Sample;
	double LataLast4Sample;
	double LataLast3Sample;
	double LataLast2Sample;
	double LataLast1Sample;
	double LataHalfwaySample;
	double LataHalfDrySample;
	double LataHalfDiffSample;
	double LataLastDiffSample;
	double LataDrySample;
	double LataDiffSample;
	double LataPrevDiffSample;
	
	double LiirDriveSampleA;
	double LiirDriveSampleB;
	double LiirDriveSampleC;
	double LiirDriveSampleD;
	double LiirDriveSampleE;
	double LiirDriveSampleF;
	
	bool LWasNegative;
	bool LSubOctave;
	double LiirHeadBumpA;
	double LiirHeadBumpB;
	double LiirHeadBumpC;
	
	double LiirSubBumpA;
	double LiirSubBumpB;
	double LiirSubBumpC;
	
	double LiirSampleA;
	double LiirSampleB;
	double LiirSampleC;
	double LiirSampleD;
	double LiirSampleE;
	double LiirSampleF;
	double LiirSampleG;
	double LiirSampleH;
	double LiirSampleI;
	double LiirSampleJ;
	double LiirSampleK;
	double LiirSampleL;
	double LiirSampleM;
	double LiirSampleN;
	double LiirSampleO;
	double LiirSampleP;
	double LiirSampleQ;
	double LiirSampleR;
	double LiirSampleS;
	double LiirSampleT;
	double LiirSampleU;
	double LiirSampleV;
	double LiirSampleW;
	double LiirSampleX;
	double LiirSampleY;
	double LiirSampleZ;		
	
	double RataLast6Sample;
	double RataLast5Sample;
	double RataLast4Sample;
	double RataLast3Sample;
	double RataLast2Sample;
	double RataLast1Sample;
	double RataHalfwaySample;
	double RataHalfDrySample;
	double RataHalfDiffSample;
	double RataLastDiffSample;
	double RataDrySample;
	double RataDiffSample;
	double RataPrevDiffSample;
	
	double RiirDriveSampleA;
	double RiirDriveSampleB;
	double RiirDriveSampleC;
	double RiirDriveSampleD;
	double RiirDriveSampleE;
	double RiirDriveSampleF;
	
	bool RWasNegative;
	bool RSubOctave;
	double RiirHeadBumpA;
	double RiirHeadBumpB;
	double RiirHeadBumpC;
	
	double RiirSubBumpA;
	double RiirSubBumpB;
	double RiirSubBumpC;
	
	double RiirSampleA;
	double RiirSampleB;
	double RiirSampleC;
	double RiirSampleD;
	double RiirSampleE;
	double RiirSampleF;
	double RiirSampleG;
	double RiirSampleH;
	double RiirSampleI;
	double RiirSampleJ;
	double RiirSampleK;
	double RiirSampleL;
	double RiirSampleM;
	double RiirSampleN;
	double RiirSampleO;
	double RiirSampleP;
	double RiirSampleQ;
	double RiirSampleR;
	double RiirSampleS;
	double RiirSampleT;
	double RiirSampleU;
	double RiirSampleV;
	double RiirSampleW;
	double RiirSampleX;
	double RiirSampleY;
	double RiirSampleZ;		
	
	double ataK1;
	double ataK2;
	double ataK3;
	double ataK4;
	double ataK5;
	double ataK6;
	double ataK7;
	double ataK8; //end antialiasing variables
	
	bool flip; //drive things	
	int bflip;
	
	uint32_t fpd;
	//default stuff

};
MIN_EXTERNAL(bassamp);

