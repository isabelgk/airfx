#include "c74_min.h"

using namespace c74::min;

class adclip7 : public object<adclip7>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"loudness maximizer / peak control clipper"};
	MIN_TAGS {"clipper, utility"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "boost", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "soften", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "enhance", 0.5, range {0.0, 1.0} };

	enum class modes : int { normal, gainmatch, cliponly, enum_count };
	enum_map mode_range = { "normal", "gainmatch", "cliponly" };
	attribute<modes> mode { this, "mode", modes::gainmatch, mode_range };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			lastSampleL = 0.0;
			lastSampleR = 0.0;
			for(int count = 0; count < 22199; count++) {bL[count] = 0; bR[count] = 0;}
			gcount = 0;
			lowsL = 0;
			lowsR = 0;
			refclipL = 0.99;
			refclipR = 0.99;
			iirLowsAL = 0.0;
			iirLowsAR = 0.0;
			iirLowsBL = 0.0;	
			iirLowsBR = 0.0;	
			
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

		long double fpOld = 0.618033988749894848204586; //golden ratio!
		long double fpNew = 1.0 - fpOld;
		double inputGain = pow(10.0,(A*18.0)/20.0);
		double softness = B * fpNew;
		double hardness = 1.0 - softness;
		double highslift = 0.307 * C;
		double adjust = pow(highslift,3) * 0.416;
		double subslift = 0.796 * C;
		double calibsubs = subslift/53;
		double invcalibsubs = 1.0 - calibsubs;
		double subs = 0.81 + (calibsubs*2);
		long double bridgerectifier;
		double overshootL;
		double overshootR;
		double offsetH1 = 1.84;
		offsetH1 *= overallscale;
		double offsetH2 = offsetH1 * 1.9;
		double offsetH3 = offsetH1 * 2.7;
		double offsetL1 = 612;
		offsetL1 *= overallscale;
		double offsetL2 = offsetL1 * 2.0;
		int refH1 = (int)floor(offsetH1);
		int refH2 = (int)floor(offsetH2);
		int refH3 = (int)floor(offsetH3);
		int refL1 = (int)floor(offsetL1);
		int refL2 = (int)floor(offsetL2);
		int temp;
		double fractionH1 = offsetH1 - floor(offsetH1);
		double fractionH2 = offsetH2 - floor(offsetH2);
		double fractionH3 = offsetH3 - floor(offsetH3);
		double minusH1 = 1.0 - fractionH1;
		double minusH2 = 1.0 - fractionH2;
		double minusH3 = 1.0 - fractionH3;
		double highsL = 0.0;
		double highsR = 0.0;
		int count = 0;
		
		long double inputSampleL;
		long double inputSampleR;
	
	
	    while (--sampleFrames >= 0)
	    {
			inputSampleL = *in1;
			inputSampleR = *in2;
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
			
			
			
			if (inputGain != 1.0) {
				inputSampleL *= inputGain;
				inputSampleR *= inputGain;
			}
			
			overshootL = fabs(inputSampleL) - refclipL;
			overshootR = fabs(inputSampleR) - refclipR;
			if (overshootL < 0.0) overshootL = 0.0;
			if (overshootR < 0.0) overshootR = 0.0;
			
			if (gcount < 0 || gcount > 11020) {gcount = 11020;}
			count = gcount;
			bL[count+11020] = bL[count] = overshootL;
			bR[count+11020] = bR[count] = overshootR;
			gcount--;
			
			if (highslift > 0.0)
			{
				//we have a big pile of b[] which is overshoots
				temp = count+refH3;
				highsL = -(bL[temp] * minusH3); //less as value moves away from .0
				highsL -= bL[temp+1]; //we can assume always using this in one way or another?
				highsL -= (bL[temp+2] * fractionH3); //greater as value moves away from .0
				highsL += (((bL[temp]-bL[temp+1])-(bL[temp+1]-bL[temp+2]))/50); //interpolation hacks 'r us
				highsL *= adjust; //add in the kernel elements backwards saves multiplies
				//stage 3 is a negative add
				highsR = -(bR[temp] * minusH3); //less as value moves away from .0
				highsR -= bR[temp+1]; //we can assume always using this in one way or another?
				highsR -= (bR[temp+2] * fractionH3); //greater as value moves away from .0
				highsR += (((bR[temp]-bR[temp+1])-(bR[temp+1]-bR[temp+2]))/50); //interpolation hacks 'r us
				highsR *= adjust; //add in the kernel elements backwards saves multiplies
				//stage 3 is a negative add
				temp = count+refH2;
				highsL += (bL[temp] * minusH2); //less as value moves away from .0
				highsL += bL[temp+1]; //we can assume always using this in one way or another?
				highsL += (bL[temp+2] * fractionH2); //greater as value moves away from .0
				highsL -= (((bL[temp]-bL[temp+1])-(bL[temp+1]-bL[temp+2]))/50); //interpolation hacks 'r us
				highsL *= adjust; //add in the kernel elements backwards saves multiplies
				//stage 2 is a positive feedback of the overshoot
				highsR += (bR[temp] * minusH2); //less as value moves away from .0
				highsR += bR[temp+1]; //we can assume always using this in one way or another?
				highsR += (bR[temp+2] * fractionH2); //greater as value moves away from .0
				highsR -= (((bR[temp]-bR[temp+1])-(bR[temp+1]-bR[temp+2]))/50); //interpolation hacks 'r us
				highsR *= adjust; //add in the kernel elements backwards saves multiplies
				//stage 2 is a positive feedback of the overshoot
				temp = count+refH1;
				highsL -= (bL[temp] * minusH1); //less as value moves away from .0
				highsL -= bL[temp+1]; //we can assume always using this in one way or another?
				highsL -= (bL[temp+2] * fractionH1); //greater as value moves away from .0
				highsL += (((bL[temp]-bL[temp+1])-(bL[temp+1]-bL[temp+2]))/50); //interpolation hacks 'r us
				highsL *= adjust; //add in the kernel elements backwards saves multiplies
				//stage 1 is a negative feedback of the overshoot
				highsR -= (bR[temp] * minusH1); //less as value moves away from .0
				highsR -= bR[temp+1]; //we can assume always using this in one way or another?
				highsR -= (bR[temp+2] * fractionH1); //greater as value moves away from .0
				highsR += (((bR[temp]-bR[temp+1])-(bR[temp+1]-bR[temp+2]))/50); //interpolation hacks 'r us
				highsR *= adjust; //add in the kernel elements backwards saves multiplies
				//stage 1 is a negative feedback of the overshoot
				//done with interpolated mostly negative feedback of the overshoot
			}
			
			bridgerectifier = sin(fabs(highsL) * hardness);
			//this will wrap around and is scaled back by softness
			//wrap around is the same principle as Fracture: no top limit to sin()
			if (highsL > 0) highsL = bridgerectifier;
			else highsL = -bridgerectifier;
			
			bridgerectifier = sin(fabs(highsR) * hardness);
			//this will wrap around and is scaled back by softness
			//wrap around is the same principle as Fracture: no top limit to sin()
			if (highsR > 0) highsR = bridgerectifier;
			else highsR = -bridgerectifier;
			
			if (subslift > 0.0) 
			{
				lowsL *= subs;
				lowsR *= subs;
				//going in we'll reel back some of the swing
				temp = count+refL1;
				
				lowsL -= bL[temp+127];
				lowsL -= bL[temp+113];
				lowsL -= bL[temp+109];
				lowsL -= bL[temp+107];
				lowsL -= bL[temp+103];
				lowsL -= bL[temp+101];
				lowsL -= bL[temp+97];
				lowsL -= bL[temp+89];
				lowsL -= bL[temp+83];
				lowsL -= bL[temp+79];
				lowsL -= bL[temp+73];
				lowsL -= bL[temp+71];
				lowsL -= bL[temp+67];
				lowsL -= bL[temp+61];
				lowsL -= bL[temp+59];
				lowsL -= bL[temp+53];
				lowsL -= bL[temp+47];
				lowsL -= bL[temp+43];
				lowsL -= bL[temp+41];
				lowsL -= bL[temp+37];
				lowsL -= bL[temp+31];
				lowsL -= bL[temp+29];
				lowsL -= bL[temp+23];
				lowsL -= bL[temp+19];
				lowsL -= bL[temp+17];
				lowsL -= bL[temp+13];
				lowsL -= bL[temp+11];
				lowsL -= bL[temp+7];
				lowsL -= bL[temp+5];
				lowsL -= bL[temp+3];
				lowsL -= bL[temp+2];
				lowsL -= bL[temp+1];
				//initial negative lobe
				
				lowsR -= bR[temp+127];
				lowsR -= bR[temp+113];
				lowsR -= bR[temp+109];
				lowsR -= bR[temp+107];
				lowsR -= bR[temp+103];
				lowsR -= bR[temp+101];
				lowsR -= bR[temp+97];
				lowsR -= bR[temp+89];
				lowsR -= bR[temp+83];
				lowsR -= bR[temp+79];
				lowsR -= bR[temp+73];
				lowsR -= bR[temp+71];
				lowsR -= bR[temp+67];
				lowsR -= bR[temp+61];
				lowsR -= bR[temp+59];
				lowsR -= bR[temp+53];
				lowsR -= bR[temp+47];
				lowsR -= bR[temp+43];
				lowsR -= bR[temp+41];
				lowsR -= bR[temp+37];
				lowsR -= bR[temp+31];
				lowsR -= bR[temp+29];
				lowsR -= bR[temp+23];
				lowsR -= bR[temp+19];
				lowsR -= bR[temp+17];
				lowsR -= bR[temp+13];
				lowsR -= bR[temp+11];
				lowsR -= bR[temp+7];
				lowsR -= bR[temp+5];
				lowsR -= bR[temp+3];
				lowsR -= bR[temp+2];
				lowsR -= bR[temp+1];
				//initial negative lobe
				
				lowsL *= subs;
				lowsL *= subs;
				lowsR *= subs;
				lowsR *= subs;
				//twice, to minimize the suckout in low boost situations
				temp = count+refL2;
				
				lowsL += bL[temp+127];
				lowsL += bL[temp+113];
				lowsL += bL[temp+109];
				lowsL += bL[temp+107];
				lowsL += bL[temp+103];
				lowsL += bL[temp+101];
				lowsL += bL[temp+97];
				lowsL += bL[temp+89];
				lowsL += bL[temp+83];
				lowsL += bL[temp+79];
				lowsL += bL[temp+73];
				lowsL += bL[temp+71];
				lowsL += bL[temp+67];
				lowsL += bL[temp+61];
				lowsL += bL[temp+59];
				lowsL += bL[temp+53];
				lowsL += bL[temp+47];
				lowsL += bL[temp+43];
				lowsL += bL[temp+41];
				lowsL += bL[temp+37];
				lowsL += bL[temp+31];
				lowsL += bL[temp+29];
				lowsL += bL[temp+23];
				lowsL += bL[temp+19];
				lowsL += bL[temp+17];
				lowsL += bL[temp+13];
				lowsL += bL[temp+11];
				lowsL += bL[temp+7];
				lowsL += bL[temp+5];
				lowsL += bL[temp+3];
				lowsL += bL[temp+2];
				lowsL += bL[temp+1];
				//followup positive lobe
				
				lowsR += bR[temp+127];
				lowsR += bR[temp+113];
				lowsR += bR[temp+109];
				lowsR += bR[temp+107];
				lowsR += bR[temp+103];
				lowsR += bR[temp+101];
				lowsR += bR[temp+97];
				lowsR += bR[temp+89];
				lowsR += bR[temp+83];
				lowsR += bR[temp+79];
				lowsR += bR[temp+73];
				lowsR += bR[temp+71];
				lowsR += bR[temp+67];
				lowsR += bR[temp+61];
				lowsR += bR[temp+59];
				lowsR += bR[temp+53];
				lowsR += bR[temp+47];
				lowsR += bR[temp+43];
				lowsR += bR[temp+41];
				lowsR += bR[temp+37];
				lowsR += bR[temp+31];
				lowsR += bR[temp+29];
				lowsR += bR[temp+23];
				lowsR += bR[temp+19];
				lowsR += bR[temp+17];
				lowsR += bR[temp+13];
				lowsR += bR[temp+11];
				lowsR += bR[temp+7];
				lowsR += bR[temp+5];
				lowsR += bR[temp+3];
				lowsR += bR[temp+2];
				lowsR += bR[temp+1];
				//followup positive lobe
				
				lowsL *= subs;
				lowsR *= subs;
				//now we have the lows content to use
			}
			
			bridgerectifier = sin(fabs(lowsL) * softness);
			//this will wrap around and is scaled back by hardness: hard = less bass push, more treble
			//wrap around is the same principle as Fracture: no top limit to sin()
			if (lowsL > 0) lowsL = bridgerectifier;
			else lowsL = -bridgerectifier;
			
			bridgerectifier = sin(fabs(lowsR) * softness);
			//this will wrap around and is scaled back by hardness: hard = less bass push, more treble
			//wrap around is the same principle as Fracture: no top limit to sin()
			if (lowsR > 0) lowsR = bridgerectifier;
			else lowsR = -bridgerectifier;
			
			iirLowsAL = (iirLowsAL * invcalibsubs) + (lowsL * calibsubs);
			lowsL = iirLowsAL;
			bridgerectifier = sin(fabs(lowsL));
			if (lowsL > 0) lowsL = bridgerectifier;
			else lowsL = -bridgerectifier;
			
			iirLowsAR = (iirLowsAR * invcalibsubs) + (lowsR * calibsubs);
			lowsR = iirLowsAR;
			bridgerectifier = sin(fabs(lowsR));
			if (lowsR > 0) lowsR = bridgerectifier;
			else lowsR = -bridgerectifier;
			
			iirLowsBL = (iirLowsBL * invcalibsubs) + (lowsL * calibsubs);
			lowsL = iirLowsBL;
			bridgerectifier = sin(fabs(lowsL)) * 2.0;
			if (lowsL > 0) lowsL = bridgerectifier;
			else lowsL = -bridgerectifier;
			
			iirLowsBR = (iirLowsBR * invcalibsubs) + (lowsR * calibsubs);
			lowsR = iirLowsBR;
			bridgerectifier = sin(fabs(lowsR)) * 2.0;
			if (lowsR > 0) lowsR = bridgerectifier;
			else lowsR = -bridgerectifier;
			
			if (highslift > 0.0) inputSampleL += (highsL * (1.0-fabs(inputSampleL*hardness)));
			if (subslift > 0.0) inputSampleL += (lowsL * (1.0-fabs(inputSampleL*softness)));
			
			if (highslift > 0.0) inputSampleR += (highsR * (1.0-fabs(inputSampleR*hardness)));
			if (subslift > 0.0) inputSampleR += (lowsR * (1.0-fabs(inputSampleR*softness)));
			
			if (inputSampleL > refclipL && refclipL > 0.9) refclipL -= 0.01;
			if (inputSampleL < -refclipL && refclipL > 0.9) refclipL -= 0.01;
			if (refclipL < 0.99) refclipL += 0.00001;
			//adjust clip level on the fly
			
			if (inputSampleR > refclipR && refclipR > 0.9) refclipR -= 0.01;
			if (inputSampleR < -refclipR && refclipR > 0.9) refclipR -= 0.01;
			if (refclipR < 0.99) refclipR += 0.00001;
			//adjust clip level on the fly
			
			if (lastSampleL >= refclipL)
			{
				if (inputSampleL < refclipL) lastSampleL = ((refclipL*hardness) + (inputSampleL * softness));
				else lastSampleL = refclipL;
			}
			
			if (lastSampleR >= refclipR)
			{
				if (inputSampleR < refclipR) lastSampleR = ((refclipR*hardness) + (inputSampleR * softness));
				else lastSampleR = refclipR;
			}
			
			if (lastSampleL <= -refclipL)
			{
				if (inputSampleL > -refclipL) lastSampleL = ((-refclipL*hardness) + (inputSampleL * softness));
				else lastSampleL = -refclipL;
			}
			
			if (lastSampleR <= -refclipR)
			{
				if (inputSampleR > -refclipR) lastSampleR = ((-refclipR*hardness) + (inputSampleR * softness));
				else lastSampleR = -refclipR;
			}
			
			if (inputSampleL > refclipL)
			{
				if (lastSampleL < refclipL) inputSampleL = ((refclipL*hardness) + (lastSampleL * softness));
				else inputSampleL = refclipL;
			}
			
			if (inputSampleR > refclipR)
			{
				if (lastSampleR < refclipR) inputSampleR = ((refclipR*hardness) + (lastSampleR * softness));
				else inputSampleR = refclipR;
			}
			
			if (inputSampleL < -refclipL)
			{
				if (lastSampleL > -refclipL) inputSampleL = ((-refclipL*hardness) + (lastSampleL * softness));
				else inputSampleL = -refclipL;
			}
			
			if (inputSampleR < -refclipR)
			{
				if (lastSampleR > -refclipR) inputSampleR = ((-refclipR*hardness) + (lastSampleR * softness));
				else inputSampleR = -refclipR;
			}
			lastSampleL = inputSampleL;
			lastSampleR = inputSampleR;
			
			switch (mode)
			{
				case modes::normal: break; //Normal
				case modes::gainmatch: inputSampleL /= inputGain; inputSampleR /= inputGain; break; //Gain Match
				case modes::cliponly: inputSampleL = overshootL + highsL + lowsL; inputSampleR = overshootR + highsR + lowsR; break; //Clip Only
			}
			//this is our output mode switch, showing the effects
			
			if (inputSampleL > refclipL) inputSampleL = refclipL;
			if (inputSampleL < -refclipL) inputSampleL = -refclipL;
			if (inputSampleR > refclipR) inputSampleR = refclipR;
			if (inputSampleR < -refclipR) inputSampleR = -refclipR;
			//final iron bar
			
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
    
	long double fpNShapeL;
	long double fpNShapeR;
	//default stuff
	long double lastSampleL;
	long double lastSampleR;
	float bL[22200];
	float bR[22200];
	int gcount;
	double lowsL;
	double lowsR;
	double iirLowsAL;
	double iirLowsAR;
	double iirLowsBL;
	double iirLowsBR;
	long double refclipL;
	long double refclipR;

};
MIN_EXTERNAL(adclip7);

