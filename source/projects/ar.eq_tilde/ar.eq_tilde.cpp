#include "c74_min.h"

using namespace c74::min;

class eq : public object<eq>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"EQ is just the EQ parts of CStrip."};
	MIN_TAGS {"equalizer"};
	MIN_AUTHOR {"Christopher Herb"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "treble", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "mid", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "bass", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "lowpass", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> E {this, "trebfrq", 0.4, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> F {this, "bassfrq", 0.4, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> G {this, "hipass", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> H {this, "outgain", 0.5, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			lastSampleL = 0.0;
			last2SampleL = 0.0;
			lastSampleR = 0.0;
			last2SampleR = 0.0;
			
			iirHighSampleLA = 0.0;
			iirHighSampleLB = 0.0;
			iirHighSampleLC = 0.0;
			iirHighSampleLD = 0.0;
			iirHighSampleLE = 0.0;
			iirLowSampleLA = 0.0;
			iirLowSampleLB = 0.0;
			iirLowSampleLC = 0.0;
			iirLowSampleLD = 0.0;
			iirLowSampleLE = 0.0;
			iirHighSampleL = 0.0;
			iirLowSampleL = 0.0;
			
			iirHighSampleRA = 0.0;
			iirHighSampleRB = 0.0;
			iirHighSampleRC = 0.0;
			iirHighSampleRD = 0.0;
			iirHighSampleRE = 0.0;
			iirLowSampleRA = 0.0;
			iirLowSampleRB = 0.0;
			iirLowSampleRC = 0.0;
			iirLowSampleRD = 0.0;
			iirLowSampleRE = 0.0;
			iirHighSampleR = 0.0;
			iirLowSampleR = 0.0;
			
			tripletLA = 0.0;
			tripletLB = 0.0;
			tripletLC = 0.0;
			tripletFactorL = 0.0;
			
			tripletRA = 0.0;
			tripletRB = 0.0;
			tripletRC = 0.0;
			tripletFactorR = 0.0;
			
			lowpassSampleLAA = 0.0;
			lowpassSampleLAB = 0.0;
			lowpassSampleLBA = 0.0;
			lowpassSampleLBB = 0.0;
			lowpassSampleLCA = 0.0;
			lowpassSampleLCB = 0.0;
			lowpassSampleLDA = 0.0;
			lowpassSampleLDB = 0.0;
			lowpassSampleLE = 0.0;
			lowpassSampleLF = 0.0;
			lowpassSampleLG = 0.0;
			
			lowpassSampleRAA = 0.0;
			lowpassSampleRAB = 0.0;
			lowpassSampleRBA = 0.0;
			lowpassSampleRBB = 0.0;
			lowpassSampleRCA = 0.0;
			lowpassSampleRCB = 0.0;
			lowpassSampleRDA = 0.0;
			lowpassSampleRDB = 0.0;
			lowpassSampleRE = 0.0;
			lowpassSampleRF = 0.0;
			lowpassSampleRG = 0.0;
			
			highpassSampleLAA = 0.0;
			highpassSampleLAB = 0.0;
			highpassSampleLBA = 0.0;
			highpassSampleLBB = 0.0;
			highpassSampleLCA = 0.0;
			highpassSampleLCB = 0.0;
			highpassSampleLDA = 0.0;
			highpassSampleLDB = 0.0;
			highpassSampleLE = 0.0;
			highpassSampleLF = 0.0;
			
			highpassSampleRAA = 0.0;
			highpassSampleRAB = 0.0;
			highpassSampleRBA = 0.0;
			highpassSampleRBB = 0.0;
			highpassSampleRCA = 0.0;
			highpassSampleRCB = 0.0;
			highpassSampleRDA = 0.0;
			highpassSampleRDB = 0.0;
			highpassSampleRE = 0.0;
			highpassSampleRF = 0.0;
			
			flip = false;
			flipthree = 0;
			
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
		double compscale = overallscale;
		overallscale = samplerate();
		compscale = compscale * overallscale;
		//compscale is the one that's 1 or something like 2.2 for 96K rates
		
		double inputSampleL;
		double inputSampleR;
		
		double highSampleL = 0.0;
		double midSampleL = 0.0;
		double bassSampleL = 0.0;
		
		double highSampleR = 0.0;
		double midSampleR = 0.0;
		double bassSampleR = 0.0;
		
		double densityA = (A*12.0)-6.0;
		double densityB = (B*12.0)-6.0;
		double densityC = (C*12.0)-6.0;
		bool engageEQ = true;
		if ( (0.0 == densityA) && (0.0 == densityB) && (0.0 == densityC) ) engageEQ = false;
		
		densityA = pow(10.0,densityA/20.0)-1.0;
		densityB = pow(10.0,densityB/20.0)-1.0;
		densityC = pow(10.0,densityC/20.0)-1.0;
		//convert to 0 to X multiplier with 1.0 being O db
		//minus one gives nearly -1 to ? (should top out at 1)
		//calibrate so that X db roughly equals X db with maximum topping out at 1 internally
		
		double tripletIntensity = -densityA;
		
		double iirAmountC = (((D*D*15.0)+1.0)*0.0188) + 0.7;
		if (iirAmountC > 1.0) iirAmountC = 1.0;
		bool engageLowpass = false;
		if (((D*D*15.0)+1.0) < 15.99) engageLowpass = true;
		
		double iirAmountA = (((E*E*15.0)+1.0)*1000)/overallscale;
		double iirAmountB = (((F*F*1570.0)+30.0)*10)/overallscale;
		double iirAmountD = (((G*G*1570.0)+30.0)*1.0)/overallscale;
		bool engageHighpass = false;
		if (((G*G*1570.0)+30.0) > 30.01) engageHighpass = true;
		//bypass the highpass and lowpass if set to extremes
		double bridgerectifier;
		double outA = fabs(densityA);
		double outB = fabs(densityB);
		double outC = fabs(densityC);
		//end EQ
		double outputgain = pow(10.0,((H*36.0)-18.0)/20.0);
		
		while (--sampleFrames >= 0)
		{
			inputSampleL = *in1;
			inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-23) inputSampleL = fpdL * 1.18e-17;
			if (fabs(inputSampleR)<1.18e-23) inputSampleR = fpdR * 1.18e-17;
			
			last2SampleL = lastSampleL;
			lastSampleL = inputSampleL;
			
			last2SampleR = lastSampleR;
			lastSampleR = inputSampleR;
			
			flip = !flip;
			flipthree++;
			if (flipthree < 1 || flipthree > 3) flipthree = 1;
			//counters
			
			//begin highpass
			if (engageHighpass)
			{
				if (flip)
				{
					highpassSampleLAA = (highpassSampleLAA * (1.0 - iirAmountD)) + (inputSampleL * iirAmountD);
					inputSampleL -= highpassSampleLAA;
					highpassSampleLBA = (highpassSampleLBA * (1.0 - iirAmountD)) + (inputSampleL * iirAmountD);
					inputSampleL -= highpassSampleLBA;
					highpassSampleLCA = (highpassSampleLCA * (1.0 - iirAmountD)) + (inputSampleL * iirAmountD);
					inputSampleL -= highpassSampleLCA;
					highpassSampleLDA = (highpassSampleLDA * (1.0 - iirAmountD)) + (inputSampleL * iirAmountD);
					inputSampleL -= highpassSampleLDA;
				}
				else
				{
					highpassSampleLAB = (highpassSampleLAB * (1.0 - iirAmountD)) + (inputSampleL * iirAmountD);
					inputSampleL -= highpassSampleLAB;
					highpassSampleLBB = (highpassSampleLBB * (1.0 - iirAmountD)) + (inputSampleL * iirAmountD);
					inputSampleL -= highpassSampleLBB;
					highpassSampleLCB = (highpassSampleLCB * (1.0 - iirAmountD)) + (inputSampleL * iirAmountD);
					inputSampleL -= highpassSampleLCB;
					highpassSampleLDB = (highpassSampleLDB * (1.0 - iirAmountD)) + (inputSampleL * iirAmountD);
					inputSampleL -= highpassSampleLDB;
				}
				highpassSampleLE = (highpassSampleLE * (1.0 - iirAmountD)) + (inputSampleL * iirAmountD);
				inputSampleL -= highpassSampleLE;
				highpassSampleLF = (highpassSampleLF * (1.0 - iirAmountD)) + (inputSampleL * iirAmountD);
				inputSampleL -= highpassSampleLF;			
				
				if (flip)
				{
					highpassSampleRAA = (highpassSampleRAA * (1.0 - iirAmountD)) + (inputSampleR * iirAmountD);
					inputSampleR -= highpassSampleRAA;
					highpassSampleRBA = (highpassSampleRBA * (1.0 - iirAmountD)) + (inputSampleR * iirAmountD);
					inputSampleR -= highpassSampleRBA;
					highpassSampleRCA = (highpassSampleRCA * (1.0 - iirAmountD)) + (inputSampleR * iirAmountD);
					inputSampleR -= highpassSampleRCA;
					highpassSampleRDA = (highpassSampleRDA * (1.0 - iirAmountD)) + (inputSampleR * iirAmountD);
					inputSampleR -= highpassSampleRDA;
				}
				else
				{
					highpassSampleRAB = (highpassSampleRAB * (1.0 - iirAmountD)) + (inputSampleR * iirAmountD);
					inputSampleR -= highpassSampleRAB;
					highpassSampleRBB = (highpassSampleRBB * (1.0 - iirAmountD)) + (inputSampleR * iirAmountD);
					inputSampleR -= highpassSampleRBB;
					highpassSampleRCB = (highpassSampleRCB * (1.0 - iirAmountD)) + (inputSampleR * iirAmountD);
					inputSampleR -= highpassSampleRCB;
					highpassSampleRDB = (highpassSampleRDB * (1.0 - iirAmountD)) + (inputSampleR * iirAmountD);
					inputSampleR -= highpassSampleRDB;
				}
				highpassSampleRE = (highpassSampleRE * (1 - iirAmountD)) + (inputSampleR * iirAmountD);
				inputSampleR -= highpassSampleRE;
				highpassSampleRF = (highpassSampleRF * (1 - iirAmountD)) + (inputSampleR * iirAmountD);
				inputSampleR -= highpassSampleRF;			
				
			}
			//end highpass 
			
			//begin EQ
			if (engageEQ)
			{
				switch (flipthree)
				{
					case 1:
						tripletFactorL = last2SampleL - inputSampleL;
						tripletLA += tripletFactorL;
						tripletLC -= tripletFactorL;
						tripletFactorL = tripletLA * tripletIntensity;
						iirHighSampleLC = (iirHighSampleLC * (1.0 - iirAmountA)) + (inputSampleL * iirAmountA);
						highSampleL = inputSampleL - iirHighSampleLC;
						iirLowSampleLC = (iirLowSampleLC * (1.0 - iirAmountB)) + (inputSampleL * iirAmountB);
						bassSampleL = iirLowSampleLC;
						
						tripletFactorR = last2SampleR - inputSampleR;
						tripletRA += tripletFactorR;
						tripletRC -= tripletFactorR;
						tripletFactorR = tripletRA * tripletIntensity;
						iirHighSampleRC = (iirHighSampleRC * (1.0 - iirAmountA)) + (inputSampleR * iirAmountA);
						highSampleR = inputSampleR - iirHighSampleRC;
						iirLowSampleRC = (iirLowSampleRC * (1.0 - iirAmountB)) + (inputSampleR * iirAmountB);
						bassSampleR = iirLowSampleRC;
						break;
					case 2:
						tripletFactorL = last2SampleL - inputSampleL;
						tripletLB += tripletFactorL;
						tripletLA -= tripletFactorL;
						tripletFactorL = tripletLB * tripletIntensity;
						iirHighSampleLD = (iirHighSampleLD * (1.0 - iirAmountA)) + (inputSampleL * iirAmountA);
						highSampleL = inputSampleL - iirHighSampleLD;
						iirLowSampleLD = (iirLowSampleLD * (1.0 - iirAmountB)) + (inputSampleL * iirAmountB);
						bassSampleL = iirLowSampleLD;
						
						tripletFactorR = last2SampleR - inputSampleR;
						tripletRB += tripletFactorR;
						tripletRA -= tripletFactorR;
						tripletFactorR = tripletRB * tripletIntensity;
						iirHighSampleRD = (iirHighSampleRD * (1.0 - iirAmountA)) + (inputSampleR * iirAmountA);
						highSampleR = inputSampleR - iirHighSampleRD;
						iirLowSampleRD = (iirLowSampleRD * (1.0 - iirAmountB)) + (inputSampleR * iirAmountB);
						bassSampleR = iirLowSampleRD;
						break;
					case 3:
						tripletFactorL = last2SampleL - inputSampleL;
						tripletLC += tripletFactorL;
						tripletLB -= tripletFactorL;
						tripletFactorL = tripletLC * tripletIntensity;
						iirHighSampleLE = (iirHighSampleLE * (1.0 - iirAmountA)) + (inputSampleL * iirAmountA);
						highSampleL = inputSampleL - iirHighSampleLE;
						iirLowSampleLE = (iirLowSampleLE * (1.0 - iirAmountB)) + (inputSampleL * iirAmountB);
						bassSampleL = iirLowSampleLE;
						
						tripletFactorR = last2SampleR - inputSampleR;
						tripletRC += tripletFactorR;
						tripletRB -= tripletFactorR;
						tripletFactorR = tripletRC * tripletIntensity;
						iirHighSampleRE = (iirHighSampleRE * (1.0 - iirAmountA)) + (inputSampleR * iirAmountA);
						highSampleR = inputSampleR - iirHighSampleRE;
						iirLowSampleRE = (iirLowSampleRE * (1.0 - iirAmountB)) + (inputSampleR * iirAmountB);
						bassSampleR = iirLowSampleRE;
						break;
				}
				tripletLA /= 2.0;
				tripletLB /= 2.0;
				tripletLC /= 2.0;
				highSampleL = highSampleL + tripletFactorL;
				
				tripletRA /= 2.0;
				tripletRB /= 2.0;
				tripletRC /= 2.0;
				highSampleR = highSampleR + tripletFactorR;
				
				if (flip)
				{
					iirHighSampleLA = (iirHighSampleLA * (1.0 - iirAmountA)) + (highSampleL * iirAmountA);
					highSampleL -= iirHighSampleLA;
					iirLowSampleLA = (iirLowSampleLA * (1.0 - iirAmountB)) + (bassSampleL * iirAmountB);
					bassSampleL = iirLowSampleLA;
					
					iirHighSampleRA = (iirHighSampleRA * (1.0 - iirAmountA)) + (highSampleR * iirAmountA);
					highSampleR -= iirHighSampleRA;
					iirLowSampleRA = (iirLowSampleRA * (1.0 - iirAmountB)) + (bassSampleR * iirAmountB);
					bassSampleR = iirLowSampleRA;
				}
				else
				{
					iirHighSampleLB = (iirHighSampleLB * (1.0 - iirAmountA)) + (highSampleL * iirAmountA);
					highSampleL -= iirHighSampleLB;
					iirLowSampleLB = (iirLowSampleLB * (1.0 - iirAmountB)) + (bassSampleL * iirAmountB);
					bassSampleL = iirLowSampleLB;
					
					iirHighSampleRB = (iirHighSampleRB * (1.0 - iirAmountA)) + (highSampleR * iirAmountA);
					highSampleR -= iirHighSampleRB;
					iirLowSampleRB = (iirLowSampleRB * (1.0 - iirAmountB)) + (bassSampleR * iirAmountB);
					bassSampleR = iirLowSampleRB;
				}
				
				iirHighSampleL = (iirHighSampleL * (1.0 - iirAmountA)) + (highSampleL * iirAmountA);
				highSampleL -= iirHighSampleL;
				iirLowSampleL = (iirLowSampleL * (1.0 - iirAmountB)) + (bassSampleL * iirAmountB);
				bassSampleL = iirLowSampleL;
				
				iirHighSampleR = (iirHighSampleR * (1.0 - iirAmountA)) + (highSampleR * iirAmountA);
				highSampleR -= iirHighSampleR;
				iirLowSampleR = (iirLowSampleR * (1.0 - iirAmountB)) + (bassSampleR * iirAmountB);
				bassSampleR = iirLowSampleR;
				
				midSampleL = (inputSampleL-bassSampleL)-highSampleL;
				midSampleR = (inputSampleR-bassSampleR)-highSampleR;
				
				//drive section
				highSampleL *= (densityA+1.0);
				bridgerectifier = fabs(highSampleL)*1.57079633;
				if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
				//max value for sine function
				if (densityA > 0) bridgerectifier = sin(bridgerectifier);
				else bridgerectifier = 1-cos(bridgerectifier);
				//produce either boosted or starved version
				if (highSampleL > 0) highSampleL = (highSampleL*(1-outA))+(bridgerectifier*outA);
				else highSampleL = (highSampleL*(1-outA))-(bridgerectifier*outA);
				//blend according to densityA control
				
				highSampleR *= (densityA+1.0);
				bridgerectifier = fabs(highSampleR)*1.57079633;
				if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
				//max value for sine function
				if (densityA > 0) bridgerectifier = sin(bridgerectifier);
				else bridgerectifier = 1-cos(bridgerectifier);
				//produce either boosted or starved version
				if (highSampleR > 0) highSampleR = (highSampleR*(1-outA))+(bridgerectifier*outA);
				else highSampleR = (highSampleR*(1-outA))-(bridgerectifier*outA);
				//blend according to densityA control
				
				midSampleL *= (densityB+1.0);
				bridgerectifier = fabs(midSampleL)*1.57079633;
				if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
				//max value for sine function
				if (densityB > 0) bridgerectifier = sin(bridgerectifier);
				else bridgerectifier = 1-cos(bridgerectifier);
				//produce either boosted or starved version
				if (midSampleL > 0) midSampleL = (midSampleL*(1-outB))+(bridgerectifier*outB);
				else midSampleL = (midSampleL*(1-outB))-(bridgerectifier*outB);
				//blend according to densityB control
				
				midSampleR *= (densityB+1.0);
				bridgerectifier = fabs(midSampleR)*1.57079633;
				if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
				//max value for sine function
				if (densityB > 0) bridgerectifier = sin(bridgerectifier);
				else bridgerectifier = 1-cos(bridgerectifier);
				//produce either boosted or starved version
				if (midSampleR > 0) midSampleR = (midSampleR*(1-outB))+(bridgerectifier*outB);
				else midSampleR = (midSampleR*(1-outB))-(bridgerectifier*outB);
				//blend according to densityB control
				
				bassSampleL *= (densityC+1.0);
				bridgerectifier = fabs(bassSampleL)*1.57079633;
				if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
				//max value for sine function
				if (densityC > 0) bridgerectifier = sin(bridgerectifier);
				else bridgerectifier = 1-cos(bridgerectifier);
				//produce either boosted or starved version
				if (bassSampleL > 0) bassSampleL = (bassSampleL*(1-outC))+(bridgerectifier*outC);
				else bassSampleL = (bassSampleL*(1-outC))-(bridgerectifier*outC);
				//blend according to densityC control
				
				bassSampleR *= (densityC+1.0);
				bridgerectifier = fabs(bassSampleR)*1.57079633;
				if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
				//max value for sine function
				if (densityC > 0) bridgerectifier = sin(bridgerectifier);
				else bridgerectifier = 1-cos(bridgerectifier);
				//produce either boosted or starved version
				if (bassSampleR > 0) bassSampleR = (bassSampleR*(1-outC))+(bridgerectifier*outC);
				else bassSampleR = (bassSampleR*(1-outC))-(bridgerectifier*outC);
				//blend according to densityC control
				
				inputSampleL = midSampleL;
				inputSampleL += highSampleL;
				inputSampleL += bassSampleL;
				
				inputSampleR = midSampleR;
				inputSampleR += highSampleR;
				inputSampleR += bassSampleR;
			}
			//end EQ
			
			//EQ lowpass is after all processing like the compressor that might produce hash
			if (engageLowpass)
			{
				if (flip)
				{
					lowpassSampleLAA = (lowpassSampleLAA * (1.0 - iirAmountC)) + (inputSampleL * iirAmountC);
					inputSampleL = lowpassSampleLAA;
					lowpassSampleLBA = (lowpassSampleLBA * (1.0 - iirAmountC)) + (inputSampleL * iirAmountC);
					inputSampleL = lowpassSampleLBA;
					lowpassSampleLCA = (lowpassSampleLCA * (1.0 - iirAmountC)) + (inputSampleL * iirAmountC);
					inputSampleL = lowpassSampleLCA;
					lowpassSampleLDA = (lowpassSampleLDA * (1.0 - iirAmountC)) + (inputSampleL * iirAmountC);
					inputSampleL = lowpassSampleLDA;
					lowpassSampleLE = (lowpassSampleLE * (1.0 - iirAmountC)) + (inputSampleL * iirAmountC);
					inputSampleL = lowpassSampleLE;
					
					lowpassSampleRAA = (lowpassSampleRAA * (1.0 - iirAmountC)) + (inputSampleR * iirAmountC);
					inputSampleR = lowpassSampleRAA;
					lowpassSampleRBA = (lowpassSampleRBA * (1.0 - iirAmountC)) + (inputSampleR * iirAmountC);
					inputSampleR = lowpassSampleRBA;
					lowpassSampleRCA = (lowpassSampleRCA * (1.0 - iirAmountC)) + (inputSampleR * iirAmountC);
					inputSampleR = lowpassSampleRCA;
					lowpassSampleRDA = (lowpassSampleRDA * (1.0 - iirAmountC)) + (inputSampleR * iirAmountC);
					inputSampleR = lowpassSampleRDA;
					lowpassSampleRE = (lowpassSampleRE * (1.0 - iirAmountC)) + (inputSampleR * iirAmountC);
					inputSampleR = lowpassSampleRE;
				}
				else
				{
					lowpassSampleLAB = (lowpassSampleLAB * (1.0 - iirAmountC)) + (inputSampleL * iirAmountC);
					inputSampleL = lowpassSampleLAB;
					lowpassSampleLBB = (lowpassSampleLBB * (1.0 - iirAmountC)) + (inputSampleL * iirAmountC);
					inputSampleL = lowpassSampleLBB;
					lowpassSampleLCB = (lowpassSampleLCB * (1.0 - iirAmountC)) + (inputSampleL * iirAmountC);
					inputSampleL = lowpassSampleLCB;
					lowpassSampleLDB = (lowpassSampleLDB * (1.0 - iirAmountC)) + (inputSampleL * iirAmountC);
					inputSampleL = lowpassSampleLDB;
					lowpassSampleLF = (lowpassSampleLF * (1.0 - iirAmountC)) + (inputSampleL * iirAmountC);
					inputSampleL = lowpassSampleLF;			
					
					lowpassSampleRAB = (lowpassSampleRAB * (1.0 - iirAmountC)) + (inputSampleR * iirAmountC);
					inputSampleR = lowpassSampleRAB;
					lowpassSampleRBB = (lowpassSampleRBB * (1.0 - iirAmountC)) + (inputSampleR * iirAmountC);
					inputSampleR = lowpassSampleRBB;
					lowpassSampleRCB = (lowpassSampleRCB * (1.0 - iirAmountC)) + (inputSampleR * iirAmountC);
					inputSampleR = lowpassSampleRCB;
					lowpassSampleRDB = (lowpassSampleRDB * (1.0 - iirAmountC)) + (inputSampleR * iirAmountC);
					inputSampleR = lowpassSampleRDB;
					lowpassSampleRF = (lowpassSampleRF * (1.0 - iirAmountC)) + (inputSampleR * iirAmountC);
					inputSampleR = lowpassSampleRF;			
				}
				lowpassSampleLG = (lowpassSampleLG * (1.0 - iirAmountC)) + (inputSampleL * iirAmountC);
				lowpassSampleRG = (lowpassSampleRG * (1.0 - iirAmountC)) + (inputSampleR * iirAmountC);
				
				inputSampleL = (lowpassSampleLG * (1.0 - iirAmountC)) + (inputSampleL * iirAmountC);
				inputSampleR = (lowpassSampleRG * (1.0 - iirAmountC)) + (inputSampleR * iirAmountC);
			}
			
			//built in output trim and dry/wet if desired
			if (outputgain != 1.0) {
				inputSampleL *= outputgain;
				inputSampleR *= outputgain;
			}
			
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

			*in1++;
			*in2++;
			*out1++;
			*out2++;
		}
	}
private:
    
	uint32_t fpdL;
	uint32_t fpdR;
	//default stuff
	
	double lastSampleL;
	double last2SampleL;
	double lastSampleR;
	double last2SampleR;
	
	//begin EQ
	double iirHighSampleLA;
	double iirHighSampleLB;
	double iirHighSampleLC;
	double iirHighSampleLD;
	double iirHighSampleLE;
	double iirLowSampleLA;
	double iirLowSampleLB;
	double iirLowSampleLC;
	double iirLowSampleLD;
	double iirLowSampleLE;
	double iirHighSampleL;
	double iirLowSampleL;
	
	double iirHighSampleRA;
	double iirHighSampleRB;
	double iirHighSampleRC;
	double iirHighSampleRD;
	double iirHighSampleRE;
	double iirLowSampleRA;
	double iirLowSampleRB;
	double iirLowSampleRC;
	double iirLowSampleRD;
	double iirLowSampleRE;
	double iirHighSampleR;
	double iirLowSampleR;
	
	double tripletLA;
	double tripletLB;
	double tripletLC;
	double tripletFactorL;
	
	double tripletRA;
	double tripletRB;
	double tripletRC;
	double tripletFactorR;
	
	double lowpassSampleLAA;
	double lowpassSampleLAB;
	double lowpassSampleLBA;
	double lowpassSampleLBB;
	double lowpassSampleLCA;
	double lowpassSampleLCB;
	double lowpassSampleLDA;
	double lowpassSampleLDB;
	double lowpassSampleLE;
	double lowpassSampleLF;
	double lowpassSampleLG;
	
	double lowpassSampleRAA;
	double lowpassSampleRAB;
	double lowpassSampleRBA;
	double lowpassSampleRBB;
	double lowpassSampleRCA;
	double lowpassSampleRCB;
	double lowpassSampleRDA;
	double lowpassSampleRDB;
	double lowpassSampleRE;
	double lowpassSampleRF;
	double lowpassSampleRG;
	
	double highpassSampleLAA;
	double highpassSampleLAB;
	double highpassSampleLBA;
	double highpassSampleLBB;
	double highpassSampleLCA;
	double highpassSampleLCB;
	double highpassSampleLDA;
	double highpassSampleLDB;
	double highpassSampleLE;
	double highpassSampleLF;
	
	double highpassSampleRAA;
	double highpassSampleRAB;
	double highpassSampleRBA;
	double highpassSampleRBB;
	double highpassSampleRCA;
	double highpassSampleRCB;
	double highpassSampleRDA;
	double highpassSampleRDB;
	double highpassSampleRE;
	double highpassSampleRF;
	
	bool flip;
	int flipthree;
	//end EQ
};
MIN_EXTERNAL(eq);

