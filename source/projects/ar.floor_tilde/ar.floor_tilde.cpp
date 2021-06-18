#include "c74_min.h"

using namespace c74::min;

class arfloor : public object<arfloor>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"add a fake bottom octave"};
	MIN_TAGS {"audio, effect"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "Floor", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "Drive", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "Dry/Wet", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.0;
			B = 0.0;
			C = 1.0;
			
			flip = false;
			iirSample1AL = 0.0;
			iirSample1BL = 0.0;
			iirSample1CL = 0.0;
			iirSample1DL = 0.0;
			iirSample1EL = 0.0;
			iirSample2AL = 0.0;
			iirSample2BL = 0.0;
			iirSample2CL = 0.0;
			iirSample2DL = 0.0;
			iirSample2EL = 0.0;
		
			iirSample1AR = 0.0;
			iirSample1BR = 0.0;
			iirSample1CR = 0.0;
			iirSample1DR = 0.0;
			iirSample1ER = 0.0;
			iirSample2AR = 0.0;
			iirSample2BR = 0.0;
			iirSample2CR = 0.0;
			iirSample2DR = 0.0;
			iirSample2ER = 0.0;
			
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
		
		double setting = pow(A,2);
		double iirAmount = (setting/4.0)/overallscale;
		double tight = -1.0;
		double gaintrim = 1.0 + (setting/4.0);
		double offset;
		double lows;
		double density = B;
		double bridgerectifier;
		double temp;
		iirAmount += (iirAmount * tight * tight);
		tight /=  3.0;
		if (iirAmount <= 0.0) iirAmount = 0.0;
		if (iirAmount > 1.0) iirAmount = 1.0;
		double wet = C;
		double dry = 1.0-wet;
		
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
			//effectively digital black, we'll subtract it again. We want a 'air' hiss
			long double drySampleL = inputSampleL;
			long double drySampleR = inputSampleR;
			
			//begin left channel
			if (tight > 0) offset = (1 - tight) + (fabs(inputSampleL)*tight);
			else offset = (1 + tight) + ((1-fabs(inputSampleL))*tight);
			if (offset < 0) offset = 0;
			if (offset > 1) offset = 1;
			iirSample1AL = (iirSample1AL * (1 - (offset * iirAmount))) + (inputSampleL * (offset * iirAmount));
			lows = iirSample1AL;
			inputSampleL -= lows;
			temp = lows;
			if (lows < 0) {lows = -sin(-lows*1.5707963267949);}
			if (lows > 0) {lows = sin(lows*1.5707963267949);}
			lows -= temp;
			inputSampleL += lows;
			inputSampleL *= gaintrim;
			
			if (tight > 0) offset = (1 - tight) + (fabs(inputSampleL)*tight);
			else offset = (1 + tight) + ((1-fabs(inputSampleL))*tight);
			if (offset < 0) offset = 0;
			if (offset > 1) offset = 1;
			iirSample1BL = (iirSample1BL * (1 - (offset * iirAmount))) + (inputSampleL * (offset * iirAmount));
			lows = iirSample1BL;
			inputSampleL -= lows;
			temp = lows;
			if (lows < 0) {lows = -sin(-lows*1.5707963267949);}
			if (lows > 0) {lows = sin(lows*1.5707963267949);}
			lows -= temp;
			inputSampleL += lows;
			inputSampleL *= gaintrim;
			
			if (tight > 0) offset = (1 - tight) + (fabs(inputSampleL)*tight);
			else offset = (1 + tight) + ((1-fabs(inputSampleL))*tight);
			if (offset < 0) offset = 0;
			if (offset > 1) offset = 1;
			iirSample1CL = (iirSample1CL * (1 - (offset * iirAmount))) + (inputSampleL * (offset * iirAmount));
			lows = iirSample1CL;
			inputSampleL -= lows;
			temp = lows;
			if (lows < 0) {lows = -sin(-lows*1.5707963267949);}
			if (lows > 0) {lows = sin(lows*1.5707963267949);}
			lows -= temp;
			inputSampleL += lows;
			inputSampleL *= gaintrim;
			
			if (tight > 0) offset = (1 - tight) + (fabs(inputSampleL)*tight);
			else offset = (1 + tight) + ((1-fabs(inputSampleL))*tight);
			if (offset < 0) offset = 0;
			if (offset > 1) offset = 1;
			iirSample1DL = (iirSample1DL * (1 - (offset * iirAmount))) + (inputSampleL * (offset * iirAmount));
			lows = iirSample1DL;
			inputSampleL -= lows;
			temp = lows;
			if (lows < 0) {lows = -sin(-lows*1.5707963267949);}
			if (lows > 0) {lows = sin(lows*1.5707963267949);}
			lows -= temp;
			inputSampleL += lows;
			inputSampleL *= gaintrim;
			
			if (tight > 0) offset = (1 - tight) + (fabs(inputSampleL)*tight);
			else offset = (1 + tight) + ((1-fabs(inputSampleL))*tight);
			if (offset < 0) offset = 0;
			if (offset > 1) offset = 1;
			iirSample1EL = (iirSample1EL * (1 - (offset * iirAmount))) + (inputSampleL * (offset * iirAmount));
			lows = iirSample1EL;
			inputSampleL -= lows;
			temp = lows;
			if (lows < 0) {lows = -sin(-lows*1.5707963267949);}
			if (lows > 0) {lows = sin(lows*1.5707963267949);}
			lows -= temp;
			inputSampleL += lows;
			inputSampleL *= gaintrim;
			//end left channel
			
			//begin right channel
			if (tight > 0) offset = (1 - tight) + (fabs(inputSampleR)*tight);
			else offset = (1 + tight) + ((1-fabs(inputSampleR))*tight);
			if (offset < 0) offset = 0;
			if (offset > 1) offset = 1;
			iirSample1AR = (iirSample1AR * (1 - (offset * iirAmount))) + (inputSampleR * (offset * iirAmount));
			lows = iirSample1AR;
			inputSampleR -= lows;
			temp = lows;
			if (lows < 0) {lows = -sin(-lows*1.5707963267949);}
			if (lows > 0) {lows = sin(lows*1.5707963267949);}
			lows -= temp;
			inputSampleR += lows;
			inputSampleR *= gaintrim;
			
			if (tight > 0) offset = (1 - tight) + (fabs(inputSampleR)*tight);
			else offset = (1 + tight) + ((1-fabs(inputSampleR))*tight);
			if (offset < 0) offset = 0;
			if (offset > 1) offset = 1;
			iirSample1BR = (iirSample1BR * (1 - (offset * iirAmount))) + (inputSampleR * (offset * iirAmount));
			lows = iirSample1BR;
			inputSampleR -= lows;
			temp = lows;
			if (lows < 0) {lows = -sin(-lows*1.5707963267949);}
			if (lows > 0) {lows = sin(lows*1.5707963267949);}
			lows -= temp;
			inputSampleR += lows;
			inputSampleR *= gaintrim;
			
			if (tight > 0) offset = (1 - tight) + (fabs(inputSampleR)*tight);
			else offset = (1 + tight) + ((1-fabs(inputSampleR))*tight);
			if (offset < 0) offset = 0;
			if (offset > 1) offset = 1;
			iirSample1CR = (iirSample1CR * (1 - (offset * iirAmount))) + (inputSampleR * (offset * iirAmount));
			lows = iirSample1CR;
			inputSampleR -= lows;
			temp = lows;
			if (lows < 0) {lows = -sin(-lows*1.5707963267949);}
			if (lows > 0) {lows = sin(lows*1.5707963267949);}
			lows -= temp;
			inputSampleR += lows;
			inputSampleR *= gaintrim;
			
			if (tight > 0) offset = (1 - tight) + (fabs(inputSampleR)*tight);
			else offset = (1 + tight) + ((1-fabs(inputSampleR))*tight);
			if (offset < 0) offset = 0;
			if (offset > 1) offset = 1;
			iirSample1DR = (iirSample1DR * (1 - (offset * iirAmount))) + (inputSampleR * (offset * iirAmount));
			lows = iirSample1DR;
			inputSampleR -= lows;
			temp = lows;
			if (lows < 0) {lows = -sin(-lows*1.5707963267949);}
			if (lows > 0) {lows = sin(lows*1.5707963267949);}
			lows -= temp;
			inputSampleR += lows;
			inputSampleR *= gaintrim;
			
			if (tight > 0) offset = (1 - tight) + (fabs(inputSampleR)*tight);
			else offset = (1 + tight) + ((1-fabs(inputSampleR))*tight);
			if (offset < 0) offset = 0;
			if (offset > 1) offset = 1;
			iirSample1ER = (iirSample1ER * (1 - (offset * iirAmount))) + (inputSampleR * (offset * iirAmount));
			lows = iirSample1ER;
			inputSampleR -= lows;
			temp = lows;
			if (lows < 0) {lows = -sin(-lows*1.5707963267949);}
			if (lows > 0) {lows = sin(lows*1.5707963267949);}
			lows -= temp;
			inputSampleR += lows;
			inputSampleR *= gaintrim;
			//end right channel
			
			if (inputSampleL > 1.0) inputSampleL = 1.0;
			if (inputSampleL < -1.0) inputSampleL = -1.0;
			bridgerectifier = fabs(inputSampleL)*1.57079633;
			bridgerectifier = sin(bridgerectifier)*1.57079633;
			bridgerectifier = (fabs(inputSampleL)*(1-density))+(bridgerectifier*density);
			bridgerectifier = sin(bridgerectifier);
			if (inputSampleL > 0) inputSampleL = (inputSampleL*(1-density))+(bridgerectifier*density);
			else inputSampleL = (inputSampleL*(1-density))-(bridgerectifier*density);
			//drive section, left
			
			if (inputSampleR > 1.0) inputSampleR = 1.0;
			if (inputSampleR < -1.0) inputSampleR = -1.0;
			bridgerectifier = fabs(inputSampleR)*1.57079633;
			bridgerectifier = sin(bridgerectifier)*1.57079633;
			bridgerectifier = (fabs(inputSampleR)*(1-density))+(bridgerectifier*density);
			bridgerectifier = sin(bridgerectifier);
			if (inputSampleR > 0) inputSampleR = (inputSampleR*(1-density))+(bridgerectifier*density);
			else inputSampleR = (inputSampleR*(1-density))-(bridgerectifier*density);
			//drive section, right
			
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
	
	bool flip; //end defining of antialiasing variables
    
	double iirSample1AL;
	double iirSample1BL;
	double iirSample1CL;
	double iirSample1DL;
	double iirSample1EL;
	double iirSample2AL;
	double iirSample2BL;
	double iirSample2CL;
	double iirSample2DL;
	double iirSample2EL;

	double iirSample1AR;
	double iirSample1BR;
	double iirSample1CR;
	double iirSample1DR;
	double iirSample1ER;
	double iirSample2AR;
	double iirSample2BR;
	double iirSample2CR;
	double iirSample2DR;
	double iirSample2ER;	
	
	long double fpNShapeL;
	long double fpNShapeR;
	//default stuff

};
MIN_EXTERNAL(arfloor);

