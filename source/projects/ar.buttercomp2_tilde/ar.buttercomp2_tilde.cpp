#include "c74_min.h"

using namespace c74::min;

class buttercomp2 : public object<buttercomp2>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"The softest, smoothest compressor, improved with an output control and sound upgrades."};
	MIN_TAGS {"audio, effect, compressor"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "compress", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "output", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			controlAposL = 1.0;
			controlAnegL = 1.0;
			controlBposL = 1.0;
			controlBnegL = 1.0;
			targetposL = 1.0;
			targetnegL = 1.0;
			lastOutputL = 0.0;
		
			controlAposR = 1.0;
			controlAnegR = 1.0;
			controlBposR = 1.0;
			controlBnegR = 1.0;
			targetposR = 1.0;
			targetnegR = 1.0;
			lastOutputR = 0.0;
		
			flip = false;
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
		
		double inputgain = pow(10.0,(A*14.0)/20.0);
		double compfactor = 0.012 * (A / 135.0);
		double output = B * 2.0;
		double wet = C;
		double dry = 1.0 - wet;
		double outputgain = inputgain;
		outputgain -= 1.0;
		outputgain /= 1.5;
		outputgain += 1.0;
	    	
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
	
			static int noisesourceL = 0;
			static int noisesourceR = 850010;
			int residue;
			double applyresidue;
			
			noisesourceL = noisesourceL % 1700021; noisesourceL++;
			residue = noisesourceL * noisesourceL;
			residue = residue % 170003; residue *= residue;
			residue = residue % 17011; residue *= residue;
			residue = residue % 1709; residue *= residue;
			residue = residue % 173; residue *= residue;
			residue = residue % 17;
			applyresidue = residue;
			applyresidue *= 0.00000001;
			applyresidue *= 0.00000001;
			inputSampleL += applyresidue;
			if (inputSampleL<1.2e-38 && -inputSampleL<1.2e-38) {
				inputSampleL -= applyresidue;
			}
			
			noisesourceR = noisesourceR % 1700021; noisesourceR++;
			residue = noisesourceR * noisesourceR;
			residue = residue % 170003; residue *= residue;
			residue = residue % 17011; residue *= residue;
			residue = residue % 1709; residue *= residue;
			residue = residue % 173; residue *= residue;
			residue = residue % 17;
			applyresidue = residue;
			applyresidue *= 0.00000001;
			applyresidue *= 0.00000001;
			inputSampleR += applyresidue;
			if (inputSampleR<1.2e-38 && -inputSampleR<1.2e-38) {
				inputSampleR -= applyresidue;
			}
			//for live air, we always apply the dither noise. Then, if our result is 
			//effectively digital black, we'll subtract it aButterComp2. We want a 'air' hiss
			double drySampleL = inputSampleL;
			double drySampleR = inputSampleR;
			
			inputSampleL *= inputgain;
			inputSampleR *= inputgain;
			
			long double divisor = compfactor / (1.0+fabs(lastOutputL));
			//this is slowing compressor recovery while output waveforms were high
			divisor /= overallscale;
			long double remainder = divisor;
			divisor = 1.0 - divisor;
			//recalculate divisor every sample		
			
			long double inputposL = inputSampleL + 1.0;
			if (inputposL < 0.0) inputposL = 0.0;
			long double outputposL = inputposL / 2.0;
			if (outputposL > 1.0) outputposL = 1.0;		
			inputposL *= inputposL;
			targetposL *= divisor;
			targetposL += (inputposL * remainder);
			long double calcposL = pow((1.0/targetposL),2);
			
			long double inputnegL = (-inputSampleL) + 1.0;
			if (inputnegL < 0.0) inputnegL = 0.0;
			long double outputnegL = inputnegL / 2.0;
			if (outputnegL > 1.0) outputnegL = 1.0;		
			inputnegL *= inputnegL;
			targetnegL *= divisor;
			targetnegL += (inputnegL * remainder);
			long double calcnegL = pow((1.0/targetnegL),2);
			//now we have mirrored targets for comp
			//outputpos and outputneg go from 0 to 1
			
			if (inputSampleL > 0)
			{ //working on pos
				if (flip)
				{
					controlAposL *= divisor;
					controlAposL += (calcposL*remainder);
					
				}
				else
				{
					controlBposL *= divisor;
					controlBposL += (calcposL*remainder);
				}
			}
			else
			{ //working on neg
				if (flip)
				{
					controlAnegL *= divisor;
					controlAnegL += (calcnegL*remainder);
				}
				else
				{
					controlBnegL *= divisor;
					controlBnegL += (calcnegL*remainder);
				}
			}
			//this causes each of the four to update only when active and in the correct 'flip'
			
			divisor = compfactor / (1.0+fabs(lastOutputR));
			//this is slowing compressor recovery while output waveforms were high
			divisor /= overallscale;
			remainder = divisor;
			divisor = 1.0 - divisor;
			//recalculate divisor every sample		
			
			long double inputposR = inputSampleR + 1.0;
			if (inputposR < 0.0) inputposR = 0.0;
			long double outputposR = inputposR / 2.0;
			if (outputposR > 1.0) outputposR = 1.0;		
			inputposR *= inputposR;
			targetposR *= divisor;
			targetposR += (inputposR * remainder);
			long double calcposR = pow((1.0/targetposR),2);
			
			long double inputnegR = (-inputSampleR) + 1.0;
			if (inputnegR < 0.0) inputnegR = 0.0;
			long double outputnegR = inputnegR / 2.0;
			if (outputnegR > 1.0) outputnegR = 1.0;		
			inputnegR *= inputnegR;
			targetnegR *= divisor;
			targetnegR += (inputnegR * remainder);
			long double calcnegR = pow((1.0/targetnegR),2);
			//now we have mirrored targets for comp
			//outputpos and outputneg go from 0 to 1
			
			if (inputSampleR > 0)
			{ //working on pos
				if (flip)
				{
					controlAposR *= divisor;
					controlAposR += (calcposR*remainder);
					
				}
				else
				{
					controlBposR *= divisor;
					controlBposR += (calcposR*remainder);
				}
			}
			else
			{ //working on neg
				if (flip)
				{
					controlAnegR *= divisor;
					controlAnegR += (calcnegR*remainder);
				}
				else
				{
					controlBnegR *= divisor;
					controlBnegR += (calcnegR*remainder);
				}
			}
			//this causes each of the four to update only when active and in the correct 'flip'
			
			long double totalmultiplierL;
			long double totalmultiplierR;
			if (flip)
			{
				totalmultiplierL = (controlAposL * outputposL) + (controlAnegL * outputnegL);
				totalmultiplierR = (controlAposR * outputposR) + (controlAnegR * outputnegR);
			}
			else
			{
				totalmultiplierL = (controlBposL * outputposL) + (controlBnegL * outputnegL);
				totalmultiplierR = (controlBposR * outputposR) + (controlBnegR * outputnegR);
			}
			//this combines the sides according to flip, blending relative to the input value
			
			inputSampleL *= totalmultiplierL;
			inputSampleL /= outputgain;
			
			inputSampleR *= totalmultiplierR;
			inputSampleR /= outputgain;
			
			if (output != 1.0) {
				inputSampleL *= output;
				inputSampleR *= output;
			}
			
			if (wet !=1.0) {
				inputSampleL = (inputSampleL * wet) + (drySampleL * dry);
				inputSampleR = (inputSampleR * wet) + (drySampleR * dry);
			}
			
			lastOutputL = inputSampleL;
			lastOutputR = inputSampleR;
			//we will make this factor respond to use of dry/wet
			
			flip = !flip;
			
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
    
	long double controlAposL;
	long double controlAnegL;
	long double controlBposL;
	long double controlBnegL;
	long double targetposL;
	long double targetnegL;
	long double lastOutputL;
	long double controlAposR;
	long double controlAnegR;
	long double controlBposR;
	long double controlBnegR;
	long double targetposR;
	long double targetnegR;
	long double lastOutputR;
	bool flip;
	long double fpNShapeL;
	long double fpNShapeR;
	//default stuff

};
MIN_EXTERNAL(buttercomp2);

