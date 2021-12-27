#include "c74_min.h"

using namespace c74::min;

class righteous4 : public object<righteous4>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a final output stage for targeting dynamic range"};
	MIN_TAGS {"utility"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "target", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "bitdepth", 0.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.0;
			B = 0.0;
		
			leftSampleA = 0.0;
			leftSampleB = 0.0;
			leftSampleC = 0.0;
			leftSampleD = 0.0;
			leftSampleE = 0.0;
			leftSampleF = 0.0;
			leftSampleG = 0.0;
			leftSampleH = 0.0;
			leftSampleI = 0.0;
			leftSampleJ = 0.0;
			leftSampleK = 0.0;
			leftSampleL = 0.0;
			leftSampleM = 0.0;
			leftSampleN = 0.0;
			leftSampleO = 0.0;
			leftSampleP = 0.0;
			leftSampleQ = 0.0;
			leftSampleR = 0.0;
			leftSampleS = 0.0;
			leftSampleT = 0.0;
			leftSampleU = 0.0;
			leftSampleV = 0.0;
			leftSampleW = 0.0;
			leftSampleX = 0.0;
			leftSampleY = 0.0;
			leftSampleZ = 0.0;
			
			rightSampleA = 0.0;
			rightSampleB = 0.0;
			rightSampleC = 0.0;
			rightSampleD = 0.0;
			rightSampleE = 0.0;
			rightSampleF = 0.0;
			rightSampleG = 0.0;
			rightSampleH = 0.0;
			rightSampleI = 0.0;
			rightSampleJ = 0.0;
			rightSampleK = 0.0;
			rightSampleL = 0.0;
			rightSampleM = 0.0;
			rightSampleN = 0.0;
			rightSampleO = 0.0;
			rightSampleP = 0.0;
			rightSampleQ = 0.0;
			rightSampleR = 0.0;
			rightSampleS = 0.0;
			rightSampleT = 0.0;
			rightSampleU = 0.0;
			rightSampleV = 0.0;
			rightSampleW = 0.0;
			rightSampleX = 0.0;
			rightSampleY = 0.0;
			rightSampleZ = 0.0;
			
			bynL[0] = 1000;
			bynL[1] = 301;
			bynL[2] = 176;
			bynL[3] = 125;
			bynL[4] = 97;
			bynL[5] = 79;
			bynL[6] = 67;
			bynL[7] = 58;
			bynL[8] = 51;
			bynL[9] = 46;
			bynL[10] = 1000;
			noiseShapingL = 0.0;
			lastSampleL = 0.0;
			IIRsampleL = 0.0;
			gwPrevL = 0.0;
			gwAL = 0.0;
			gwBL = 0.0;
			
			bynR[0] = 1000;
			bynR[1] = 301;
			bynR[2] = 176;
			bynR[3] = 125;
			bynR[4] = 97;
			bynR[5] = 79;
			bynR[6] = 67;
			bynR[7] = 58;
			bynR[8] = 51;
			bynR[9] = 46;
			bynR[10] = 1000;
			noiseShapingR = 0.0;
			lastSampleR = 0.0;
			IIRsampleR = 0.0;
			gwPrevR = 0.0;
			gwAR = 0.0;
			gwBR = 0.0;
			
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
		long double fpOld = 0.618033988749894848204586; //golden ratio!
		long double fpNew = 1.0 - fpOld;
		double IIRscaleback = 0.0002597;//scaleback of harmonic avg
		IIRscaleback /= overallscale;
		IIRscaleback = 1.0 - IIRscaleback;
		double target = (A*24.0)-28.0;
		target += 17; //gives us scaled distortion factor based on test conditions
		target = pow(10.0,target/20.0); //we will multiply and divide by this
		//ShortBuss section
		if (target == 0) target = 1; //insanity check
		int bitDepth = (uint32_t)( B * 2.999 )+1; // +1 for Reaper bug workaround
		double fusswithscale = 149940.0; //corrected
		double cutofffreq = 20; //was 46/2.0
		double midAmount = (cutofffreq)/fusswithscale;
		midAmount /= overallscale;
		double midaltAmount = 1.0 - midAmount;
		double gwAfactor = 0.718;
		gwAfactor -= (overallscale*0.05); //0.2 at 176K, 0.1 at 88.2K, 0.05 at 44.1K
		//reduce slightly to not less than 0.5 to increase effect
		double gwBfactor = 1.0 - gwAfactor;
		double softness = 0.2135;
		double hardness = 1.0 - softness;
		double refclip = pow(10.0,-0.0058888);
		
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (inputSampleL<1.2e-38 && -inputSampleL<1.2e-38) {
				static int noisesource = 0;
				//this declares a variable before anything else is compiled. It won't keep assigning
				//it to 0 for every sample, it's as if the declaration doesn't exist in this context,
				//but it lets me add this denormalization fix in a single place rather than updating
				//it in three different locations. The variable isn't thread-safe but this is only
				//a random seed and we can share it with whatever.
				noisesource = noisesource % 1700021; noisesource++;
				int residue = noisesource * noisesource;
				residue = residue % 170003; residue *= residue;
				residue = residue % 17011; residue *= residue;
				residue = residue % 1709; residue *= residue;
				residue = residue % 173; residue *= residue;
				residue = residue % 17;
				double applyresidue = residue;
				applyresidue *= 0.00000001;
				applyresidue *= 0.00000001;
				inputSampleL = applyresidue;
			}
			if (inputSampleR<1.2e-38 && -inputSampleR<1.2e-38) {
				static int noisesource = 0;
				noisesource = noisesource % 1700021; noisesource++;
				int residue = noisesource * noisesource;
				residue = residue % 170003; residue *= residue;
				residue = residue % 17011; residue *= residue;
				residue = residue % 1709; residue *= residue;
				residue = residue % 173; residue *= residue;
				residue = residue % 17;
				double applyresidue = residue;
				applyresidue *= 0.00000001;
				applyresidue *= 0.00000001;
				inputSampleR = applyresidue;
				//this denormalization routine produces a white noise at -300 dB which the noise
				//shaping will interact with to produce a bipolar output, but the noise is actually
				//all positive. That should stop any variables from going denormal, and the routine
				//only kicks in if digital black is input. As a final touch, if you save to 24-bit
				//the silence will return to being digital black again.
			}
			double drySampleL = inputSampleL;
			double drySampleR = inputSampleR;
			//begin the whole distortion dealiebop
			inputSampleL /= target;
			inputSampleR /= target;
			
			//running shortbuss on direct sample
			IIRsampleL *= IIRscaleback;
			double secondharmonicL = sin((2.0 * inputSampleL * inputSampleL) * IIRsampleL);
			IIRsampleR *= IIRscaleback;
			double secondharmonicR = sin((2.0 * inputSampleR * inputSampleR) * IIRsampleR);
			//secondharmonic is calculated before IIRsample is updated, to delay reaction
			
			long double bridgerectifier = inputSampleL;
			if (bridgerectifier > 1.2533141373155) bridgerectifier = 1.2533141373155;
			if (bridgerectifier < -1.2533141373155) bridgerectifier = -1.2533141373155;
			//clip to 1.2533141373155 to reach maximum output
			bridgerectifier = sin(bridgerectifier * fabs(bridgerectifier)) / ((bridgerectifier == 0.0) ?1:fabs(bridgerectifier));
			if (inputSampleL > bridgerectifier) IIRsampleL += ((inputSampleL - bridgerectifier)*0.0009);
			if (inputSampleL < -bridgerectifier) IIRsampleL += ((inputSampleL + bridgerectifier)*0.0009);
			//manipulate IIRSampleL
			inputSampleL = bridgerectifier;
			//apply the distortion transform for reals. Has been converted back to -1/1
			
			bridgerectifier = inputSampleR;
			if (bridgerectifier > 1.2533141373155) bridgerectifier = 1.2533141373155;
			if (bridgerectifier < -1.2533141373155) bridgerectifier = -1.2533141373155;
			//clip to 1.2533141373155 to reach maximum output
			bridgerectifier = sin(bridgerectifier * fabs(bridgerectifier)) / ((bridgerectifier == 0.0) ?1:fabs(bridgerectifier));
			if (inputSampleR > bridgerectifier) IIRsampleR += ((inputSampleR - bridgerectifier)*0.0009);
			if (inputSampleR < -bridgerectifier) IIRsampleR += ((inputSampleR + bridgerectifier)*0.0009);
			//manipulate IIRSampleR
			inputSampleR = bridgerectifier;
			//apply the distortion transform for reals. Has been converted back to -1/1
			
			
			//apply resonant highpass L
			double tempSample = inputSampleL;
			leftSampleA = (leftSampleA * midaltAmount) + (tempSample * midAmount); tempSample -= leftSampleA; double correction = leftSampleA;
			leftSampleB = (leftSampleB * midaltAmount) + (tempSample * midAmount); tempSample -= leftSampleB; correction += leftSampleB;
			leftSampleC = (leftSampleC * midaltAmount) + (tempSample * midAmount); tempSample -= leftSampleC; correction += leftSampleC;
			leftSampleD = (leftSampleD * midaltAmount) + (tempSample * midAmount); tempSample -= leftSampleD; correction += leftSampleD;
			leftSampleE = (leftSampleE * midaltAmount) + (tempSample * midAmount); tempSample -= leftSampleE; correction += leftSampleE;
			leftSampleF = (leftSampleF * midaltAmount) + (tempSample * midAmount); tempSample -= leftSampleF; correction += leftSampleF;
			leftSampleG = (leftSampleG * midaltAmount) + (tempSample * midAmount); tempSample -= leftSampleG; correction += leftSampleG;
			leftSampleH = (leftSampleH * midaltAmount) + (tempSample * midAmount); tempSample -= leftSampleH; correction += leftSampleH;
			leftSampleI = (leftSampleI * midaltAmount) + (tempSample * midAmount); tempSample -= leftSampleI; correction += leftSampleI;
			leftSampleJ = (leftSampleJ * midaltAmount) + (tempSample * midAmount); tempSample -= leftSampleJ; correction += leftSampleJ;
			leftSampleK = (leftSampleK * midaltAmount) + (tempSample * midAmount); tempSample -= leftSampleK; correction += leftSampleK;
			leftSampleL = (leftSampleL * midaltAmount) + (tempSample * midAmount); tempSample -= leftSampleL; correction += leftSampleL;
			leftSampleM = (leftSampleM * midaltAmount) + (tempSample * midAmount); tempSample -= leftSampleM; correction += leftSampleM;
			leftSampleN = (leftSampleN * midaltAmount) + (tempSample * midAmount); tempSample -= leftSampleN; correction += leftSampleN;
			leftSampleO = (leftSampleO * midaltAmount) + (tempSample * midAmount); tempSample -= leftSampleO; correction += leftSampleO;
			leftSampleP = (leftSampleP * midaltAmount) + (tempSample * midAmount); tempSample -= leftSampleP; correction += leftSampleP;
			leftSampleQ = (leftSampleQ * midaltAmount) + (tempSample * midAmount); tempSample -= leftSampleQ; correction += leftSampleQ;
			leftSampleR = (leftSampleR * midaltAmount) + (tempSample * midAmount); tempSample -= leftSampleR; correction += leftSampleR;
			leftSampleS = (leftSampleS * midaltAmount) + (tempSample * midAmount); tempSample -= leftSampleS; correction += leftSampleS;
			leftSampleT = (leftSampleT * midaltAmount) + (tempSample * midAmount); tempSample -= leftSampleT; correction += leftSampleT;
			leftSampleU = (leftSampleU * midaltAmount) + (tempSample * midAmount); tempSample -= leftSampleU; correction += leftSampleU;
			leftSampleV = (leftSampleV * midaltAmount) + (tempSample * midAmount); tempSample -= leftSampleV; correction += leftSampleV;
			leftSampleW = (leftSampleW * midaltAmount) + (tempSample * midAmount); tempSample -= leftSampleW; correction += leftSampleW;
			leftSampleX = (leftSampleX * midaltAmount) + (tempSample * midAmount); tempSample -= leftSampleX; correction += leftSampleX;
			leftSampleY = (leftSampleY * midaltAmount) + (tempSample * midAmount); tempSample -= leftSampleY; correction += leftSampleY;
			leftSampleZ = (leftSampleZ * midaltAmount) + (tempSample * midAmount); tempSample -= leftSampleZ; correction += leftSampleZ;
			correction *= fabs(secondharmonicL);
			//scale it directly by second harmonic: DC block is now adding harmonics too
			correction -= secondharmonicL*fpOld;
			//apply the shortbuss processing to output DCblock by subtracting it 
			//we are not a peak limiter! not using it to clip or nothin'
			//adding it inversely, it's the same as adding to inputsample only we are accumulating 'stuff' in 'correction'
			inputSampleL -= correction;
			if (inputSampleL < 0) inputSampleL = (inputSampleL * fpNew) - (sin(-inputSampleL)*fpOld);
			//lastly, class A clipping on the negative to combat the one-sidedness
			//uses bloom/antibloom to dial in previous unconstrained behavior
			//end the whole distortion dealiebop
			inputSampleL *= target;
			//begin simplified Groove Wear, outside the scaling
			//varies depending on what sample rate you're at:
			//high sample rate makes it more airy
			gwBL = gwAL; gwAL = tempSample = (inputSampleL-gwPrevL);
			tempSample *= gwAfactor;
			tempSample += (gwBL * gwBfactor);
			correction = (inputSampleL-gwPrevL) - tempSample;
			gwPrevL = inputSampleL;		
			inputSampleL -= correction;		
			//simplified Groove Wear L
			
			//apply resonant highpass R
			tempSample = inputSampleR;
			rightSampleA = (rightSampleA * midaltAmount) + (tempSample * midAmount); tempSample -= rightSampleA; correction = rightSampleA;
			rightSampleB = (rightSampleB * midaltAmount) + (tempSample * midAmount); tempSample -= rightSampleB; correction += rightSampleB;
			rightSampleC = (rightSampleC * midaltAmount) + (tempSample * midAmount); tempSample -= rightSampleC; correction += rightSampleC;
			rightSampleD = (rightSampleD * midaltAmount) + (tempSample * midAmount); tempSample -= rightSampleD; correction += rightSampleD;
			rightSampleE = (rightSampleE * midaltAmount) + (tempSample * midAmount); tempSample -= rightSampleE; correction += rightSampleE;
			rightSampleF = (rightSampleF * midaltAmount) + (tempSample * midAmount); tempSample -= rightSampleF; correction += rightSampleF;
			rightSampleG = (rightSampleG * midaltAmount) + (tempSample * midAmount); tempSample -= rightSampleG; correction += rightSampleG;
			rightSampleH = (rightSampleH * midaltAmount) + (tempSample * midAmount); tempSample -= rightSampleH; correction += rightSampleH;
			rightSampleI = (rightSampleI * midaltAmount) + (tempSample * midAmount); tempSample -= rightSampleI; correction += rightSampleI;
			rightSampleJ = (rightSampleJ * midaltAmount) + (tempSample * midAmount); tempSample -= rightSampleJ; correction += rightSampleJ;
			rightSampleK = (rightSampleK * midaltAmount) + (tempSample * midAmount); tempSample -= rightSampleK; correction += rightSampleK;
			rightSampleL = (rightSampleL * midaltAmount) + (tempSample * midAmount); tempSample -= rightSampleL; correction += rightSampleL;
			rightSampleM = (rightSampleM * midaltAmount) + (tempSample * midAmount); tempSample -= rightSampleM; correction += rightSampleM;
			rightSampleN = (rightSampleN * midaltAmount) + (tempSample * midAmount); tempSample -= rightSampleN; correction += rightSampleN;
			rightSampleO = (rightSampleO * midaltAmount) + (tempSample * midAmount); tempSample -= rightSampleO; correction += rightSampleO;
			rightSampleP = (rightSampleP * midaltAmount) + (tempSample * midAmount); tempSample -= rightSampleP; correction += rightSampleP;
			rightSampleQ = (rightSampleQ * midaltAmount) + (tempSample * midAmount); tempSample -= rightSampleQ; correction += rightSampleQ;
			rightSampleR = (rightSampleR * midaltAmount) + (tempSample * midAmount); tempSample -= rightSampleR; correction += rightSampleR;
			rightSampleS = (rightSampleS * midaltAmount) + (tempSample * midAmount); tempSample -= rightSampleS; correction += rightSampleS;
			rightSampleT = (rightSampleT * midaltAmount) + (tempSample * midAmount); tempSample -= rightSampleT; correction += rightSampleT;
			rightSampleU = (rightSampleU * midaltAmount) + (tempSample * midAmount); tempSample -= rightSampleU; correction += rightSampleU;
			rightSampleV = (rightSampleV * midaltAmount) + (tempSample * midAmount); tempSample -= rightSampleV; correction += rightSampleV;
			rightSampleW = (rightSampleW * midaltAmount) + (tempSample * midAmount); tempSample -= rightSampleW; correction += rightSampleW;
			rightSampleX = (rightSampleX * midaltAmount) + (tempSample * midAmount); tempSample -= rightSampleX; correction += rightSampleX;
			rightSampleY = (rightSampleY * midaltAmount) + (tempSample * midAmount); tempSample -= rightSampleY; correction += rightSampleY;
			rightSampleZ = (rightSampleZ * midaltAmount) + (tempSample * midAmount); tempSample -= rightSampleZ; correction += rightSampleZ;
			correction *= fabs(secondharmonicR);
			//scale it directly by second harmonic: DC block is now adding harmonics too
			correction -= secondharmonicR*fpOld;
			//apply the shortbuss processing to output DCblock by subtracting it 
			//we are not a peak limiter! not using it to clip or nothin'
			//adding it inversely, it's the same as adding to inputsample only we are accumulating 'stuff' in 'correction'
			inputSampleR -= correction;
			if (inputSampleR < 0) inputSampleR = (inputSampleR * fpNew) - (sin(-inputSampleR)*fpOld);
			//lastly, class A clipping on the negative to combat the one-sidedness
			//uses bloom/antibloom to dial in previous unconstrained behavior
			//end the whole distortion dealiebop
			inputSampleR *= target;
			//begin simplified Groove Wear, outside the scaling
			//varies depending on what sample rate you're at:
			//high sample rate makes it more airy
			gwBR = gwAR; gwAR = tempSample = (inputSampleR-gwPrevR);
			tempSample *= gwAfactor;
			tempSample += (gwBR * gwBfactor);
			correction = (inputSampleR-gwPrevR) - tempSample;
			gwPrevR = inputSampleR;		
			inputSampleR -= correction;		
			//simplified Groove Wear R
			
			//begin simplified ADClip L
			drySampleL = inputSampleL;
			if (lastSampleL >= refclip)
			{
				if (inputSampleL < refclip)
				{
					lastSampleL = ((refclip*hardness) + (inputSampleL * softness));
				}
				else lastSampleL = refclip;
			}
			
			if (lastSampleL <= -refclip)
			{
				if (inputSampleL > -refclip)
				{
					lastSampleL = ((-refclip*hardness) + (inputSampleL * softness));
				}
				else lastSampleL = -refclip;
			}
			
			if (inputSampleL > refclip)
			{
				if (lastSampleL < refclip)
				{
					inputSampleL = ((refclip*hardness) + (lastSampleL * softness));
				}
				else inputSampleL = refclip;
			}
			
			if (inputSampleL < -refclip)
			{
				if (lastSampleL > -refclip)
				{
					inputSampleL = ((-refclip*hardness) + (lastSampleL * softness));
				}
				else inputSampleL = -refclip;
			}
			lastSampleL = drySampleL;
			
			//begin simplified ADClip R
			drySampleR = inputSampleR;
			if (lastSampleR >= refclip)
			{
				if (inputSampleR < refclip)
				{
					lastSampleR = ((refclip*hardness) + (inputSampleR * softness));
				}
				else lastSampleR = refclip;
			}
			
			if (lastSampleR <= -refclip)
			{
				if (inputSampleR > -refclip)
				{
					lastSampleR = ((-refclip*hardness) + (inputSampleR * softness));
				}
				else lastSampleR = -refclip;
			}
			
			if (inputSampleR > refclip)
			{
				if (lastSampleR < refclip)
				{
					inputSampleR = ((refclip*hardness) + (lastSampleR * softness));
				}
				else inputSampleR = refclip;
			}
			
			if (inputSampleR < -refclip)
			{
				if (lastSampleR > -refclip)
				{
					inputSampleR = ((-refclip*hardness) + (lastSampleR * softness));
				}
				else inputSampleR = -refclip;
			}
			lastSampleR = drySampleR;
			
			//output dither section
			if (bitDepth == 3) {
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
			} else {
				//entire Naturalize section used when not on 32 bit out
				
				inputSampleL -= noiseShapingL;
				inputSampleR -= noiseShapingR;
				
				if (bitDepth == 2) {
					inputSampleL *= 8388608.0; //go to dither at 24 bit
					inputSampleR *= 8388608.0; //go to dither at 24 bit
				}
				if (bitDepth == 1) {
					inputSampleL *= 32768.0; //go to dither at 16 bit
					inputSampleR *= 32768.0; //go to dither at 16 bit
				}
				
				//begin L
				double benfordize = floor(inputSampleL);
				while (benfordize >= 1.0) {benfordize /= 10;}
				if (benfordize < 1.0) {benfordize *= 10;}
				if (benfordize < 1.0) {benfordize *= 10;}
				if (benfordize < 1.0) {benfordize *= 10;}
				if (benfordize < 1.0) {benfordize *= 10;}
				if (benfordize < 1.0) {benfordize *= 10;}
				int hotbinA = floor(benfordize);
				//hotbin becomes the Benford bin value for this number floored
				double totalA = 0;
				if ((hotbinA > 0) && (hotbinA < 10))
				{
					bynL[hotbinA] += 1;
					totalA += (301-bynL[1]);
					totalA += (176-bynL[2]);
					totalA += (125-bynL[3]);
					totalA += (97-bynL[4]);
					totalA += (79-bynL[5]);
					totalA += (67-bynL[6]);
					totalA += (58-bynL[7]);
					totalA += (51-bynL[8]);
					totalA += (46-bynL[9]);
					bynL[hotbinA] -= 1;
				} else {hotbinA = 10;}
				//produce total number- smaller is closer to Benford real
				
				benfordize = ceil(inputSampleL);
				while (benfordize >= 1.0) {benfordize /= 10;}
				if (benfordize < 1.0) {benfordize *= 10;}
				if (benfordize < 1.0) {benfordize *= 10;}
				if (benfordize < 1.0) {benfordize *= 10;}
				if (benfordize < 1.0) {benfordize *= 10;}
				if (benfordize < 1.0) {benfordize *= 10;}
				int hotbinB = floor(benfordize);
				//hotbin becomes the Benford bin value for this number ceiled
				double totalB = 0;
				if ((hotbinB > 0) && (hotbinB < 10))
				{
					bynL[hotbinB] += 1;
					totalB += (301-bynL[1]);
					totalB += (176-bynL[2]);
					totalB += (125-bynL[3]);
					totalB += (97-bynL[4]);
					totalB += (79-bynL[5]);
					totalB += (67-bynL[6]);
					totalB += (58-bynL[7]);
					totalB += (51-bynL[8]);
					totalB += (46-bynL[9]);
					bynL[hotbinB] -= 1;
				} else {hotbinB = 10;}
				//produce total number- smaller is closer to Benford real
				
				if (totalA < totalB)
				{
					bynL[hotbinA] += 1;
					inputSampleL = floor(inputSampleL);
				}
				else
				{
					bynL[hotbinB] += 1;
					inputSampleL = ceil(inputSampleL);
				}
				//assign the relevant one to the delay line
				//and floor/ceil signal accordingly
				
				totalA = bynL[1] + bynL[2] + bynL[3] + bynL[4] + bynL[5] + bynL[6] + bynL[7] + bynL[8] + bynL[9];
				totalA /= 1000;
				if (totalA = 0) totalA = 1; // spotted by Laserbat: this 'scaling back' code doesn't. It always divides by the fallback of 1. Old NJAD doesn't scale back the things we're comparing against. Kept to retain known behavior, use the one in StudioTan and Monitoring for a tuned-as-intended NJAD.
				bynL[1] /= totalA;
				bynL[2] /= totalA;
				bynL[3] /= totalA;
				bynL[4] /= totalA;
				bynL[5] /= totalA;
				bynL[6] /= totalA;
				bynL[7] /= totalA;
				bynL[8] /= totalA;
				bynL[9] /= totalA;
				bynL[10] /= 2; //catchall for garbage data
				//end L
				
				//begin R
				benfordize = floor(inputSampleR);
				while (benfordize >= 1.0) {benfordize /= 10;}
				if (benfordize < 1.0) {benfordize *= 10;}
				if (benfordize < 1.0) {benfordize *= 10;}
				if (benfordize < 1.0) {benfordize *= 10;}
				if (benfordize < 1.0) {benfordize *= 10;}
				if (benfordize < 1.0) {benfordize *= 10;}
				hotbinA = floor(benfordize);
				//hotbin becomes the Benford bin value for this number floored
				totalA = 0;
				if ((hotbinA > 0) && (hotbinA < 10))
				{
					bynR[hotbinA] += 1;
					totalA += (301-bynR[1]);
					totalA += (176-bynR[2]);
					totalA += (125-bynR[3]);
					totalA += (97-bynR[4]);
					totalA += (79-bynR[5]);
					totalA += (67-bynR[6]);
					totalA += (58-bynR[7]);
					totalA += (51-bynR[8]);
					totalA += (46-bynR[9]);
					bynR[hotbinA] -= 1;
				} else {hotbinA = 10;}
				//produce total number- smaller is closer to Benford real
				
				benfordize = ceil(inputSampleR);
				while (benfordize >= 1.0) {benfordize /= 10;}
				if (benfordize < 1.0) {benfordize *= 10;}
				if (benfordize < 1.0) {benfordize *= 10;}
				if (benfordize < 1.0) {benfordize *= 10;}
				if (benfordize < 1.0) {benfordize *= 10;}
				if (benfordize < 1.0) {benfordize *= 10;}
				hotbinB = floor(benfordize);
				//hotbin becomes the Benford bin value for this number ceiled
				totalB = 0;
				if ((hotbinB > 0) && (hotbinB < 10))
				{
					bynR[hotbinB] += 1;
					totalB += (301-bynR[1]);
					totalB += (176-bynR[2]);
					totalB += (125-bynR[3]);
					totalB += (97-bynR[4]);
					totalB += (79-bynR[5]);
					totalB += (67-bynR[6]);
					totalB += (58-bynR[7]);
					totalB += (51-bynR[8]);
					totalB += (46-bynR[9]);
					bynR[hotbinB] -= 1;
				} else {hotbinB = 10;}
				//produce total number- smaller is closer to Benford real
				
				if (totalA < totalB)
				{
					bynR[hotbinA] += 1;
					inputSampleR = floor(inputSampleR);
				}
				else
				{
					bynR[hotbinB] += 1;
					inputSampleR = ceil(inputSampleR);
				}
				//assign the relevant one to the delay line
				//and floor/ceil signal accordingly
				
				totalA = bynR[1] + bynR[2] + bynR[3] + bynR[4] + bynR[5] + bynR[6] + bynR[7] + bynR[8] + bynR[9];
				totalA /= 1000;
				if (totalA = 0) totalA = 1; // spotted by Laserbat: this 'scaling back' code doesn't. It always divides by the fallback of 1. Old NJAD doesn't scale back the things we're comparing against. Kept to retain known behavior, use the one in StudioTan and Monitoring for a tuned-as-intended NJAD.
				bynR[1] /= totalA;
				bynR[2] /= totalA;
				bynR[3] /= totalA;
				bynR[4] /= totalA;
				bynR[5] /= totalA;
				bynR[6] /= totalA;
				bynR[7] /= totalA;
				bynR[8] /= totalA;
				bynR[9] /= totalA;
				bynR[10] /= 2; //catchall for garbage data
				//end R
				
				if (bitDepth == 2) {
					inputSampleL /= 8388608.0;
					inputSampleR /= 8388608.0;
				}
				if (bitDepth == 1) {
					inputSampleL /= 32768.0;
					inputSampleR /= 32768.0;
				}
				noiseShapingL += inputSampleL - drySampleL;
				noiseShapingR += inputSampleR - drySampleR;
			}
			
			if (inputSampleL > refclip) inputSampleL = refclip;
			if (inputSampleL < -refclip) inputSampleL = -refclip;
			//iron bar prohibits any overs
			if (inputSampleR > refclip) inputSampleR = refclip;
			if (inputSampleR < -refclip) inputSampleR = -refclip;
			//iron bar prohibits any overs
			
			*out1 = inputSampleL;
			*out2 = inputSampleR;
			
			*in1++;
			*in2++;
			*out1++;
			*out2++;
		}
	}
