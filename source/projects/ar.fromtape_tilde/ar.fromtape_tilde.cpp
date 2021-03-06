#include "c74_min.h"

using namespace c74::min;

class fromtape : public object<fromtape>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a minimalist, cleaner analog tape emulation"};
	MIN_TAGS {"analog, tape"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "louder", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "softer", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "weight", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "output", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> E {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			iirMidRollerAL = 0.0;
			iirMidRollerBL = 0.0;
			iirMidRollerCL = 0.0;
			
			iirMidRollerAR = 0.0;
			iirMidRollerBR = 0.0;
			iirMidRollerCR = 0.0;
			
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
				
			flip = 0;
			
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
		double inputgain = A*2.0;
		double softnessControl = B;
		double RollAmount = (1.0-softnessControl)/overallscale;
		double iirAmount = (0.004*(1.0-C))/overallscale;
		double altAmount = 1.0 - iirAmount;
		double outputgain = D*2.0;
		double wet = E;
		double dry = 1.0 - wet;
		double HighsSampleL = 0.0;
		double SubtractL;
		double bridgerectifierL;
		double tempSampleL;
		double drySampleL;
		double HighsSampleR = 0.0;
		double SubtractR;
		double bridgerectifierR;
		double tempSampleR;
		double drySampleR;
		double randy;
		double invrandy;	
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
			drySampleL = inputSampleL;
			drySampleR = inputSampleR;
			
	
			if (inputgain != 1.0) {
				inputSampleL *= inputgain;
				inputSampleR *= inputgain;
			}		
			
			randy = (rand()/(double)RAND_MAX) * softnessControl; //for soften
			invrandy = (1.0-randy);
			randy /= 2.0;
			//we've set up so that we dial in the amount of the alt sections (in pairs) with invrandy being the source section
			
			SubtractL = 0.0;
			SubtractR = 0.0;
			tempSampleL = inputSampleL;
			tempSampleR = inputSampleR;
			
			iirSampleAL = (iirSampleAL * altAmount) + (tempSampleL * iirAmount); tempSampleL -= iirSampleAL; SubtractL += iirSampleAL;
			iirSampleBL = (iirSampleBL * altAmount) + (tempSampleL * iirAmount); tempSampleL -= iirSampleBL; SubtractL += iirSampleBL;
			iirSampleCL = (iirSampleCL * altAmount) + (tempSampleL * iirAmount); tempSampleL -= iirSampleCL; SubtractL += iirSampleCL;
			iirSampleDL = (iirSampleDL * altAmount) + (tempSampleL * iirAmount); tempSampleL -= iirSampleDL; SubtractL += iirSampleDL;
			iirSampleEL = (iirSampleEL * altAmount) + (tempSampleL * iirAmount); tempSampleL -= iirSampleEL; SubtractL += iirSampleEL;
			iirSampleFL = (iirSampleFL * altAmount) + (tempSampleL * iirAmount); tempSampleL -= iirSampleFL; SubtractL += iirSampleFL;
			iirSampleGL = (iirSampleGL * altAmount) + (tempSampleL * iirAmount); tempSampleL -= iirSampleGL; SubtractL += iirSampleGL;
			iirSampleHL = (iirSampleHL * altAmount) + (tempSampleL * iirAmount); tempSampleL -= iirSampleHL; SubtractL += iirSampleHL;
			iirSampleIL = (iirSampleIL * altAmount) + (tempSampleL * iirAmount); tempSampleL -= iirSampleIL; SubtractL += iirSampleIL;
			iirSampleJL = (iirSampleJL * altAmount) + (tempSampleL * iirAmount); tempSampleL -= iirSampleJL; SubtractL += iirSampleJL;
			iirSampleKL = (iirSampleKL * altAmount) + (tempSampleL * iirAmount); tempSampleL -= iirSampleKL; SubtractL += iirSampleKL;
			iirSampleLL = (iirSampleLL * altAmount) + (tempSampleL * iirAmount); tempSampleL -= iirSampleLL; SubtractL += iirSampleLL;
			iirSampleML = (iirSampleML * altAmount) + (tempSampleL * iirAmount); tempSampleL -= iirSampleML; SubtractL += iirSampleML;
			iirSampleNL = (iirSampleNL * altAmount) + (tempSampleL * iirAmount); tempSampleL -= iirSampleNL; SubtractL += iirSampleNL;
			iirSampleOL = (iirSampleOL * altAmount) + (tempSampleL * iirAmount); tempSampleL -= iirSampleOL; SubtractL += iirSampleOL;
			iirSamplePL = (iirSamplePL * altAmount) + (tempSampleL * iirAmount); tempSampleL -= iirSamplePL; SubtractL += iirSamplePL;
			iirSampleQL = (iirSampleQL * altAmount) + (tempSampleL * iirAmount); tempSampleL -= iirSampleQL; SubtractL += iirSampleQL;
			iirSampleRL = (iirSampleRL * altAmount) + (tempSampleL * iirAmount); tempSampleL -= iirSampleRL; SubtractL += iirSampleRL;
			iirSampleSL = (iirSampleSL * altAmount) + (tempSampleL * iirAmount); tempSampleL -= iirSampleSL; SubtractL += iirSampleSL;
			iirSampleTL = (iirSampleTL * altAmount) + (tempSampleL * iirAmount); tempSampleL -= iirSampleTL; SubtractL += iirSampleTL;
			iirSampleUL = (iirSampleUL * altAmount) + (tempSampleL * iirAmount); tempSampleL -= iirSampleUL; SubtractL += iirSampleUL;
			iirSampleVL = (iirSampleVL * altAmount) + (tempSampleL * iirAmount); tempSampleL -= iirSampleVL; SubtractL += iirSampleVL;
			iirSampleWL = (iirSampleWL * altAmount) + (tempSampleL * iirAmount); tempSampleL -= iirSampleWL; SubtractL += iirSampleWL;
			iirSampleXL = (iirSampleXL * altAmount) + (tempSampleL * iirAmount); tempSampleL -= iirSampleXL; SubtractL += iirSampleXL;
			iirSampleYL = (iirSampleYL * altAmount) + (tempSampleL * iirAmount); tempSampleL -= iirSampleYL; SubtractL += iirSampleYL;
			iirSampleZL = (iirSampleZL * altAmount) + (tempSampleL * iirAmount); tempSampleL -= iirSampleZL; SubtractL += iirSampleZL;
			
			iirSampleAR = (iirSampleAR * altAmount) + (tempSampleR * iirAmount); tempSampleR -= iirSampleAR; SubtractR += iirSampleAR;
			iirSampleBR = (iirSampleBR * altAmount) + (tempSampleR * iirAmount); tempSampleR -= iirSampleBR; SubtractR += iirSampleBR;
			iirSampleCR = (iirSampleCR * altAmount) + (tempSampleR * iirAmount); tempSampleR -= iirSampleCR; SubtractR += iirSampleCR;
			iirSampleDR = (iirSampleDR * altAmount) + (tempSampleR * iirAmount); tempSampleR -= iirSampleDR; SubtractR += iirSampleDR;
			iirSampleER = (iirSampleER * altAmount) + (tempSampleR * iirAmount); tempSampleR -= iirSampleER; SubtractR += iirSampleER;
			iirSampleFR = (iirSampleFR * altAmount) + (tempSampleR * iirAmount); tempSampleR -= iirSampleFR; SubtractR += iirSampleFR;
			iirSampleGR = (iirSampleGR * altAmount) + (tempSampleR * iirAmount); tempSampleR -= iirSampleGR; SubtractR += iirSampleGR;
			iirSampleHR = (iirSampleHR * altAmount) + (tempSampleR * iirAmount); tempSampleR -= iirSampleHR; SubtractR += iirSampleHR;
			iirSampleIR = (iirSampleIR * altAmount) + (tempSampleR * iirAmount); tempSampleR -= iirSampleIR; SubtractR += iirSampleIR;
			iirSampleJR = (iirSampleJR * altAmount) + (tempSampleR * iirAmount); tempSampleR -= iirSampleJR; SubtractR += iirSampleJR;
			iirSampleKR = (iirSampleKR * altAmount) + (tempSampleR * iirAmount); tempSampleR -= iirSampleKR; SubtractR += iirSampleKR;
			iirSampleLR = (iirSampleLR * altAmount) + (tempSampleR * iirAmount); tempSampleR -= iirSampleLR; SubtractR += iirSampleLR;
			iirSampleMR = (iirSampleMR * altAmount) + (tempSampleR * iirAmount); tempSampleR -= iirSampleMR; SubtractR += iirSampleMR;
			iirSampleNR = (iirSampleNR * altAmount) + (tempSampleR * iirAmount); tempSampleR -= iirSampleNR; SubtractR += iirSampleNR;
			iirSampleOR = (iirSampleOR * altAmount) + (tempSampleR * iirAmount); tempSampleR -= iirSampleOR; SubtractR += iirSampleOR;
			iirSamplePR = (iirSamplePR * altAmount) + (tempSampleR * iirAmount); tempSampleR -= iirSamplePR; SubtractR += iirSamplePR;
			iirSampleQR = (iirSampleQR * altAmount) + (tempSampleR * iirAmount); tempSampleR -= iirSampleQR; SubtractR += iirSampleQR;
			iirSampleRR = (iirSampleRR * altAmount) + (tempSampleR * iirAmount); tempSampleR -= iirSampleRR; SubtractR += iirSampleRR;
			iirSampleSR = (iirSampleSR * altAmount) + (tempSampleR * iirAmount); tempSampleR -= iirSampleSR; SubtractR += iirSampleSR;
			iirSampleTR = (iirSampleTR * altAmount) + (tempSampleR * iirAmount); tempSampleR -= iirSampleTR; SubtractR += iirSampleTR;
			iirSampleUR = (iirSampleUR * altAmount) + (tempSampleR * iirAmount); tempSampleR -= iirSampleUR; SubtractR += iirSampleUR;
			iirSampleVR = (iirSampleVR * altAmount) + (tempSampleR * iirAmount); tempSampleR -= iirSampleVR; SubtractR += iirSampleVR;
			iirSampleWR = (iirSampleWR * altAmount) + (tempSampleR * iirAmount); tempSampleR -= iirSampleWR; SubtractR += iirSampleWR;
			iirSampleXR = (iirSampleXR * altAmount) + (tempSampleR * iirAmount); tempSampleR -= iirSampleXR; SubtractR += iirSampleXR;
			iirSampleYR = (iirSampleYR * altAmount) + (tempSampleR * iirAmount); tempSampleR -= iirSampleYR; SubtractR += iirSampleYR;
			iirSampleZR = (iirSampleZR * altAmount) + (tempSampleR * iirAmount); tempSampleR -= iirSampleZR; SubtractR += iirSampleZR;
			//do the IIR on a dummy sample, and store up the correction in a variable at the same scale as the very low level
			//numbers being used. Don't keep doing it against the possibly high level signal number.
			//This has been known to add a resonant quality to the cutoff, which we're using on purpose.
			inputSampleL -= SubtractL;
			inputSampleR -= SubtractR;
			//apply stored up tiny corrections.
			
			
			if (flip < 1 || flip > 3) flip = 1;
			switch (flip)
			{
				case 1:				
					iirMidRollerAL = (iirMidRollerAL * (1.0 - RollAmount)) + (inputSampleL * RollAmount);
					iirMidRollerAL = (invrandy * iirMidRollerAL) + (randy * iirMidRollerBL) + (randy * iirMidRollerCL);
					HighsSampleL = inputSampleL - iirMidRollerAL;
					iirMidRollerAR = (iirMidRollerAR * (1.0 - RollAmount)) + (inputSampleR * RollAmount);
					iirMidRollerAR = (invrandy * iirMidRollerAR) + (randy * iirMidRollerBR) + (randy * iirMidRollerCR);
					HighsSampleR = inputSampleR - iirMidRollerAR;
					break;
				case 2:
					iirMidRollerBL = (iirMidRollerBL * (1.0 - RollAmount)) + (inputSampleL * RollAmount);
					iirMidRollerBL = (randy * iirMidRollerAL) + (invrandy * iirMidRollerBL) + (randy * iirMidRollerCL);
					HighsSampleL = inputSampleL - iirMidRollerBL;
					iirMidRollerBR = (iirMidRollerBR * (1.0 - RollAmount)) + (inputSampleR * RollAmount);
					iirMidRollerBR = (randy * iirMidRollerAR) + (invrandy * iirMidRollerBR) + (randy * iirMidRollerCR);
					HighsSampleR = inputSampleR - iirMidRollerBR;
					break;
				case 3:
					iirMidRollerCL = (iirMidRollerCL * (1.0 - RollAmount)) + (inputSampleL * RollAmount);
					iirMidRollerCL = (randy * iirMidRollerAL) + (randy * iirMidRollerBL) + (invrandy * iirMidRollerCL);
					HighsSampleL = inputSampleL - iirMidRollerCL;
					iirMidRollerCR = (iirMidRollerCR * (1.0 - RollAmount)) + (inputSampleR * RollAmount);
					iirMidRollerCR = (randy * iirMidRollerAR) + (randy * iirMidRollerBR) + (invrandy * iirMidRollerCR);
					HighsSampleR = inputSampleR - iirMidRollerCR;
					break;
			}
			flip++; //increment the triplet counter
			
			SubtractL = HighsSampleL;		
			bridgerectifierL = fabs(SubtractL)*1.57079633;
			if (bridgerectifierL > 1.57079633) bridgerectifierL = 1.57079633;
			bridgerectifierL = 1-cos(bridgerectifierL);
			if (SubtractL > 0) SubtractL = bridgerectifierL;
			if (SubtractL < 0) SubtractL = -bridgerectifierL;
			inputSampleL -= SubtractL;
			
			SubtractR = HighsSampleR;		
			bridgerectifierR = fabs(SubtractR)*1.57079633;
			if (bridgerectifierR > 1.57079633) bridgerectifierR = 1.57079633;
			bridgerectifierR = 1-cos(bridgerectifierR);
			if (SubtractR > 0) SubtractR = bridgerectifierR;
			if (SubtractR < 0) SubtractR = -bridgerectifierR;
			inputSampleR -= SubtractR;
			//softness works using the MidRoller stuff, defining a bright parallel channel that we apply negative Density
			//to, and then subtract from the main audio. That makes the 'highs channel subtract' hit only the loudest
			//transients, plus we are subtracting any artifacts we got from the negative Density.				
			
			if (outputgain != 1.0) {
				inputSampleL *= outputgain;
				inputSampleR *= outputgain;
			}
			
			if (wet !=1.0) {
				inputSampleL = (inputSampleL * wet) + (drySampleL * dry);
				inputSampleR = (inputSampleR * wet) + (drySampleR * dry);
			}
			
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
    
	int flip;
		
	double iirMidRollerAL;
	double iirMidRollerBL;
	double iirMidRollerCL;
	
	double iirMidRollerAR;
	double iirMidRollerBR;
	double iirMidRollerCR;
	
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
    
	long double fpNShapeL;
	long double fpNShapeR;
	//default stuff
	
};
MIN_EXTERNAL(fromtape);

