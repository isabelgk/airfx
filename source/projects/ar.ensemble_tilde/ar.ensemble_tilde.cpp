#include "c74_min.h"

using namespace c74::min;

class ensemble : public object<ensemble>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"weird flangey little modulation effect"};
	MIN_TAGS {"chorus"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "ensemble", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "fullness", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "brightness", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			for(int count = 0; count < totalsamples-1; count++) {dL[count] = 0; dR[count] = 0;}
			for(int count = 0; count < 49; count++) {sweep[count] = 3.141592653589793238 / 2.0;}
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
		double overallscale = 1.0;
		overallscale /= 44100.0;
		overallscale *= samplerate();

		long sampleFrames = _input.frame_count();
		
		double spd = pow(0.4+(B/12),10);
		spd *= overallscale;
		double depth = 0.002 / spd;
		double tupi = 3.141592653589793238 * 2.0;
		double taps = floor((A*46.0)+2.9);
		double brighten = C;
		double wet = D;
		double dry = 1.0 - wet;
		double hapi = 3.141592653589793238 / taps;
		double offset;
		double floffset;
		double start[49];
		double sinoffset[49];	
		double speed[49];
		int count;
		int ensemble;
		double tempL;
		double tempR;
		
	
		long double inputSampleL;
		long double inputSampleR;
		double drySampleL;
		double drySampleR;
		//now we'll precalculate some stuff that needn't be in every sample
		
		for(count = 1; count <= taps; count++)
		{
			start[count] = depth * count;
			sinoffset[count] = hapi * (count-1);
			speed[count] = spd / (1 + (count/taps));
		}
		//that's for speeding up things in the sample-processing area
		
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
			inputSampleL += (airFactorL*brighten);
			//air, compensates for loss of highs in flanger's interpolation
			
			airFactorR = airPrevR - inputSampleR;
			if (fpFlip) {airEvenR += airFactorR; airOddR -= airFactorR; airFactorR = airEvenR;}
			else {airOddR += airFactorR; airEvenR -= airFactorR; airFactorR = airOddR;}
			airOddR = (airOddR - ((airOddR - airEvenR)/256.0)) / 1.0001;
			airEvenR = (airEvenR - ((airEvenR - airOddR)/256.0)) / 1.0001;
			airPrevR = inputSampleR;
			inputSampleR += (airFactorR*brighten);
			//air, compensates for loss of highs in flanger's interpolation
			fpFlip = !fpFlip;
			
			if (gcount < 1 || gcount > 32767) {gcount = 32767;}
			count = gcount;
			dL[count+32767] = dL[count] = tempL = inputSampleL;
			dR[count+32767] = dR[count] = tempR = inputSampleR;
			//double buffer
			
			for(ensemble = 1; ensemble <= taps; ensemble++)
			{
				offset = start[ensemble] + (depth * sin(sweep[ensemble]+sinoffset[ensemble]));
				floffset = offset-floor(offset);
				count = gcount + (int)floor(offset);
				
				tempL += dL[count] * (1-floffset); //less as value moves away from .0
				tempL += dL[count+1]; //we can assume always using this in one way or another?
				tempL += dL[count+2] * floffset; //greater as value moves away from .0
				tempL -= ((dL[count]-dL[count+1])-(dL[count+1]-dL[count+2]))/50; //interpolation hacks 'r us
				
				tempR += dR[count] * (1-floffset); //less as value moves away from .0
				tempR += dR[count+1]; //we can assume always using this in one way or another?
				tempR += dR[count+2] * floffset; //greater as value moves away from .0
				tempR -= ((dR[count]-dR[count+1])-(dR[count+1]-dR[count+2]))/50; //interpolation hacks 'r us
				
				sweep[ensemble] += speed[ensemble];
				if (sweep[ensemble] > tupi){sweep[ensemble] -= tupi;}
			}
			gcount--;
			//still scrolling through the samples, remember
			
			inputSampleL = tempL/(4.0*sqrt(taps));
			inputSampleR = tempR/(4.0*sqrt(taps));
			
			
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
    
	long double fpNShapeL;
	long double fpNShapeR;
	//default stuff
	const static int totalsamples = 65540;
	float dL[totalsamples];
	float dR[totalsamples];
	double sweep[49];
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
};
MIN_EXTERNAL(ensemble);

