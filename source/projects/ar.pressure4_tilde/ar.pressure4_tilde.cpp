#include "c74_min.h"

using namespace c74::min;

class pressure4 : public object<pressure4>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a compressor adjustable between vari-mu and New York peak-retaining behaviors"};
	MIN_TAGS {"compressor"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "pressure", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "speed", 0.2, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "mewiness", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "output", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			fpNShapeL = 0.0;
			fpNShapeR = 0.0;
			muSpeedA = 10000;
			muSpeedB = 10000;
			muCoefficientA = 1;
			muCoefficientB = 1;
			muVary = 1;
			flip = false;	
			//this is reset: values being initialized only once. Startup values, whatever they are.
			
			return {};
		}
	};

	void operator()(audio_bundle _input, audio_bundle _output) {
		double* inputL = _input.samples(0);
		double* inputR = _input.samples(1);
		double* outputL = _output.samples(0);
		double* outputR = _output.samples(1);
		long sampleFrames = _input.frame_count();

		double overallscale = 1.0;
		overallscale /= 44100.0;
		overallscale *= samplerate();
		double threshold = 1.0 - (A * 0.95);
		double muMakeupGain = 1.0 / threshold;
		//gain settings around threshold
		double release = pow((1.28-B),5)*32768.0;
		release /= overallscale;
		double fastest = sqrt(release);
		//speed settings around release
		long double bridgerectifier;
		double coefficient;
		double inputSense;
		double mewiness = (C*2.0)-1.0;
		double unmewiness;
		double outputGain = D;
		bool positivemu;
		if (mewiness >= 0)
		{
			positivemu = true;
			unmewiness = 1.0-mewiness;
		}
		else
		{
			positivemu = false;
			mewiness = -mewiness;
			unmewiness = 1.0-mewiness;
		}
		// µ µ µ µ µ µ µ µ µ µ µ µ is the kitten song o/~
	
		long double inputSampleL;
		long double inputSampleR;
	 
	
	    while (--sampleFrames >= 0)
	    {
			inputSampleL = *inputL;
			inputSampleR = *inputR;
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
			
			inputSampleL = inputSampleL * muMakeupGain;
			inputSampleR = inputSampleR * muMakeupGain;
			
			inputSense = fabs(inputSampleL);
			if (fabs(inputSampleR) > inputSense)
				inputSense = fabs(inputSampleR);
			//we will take the greater of either channel and just use that, then apply the result
			//to both stereo channels.
			
			if (flip)
			{
				if (inputSense > threshold)
				{
					muVary = threshold / inputSense;
					muAttack = sqrt(fabs(muSpeedA));
					muCoefficientA = muCoefficientA * (muAttack-1.0);
					if (muVary < threshold)
					{
						muCoefficientA = muCoefficientA + threshold;
					}
					else
					{
						muCoefficientA = muCoefficientA + muVary;
					}
					muCoefficientA = muCoefficientA / muAttack;
				}
				else
				{
					muCoefficientA = muCoefficientA * ((muSpeedA * muSpeedA)-1.0);
					muCoefficientA = muCoefficientA + 1.0;
					muCoefficientA = muCoefficientA / (muSpeedA * muSpeedA);
				}
				muNewSpeed = muSpeedA * (muSpeedA-1);
				muNewSpeed = muNewSpeed + fabs(inputSense*release)+fastest;
				muSpeedA = muNewSpeed / muSpeedA;
			}
			else
			{
				if (inputSense > threshold)
				{
					muVary = threshold / inputSense;
					muAttack = sqrt(fabs(muSpeedB));
					muCoefficientB = muCoefficientB * (muAttack-1);
					if (muVary < threshold)
					{
						muCoefficientB = muCoefficientB + threshold;
					}
					else
					{
						muCoefficientB = muCoefficientB + muVary;
					}
					muCoefficientB = muCoefficientB / muAttack;
				}
				else
				{
					muCoefficientB = muCoefficientB * ((muSpeedB * muSpeedB)-1.0);
					muCoefficientB = muCoefficientB + 1.0;
					muCoefficientB = muCoefficientB / (muSpeedB * muSpeedB);
				}
				muNewSpeed = muSpeedB * (muSpeedB-1);
				muNewSpeed = muNewSpeed + fabs(inputSense*release)+fastest;
				muSpeedB = muNewSpeed / muSpeedB;
			}
			//got coefficients, adjusted speeds
			
			if (flip)
			{
				if (positivemu) coefficient = pow(muCoefficientA,2);
				else coefficient = sqrt(muCoefficientA);
				coefficient = (coefficient*mewiness)+(muCoefficientA*unmewiness);
				inputSampleL *= coefficient;
				inputSampleR *= coefficient;
			}
			else
			{
				if (positivemu) coefficient = pow(muCoefficientB,2);
				else coefficient = sqrt(muCoefficientB);
				coefficient = (coefficient*mewiness)+(muCoefficientB*unmewiness);
				inputSampleL *= coefficient;
				inputSampleR *= coefficient;
			}
			//applied compression with vari-vari-µ-µ-µ-µ-µ-µ-is-the-kitten-song o/~
			//applied gain correction to control output level- tends to constrain sound rather than inflate it
			
			if (outputGain != 1.0) {
				inputSampleL *= outputGain;
				inputSampleR *= outputGain;
			}		
	
			bridgerectifier = fabs(inputSampleL);
			if (bridgerectifier > 1.57079633) bridgerectifier = 1.0;
			else bridgerectifier = sin(bridgerectifier);
			if (inputSampleL > 0){inputSampleL = bridgerectifier;}
			else {inputSampleL = -bridgerectifier;}
			//second stage of overdrive to prevent overs and allow bloody loud extremeness
			bridgerectifier = fabs(inputSampleR);
			if (bridgerectifier > 1.57079633) bridgerectifier = 1.0;
			else bridgerectifier = sin(bridgerectifier);
			if (inputSampleR > 0){inputSampleR = bridgerectifier;}
			else {inputSampleR = -bridgerectifier;}
			//second stage of overdrive to prevent overs and allow bloody loud extremeness
			
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
			
			*outputL = inputSampleL;
			*outputR = inputSampleR;
	
			*inputL++;
			*inputR++;
			*outputL++;
			*outputR++;
		}
	}
private:
    
	double muVary;
	double muAttack;
	double muNewSpeed;
	double muSpeedA;
	double muSpeedB;
	double muCoefficientA;
	double muCoefficientB;
	long double fpNShapeL;
	long double fpNShapeR;
	bool flip;

};
MIN_EXTERNAL(pressure4);

