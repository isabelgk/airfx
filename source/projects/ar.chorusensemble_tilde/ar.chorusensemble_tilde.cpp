#include "c74_min.h"

using namespace c74::min;

class chorusensemble : public object<chorusensemble>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a more complex, multi-tap mono chorus"};
	MIN_TAGS {"chorus"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "speed", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "range", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "mix", 0.8, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			for(int count = 0; count < totalsamples-1; count++) {dL[count] = 0; dR[count] = 0;}
			sweep = 3.141592653589793238 / 2.0;
			gcount = 0;
			airPrevL = 0.0;
			airEvenL = 0.0;
			airOddL = 0.0;
			airFactorL = 0.0;
			airPrevR = 0.0;
			airEvenR = 0.0;
			airOddR = 0.0;
			airFactorR = 0.0;
			fpFlip = true;
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
	
		double speed = pow(A,3) * 0.001;
		speed *= overallscale;
		int loopLimit = (int)(totalsamples * 0.499);
		int count;
		double range = pow(B,3) * loopLimit * 0.12;
		double wet = C;
		double modulation = range*wet;
		double dry = 1.0 - wet;
		double tupi = 3.141592653589793238 * 2.0;
		double offset;
		double start[4];
		
		long double inputSampleL;
		long double inputSampleR;
		double drySampleL;
		double drySampleR;
		//now we'll precalculate some stuff that needn't be in every sample
		start[0] = range;
		start[1] = range * 2;
		start[2] = range * 3;
		start[3] = range * 4;
	    
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
	
			airFactorL = airPrevL - inputSampleL;
			if (fpFlip) {airEvenL += airFactorL; airOddL -= airFactorL; airFactorL = airEvenL;}
			else {airOddL += airFactorL; airEvenL -= airFactorL; airFactorL = airOddL;}
			airOddL = (airOddL - ((airOddL - airEvenL)/256.0)) / 1.0001;
			airEvenL = (airEvenL - ((airEvenL - airOddL)/256.0)) / 1.0001;
			airPrevL = inputSampleL;
			inputSampleL += (airFactorL*wet);
			//air, compensates for loss of highs in flanger's interpolation
			
			airFactorR = airPrevR - inputSampleR;
			if (fpFlip) {airEvenR += airFactorR; airOddR -= airFactorR; airFactorR = airEvenR;}
			else {airOddR += airFactorR; airEvenR -= airFactorR; airFactorR = airOddR;}
			airOddR = (airOddR - ((airOddR - airEvenR)/256.0)) / 1.0001;
			airEvenR = (airEvenR - ((airEvenR - airOddR)/256.0)) / 1.0001;
			airPrevR = inputSampleR;
			inputSampleR += (airFactorR*wet);
			//air, compensates for loss of highs in flanger's interpolation
			
			if (gcount < 1 || gcount > loopLimit) {gcount = loopLimit;}
			count = gcount;
			dL[count+loopLimit] = dL[count] = inputSampleL;
			dR[count+loopLimit] = dR[count] = inputSampleR;
			gcount--;
			//double buffer
			
			offset = start[0] + (modulation * sin(sweep));
			count = gcount + (int)floor(offset);
			inputSampleL = dL[count] * (1-(offset-floor(offset))); //less as value moves away from .0
			inputSampleL += dL[count+1]; //we can assume always using this in one way or another?
			inputSampleL += (dL[count+2] * (offset-floor(offset))); //greater as value moves away from .0
			inputSampleL -= (((dL[count]-dL[count+1])-(dL[count+1]-dL[count+2]))/50); //interpolation hacks 'r us
			
			inputSampleR = dR[count] * (1-(offset-floor(offset))); //less as value moves away from .0
			inputSampleR += dR[count+1]; //we can assume always using this in one way or another?
			inputSampleR += (dR[count+2] * (offset-floor(offset))); //greater as value moves away from .0
			inputSampleR -= (((dR[count]-dR[count+1])-(dR[count+1]-dR[count+2]))/50); //interpolation hacks 'r us
			
			offset = start[1] + (modulation * sin(sweep + 1.0));
			count = gcount + (int)floor(offset);
			inputSampleL += dL[count] * (1-(offset-floor(offset))); //less as value moves away from .0
			inputSampleL += dL[count+1]; //we can assume always using this in one way or another?
			inputSampleL += (dL[count+2] * (offset-floor(offset))); //greater as value moves away from .0
			inputSampleL -= (((dL[count]-dL[count+1])-(dL[count+1]-dL[count+2]))/50); //interpolation hacks 'r us
			
			inputSampleR += dR[count] * (1-(offset-floor(offset))); //less as value moves away from .0
			inputSampleR += dR[count+1]; //we can assume always using this in one way or another?
			inputSampleR += (dR[count+2] * (offset-floor(offset))); //greater as value moves away from .0
			inputSampleR -= (((dR[count]-dR[count+1])-(dR[count+1]-dR[count+2]))/50); //interpolation hacks 'r us
			
			
			offset = start[2] + (modulation * sin(sweep + 2.0));
			count = gcount + (int)floor(offset);
			inputSampleL += dL[count] * (1-(offset-floor(offset))); //less as value moves away from .0
			inputSampleL += dL[count+1]; //we can assume always using this in one way or another?
			inputSampleL += (dL[count+2] * (offset-floor(offset))); //greater as value moves away from .0
			inputSampleL -= (((dL[count]-dL[count+1])-(dL[count+1]-dL[count+2]))/50); //interpolation hacks 'r us
			
			inputSampleR += dR[count] * (1-(offset-floor(offset))); //less as value moves away from .0
			inputSampleR += dR[count+1]; //we can assume always using this in one way or another?
			inputSampleR += (dR[count+2] * (offset-floor(offset))); //greater as value moves away from .0
			inputSampleR -= (((dR[count]-dR[count+1])-(dR[count+1]-dR[count+2]))/50); //interpolation hacks 'r us
			
			
			offset = start[3] + (modulation * sin(sweep + 3.0));
			count = gcount + (int)floor(offset);
			inputSampleL += dL[count] * (1-(offset-floor(offset))); //less as value moves away from .0
			inputSampleL += dL[count+1]; //we can assume always using this in one way or another?
			inputSampleL += (dL[count+2] * (offset-floor(offset))); //greater as value moves away from .0
			inputSampleL -= (((dL[count]-dL[count+1])-(dL[count+1]-dL[count+2]))/50); //interpolation hacks 'r us
			
			inputSampleR += dR[count] * (1-(offset-floor(offset))); //less as value moves away from .0
			inputSampleR += dR[count+1]; //we can assume always using this in one way or another?
			inputSampleR += (dR[count+2] * (offset-floor(offset))); //greater as value moves away from .0
			inputSampleR -= (((dR[count]-dR[count+1])-(dR[count+1]-dR[count+2]))/50); //interpolation hacks 'r us
			
			inputSampleL *= 0.125; //to get a comparable level
			inputSampleR *= 0.125; //to get a comparable level
			
			sweep += speed;
			if (sweep > tupi){sweep -= tupi;}
			//still scrolling through the samples, remember
			
			if (wet !=1.0) {
				inputSampleL = (inputSampleL * wet) + (drySampleL * dry);
				inputSampleR = (inputSampleR * wet) + (drySampleR * dry);
			}
			fpFlip = !fpFlip;
			
			
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
	
	const static int totalsamples = 16386;
	float dL[totalsamples];
	float dR[totalsamples];
	double sweep;
	int gcount;
	double airPrevL;
	double airEvenL;
	double airOddL;
	double airFactorL;
	double airPrevR;
	double airEvenR;
	double airOddR;
	double airFactorR;
	bool fpFlip;
	long double fpNShapeL;
	long double fpNShapeR;
	//default stuff

};
MIN_EXTERNAL(chorusensemble);

