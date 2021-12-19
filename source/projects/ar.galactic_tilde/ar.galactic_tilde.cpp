#include "c74_min.h"

using namespace c74::min;

class galactic : public object<galactic>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"super-reverb designed specially for pads and space ambient"};
	MIN_TAGS {"audio, effect, reverb"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "replace", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "brightness", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "detune", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "bigness", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> E {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.5;
			B = 0.5;
			C = 0.5;
			D = 1.0;
			E = 1.0;
			
			iirAL = 0.0; iirAR = 0.0;
			iirBL = 0.0; iirBR = 0.0;
			
			for(int count = 0; count < 6479; count++) {aIL[count] = 0.0;aIR[count] = 0.0;}
			for(int count = 0; count < 3659; count++) {aJL[count] = 0.0;aJR[count] = 0.0;}
			for(int count = 0; count < 1719; count++) {aKL[count] = 0.0;aKR[count] = 0.0;}
			for(int count = 0; count < 679; count++) {aLL[count] = 0.0;aLR[count] = 0.0;}
			
			for(int count = 0; count < 9699; count++) {aAL[count] = 0.0;aAR[count] = 0.0;}
			for(int count = 0; count < 5999; count++) {aBL[count] = 0.0;aBR[count] = 0.0;}
			for(int count = 0; count < 2319; count++) {aCL[count] = 0.0;aCR[count] = 0.0;}
			for(int count = 0; count < 939; count++) {aDL[count] = 0.0;aDR[count] = 0.0;}
			
			for(int count = 0; count < 15219; count++) {aEL[count] = 0.0;aER[count] = 0.0;}
			for(int count = 0; count < 8459; count++) {aFL[count] = 0.0;aFR[count] = 0.0;}
			for(int count = 0; count < 4539; count++) {aGL[count] = 0.0;aGR[count] = 0.0;}
			for(int count = 0; count < 3199; count++) {aHL[count] = 0.0;aHR[count] = 0.0;}
			
			for(int count = 0; count < 3110; count++) {aML[count] = aMR[count] = 0.0;}	
			
			feedbackAL = 0.0; feedbackAR = 0.0;
			feedbackBL = 0.0; feedbackBR = 0.0;
			feedbackCL = 0.0; feedbackCR = 0.0;
			feedbackDL = 0.0; feedbackDR = 0.0;
			
			for(int count = 0; count < 6; count++) {lastRefL[count] = 0.0;lastRefR[count] = 0.0;}
			
			thunderL = 0; thunderR = 0;
			
			countI = 1;
			countJ = 1;
			countK = 1;
			countL = 1;
			
			countA = 1;
			countB = 1;
			countC = 1;
			countD = 1;	
			
			countE = 1;
			countF = 1;
			countG = 1;
			countH = 1;
			countM = 1;
			//the predelay
			cycle = 0;
			
			vibM = 3.0;
			
			oldfpd = 429496.7295;
				
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
		double overallscale = 1.0;
		overallscale /= 44100.0;
		overallscale *= samplerate();

		long sampleFrames = _input.frame_count();
		
		int cycleEnd = floor(overallscale);
		if (cycleEnd < 1) cycleEnd = 1;
		if (cycleEnd > 4) cycleEnd = 4;
		//this is going to be 2 for 88.1 or 96k, 3 for silly people, 4 for 176 or 192k
		if (cycle > cycleEnd-1) cycle = cycleEnd-1; //sanity check
		
		double regen = 0.0625+((1.0-A)*0.0625);
		double attenuate = (1.0 - (regen / 0.125))*1.333;
		double lowpass = pow(1.00001-(1.0-B),2.0)/sqrt(overallscale);
		double drift = pow(C,3)*0.001;
		double size = (D*1.77)+0.1;
		double wet = 1.0-(pow(1.0-E,3));
		
		delayI = 3407.0*size;
		delayJ = 1823.0*size;
		delayK = 859.0*size;
		delayL = 331.0*size;
		delayA = 4801.0*size;
		delayB = 2909.0*size;
		delayC = 1153.0*size;
		delayD = 461.0*size;
		delayE = 7607.0*size;
		delayF = 4217.0*size;
		delayG = 2269.0*size;
		delayH = 1597.0*size;
		delayM = 256;
		
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpdL * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpdR * 1.18e-43;
			long double drySampleL = inputSampleL;
			long double drySampleR = inputSampleR;
			
			vibM += (oldfpd*drift);
			if (vibM > (3.141592653589793238*2.0)) {
				vibM = 0.0;
				oldfpd = 0.4294967295+(fpdL*0.0000000000618);
			}
			
			aML[countM] = inputSampleL * attenuate;
			aMR[countM] = inputSampleR * attenuate;
			countM++; if (countM < 0 || countM > delayM) countM = 0;
			
			double offsetML = (sin(vibM)+1.0)*127;
			double offsetMR = (sin(vibM+(3.141592653589793238/2.0))+1.0)*127;
			int workingML = countM + offsetML;
			int workingMR = countM + offsetMR;
			double interpolML = (aML[workingML-((workingML > delayM)?delayM+1:0)] * (1-(offsetML-floor(offsetML))));
			interpolML += (aML[workingML+1-((workingML+1 > delayM)?delayM+1:0)] * ((offsetML-floor(offsetML))) );
			double interpolMR = (aMR[workingMR-((workingMR > delayM)?delayM+1:0)] * (1-(offsetMR-floor(offsetMR))));
			interpolMR += (aMR[workingMR+1-((workingMR+1 > delayM)?delayM+1:0)] * ((offsetMR-floor(offsetMR))) );
			inputSampleL = interpolML;
			inputSampleR = interpolMR;
			//predelay that applies vibrato
			//want vibrato speed AND depth like in MatrixVerb
			
			if (fabs(iirAL)<1.18e-37) iirAL = 0.0;
			iirAL = (iirAL*(1.0-lowpass))+(inputSampleL*lowpass); inputSampleL = iirAL;
			if (fabs(iirAR)<1.18e-37) iirAR = 0.0;
			iirAR = (iirAR*(1.0-lowpass))+(inputSampleR*lowpass); inputSampleR = iirAR;
			//initial filter
			
			cycle++;
			if (cycle == cycleEnd) { //hit the end point and we do a reverb sample
				aIL[countI] = inputSampleL + (feedbackAR * regen);
				aJL[countJ] = inputSampleL + (feedbackBR * regen);
				aKL[countK] = inputSampleL + (feedbackCR * regen);
				aLL[countL] = inputSampleL + (feedbackDR * regen);
				aIR[countI] = inputSampleR + (feedbackAL * regen);
				aJR[countJ] = inputSampleR + (feedbackBL * regen);
				aKR[countK] = inputSampleR + (feedbackCL * regen);
				aLR[countL] = inputSampleR + (feedbackDL * regen);
				
				countI++; if (countI < 0 || countI > delayI) countI = 0;
				countJ++; if (countJ < 0 || countJ > delayJ) countJ = 0;
				countK++; if (countK < 0 || countK > delayK) countK = 0;
				countL++; if (countL < 0 || countL > delayL) countL = 0;
				
				double outIL = aIL[countI-((countI > delayI)?delayI+1:0)];
				double outJL = aJL[countJ-((countJ > delayJ)?delayJ+1:0)];
				double outKL = aKL[countK-((countK > delayK)?delayK+1:0)];
				double outLL = aLL[countL-((countL > delayL)?delayL+1:0)];
				double outIR = aIR[countI-((countI > delayI)?delayI+1:0)];
				double outJR = aJR[countJ-((countJ > delayJ)?delayJ+1:0)];
				double outKR = aKR[countK-((countK > delayK)?delayK+1:0)];
				double outLR = aLR[countL-((countL > delayL)?delayL+1:0)];
				//first block: now we have four outputs
				
				aAL[countA] = (outIL - (outJL + outKL + outLL));
				aBL[countB] = (outJL - (outIL + outKL + outLL));
				aCL[countC] = (outKL - (outIL + outJL + outLL));
				aDL[countD] = (outLL - (outIL + outJL + outKL));
				aAR[countA] = (outIR - (outJR + outKR + outLR));
				aBR[countB] = (outJR - (outIR + outKR + outLR));
				aCR[countC] = (outKR - (outIR + outJR + outLR));
				aDR[countD] = (outLR - (outIR + outJR + outKR));
				
				countA++; if (countA < 0 || countA > delayA) countA = 0;
				countB++; if (countB < 0 || countB > delayB) countB = 0;
				countC++; if (countC < 0 || countC > delayC) countC = 0;
				countD++; if (countD < 0 || countD > delayD) countD = 0;
				
				double outAL = aAL[countA-((countA > delayA)?delayA+1:0)];
				double outBL = aBL[countB-((countB > delayB)?delayB+1:0)];
				double outCL = aCL[countC-((countC > delayC)?delayC+1:0)];
				double outDL = aDL[countD-((countD > delayD)?delayD+1:0)];
				double outAR = aAR[countA-((countA > delayA)?delayA+1:0)];
				double outBR = aBR[countB-((countB > delayB)?delayB+1:0)];
				double outCR = aCR[countC-((countC > delayC)?delayC+1:0)];
				double outDR = aDR[countD-((countD > delayD)?delayD+1:0)];
				//second block: four more outputs
				
				aEL[countE] = (outAL - (outBL + outCL + outDL));
				aFL[countF] = (outBL - (outAL + outCL + outDL));
				aGL[countG] = (outCL - (outAL + outBL + outDL));
				aHL[countH] = (outDL - (outAL + outBL + outCL));
				aER[countE] = (outAR - (outBR + outCR + outDR));
				aFR[countF] = (outBR - (outAR + outCR + outDR));
				aGR[countG] = (outCR - (outAR + outBR + outDR));
				aHR[countH] = (outDR - (outAR + outBR + outCR));
				
				countE++; if (countE < 0 || countE > delayE) countE = 0;
				countF++; if (countF < 0 || countF > delayF) countF = 0;
				countG++; if (countG < 0 || countG > delayG) countG = 0;
				countH++; if (countH < 0 || countH > delayH) countH = 0;
				
				double outEL = aEL[countE-((countE > delayE)?delayE+1:0)];
				double outFL = aFL[countF-((countF > delayF)?delayF+1:0)];
				double outGL = aGL[countG-((countG > delayG)?delayG+1:0)];
				double outHL = aHL[countH-((countH > delayH)?delayH+1:0)];
				double outER = aER[countE-((countE > delayE)?delayE+1:0)];
				double outFR = aFR[countF-((countF > delayF)?delayF+1:0)];
				double outGR = aGR[countG-((countG > delayG)?delayG+1:0)];
				double outHR = aHR[countH-((countH > delayH)?delayH+1:0)];
				//third block: final outputs
				
				feedbackAL = (outEL - (outFL + outGL + outHL));
				feedbackBL = (outFL - (outEL + outGL + outHL));
				feedbackCL = (outGL - (outEL + outFL + outHL));
				feedbackDL = (outHL - (outEL + outFL + outGL));
				feedbackAR = (outER - (outFR + outGR + outHR));
				feedbackBR = (outFR - (outER + outGR + outHR));
				feedbackCR = (outGR - (outER + outFR + outHR));
				feedbackDR = (outHR - (outER + outFR + outGR));
				//which we need to feed back into the input again, a bit
				
				inputSampleL = (outEL + outFL + outGL + outHL)/8.0;
				inputSampleR = (outER + outFR + outGR + outHR)/8.0;
				//and take the final combined sum of outputs
				if (cycleEnd == 4) {
					lastRefL[0] = lastRefL[4]; //start from previous last
					lastRefL[2] = (lastRefL[0] + inputSampleL)/2; //half
					lastRefL[1] = (lastRefL[0] + lastRefL[2])/2; //one quarter
					lastRefL[3] = (lastRefL[2] + inputSampleL)/2; //three quarters
					lastRefL[4] = inputSampleL; //full
					lastRefR[0] = lastRefR[4]; //start from previous last
					lastRefR[2] = (lastRefR[0] + inputSampleR)/2; //half
					lastRefR[1] = (lastRefR[0] + lastRefR[2])/2; //one quarter
					lastRefR[3] = (lastRefR[2] + inputSampleR)/2; //three quarters
					lastRefR[4] = inputSampleR; //full
				}
				if (cycleEnd == 3) {
					lastRefL[0] = lastRefL[3]; //start from previous last
					lastRefL[2] = (lastRefL[0]+lastRefL[0]+inputSampleL)/3; //third
					lastRefL[1] = (lastRefL[0]+inputSampleL+inputSampleL)/3; //two thirds
					lastRefL[3] = inputSampleL; //full
					lastRefR[0] = lastRefR[3]; //start from previous last
					lastRefR[2] = (lastRefR[0]+lastRefR[0]+inputSampleR)/3; //third
					lastRefR[1] = (lastRefR[0]+inputSampleR+inputSampleR)/3; //two thirds
					lastRefR[3] = inputSampleR; //full
				}
				if (cycleEnd == 2) {
					lastRefL[0] = lastRefL[2]; //start from previous last
					lastRefL[1] = (lastRefL[0] + inputSampleL)/2; //half
					lastRefL[2] = inputSampleL; //full
					lastRefR[0] = lastRefR[2]; //start from previous last
					lastRefR[1] = (lastRefR[0] + inputSampleR)/2; //half
					lastRefR[2] = inputSampleR; //full
				}
				cycle = 0; //reset
			} else {
				inputSampleL = lastRefL[cycle];
				inputSampleR = lastRefR[cycle];
				//we are going through our references now
			}
			
			if (fabs(iirBL)<1.18e-37) iirBL = 0.0;
			iirBL = (iirBL*(1.0-lowpass))+(inputSampleL*lowpass); inputSampleL = iirBL;
			if (fabs(iirBR)<1.18e-37) iirBR = 0.0;
			iirBR = (iirBR*(1.0-lowpass))+(inputSampleR*lowpass); inputSampleR = iirBR;
			//end filter
			
			if (wet < 1.0) {
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

	double iirAL;
	double iirBL;
	
	double aIL[6480];
	double aJL[3660];
	double aKL[1720];
	double aLL[680];
	
	double aAL[9700];
	double aBL[6000];
	double aCL[2320];
	double aDL[940];
	
	double aEL[15220];
	double aFL[8460];
	double aGL[4540];
	double aHL[3200];
	
	double aML[3111];
	double aMR[3111];
	double vibML, vibMR, depthM, oldfpd;
	
	double feedbackAL;
	double feedbackBL;
	double feedbackCL;
	double feedbackDL;
	
	double lastRefL[7];
	double thunderL;
	
	double iirAR;
	double iirBR;
	
	double aIR[6480];
	double aJR[3660];
	double aKR[1720];
	double aLR[680];
	
	double aAR[9700];
	double aBR[6000];
	double aCR[2320];
	double aDR[940];
	
	double aER[15220];
	double aFR[8460];
	double aGR[4540];
	double aHR[3200];
	
	double feedbackAR;
	double feedbackBR;
	double feedbackCR;
	double feedbackDR;
	
	double lastRefR[7];
	double thunderR;
	
	int countA, delayA;
	int countB, delayB;
	int countC, delayC;
	int countD, delayD;
	int countE, delayE;
	int countF, delayF;
	int countG, delayG;
	int countH, delayH;
	int countI, delayI;
	int countJ, delayJ;
	int countK, delayK;
	int countL, delayL;
	int countM, delayM;
	int cycle; //all these ints are shared across channels, not duplicated
	
	double vibM;
		
	uint32_t fpdL;
	uint32_t fpdR;
	//default stuff

};
MIN_EXTERNAL(galactic);

