#include "c74_min.h"

using namespace c74::min;

class mv : public object<mv>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a dual-mono reverb based on BitShiftGain and the old Midiverbs"};
	MIN_TAGS {"reverb"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "depth", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "brightness", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "regen", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "output", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> E {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			int count;
			for(count = 0; count < 15149; count++) {aAL[count] = 0.0; aAR[count] = 0.0;}
			for(count = 0; count < 14617; count++) {aBL[count] = 0.0; aBR[count] = 0.0;}
			for(count = 0; count < 14357; count++) {aCL[count] = 0.0; aCR[count] = 0.0;}
			for(count = 0; count < 13817; count++) {aDL[count] = 0.0; aDR[count] = 0.0;}
			for(count = 0; count < 13561; count++) {aEL[count] = 0.0; aER[count] = 0.0;}
			for(count = 0; count < 13045; count++) {aFL[count] = 0.0; aFR[count] = 0.0;}
			for(count = 0; count < 11965; count++) {aGL[count] = 0.0; aGR[count] = 0.0;}
			for(count = 0; count < 11129; count++) {aHL[count] = 0.0; aHR[count] = 0.0;}
			for(count = 0; count < 10597; count++) {aIL[count] = 0.0; aIR[count] = 0.0;}
			for(count = 0; count < 9809; count++) {aJL[count] = 0.0; aJR[count] = 0.0;}
			for(count = 0; count < 9521; count++) {aKL[count] = 0.0; aKR[count] = 0.0;}
			for(count = 0; count < 8981; count++) {aLL[count] = 0.0; aLR[count] = 0.0;}
			for(count = 0; count < 8785; count++) {aML[count] = 0.0; aMR[count] = 0.0;}
			for(count = 0; count < 8461; count++) {aNL[count] = 0.0; aNR[count] = 0.0;}
			for(count = 0; count < 8309; count++) {aOL[count] = 0.0; aOR[count] = 0.0;}
			for(count = 0; count < 7981; count++) {aPL[count] = 0.0; aPR[count] = 0.0;}
			for(count = 0; count < 7321; count++) {aQL[count] = 0.0; aQR[count] = 0.0;}
			for(count = 0; count < 6817; count++) {aRL[count] = 0.0; aRR[count] = 0.0;}
			for(count = 0; count < 6505; count++) {aSL[count] = 0.0; aSR[count] = 0.0;}
			for(count = 0; count < 6001; count++) {aTL[count] = 0.0; aTR[count] = 0.0;}
			for(count = 0; count < 5837; count++) {aUL[count] = 0.0; aUR[count] = 0.0;}
			for(count = 0; count < 5501; count++) {aVL[count] = 0.0; aVR[count] = 0.0;}
			for(count = 0; count < 5009; count++) {aWL[count] = 0.0; aWR[count] = 0.0;}
			for(count = 0; count < 4849; count++) {aXL[count] = 0.0; aXR[count] = 0.0;}
			for(count = 0; count < 4295; count++) {aYL[count] = 0.0; aYR[count] = 0.0;}
			for(count = 0; count < 4179; count++) {aZL[count] = 0.0; aZR[count] = 0.0;}	
			
			alpA = 1; delayA = 7573; avgAL = 0.0; avgAR = 0.0;
			alpB = 1; delayB = 7307; avgBL = 0.0; avgBR = 0.0;
			alpC = 1; delayC = 7177; avgCL = 0.0; avgCR = 0.0;
			alpD = 1; delayD = 6907; avgDL = 0.0; avgDR = 0.0;
			alpE = 1; delayE = 6779; avgEL = 0.0; avgER = 0.0;
			alpF = 1; delayF = 6521; avgFL = 0.0; avgFR = 0.0;
			alpG = 1; delayG = 5981; avgGL = 0.0; avgGR = 0.0;
			alpH = 1; delayH = 5563; avgHL = 0.0; avgHR = 0.0;
			alpI = 1; delayI = 5297; avgIL = 0.0; avgIR = 0.0;
			alpJ = 1; delayJ = 4903; avgJL = 0.0; avgJR = 0.0;
			alpK = 1; delayK = 4759; avgKL = 0.0; avgKR = 0.0;
			alpL = 1; delayL = 4489; avgLL = 0.0; avgLR = 0.0;
			alpM = 1; delayM = 4391; avgML = 0.0; avgMR = 0.0;
			alpN = 1; delayN = 4229; avgNL = 0.0; avgNR = 0.0;
			alpO = 1; delayO = 4153; avgOL = 0.0; avgOR = 0.0;
			alpP = 1; delayP = 3989; avgPL = 0.0; avgPR = 0.0;
			alpQ = 1; delayQ = 3659; avgQL = 0.0; avgQR = 0.0;
			alpR = 1; delayR = 3407; avgRL = 0.0; avgRR = 0.0;
			alpS = 1; delayS = 3251; avgSL = 0.0; avgSR = 0.0;
			alpT = 1; delayT = 2999; avgTL = 0.0; avgTR = 0.0;
			alpU = 1; delayU = 2917; avgUL = 0.0; avgUR = 0.0;
			alpV = 1; delayV = 2749; avgVL = 0.0; avgVR = 0.0;
			alpW = 1; delayW = 2503; avgWL = 0.0; avgWR = 0.0;
			alpX = 1; delayX = 2423; avgXL = 0.0; avgXR = 0.0;
			alpY = 1; delayY = 2146; avgYL = 0.0; avgYR = 0.0;
			alpZ = 1; delayZ = 2088; avgZL = 0.0; avgZR = 0.0;
			
			feedbackL = 0.0;
			feedbackR = 0.0;
			
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

		int allpasstemp;
		double avgtemp;
		int stage = A * 27.0;
		int damp = (1.0-B) * stage;
		double feedbacklevel = C;
		if (feedbacklevel <= 0.0625) feedbacklevel = 0.0;
		if (feedbacklevel > 0.0625 && feedbacklevel <= 0.125) feedbacklevel = 0.0625; //-24db
		if (feedbacklevel > 0.125 && feedbacklevel <= 0.25) feedbacklevel = 0.125; //-18db
		if (feedbacklevel > 0.25 && feedbacklevel <= 0.5) feedbacklevel = 0.25; //-12db
		if (feedbacklevel > 0.5 && feedbacklevel <= 0.99) feedbacklevel = 0.5; //-6db
		if (feedbacklevel > 0.99) feedbacklevel = 1.0;
		//we're forcing even the feedback level to be Midiverb-ized
		double gain = D;
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
			double drySampleL = inputSampleL;
			double drySampleR = inputSampleR;
			
			inputSampleL += feedbackL;
			inputSampleR += feedbackR;
	
			inputSampleL = sin(inputSampleL);
			inputSampleR = sin(inputSampleR);
			
			switch (stage){
				case 27:
				case 26:
					allpasstemp = alpA - 1;
					if (allpasstemp < 0 || allpasstemp > delayA) {allpasstemp = delayA;}
					inputSampleL -= aAL[allpasstemp]*0.5;
					aAL[alpA] = inputSampleL;
					inputSampleL *= 0.5;
					
					inputSampleR -= aAR[allpasstemp]*0.5;
					aAR[alpA] = inputSampleR;
					inputSampleR *= 0.5;
					
					alpA--; if (alpA < 0 || alpA > delayA) {alpA = delayA;}
					inputSampleL += (aAL[alpA]);
					inputSampleR += (aAR[alpA]);
					if (damp > 26) {
						avgtemp = inputSampleL;
						inputSampleL += avgAL;
						inputSampleL *= 0.5;
						avgAL = avgtemp;
						
						avgtemp = inputSampleR;
						inputSampleR += avgAR;
						inputSampleR *= 0.5;
						avgAR = avgtemp;
					}
					//allpass filter A		
				case 25:
					allpasstemp = alpB - 1;
					if (allpasstemp < 0 || allpasstemp > delayB) {allpasstemp = delayB;}
					inputSampleL -= aBL[allpasstemp]*0.5;
					aBL[alpB] = inputSampleL;
					inputSampleL *= 0.5;
					
					inputSampleR -= aBR[allpasstemp]*0.5;
					aBR[alpB] = inputSampleR;
					inputSampleR *= 0.5;
					
					alpB--; if (alpB < 0 || alpB > delayB) {alpB = delayB;}
					inputSampleL += (aBL[alpB]);
					inputSampleR += (aBR[alpB]);
					if (damp > 25) {
						avgtemp = inputSampleL;
						inputSampleL += avgBL;
						inputSampleL *= 0.5;
						avgBL = avgtemp;
						
						avgtemp = inputSampleR;
						inputSampleR += avgBR;
						inputSampleR *= 0.5;
						avgBR = avgtemp;
					}
					//allpass filter B
				case 24:
					allpasstemp = alpC - 1;
					if (allpasstemp < 0 || allpasstemp > delayC) {allpasstemp = delayC;}
					inputSampleL -= aCL[allpasstemp]*0.5;
					aCL[alpC] = inputSampleL;
					inputSampleL *= 0.5;
					
					inputSampleR -= aCR[allpasstemp]*0.5;
					aCR[alpC] = inputSampleR;
					inputSampleR *= 0.5;
					
					alpC--; if (alpC < 0 || alpC > delayC) {alpC = delayC;}
					inputSampleL += (aCL[alpC]);
					inputSampleR += (aCR[alpC]);
					if (damp > 24) {
						avgtemp = inputSampleL;
						inputSampleL += avgCL;
						inputSampleL *= 0.5;
						avgCL = avgtemp;
						
						avgtemp = inputSampleR;
						inputSampleR += avgCR;
						inputSampleR *= 0.5;
						avgCR = avgtemp;
					}
					//allpass filter C
				case 23:
					allpasstemp = alpD - 1;
					if (allpasstemp < 0 || allpasstemp > delayD) {allpasstemp = delayD;}
					inputSampleL -= aDL[allpasstemp]*0.5;
					aDL[alpD] = inputSampleL;
					inputSampleL *= 0.5;
					
					inputSampleR -= aDR[allpasstemp]*0.5;
					aDR[alpD] = inputSampleR;
					inputSampleR *= 0.5;
					
					alpD--; if (alpD < 0 || alpD > delayD) {alpD = delayD;}
					inputSampleL += (aDL[alpD]);
					inputSampleR += (aDR[alpD]);
					if (damp > 23) {
						avgtemp = inputSampleL;
						inputSampleL += avgDL;
						inputSampleL *= 0.5;
						avgDL = avgtemp;
						
						avgtemp = inputSampleR;
						inputSampleR += avgDR;
						inputSampleR *= 0.5;
						avgDR = avgtemp;
					}
					//allpass filter D
				case 22:
					allpasstemp = alpE - 1;
					if (allpasstemp < 0 || allpasstemp > delayE) {allpasstemp = delayE;}
					inputSampleL -= aEL[allpasstemp]*0.5;
					aEL[alpE] = inputSampleL;
					inputSampleL *= 0.5;
					
					inputSampleR -= aER[allpasstemp]*0.5;
					aER[alpE] = inputSampleR;
					inputSampleR *= 0.5;
					
					alpE--; if (alpE < 0 || alpE > delayE) {alpE = delayE;}
					inputSampleL += (aEL[alpE]);
					inputSampleR += (aER[alpE]);
					if (damp > 22) {
						avgtemp = inputSampleL;
						inputSampleL += avgEL;
						inputSampleL *= 0.5;
						avgEL = avgtemp;
						
						avgtemp = inputSampleR;
						inputSampleR += avgER;
						inputSampleR *= 0.5;
						avgER = avgtemp;
					}
					//allpass filter E
				case 21:
					allpasstemp = alpF - 1;
					if (allpasstemp < 0 || allpasstemp > delayF) {allpasstemp = delayF;}
					inputSampleL -= aFL[allpasstemp]*0.5;
					aFL[alpF] = inputSampleL;
					inputSampleL *= 0.5;
					
					inputSampleR -= aFR[allpasstemp]*0.5;
					aFR[alpF] = inputSampleR;
					inputSampleR *= 0.5;
					
					alpF--; if (alpF < 0 || alpF > delayF) {alpF = delayF;}
					inputSampleL += (aFL[alpF]);
					inputSampleR += (aFR[alpF]);
					if (damp > 21) {
						avgtemp = inputSampleL;
						inputSampleL += avgFL;
						inputSampleL *= 0.5;
						avgFL = avgtemp;
						
						avgtemp = inputSampleR;
						inputSampleR += avgFR;
						inputSampleR *= 0.5;
						avgFR = avgtemp;
					}
					//allpass filter F
				case 20:
					allpasstemp = alpG - 1;
					if (allpasstemp < 0 || allpasstemp > delayG) {allpasstemp = delayG;}
					inputSampleL -= aGL[allpasstemp]*0.5;
					aGL[alpG] = inputSampleL;
					inputSampleL *= 0.5;
					
					inputSampleR -= aGR[allpasstemp]*0.5;
					aGR[alpG] = inputSampleR;
					inputSampleR *= 0.5;
					
					alpG--; if (alpG < 0 || alpG > delayG) {alpG = delayG;}
					inputSampleL += (aGL[alpG]);
					inputSampleR += (aGR[alpG]);
					if (damp > 20) {
						avgtemp = inputSampleL;
						inputSampleL += avgGL;
						inputSampleL *= 0.5;
						avgGL = avgtemp;
						
						avgtemp = inputSampleR;
						inputSampleR += avgGR;
						inputSampleR *= 0.5;
						avgGR = avgtemp;
					}
					//allpass filter G
				case 19:
					allpasstemp = alpH - 1;
					if (allpasstemp < 0 || allpasstemp > delayH) {allpasstemp = delayH;}
					inputSampleL -= aHL[allpasstemp]*0.5;
					aHL[alpH] = inputSampleL;
					inputSampleL *= 0.5;
					
					inputSampleR -= aHR[allpasstemp]*0.5;
					aHR[alpH] = inputSampleR;
					inputSampleR *= 0.5;
					
					alpH--; if (alpH < 0 || alpH > delayH) {alpH = delayH;}
					inputSampleL += (aHL[alpH]);
					inputSampleR += (aHR[alpH]);
					if (damp > 19) {
						avgtemp = inputSampleL;
						inputSampleL += avgHL;
						inputSampleL *= 0.5;
						avgHL = avgtemp;
						
						avgtemp = inputSampleR;
						inputSampleR += avgHR;
						inputSampleR *= 0.5;
						avgHR = avgtemp;
					}
					//allpass filter H
				case 18:
					allpasstemp = alpI - 1;
					if (allpasstemp < 0 || allpasstemp > delayI) {allpasstemp = delayI;}
					inputSampleL -= aIL[allpasstemp]*0.5;
					aIL[alpI] = inputSampleL;
					inputSampleL *= 0.5;
					
					inputSampleR -= aIR[allpasstemp]*0.5;
					aIR[alpI] = inputSampleR;
					inputSampleR *= 0.5;
					
					alpI--; if (alpI < 0 || alpI > delayI) {alpI = delayI;}
					inputSampleL += (aIL[alpI]);
					inputSampleR += (aIR[alpI]);
					if (damp > 18) {
						avgtemp = inputSampleL;
						inputSampleL += avgIL;
						inputSampleL *= 0.5;
						avgIL = avgtemp;
						
						avgtemp = inputSampleR;
						inputSampleR += avgIR;
						inputSampleR *= 0.5;
						avgIR = avgtemp;
					}
					//allpass filter I
				case 17:
					allpasstemp = alpJ - 1;
					if (allpasstemp < 0 || allpasstemp > delayJ) {allpasstemp = delayJ;}
					inputSampleL -= aJL[allpasstemp]*0.5;
					aJL[alpJ] = inputSampleL;
					inputSampleL *= 0.5;
					
					inputSampleR -= aJR[allpasstemp]*0.5;
					aJR[alpJ] = inputSampleR;
					inputSampleR *= 0.5;
					
					alpJ--; if (alpJ < 0 || alpJ > delayJ) {alpJ = delayJ;}
					inputSampleL += (aJL[alpJ]);
					inputSampleR += (aJR[alpJ]);
					if (damp > 17) {
						avgtemp = inputSampleL;
						inputSampleL += avgJL;
						inputSampleL *= 0.5;
						avgJL = avgtemp;
						
						avgtemp = inputSampleR;
						inputSampleR += avgJR;
						inputSampleR *= 0.5;
						avgJR = avgtemp;
					}
					//allpass filter J
				case 16:
					allpasstemp = alpK - 1;
					if (allpasstemp < 0 || allpasstemp > delayK) {allpasstemp = delayK;}
					inputSampleL -= aKL[allpasstemp]*0.5;
					aKL[alpK] = inputSampleL;
					inputSampleL *= 0.5;
					
					inputSampleR -= aKR[allpasstemp]*0.5;
					aKR[alpK] = inputSampleR;
					inputSampleR *= 0.5;
					
					alpK--; if (alpK < 0 || alpK > delayK) {alpK = delayK;}
					inputSampleL += (aKL[alpK]);
					inputSampleR += (aKR[alpK]);
					if (damp > 16) {
						avgtemp = inputSampleL;
						inputSampleL += avgKL;
						inputSampleL *= 0.5;
						avgKL = avgtemp;
						
						avgtemp = inputSampleR;
						inputSampleR += avgKR;
						inputSampleR *= 0.5;
						avgKR = avgtemp;
					}
					//allpass filter K
				case 15:
					allpasstemp = alpL - 1;
					if (allpasstemp < 0 || allpasstemp > delayL) {allpasstemp = delayL;}
					inputSampleL -= aLL[allpasstemp]*0.5;
					aLL[alpL] = inputSampleL;
					inputSampleL *= 0.5;
					
					inputSampleR -= aLR[allpasstemp]*0.5;
					aLR[alpL] = inputSampleR;
					inputSampleR *= 0.5;
					
					alpL--; if (alpL < 0 || alpL > delayL) {alpL = delayL;}
					inputSampleL += (aLL[alpL]);
					inputSampleR += (aLR[alpL]);
					if (damp > 15) {
						avgtemp = inputSampleL;
						inputSampleL += avgLL;
						inputSampleL *= 0.5;
						avgLL = avgtemp;
						
						avgtemp = inputSampleR;
						inputSampleR += avgLR;
						inputSampleR *= 0.5;
						avgLR = avgtemp;
					}
					//allpass filter L
				case 14:
					allpasstemp = alpM - 1;
					if (allpasstemp < 0 || allpasstemp > delayM) {allpasstemp = delayM;}
					inputSampleL -= aML[allpasstemp]*0.5;
					aML[alpM] = inputSampleL;
					inputSampleL *= 0.5;
					
					inputSampleR -= aMR[allpasstemp]*0.5;
					aMR[alpM] = inputSampleR;
					inputSampleR *= 0.5;
					
					alpM--; if (alpM < 0 || alpM > delayM) {alpM = delayM;}
					inputSampleL += (aML[alpM]);
					inputSampleR += (aMR[alpM]);
					if (damp > 14) {
						avgtemp = inputSampleL;
						inputSampleL += avgML;
						inputSampleL *= 0.5;
						avgML = avgtemp;
						
						avgtemp = inputSampleR;
						inputSampleR += avgMR;
						inputSampleR *= 0.5;
						avgMR = avgtemp;
					}
					//allpass filter M
				case 13:
					allpasstemp = alpN - 1;
					if (allpasstemp < 0 || allpasstemp > delayN) {allpasstemp = delayN;}
					inputSampleL -= aNL[allpasstemp]*0.5;
					aNL[alpN] = inputSampleL;
					inputSampleL *= 0.5;
					
					inputSampleR -= aNR[allpasstemp]*0.5;
					aNR[alpN] = inputSampleR;
					inputSampleR *= 0.5;
					
					alpN--; if (alpN < 0 || alpN > delayN) {alpN = delayN;}
					inputSampleL += (aNL[alpN]);
					inputSampleR += (aNR[alpN]);
					if (damp > 13) {
						avgtemp = inputSampleL;
						inputSampleL += avgNL;
						inputSampleL *= 0.5;
						avgNL = avgtemp;
						
						avgtemp = inputSampleR;
						inputSampleR += avgNR;
						inputSampleR *= 0.5;
						avgNR = avgtemp;
					}
					//allpass filter N
				case 12:
					allpasstemp = alpO - 1;
					if (allpasstemp < 0 || allpasstemp > delayO) {allpasstemp = delayO;}
					inputSampleL -= aOL[allpasstemp]*0.5;
					aOL[alpO] = inputSampleL;
					inputSampleL *= 0.5;
					
					inputSampleR -= aOR[allpasstemp]*0.5;
					aOR[alpO] = inputSampleR;
					inputSampleR *= 0.5;
					
					alpO--; if (alpO < 0 || alpO > delayO) {alpO = delayO;}
					inputSampleL += (aOL[alpO]);
					inputSampleR += (aOR[alpO]);
					if (damp > 12) {
						avgtemp = inputSampleL;
						inputSampleL += avgOL;
						inputSampleL *= 0.5;
						avgOL = avgtemp;
						
						avgtemp = inputSampleR;
						inputSampleR += avgOR;
						inputSampleR *= 0.5;
						avgOR = avgtemp;
					}
					//allpass filter O
				case 11:
					allpasstemp = alpP - 1;
					if (allpasstemp < 0 || allpasstemp > delayP) {allpasstemp = delayP;}
					inputSampleL -= aPL[allpasstemp]*0.5;
					aPL[alpP] = inputSampleL;
					inputSampleL *= 0.5;
					
					inputSampleR -= aPR[allpasstemp]*0.5;
					aPR[alpP] = inputSampleR;
					inputSampleR *= 0.5;
					
					alpP--; if (alpP < 0 || alpP > delayP) {alpP = delayP;}
					inputSampleL += (aPL[alpP]);
					inputSampleR += (aPR[alpP]);
					if (damp > 11) {
						avgtemp = inputSampleL;
						inputSampleL += avgPL;
						inputSampleL *= 0.5;
						avgPL = avgtemp;
						
						avgtemp = inputSampleR;
						inputSampleR += avgPR;
						inputSampleR *= 0.5;
						avgPR = avgtemp;
					}
					//allpass filter P
				case 10:
					allpasstemp = alpQ - 1;
					if (allpasstemp < 0 || allpasstemp > delayQ) {allpasstemp = delayQ;}
					inputSampleL -= aQL[allpasstemp]*0.5;
					aQL[alpQ] = inputSampleL;
					inputSampleL *= 0.5;
					
					inputSampleR -= aQR[allpasstemp]*0.5;
					aQR[alpQ] = inputSampleR;
					inputSampleR *= 0.5;
					
					alpQ--; if (alpQ < 0 || alpQ > delayQ) {alpQ = delayQ;}
					inputSampleL += (aQL[alpQ]);
					inputSampleR += (aQR[alpQ]);
					if (damp > 10) {
						avgtemp = inputSampleL;
						inputSampleL += avgQL;
						inputSampleL *= 0.5;
						avgQL = avgtemp;
						
						avgtemp = inputSampleR;
						inputSampleR += avgQR;
						inputSampleR *= 0.5;
						avgQR = avgtemp;
					}
					//allpass filter Q
				case 9:
					allpasstemp = alpR - 1;
					if (allpasstemp < 0 || allpasstemp > delayR) {allpasstemp = delayR;}
					inputSampleL -= aRL[allpasstemp]*0.5;
					aRL[alpR] = inputSampleL;
					inputSampleL *= 0.5;
					
					inputSampleR -= aRR[allpasstemp]*0.5;
					aRR[alpR] = inputSampleR;
					inputSampleR *= 0.5;
					
					alpR--; if (alpR < 0 || alpR > delayR) {alpR = delayR;}
					inputSampleL += (aRL[alpR]);
					inputSampleR += (aRR[alpR]);
					if (damp > 9) {
						avgtemp = inputSampleL;
						inputSampleL += avgRL;
						inputSampleL *= 0.5;
						avgRL = avgtemp;
						
						avgtemp = inputSampleR;
						inputSampleR += avgRR;
						inputSampleR *= 0.5;
						avgRR = avgtemp;
					}
					//allpass filter R
				case 8:
					allpasstemp = alpS - 1;
					if (allpasstemp < 0 || allpasstemp > delayS) {allpasstemp = delayS;}
					inputSampleL -= aSL[allpasstemp]*0.5;
					aSL[alpS] = inputSampleL;
					inputSampleL *= 0.5;
					
					inputSampleR -= aSR[allpasstemp]*0.5;
					aSR[alpS] = inputSampleR;
					inputSampleR *= 0.5;
					
					alpS--; if (alpS < 0 || alpS > delayS) {alpS = delayS;}
					inputSampleL += (aSL[alpS]);
					inputSampleR += (aSR[alpS]);
					if (damp > 8) {
						avgtemp = inputSampleL;
						inputSampleL += avgSL;
						inputSampleL *= 0.5;
						avgSL = avgtemp;
						
						avgtemp = inputSampleR;
						inputSampleR += avgSR;
						inputSampleR *= 0.5;
						avgSR = avgtemp;
					}
					//allpass filter S
				case 7:
					allpasstemp = alpT - 1;
					if (allpasstemp < 0 || allpasstemp > delayT) {allpasstemp = delayT;}
					inputSampleL -= aTL[allpasstemp]*0.5;
					aTL[alpT] = inputSampleL;
					inputSampleL *= 0.5;
					
					inputSampleR -= aTR[allpasstemp]*0.5;
					aTR[alpT] = inputSampleR;
					inputSampleR *= 0.5;
					
					alpT--; if (alpT < 0 || alpT > delayT) {alpT = delayT;}
					inputSampleL += (aTL[alpT]);
					inputSampleR += (aTR[alpT]);
					if (damp > 7) {
						avgtemp = inputSampleL;
						inputSampleL += avgTL;
						inputSampleL *= 0.5;
						avgTL = avgtemp;
						
						avgtemp = inputSampleR;
						inputSampleR += avgTR;
						inputSampleR *= 0.5;
						avgTR = avgtemp;
					}
					//allpass filter T
				case 6:
					allpasstemp = alpU - 1;
					if (allpasstemp < 0 || allpasstemp > delayU) {allpasstemp = delayU;}
					inputSampleL -= aUL[allpasstemp]*0.5;
					aUL[alpU] = inputSampleL;
					inputSampleL *= 0.5;
					
					inputSampleR -= aUR[allpasstemp]*0.5;
					aUR[alpU] = inputSampleR;
					inputSampleR *= 0.5;
					
					alpU--; if (alpU < 0 || alpU > delayU) {alpU = delayU;}
					inputSampleL += (aUL[alpU]);
					inputSampleR += (aUR[alpU]);
					if (damp > 6) {
						avgtemp = inputSampleL;
						inputSampleL += avgUL;
						inputSampleL *= 0.5;
						avgUL = avgtemp;
						
						avgtemp = inputSampleR;
						inputSampleR += avgUR;
						inputSampleR *= 0.5;
						avgUR = avgtemp;
					}
					//allpass filter U
				case 5:
					allpasstemp = alpV - 1;
					if (allpasstemp < 0 || allpasstemp > delayV) {allpasstemp = delayV;}
					inputSampleL -= aVL[allpasstemp]*0.5;
					aVL[alpV] = inputSampleL;
					inputSampleL *= 0.5;
					
					inputSampleR -= aVR[allpasstemp]*0.5;
					aVR[alpV] = inputSampleR;
					inputSampleR *= 0.5;
					
					alpV--; if (alpV < 0 || alpV > delayV) {alpV = delayV;}
					inputSampleL += (aVL[alpV]);
					inputSampleR += (aVR[alpV]);
					if (damp > 5) {
						avgtemp = inputSampleL;
						inputSampleL += avgVL;
						inputSampleL *= 0.5;
						avgVL = avgtemp;
						
						avgtemp = inputSampleR;
						inputSampleR += avgVR;
						inputSampleR *= 0.5;
						avgVR = avgtemp;
					}
					//allpass filter V
				case 4:
					allpasstemp = alpW - 1;
					if (allpasstemp < 0 || allpasstemp > delayW) {allpasstemp = delayW;}
					inputSampleL -= aWL[allpasstemp]*0.5;
					aWL[alpW] = inputSampleL;
					inputSampleL *= 0.5;
					
					inputSampleR -= aWR[allpasstemp]*0.5;
					aWR[alpW] = inputSampleR;
					inputSampleR *= 0.5;
					
					alpW--; if (alpW < 0 || alpW > delayW) {alpW = delayW;}
					inputSampleL += (aWL[alpW]);
					inputSampleR += (aWR[alpW]);
					if (damp > 4) {
						avgtemp = inputSampleL;
						inputSampleL += avgWL;
						inputSampleL *= 0.5;
						avgWL = avgtemp;
						
						avgtemp = inputSampleR;
						inputSampleR += avgWR;
						inputSampleR *= 0.5;
						avgWR = avgtemp;
					}
					//allpass filter W
				case 3:
					allpasstemp = alpX - 1;
					if (allpasstemp < 0 || allpasstemp > delayX) {allpasstemp = delayX;}
					inputSampleL -= aXL[allpasstemp]*0.5;
					aXL[alpX] = inputSampleL;
					inputSampleL *= 0.5;
					
					inputSampleR -= aXR[allpasstemp]*0.5;
					aXR[alpX] = inputSampleR;
					inputSampleR *= 0.5;
					
					alpX--; if (alpX < 0 || alpX > delayX) {alpX = delayX;}
					inputSampleL += (aXL[alpX]);
					inputSampleR += (aXR[alpX]);
					if (damp > 3) {
						avgtemp = inputSampleL;
						inputSampleL += avgXL;
						inputSampleL *= 0.5;
						avgXL = avgtemp;
						
						avgtemp = inputSampleR;
						inputSampleR += avgXR;
						inputSampleR *= 0.5;
						avgXR = avgtemp;
					}
					//allpass filter X
				case 2:
					allpasstemp = alpY - 1;
					if (allpasstemp < 0 || allpasstemp > delayY) {allpasstemp = delayY;}
					inputSampleL -= aYL[allpasstemp]*0.5;
					aYL[alpY] = inputSampleL;
					inputSampleL *= 0.5;
					
					inputSampleR -= aYR[allpasstemp]*0.5;
					aYR[alpY] = inputSampleR;
					inputSampleR *= 0.5;
					
					alpY--; if (alpY < 0 || alpY > delayY) {alpY = delayY;}
					inputSampleL += (aYL[alpY]);
					inputSampleR += (aYR[alpY]);
					if (damp > 2) {
						avgtemp = inputSampleL;
						inputSampleL += avgYL;
						inputSampleL *= 0.5;
						avgYL = avgtemp;
						
						avgtemp = inputSampleR;
						inputSampleR += avgYR;
						inputSampleR *= 0.5;
						avgYR = avgtemp;
					}
					//allpass filter Y
				case 1:
					allpasstemp = alpZ - 1;
					if (allpasstemp < 0 || allpasstemp > delayZ) {allpasstemp = delayZ;}
					inputSampleL -= aZL[allpasstemp]*0.5;
					aZL[alpZ] = inputSampleL;
					inputSampleL *= 0.5;
					
					inputSampleR -= aZR[allpasstemp]*0.5;
					aZR[alpZ] = inputSampleR;
					inputSampleR *= 0.5;
					
					alpZ--; if (alpZ < 0 || alpZ > delayZ) {alpZ = delayZ;}
					inputSampleL += (aZL[alpZ]);
					inputSampleR += (aZR[alpZ]);
					if (damp > 1) {
						avgtemp = inputSampleL;
						inputSampleL += avgZL;
						inputSampleL *= 0.5;
						avgZL = avgtemp;
						
						avgtemp = inputSampleR;
						inputSampleR += avgZR;
						inputSampleR *= 0.5;
						avgZR = avgtemp;
					}
					//allpass filter Z
			}
			
			feedbackL = inputSampleL * feedbacklevel;
			feedbackR = inputSampleR * feedbacklevel;
			
			if (gain != 1.0) {
				inputSampleL *= gain;
				inputSampleR *= gain;
			}
			//we can pad with the gain to tame distortyness from the PurestConsole code
			
			if (inputSampleL > 1.0) inputSampleL = 1.0;
			if (inputSampleL < -1.0) inputSampleL = -1.0;
			if (inputSampleR > 1.0) inputSampleR = 1.0;
			if (inputSampleR < -1.0) inputSampleR = -1.0;
			//without this, you can get a NaN condition where it spits out DC offset at full blast!
			
			inputSampleL = asin(inputSampleL);
			inputSampleR = asin(inputSampleR);
			
			
			if (wet !=1.0) {
				inputSampleL = (inputSampleL * wet) + (drySampleL * (1.0-wet));
				inputSampleR = (inputSampleR * wet) + (drySampleR * (1.0-wet));
			}
			//Dry/Wet control, defaults to the last slider
			
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
 	double aAL[15150];
	double aBL[14618];
	double aCL[14358];
	double aDL[13818];		
	double aEL[13562];
	double aFL[13046];
	double aGL[11966];
	double aHL[11130];
	double aIL[10598];
	double aJL[9810];
	double aKL[9522];
	double aLL[8982];
	double aML[8786];
	double aNL[8462];
	double aOL[8310];
	double aPL[7982];
	double aQL[7322];
	double aRL[6818];
	double aSL[6506];
	double aTL[6002];
	double aUL[5838];
	double aVL[5502];
	double aWL[5010];
	double aXL[4850];
	double aYL[4296];
	double aZL[4180];
		
	double avgAL;
	double avgBL;
	double avgCL;
	double avgDL;
	double avgEL;
	double avgFL;
	double avgGL;
	double avgHL;
	double avgIL;
	double avgJL;
	double avgKL;
	double avgLL;
	double avgML;
	double avgNL;
	double avgOL;
	double avgPL;
	double avgQL;
	double avgRL;
	double avgSL;
	double avgTL;
	double avgUL;
	double avgVL;
	double avgWL;
	double avgXL;
	double avgYL;
	double avgZL;
	
	double feedbackL;
	
	double aAR[15150];
	double aBR[14618];
	double aCR[14358];
	double aDR[13818];		
	double aER[13562];
	double aFR[13046];
	double aGR[11966];
	double aHR[11130];
	double aIR[10598];
	double aJR[9810];
	double aKR[9522];
	double aLR[8982];
	double aMR[8786];
	double aNR[8462];
	double aOR[8310];
	double aPR[7982];
	double aQR[7322];
	double aRR[6818];
	double aSR[6506];
	double aTR[6002];
	double aUR[5838];
	double aVR[5502];
	double aWR[5010];
	double aXR[4850];
	double aYR[4296];
	double aZR[4180];
	
	double avgAR;
	double avgBR;
	double avgCR;
	double avgDR;
	double avgER;
	double avgFR;
	double avgGR;
	double avgHR;
	double avgIR;
	double avgJR;
	double avgKR;
	double avgLR;
	double avgMR;
	double avgNR;
	double avgOR;
	double avgPR;
	double avgQR;
	double avgRR;
	double avgSR;
	double avgTR;
	double avgUR;
	double avgVR;
	double avgWR;
	double avgXR;
	double avgYR;
	double avgZR;
	
	double feedbackR;
	
	//these are delay lengths and same for both sides
	int alpA, delayA;
	int alpB, delayB;
	int alpC, delayC;
	int alpD, delayD;
	int alpE, delayE;
	int alpF, delayF;
	int alpG, delayG;
	int alpH, delayH;
	int alpI, delayI;
	int alpJ, delayJ;
	int alpK, delayK;
	int alpL, delayL;
	int alpM, delayM;
	int alpN, delayN;
	int alpO, delayO;
	int alpP, delayP;
	int alpQ, delayQ;
	int alpR, delayR;
	int alpS, delayS;
	int alpT, delayT;
	int alpU, delayU;
	int alpV, delayV;
	int alpW, delayW;
	int alpX, delayX;
	int alpY, delayY;
	int alpZ, delayZ;   
		uint32_t fpd;
	//default stuff

};
MIN_EXTERNAL(mv);

