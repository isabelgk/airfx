#include "c74_min.h"

using namespace c74::min;

class tremolo : public object<tremolo>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"fluctuating saturation curves for a tubey tremolo"};
	MIN_TAGS {"audio, effect"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "Speed", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "Depth", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.5;
			B = 1.0;
			sweep = 3.141592653589793238 / 2.0;
			speedChase = 0.0;
			depthChase = 0.0;
			speedAmount = 1.0;
			depthAmount = 0.0;
			lastSpeed = 1000.0;
			lastDepth = 1000.0;
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
	
		speedChase = pow(A,4);
		depthChase = B;
		double speedSpeed = 300 / (fabs( lastSpeed - speedChase)+1.0);
		double depthSpeed = 300 / (fabs( lastDepth - depthChase)+1.0);
		lastSpeed = speedChase;
		lastDepth = depthChase;
		
		double speed;
		double depth;
		double skew;
		double density;
		
		double tupi = 3.141592653589793238;
		double control;
		double tempcontrol;
		double thickness;
		double out;
		double bridgerectifier;
		double offset;
		
		long double inputSampleL;
		long double inputSampleR;
		long double drySampleL;
		long double drySampleR;
		
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
			
			
			speedAmount = (((speedAmount*speedSpeed)+speedChase)/(speedSpeed + 1.0));
			depthAmount = (((depthAmount*depthSpeed)+depthChase)/(depthSpeed + 1.0));
			speed = 0.0001+(speedAmount/1000.0);
			speed /= overallscale;
			depth = 1.0 - pow(1.0-depthAmount,5);
			skew = 1.0+pow(depthAmount,9);
			density = ((1.0-depthAmount)*2.0) - 1.0;		
	
			offset = sin(sweep);
			sweep += speed;
			if (sweep > tupi){sweep -= tupi;}
			control = fabs(offset);
			if (density > 0)
			{
				tempcontrol = sin(control);
				control = (control * (1.0-density))+(tempcontrol * density);
			}
			else
			{
				tempcontrol = 1-cos(control);
				control = (control * (1.0+density))+(tempcontrol * -density);
			}
			//produce either boosted or starved version of control signal
			//will go from 0 to 1
			
			thickness = ((control * 2.0) - 1.0)*skew;
			out = fabs(thickness);
			
			//do L
			bridgerectifier = fabs(inputSampleL);
			if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
			//max value for sine function
			if (thickness > 0) bridgerectifier = sin(bridgerectifier);
			else bridgerectifier = 1-cos(bridgerectifier);
			//produce either boosted or starved version
			if (inputSampleL > 0) inputSampleL = (inputSampleL*(1-out))+(bridgerectifier*out);
			else inputSampleL = (inputSampleL*(1-out))-(bridgerectifier*out);
			//blend according to density control
			inputSampleL *= (1.0 - control);
			inputSampleL *= 2.0;
			//apply tremolo, apply gain boost to compensate for volume loss
			inputSampleL = (drySampleL * (1-depth)) + (inputSampleL*depth);
			//end L
			
			//do R
			bridgerectifier = fabs(inputSampleR);
			if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
			//max value for sine function
			if (thickness > 0) bridgerectifier = sin(bridgerectifier);
			else bridgerectifier = 1-cos(bridgerectifier);
			//produce either boosted or starved version
			if (inputSampleR > 0) inputSampleR = (inputSampleR*(1-out))+(bridgerectifier*out);
			else inputSampleR = (inputSampleR*(1-out))-(bridgerectifier*out);
			//blend according to density control
			inputSampleR *= (1.0 - control);
			inputSampleR *= 2.0;
			//apply tremolo, apply gain boost to compensate for volume loss
			inputSampleR = (drySampleR * (1-depth)) + (inputSampleR*depth);
			//end R
			
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

	double sweep;
	double speedChase;
	double depthChase;
	double speedAmount;
	double depthAmount;
	double lastSpeed;
	double lastDepth;
	
};
MIN_EXTERNAL(tremolo);