private:
	
	double leftSampleA;
	double leftSampleB;
	double leftSampleC;
	double leftSampleD;
	double leftSampleE;
	double leftSampleF;
	double leftSampleG;
	double leftSampleH;
	double leftSampleI;
	double leftSampleJ;
	double leftSampleK;
	double leftSampleL;
	double leftSampleM;
	double leftSampleN;
	double leftSampleO;
	double leftSampleP;
	double leftSampleQ;
	double leftSampleR;
	double leftSampleS;
	double leftSampleT;
	double leftSampleU;
	double leftSampleV;
	double leftSampleW;
	double leftSampleX;
	double leftSampleY;
	double leftSampleZ;
	
	double rightSampleA;
	double rightSampleB;
	double rightSampleC;
	double rightSampleD;
	double rightSampleE;
	double rightSampleF;
	double rightSampleG;
	double rightSampleH;
	double rightSampleI;
	double rightSampleJ;
	double rightSampleK;
	double rightSampleL;
	double rightSampleM;
	double rightSampleN;
	double rightSampleO;
	double rightSampleP;
	double rightSampleQ;
	double rightSampleR;
	double rightSampleS;
	double rightSampleT;
	double rightSampleU;
	double rightSampleV;
	double rightSampleW;
	double rightSampleX;
	double rightSampleY;
	double rightSampleZ;
	
	double bynL[13];
	long double noiseShapingL;
	double lastSampleL;
	double IIRsampleL;
	double gwPrevL;
	double gwAL;
	double gwBL;
    
	double bynR[13];
	long double noiseShapingR;
	double lastSampleR;
	double IIRsampleR;
	double gwPrevR;
	double gwAR;
	double gwBR;
    
	long double fpNShapeL;
	long double fpNShapeR;

};
MIN_EXTERNAL(righteous4);

