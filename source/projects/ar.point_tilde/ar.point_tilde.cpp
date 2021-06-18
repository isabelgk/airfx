#include "c74_min.h"

using namespace c74::min;

class point : public object<point>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"explosive transient designer"};
	MIN_TAGS {"audio, effect"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "Input Trim", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "Point", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "Reaction Speed", 0.5, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.5;
			B = 0.5;
			C = 0.5;
			nibAL = 0.0;
			nobAL = 0.0;
			nibBL = 0.0;
			nobBL = 0.0;
			nibAR = 0.0;
			nobAR = 0.0;
			nibBR = 0.0;
			nobBR = 0.0;
			
			fpNShapeL = 0.0;
			fpNShapeR = 0.0;
			fpFlip = true;
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
		
		double gaintrim = pow(10.0,((A*24.0)-12.0)/20);
		double nibDiv = 1 / pow(C+0.2,7);
		nibDiv /= overallscale;
		double nobDiv;
		if (((B*2.0)-1.0) > 0) nobDiv = nibDiv / (1.001-((B*2.0)-1.0));
		else nobDiv = nibDiv * (1.001-pow(((B*2.0)-1.0)*0.75,2));
		double nibnobFactor = 0.0; //start with the fallthrough value, why not
		double absolute;
		
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
			
			inputSampleL *= gaintrim;
			absolute = fabs(inputSampleL);
			if (fpFlip)
			{
				nibAL = nibAL + (absolute / nibDiv);
				nibAL = nibAL / (1 + (1/nibDiv));
				nobAL = nobAL + (absolute / nobDiv);
				nobAL = nobAL / (1 + (1/nobDiv));
				if (nobAL > 0)
				{
					nibnobFactor = nibAL / nobAL;
				}
			}
			else
			{
				nibBL = nibBL + (absolute / nibDiv);
				nibBL = nibBL / (1 + (1/nibDiv));
				nobBL = nobBL + (absolute / nobDiv);
				nobBL = nobBL / (1 + (1/nobDiv));
				if (nobBL > 0)
				{
					nibnobFactor = nibBL / nobBL;
				}		
			}
			inputSampleL *= nibnobFactor;
			
			
			inputSampleR *= gaintrim;
			absolute = fabs(inputSampleR);
			if (fpFlip)
			{
				nibAR = nibAR + (absolute / nibDiv);
				nibAR = nibAR / (1 + (1/nibDiv));
				nobAR = nobAR + (absolute / nobDiv);
				nobAR = nobAR / (1 + (1/nobDiv));
				if (nobAR > 0)
				{
					nibnobFactor = nibAR / nobAR;
				}
			}
			else
			{
				nibBR = nibBR + (absolute / nibDiv);
				nibBR = nibBR / (1 + (1/nibDiv));
				nobBR = nobBR + (absolute / nobDiv);
				nobBR = nobBR / (1 + (1/nobDiv));
				if (nobBR > 0)
				{
					nibnobFactor = nibBR / nobBR;
				}		
			}
			inputSampleR *= nibnobFactor;
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
    
	long double fpNShapeL;
	long double fpNShapeR;
	bool fpFlip;
	//default stuff
	double nibAL;
	double nobAL;
	double nibBL;
	double nobBL;
	double nibAR;
	double nobAR;
	double nibBR;
	double nobBR;
	
};
MIN_EXTERNAL(point);

