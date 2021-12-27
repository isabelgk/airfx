#include "c74_min.h"

using namespace c74::min;

class ironoxide5 : public object<ironoxide5>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"old school, heavily colored Airwindows tape emulation"};
	MIN_TAGS {"tape, lofi"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "inputtrim", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "tapehigh", 0.562341325190349, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "tapelow", 0.562341325190349, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "flutter", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> E {this, "noise", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> F {this, "outputtrim", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> G {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.5; //0.0 input trim in dB -18 to +18, default 0 ((A*36.0)-18.0)
			B = 0.562341325190349; //15.0 ips 1.5 to 150.0 logarithmic. B*B
			C = 0.562341325190349; // (C*C) * (C*C) * 150 gives 15 ips (clamp to 1.5 minimum)
			D = 0.5; //0.5 flutter 0 to 1
			E = 0.5; //0.5 noise 0 to 1
			F = 0.5; //0.0 output trim in dB -18 to +18, default 0 ((E*36.0)-18.0)
			G = 1.0; //1.0 inv/dry/wet -1 0 1 ((F*2.0)-1.0)
			//needs very fussy defaults to comply with unusual defaults
			
			for (int temp = 0; temp < 263; temp++) {dL[temp] = 0.0; dR[temp] = 0.0;}
			gcount = 0;
			
			fastIIRAL = fastIIRBL = slowIIRAL = slowIIRBL = 0.0;
			fastIIHAL = fastIIHBL = slowIIHAL = slowIIHBL = 0.0;
			iirSamplehAL = iirSamplehBL = 0.0;
			iirSampleAL = iirSampleBL = 0.0;
			prevInputSampleL = 0.0;
			
			fastIIRAR = fastIIRBR = slowIIRAR = slowIIRBR = 0.0;
			fastIIHAR = fastIIHBR = slowIIHAR = slowIIHBR = 0.0;
			iirSamplehAR = iirSamplehBR = 0.0;
			iirSampleAR = iirSampleBR = 0.0;
			prevInputSampleR = 0.0;
				
			flip = false;
			for (int temp = 0; temp < 99; temp++) {flL[temp] = 0.0; flR[temp] = 0.0;}
			
			fstoredcount = 0;	
			sweep = 0.0;
			rateof = 0.5;
			nextmax = 0.5;
			
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
		
		double inputgain = pow(10.0,((A*36.0)-18.0)/20.0);
		double outputgain = pow(10.0,((F*36.0)-18.0)/20.0);
		double ips = (((B*B)*(B*B)*148.5)+1.5) * 1.1;
		//slight correction to dial in convincing ips settings
		if (ips < 1 || ips > 200){ips=33.0;}
		//sanity checks are always key
		double tempRandy = 0.04+(0.11/sqrt(ips));
		double randy;
		double lps = (((C*C)*(C*C)*148.5)+1.5) * 1.1;
		//slight correction to dial in convincing ips settings
		if (lps < 1 || lps > 200){lps=33.0;}
		//sanity checks are always key
		double iirAmount = lps/430.0; //for low leaning
		double bridgerectifierL;
		double bridgerectifierR;
		double fastTaper = ips/15.0;
		double slowTaper = 2.0/(lps*lps);
		double lowspeedscale = (5.0/ips);
		int count;
		int flutcount;
		double flutterrandy;
		double temp;
		double depth = pow(D,2)*overallscale;
		double fluttertrim = 0.00581/overallscale;
		double sweeptrim = (0.0005*depth)/overallscale;
		double offset;	
		double flooroffset;	
		double tupi = 3.141592653589793238 * 2.0;
		double newrate = 0.006/overallscale;
		double oldrate = 1.0-newrate;	
		if (overallscale == 0) {fastTaper += 1.0; slowTaper += 1.0;}
		else
		{
			iirAmount /= overallscale;
			lowspeedscale *= overallscale;
			fastTaper = 1.0 + (fastTaper / overallscale);
			slowTaper = 1.0 + (slowTaper / overallscale);
		}
		
		double noise = E * 0.5;
		double invdrywet = ((G*2.0)-1.0);
		double dry = 1.0;
		if (invdrywet > 0.0) dry -= invdrywet;
		
		long double inputSampleL;
		long double inputSampleR;
		double drySampleL;
		double drySampleR;
		
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
			drySampleL = inputSampleL;
			drySampleR = inputSampleR;
			
			flutterrandy = (rand()/(double)RAND_MAX);
			//part of flutter section
			//now we've got a random flutter, so we're messing with the pitch before tape effects go on
			if (fstoredcount < 0 || fstoredcount > 30) {fstoredcount = 30;}
			flutcount = fstoredcount;
			flL[flutcount+31] = flL[flutcount] = inputSampleL;
			flR[flutcount+31] = flR[flutcount] = inputSampleR;
			offset = (1.0 + sin(sweep)) * depth;
			flooroffset = offset-floor(offset);
			flutcount += (int)floor(offset);
			bridgerectifierL = (flL[flutcount] * (1-flooroffset));
			bridgerectifierR = (flR[flutcount] * (1-flooroffset));
			bridgerectifierL += (flL[flutcount+1] * flooroffset);
			bridgerectifierR += (flR[flutcount+1] * flooroffset);
			rateof = (nextmax * newrate) + (rateof * oldrate);
			sweep += rateof * fluttertrim;
			sweep += sweep * sweeptrim;
			if (sweep >= tupi){sweep = 0.0; nextmax = 0.02 + (flutterrandy*0.98);}
			fstoredcount--;
			inputSampleL = bridgerectifierL;
			inputSampleR = bridgerectifierR;
			//apply to input signal, interpolate samples
			//all the funky renaming is just trying to fix how I never reassigned the control numbers
			
			if (flip)
			{
				iirSampleAL = (iirSampleAL * (1 - iirAmount)) + (inputSampleL * iirAmount);
				iirSampleAR = (iirSampleAR * (1 - iirAmount)) + (inputSampleR * iirAmount);
				inputSampleL -= iirSampleAL;
				inputSampleR -= iirSampleAR;
			}
			else
			{
				iirSampleBL = (iirSampleBL * (1 - iirAmount)) + (inputSampleL * iirAmount);
				iirSampleBR = (iirSampleBR * (1 - iirAmount)) + (inputSampleR * iirAmount);
				inputSampleL -= iirSampleBL;
				inputSampleR -= iirSampleBR;
			}
			//do IIR highpass for leaning out
			
			inputSampleL *= inputgain;
			inputSampleR *= inputgain;
			
			bridgerectifierL = fabs(inputSampleL);
			if (bridgerectifierL > 1.57079633) bridgerectifierL = 1.57079633;
			bridgerectifierL = sin(bridgerectifierL);
			if (inputSampleL > 0.0) inputSampleL = bridgerectifierL;
			else inputSampleL = -bridgerectifierL;
			//preliminary gain stage using antialiasing
			
			bridgerectifierR = fabs(inputSampleR);
			if (bridgerectifierR > 1.57079633) bridgerectifierR = 1.57079633;
			bridgerectifierR = sin(bridgerectifierR);
			if (inputSampleR > 0.0) inputSampleR = bridgerectifierR;
			else inputSampleR = -bridgerectifierR;
			//preliminary gain stage using antialiasing
			
			//over to the Iron Oxide shaping code using inputsample
			if (gcount < 0 || gcount > 131) {gcount = 131;}
			count = gcount;
			//increment the counter
			
			dL[count+131] = dL[count] = inputSampleL;
			dR[count+131] = dR[count] = inputSampleR;
			
			if (flip)
			{
				fastIIRAL = fastIIRAL/fastTaper;
				slowIIRAL = slowIIRAL/slowTaper;
				fastIIRAL += dL[count];
				//scale stuff down
				
				fastIIRAR = fastIIRAR/fastTaper;
				slowIIRAR = slowIIRAR/slowTaper;
				fastIIRAR += dR[count];
				//scale stuff down
				count += 3;
				
				temp = dL[count+127];
				temp += dL[count+113];
				temp += dL[count+109];
				temp += dL[count+107];
				temp += dL[count+103];
				temp += dL[count+101];
				temp += dL[count+97];
				temp += dL[count+89];
				temp += dL[count+83];
				temp /= 2;
				temp += dL[count+79];
				temp += dL[count+73];
				temp += dL[count+71];
				temp += dL[count+67];
				temp += dL[count+61];
				temp += dL[count+59];
				temp += dL[count+53];
				temp += dL[count+47];
				temp += dL[count+43];
				temp += dL[count+41];
				temp += dL[count+37];
				temp += dL[count+31];
				temp += dL[count+29];
				temp /= 2;
				temp += dL[count+23];
				temp += dL[count+19];
				temp += dL[count+17];
				temp += dL[count+13];
				temp += dL[count+11];
				temp /= 2;
				temp += dL[count+7];
				temp += dL[count+5];
				temp += dL[count+3];
				temp /= 2;
				temp += dL[count+2];
				temp += dL[count+1]; //end L
				slowIIRAL += (temp/128);
				
				temp = dR[count+127];
				temp += dR[count+113];
				temp += dR[count+109];
				temp += dR[count+107];
				temp += dR[count+103];
				temp += dR[count+101];
				temp += dR[count+97];
				temp += dR[count+89];
				temp += dR[count+83];
				temp /= 2;
				temp += dR[count+79];
				temp += dR[count+73];
				temp += dR[count+71];
				temp += dR[count+67];
				temp += dR[count+61];
				temp += dR[count+59];
				temp += dR[count+53];
				temp += dR[count+47];
				temp += dR[count+43];
				temp += dR[count+41];
				temp += dR[count+37];
				temp += dR[count+31];
				temp += dR[count+29];
				temp /= 2;
				temp += dR[count+23];
				temp += dR[count+19];
				temp += dR[count+17];
				temp += dR[count+13];
				temp += dR[count+11];
				temp /= 2;
				temp += dR[count+7];
				temp += dR[count+5];
				temp += dR[count+3];
				temp /= 2;
				temp += dR[count+2];
				temp += dR[count+1]; //end R
				slowIIRAR += (temp/128);
				
				inputSampleL = fastIIRAL - (slowIIRAL / slowTaper);
				inputSampleR = fastIIRAR - (slowIIRAR / slowTaper);
			}
			else
			{
				fastIIRBL = fastIIRBL/fastTaper;
				slowIIRBL = slowIIRBL/slowTaper;
				fastIIRBL += dL[count];
				//scale stuff down
				
				fastIIRBR = fastIIRBR/fastTaper;
				slowIIRBR = slowIIRBR/slowTaper;
				fastIIRBR += dR[count];
				//scale stuff down
				count += 3;
				
				temp = dL[count+127];
				temp += dL[count+113];
				temp += dL[count+109];
				temp += dL[count+107];
				temp += dL[count+103];
				temp += dL[count+101];
				temp += dL[count+97];
				temp += dL[count+89];
				temp += dL[count+83];
				temp /= 2;
				temp += dL[count+79];
				temp += dL[count+73];
				temp += dL[count+71];
				temp += dL[count+67];
				temp += dL[count+61];
				temp += dL[count+59];
				temp += dL[count+53];
				temp += dL[count+47];
				temp += dL[count+43];
				temp += dL[count+41];
				temp += dL[count+37];
				temp += dL[count+31];
				temp += dL[count+29];
				temp /= 2;
				temp += dL[count+23];
				temp += dL[count+19];
				temp += dL[count+17];
				temp += dL[count+13];
				temp += dL[count+11];
				temp /= 2;
				temp += dL[count+7];
				temp += dL[count+5];
				temp += dL[count+3];
				temp /= 2;
				temp += dL[count+2];
				temp += dL[count+1];
				slowIIRBL += (temp/128);
				
				temp = dR[count+127];
				temp += dR[count+113];
				temp += dR[count+109];
				temp += dR[count+107];
				temp += dR[count+103];
				temp += dR[count+101];
				temp += dR[count+97];
				temp += dR[count+89];
				temp += dR[count+83];
				temp /= 2;
				temp += dR[count+79];
				temp += dR[count+73];
				temp += dR[count+71];
				temp += dR[count+67];
				temp += dR[count+61];
				temp += dR[count+59];
				temp += dR[count+53];
				temp += dR[count+47];
				temp += dR[count+43];
				temp += dR[count+41];
				temp += dR[count+37];
				temp += dR[count+31];
				temp += dR[count+29];
				temp /= 2;
				temp += dR[count+23];
				temp += dR[count+19];
				temp += dR[count+17];
				temp += dR[count+13];
				temp += dR[count+11];
				temp /= 2;
				temp += dR[count+7];
				temp += dR[count+5];
				temp += dR[count+3];
				temp /= 2;
				temp += dR[count+2];
				temp += dR[count+1];
				slowIIRBR += (temp/128);
				
				inputSampleL = fastIIRBL - (slowIIRBL / slowTaper);
				inputSampleR = fastIIRBR - (slowIIRBR / slowTaper);
			}
			
			inputSampleL /= fastTaper;
			inputSampleR /= fastTaper;
			inputSampleL /= lowspeedscale;
			inputSampleR /= lowspeedscale;
			
			bridgerectifierL = fabs(inputSampleL);
			if (bridgerectifierL > 1.57079633) bridgerectifierL = 1.57079633;
			bridgerectifierL = sin(bridgerectifierL);
			//can use as an output limiter
			if (inputSampleL > 0.0) inputSampleL = bridgerectifierL;
			else inputSampleL = -bridgerectifierL;
			//second stage of overdrive to prevent overs and allow bloody loud extremeness		
			
			bridgerectifierR = fabs(inputSampleR);
			if (bridgerectifierR > 1.57079633) bridgerectifierR = 1.57079633;
			bridgerectifierR = sin(bridgerectifierR);
			//can use as an output limiter
			if (inputSampleR > 0.0) inputSampleR = bridgerectifierR;
			else inputSampleR = -bridgerectifierR;
			//second stage of overdrive to prevent overs and allow bloody loud extremeness		
			
			randy = (0.55 + tempRandy + ((rand()/(double)RAND_MAX)*tempRandy))*noise; //0 to 2
			
			inputSampleL *= (1.0 - randy);
			inputSampleL += (prevInputSampleL*randy);
			prevInputSampleL = drySampleL;
			
			inputSampleR *= (1.0 - randy);
			inputSampleR += (prevInputSampleR*randy);
			prevInputSampleR = drySampleR;
			//a slew-based noise generator: noise is only relative to how much change between samples there is.
			//This will cause high sample rates to be a little 'smoother' and clearer. I see this mechanic as something that
			//interacts with the sample rate. The 'dust' is scaled to the size of the samples.
			
			flip = !flip;
			
			//begin invdrywet block with outputgain
			if (outputgain != 1.0) {
				inputSampleL *= outputgain;
				inputSampleR *= outputgain;
			}
			if (invdrywet != 1.0) {
				inputSampleL *= invdrywet;
				inputSampleR *= invdrywet;
			}
			if (dry != 1.0) {
				drySampleL *= dry;
				drySampleR *= dry;
			}
			if (fabs(drySampleL) > 0.0) {
				inputSampleL += drySampleL;
			}
			if (fabs(drySampleR) > 0.0) {
				inputSampleR += drySampleR;
			}
			//end invdrywet block with outputgain
			
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
	
	double iirSamplehAL;
	double iirSamplehBL;
	double iirSampleAL;
	double iirSampleBL;
	double dL[264];
	double fastIIRAL;
	double fastIIRBL;
	double slowIIRAL;
	double slowIIRBL;
	double fastIIHAL;
	double fastIIHBL;
	double slowIIHAL;
	double slowIIHBL;
	double prevInputSampleL;

	double iirSamplehAR;
	double iirSamplehBR;
	double iirSampleAR;
	double iirSampleBR;
	double dR[264];
	double fastIIRAR;
	double fastIIRBR;
	double slowIIRAR;
	double slowIIRBR;
	double fastIIHAR;
	double fastIIHBR;
	double slowIIHAR;
	double slowIIHBR;
	double prevInputSampleR;
	
	int gcount;
	bool flip;
	
	double flL[100];
	double flR[100];
	
	int fstoredcount;
	double rateof;
	double sweep;
	double nextmax;
	
    
	long double fpNShapeL;
	long double fpNShapeR;
	//default stuff

};
MIN_EXTERNAL(ironoxide5);

