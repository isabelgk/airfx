#include "c74_min.h"

using namespace c74::min;

class verbity : public object<verbity>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"reverb with feedforward reverb topology"};
	MIN_TAGS {"audio, effect"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "Bigness", 0.25, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "Longness", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "Darkness", 0.25, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "Wetness", 0.25, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.25;
			B = 0.0;
			C = 0.25;
			D = 0.25;
			
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
			
			feedbackAL = 0.0; feedbackAR = 0.0;
			feedbackBL = 0.0; feedbackBR = 0.0;
			feedbackCL = 0.0; feedbackCR = 0.0;
			feedbackDL = 0.0; feedbackDR = 0.0;
			previousAL = 0.0; previousAR = 0.0;
			previousBL = 0.0; previousBR = 0.0;
			previousCL = 0.0; previousCR = 0.0;
			previousDL = 0.0; previousDR = 0.0;
			
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
			cycle = 0;
			
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
		
		int cycleEnd = floor(overallscale);
		if (cycleEnd < 1) cycleEnd = 1;
		if (cycleEnd > 4) cycleEnd = 4;
		//this is going to be 2 for 88.1 or 96k, 3 for silly people, 4 for 176 or 192k
		if (cycle > cycleEnd-1) cycle = cycleEnd-1; //sanity check
		
		double size = (A*1.77)+0.1;
		double regen = 0.0625+(B*0.03125); //0.09375 max;
		double lowpass = (1.0-pow(C,2.0))/sqrt(overallscale);
		double interpolate = pow(C,2.0)*0.618033988749894848204586; //has IIRlike qualities
		double thunderAmount = (0.3-(B*0.22))*C*0.1;
		double wet = D*2.0;
		double dry = 2.0 - wet;
		if (wet > 1.0) wet = 1.0;
		if (wet < 0.0) wet = 0.0;
		if (dry > 1.0) dry = 1.0;
		if (dry < 0.0) dry = 0.0;
		//this reverb makes 50% full dry AND full wet, not crossfaded.
		//that's so it can be on submixes without cutting back dry channel when adjusted:
		//unless you go super heavy, you are only adjusting the added verb loudness.
		
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
	    
		while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpdL * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpdR * 1.18e-43;
			long double drySampleL = inputSampleL;
			long double drySampleR = inputSampleR;
	
			if (fabs(iirAL)<1.18e-37) iirAL = 0.0;
			iirAL = (iirAL*(1.0-lowpass))+(inputSampleL*lowpass); inputSampleL = iirAL;
			if (fabs(iirAR)<1.18e-37) iirAR = 0.0;
			iirAR = (iirAR*(1.0-lowpass))+(inputSampleR*lowpass); inputSampleR = iirAR;
			//initial filter
			
			cycle++;
			if (cycle == cycleEnd) { //hit the end point and we do a reverb sample
				feedbackAL = (feedbackAL*(1.0-interpolate))+(previousAL*interpolate); previousAL = feedbackAL;
				feedbackBL = (feedbackBL*(1.0-interpolate))+(previousBL*interpolate); previousBL = feedbackBL;
				feedbackCL = (feedbackCL*(1.0-interpolate))+(previousCL*interpolate); previousCL = feedbackCL;
				feedbackDL = (feedbackDL*(1.0-interpolate))+(previousDL*interpolate); previousDL = feedbackDL;
				feedbackAR = (feedbackAR*(1.0-interpolate))+(previousAR*interpolate); previousAR = feedbackAR;
				feedbackBR = (feedbackBR*(1.0-interpolate))+(previousBR*interpolate); previousBR = feedbackBR;
				feedbackCR = (feedbackCR*(1.0-interpolate))+(previousCR*interpolate); previousCR = feedbackCR;
				feedbackDR = (feedbackDR*(1.0-interpolate))+(previousDR*interpolate); previousDR = feedbackDR;
				
				thunderL = (thunderL*0.99)-(feedbackAL*thunderAmount);
				thunderR = (thunderR*0.99)-(feedbackAR*thunderAmount);
				
				aIL[countI] = inputSampleL + ((feedbackAL+thunderL) * regen);
				aJL[countJ] = inputSampleL + (feedbackBL * regen);
				aKL[countK] = inputSampleL + (feedbackCL * regen);
				aLL[countL] = inputSampleL + (feedbackDL * regen);
				aIR[countI] = inputSampleR + ((feedbackAR+thunderR) * regen);
				aJR[countJ] = inputSampleR + (feedbackBR * regen);
				aKR[countK] = inputSampleR + (feedbackCR * regen);
				aLR[countL] = inputSampleR + (feedbackDR * regen);
				
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
			
			if (wet < 1.0) {inputSampleL *= wet; inputSampleR *= wet;}
			if (dry < 1.0) {drySampleL *= dry; drySampleR *= dry;}
			inputSampleL += drySampleL;
			inputSampleR += drySampleR;
			//this is our submix verb dry/wet: 0.5 is BOTH at FULL VOLUME
			//purpose is that, if you're adding verb, you're not altering other balances
			
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
	
	double feedbackAL;
	double feedbackBL;
	double feedbackCL;
	double feedbackDL;
	double previousAL;
	double previousBL;
	double previousCL;
	double previousDL;
	
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
	double previousAR;
	double previousBR;
	double previousCR;
	double previousDR;
	
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
	int cycle; //all these ints are shared across channels, not duplicated
		
	uint32_t fpdL;
	uint32_t fpdR;
	//default stuff

};
MIN_EXTERNAL(verbity);

