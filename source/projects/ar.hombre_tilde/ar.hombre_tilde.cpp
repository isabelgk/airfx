#include "c74_min.h"

using namespace c74::min;

class hombre : public object<hombre>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"atmosphere and texture (through very short delays)"};
	MIN_TAGS {"audio, effect"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "Voicing", 0.421, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "Intensity", 0.5, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.421;
			B = 0.5;
			for(int count = 0; count < 4000; count++) {pL[count] = 0.0; pR[count] = 0.0;}
			gcount = 0;
			slide = 0.421;
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
	
		double target = A;
		double offsetA;
		double offsetB;
		int widthA = (int)(1.0*overallscale);
		int widthB = (int)(7.0*overallscale); //max 364 at 44.1, 792 at 96K
		double wet = B;
		double dry = 1.0 - wet;
		double totalL;
		double totalR;
		int count;
		
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
	
			slide = (slide * 0.9997)+(target*0.0003);
			
			offsetA = ((pow(slide,2)) * 77)+3.2;
			offsetB = (3.85 * offsetA)+41;
			offsetA *= overallscale;
			offsetB *= overallscale;
			//adjust for sample rate
			
			if (gcount < 1 || gcount > 2000) {gcount = 2000;}
			count = gcount;
			
			pL[count+2000] = pL[count] = inputSampleL;
			pR[count+2000] = pR[count] = inputSampleR;
			//double buffer
			
			count = (int)(gcount+floor(offsetA));
			
			totalL = pL[count] * 0.391; //less as value moves away from .0
			totalL += pL[count+widthA]; //we can assume always using this in one way or another?
			totalL += pL[count+widthA+widthA] * 0.391; //greater as value moves away from .0
			
			totalR = pR[count] * 0.391; //less as value moves away from .0
			totalR += pR[count+widthA]; //we can assume always using this in one way or another?
			totalR += pR[count+widthA+widthA] * 0.391; //greater as value moves away from .0
			
			inputSampleL += ((totalL * 0.274));
			inputSampleR += ((totalR * 0.274));
			
			count = (int)(gcount+floor(offsetB));
			
			totalL = pL[count] * 0.918; //less as value moves away from .0
			totalL += pL[count+widthB]; //we can assume always using this in one way or another?
			totalL += pL[count+widthB+widthB] * 0.918; //greater as value moves away from .0
			
			totalR = pR[count] * 0.918; //less as value moves away from .0
			totalR += pR[count+widthB]; //we can assume always using this in one way or another?
			totalR += pR[count+widthB+widthB] * 0.918; //greater as value moves away from .0
			
			inputSampleL -= ((totalL * 0.629));
			inputSampleR -= ((totalR * 0.629));
			
			inputSampleL /= 4;
			inputSampleR /= 4;
			
			gcount--;
			//still scrolling through the samples, remember
			
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
	
	double pL[4001];
	double pR[4001];
	double slide;
	int gcount;
	
	long double fpNShapeL;
	long double fpNShapeR;
	//default stuff

};
MIN_EXTERNAL(hombre);

