#include "c74_min.h"

using namespace c74::min;

class lowpass2 : public object<lowpass2>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"an unusual-sounding variable-slope lowpass filter"};
	MIN_TAGS {"filter"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "lowpass", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "hardness", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "poles", 0.25, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			fpd = 17;
			
			iirSampleAL = 0.0;
			iirSampleBL = 0.0;
			iirSampleCL = 0.0;
			iirSampleDL = 0.0;
			iirSampleEL = 0.0;
			iirSampleFL = 0.0;
			iirSampleGL = 0.0;
			iirSampleHL = 0.0;
		
			iirSampleAR = 0.0;
			iirSampleBR = 0.0;
			iirSampleCR = 0.0;
			iirSampleDR = 0.0;
			iirSampleER = 0.0;
			iirSampleFR = 0.0;
			iirSampleGR = 0.0;
			iirSampleHR = 0.0;
		
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

		double iirAmount = A;
		double tight = (B*2.0)-1.0;
		iirAmount += fabs(tight);
		if (iirAmount < 0.0000001) iirAmount = 0.0000001;
		if (iirAmount > 1) iirAmount = 1;
		if (tight < 0.0) tight *= 0.5;
		double offsetL;
		double offsetR;
		double aWet = 1.0;
		double bWet = 1.0;
		double cWet = 1.0;
		double dWet = C*4.0;
		//four-stage wet/dry control using progressive stages that bypass when not engaged
		if (dWet < 1.0) {aWet = dWet; bWet = 0.0; cWet = 0.0; dWet = 0.0;}
		else if (dWet < 2.0) {bWet = dWet - 1.0; cWet = 0.0; dWet = 0.0;}
		else if (dWet < 3.0) {cWet = dWet - 2.0; dWet = 0.0;}
		else {dWet -= 3.0;}
		//this is one way to make a little set of dry/wet stages that are successively added to the
		//output as the control is turned up. Each one independently goes from 0-1 and stays at 1
		//beyond that point: this is a way to progressively add a 'black box' sound processing
		//which lets you fall through to simpler processing at lower settings.
		double wet = D;
		
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
			
			if (tight > 0) offsetL = (1 - tight) + (fabs(inputSampleL)*tight);
			else offsetL = (1 + tight) + ((1-fabs(inputSampleL))*tight);
			if (offsetL < 0.0000001) offsetL = 0.0000001; if (offsetL > 1) offsetL = 1;
			
			if (tight > 0) offsetR = (1 - tight) + (fabs(inputSampleR)*tight);
			else offsetR = (1 + tight) + ((1-fabs(inputSampleR))*tight);
			if (offsetR < 0.0000001) offsetR = 0.0000001; if (offsetR > 1) offsetR = 1;
			
			if (fpFlip)
			{
				if (aWet > 0.0) {
					iirSampleAL = (iirSampleAL * (1 - (offsetL * iirAmount))) + (inputSampleL * (offsetL * iirAmount));
					inputSampleL = (iirSampleAL * aWet) + (inputSampleL * (1.0-aWet));
					
					iirSampleAR = (iirSampleAR * (1 - (offsetR * iirAmount))) + (inputSampleR * (offsetR * iirAmount));
					inputSampleR = (iirSampleAR * aWet) + (inputSampleR * (1.0-aWet));
				}
				if (bWet > 0.0) {
					iirSampleCL = (iirSampleCL * (1 - (offsetL * iirAmount))) + (inputSampleL * (offsetL * iirAmount));
					inputSampleL = (iirSampleCL * bWet) + (inputSampleL * (1.0-bWet));
					
					iirSampleCR = (iirSampleCR * (1 - (offsetR * iirAmount))) + (inputSampleR * (offsetR * iirAmount));
					inputSampleR = (iirSampleCR * bWet) + (inputSampleR * (1.0-bWet));
				}
				if (cWet > 0.0) {
					iirSampleEL = (iirSampleEL * (1 - (offsetL * iirAmount))) + (inputSampleL * (offsetL * iirAmount));
					inputSampleL = (iirSampleEL * cWet) + (inputSampleL * (1.0-cWet));
					
					iirSampleER = (iirSampleER * (1 - (offsetR * iirAmount))) + (inputSampleR * (offsetR * iirAmount));
					inputSampleR = (iirSampleER * cWet) + (inputSampleR * (1.0-cWet));
				}
				if (dWet > 0.0) {
					iirSampleGL = (iirSampleGL * (1 - (offsetL * iirAmount))) + (inputSampleL * (offsetL * iirAmount));
					inputSampleL = (iirSampleGL * dWet) + (inputSampleL * (1.0-dWet));
					
					iirSampleGR = (iirSampleGR * (1 - (offsetR * iirAmount))) + (inputSampleR * (offsetR * iirAmount));
					inputSampleR = (iirSampleGR * dWet) + (inputSampleR * (1.0-dWet));
				}
			}
			else
			{
				if (aWet > 0.0) {
					iirSampleBL = (iirSampleBL * (1 - (offsetL * iirAmount))) + (inputSampleL * (offsetL * iirAmount));
					inputSampleL = (iirSampleBL * aWet) + (inputSampleL * (1.0-aWet));
					
					iirSampleBR = (iirSampleBR * (1 - (offsetR * iirAmount))) + (inputSampleR * (offsetR * iirAmount));
					inputSampleR = (iirSampleBR * aWet) + (inputSampleR * (1.0-aWet));
				}
				if (bWet > 0.0) {
					iirSampleDL = (iirSampleDL * (1 - (offsetL * iirAmount))) + (inputSampleL * (offsetL * iirAmount));
					inputSampleL = (iirSampleDL * bWet) + (inputSampleL * (1.0-bWet));
					
					iirSampleDR = (iirSampleDR * (1 - (offsetR * iirAmount))) + (inputSampleR * (offsetR * iirAmount));
					inputSampleR = (iirSampleDR * bWet) + (inputSampleR * (1.0-bWet));
				}
				if (cWet > 0.0) {
					iirSampleFL = (iirSampleFL * (1 - (offsetL * iirAmount))) + (inputSampleL * (offsetL * iirAmount));
					inputSampleL = (iirSampleFL * cWet) + (inputSampleL * (1.0-cWet));
					
					iirSampleFR = (iirSampleFR * (1 - (offsetR * iirAmount))) + (inputSampleR * (offsetR * iirAmount));
					inputSampleR = (iirSampleFR * cWet) + (inputSampleR * (1.0-cWet));
				}
				if (dWet > 0.0) {
					iirSampleHL = (iirSampleHL * (1 - (offsetL * iirAmount))) + (inputSampleL * (offsetL * iirAmount));
					inputSampleL = (iirSampleHL * dWet) + (inputSampleL * (1.0-dWet));
					
					iirSampleHR = (iirSampleHR * (1 - (offsetR * iirAmount))) + (inputSampleR * (offsetR * iirAmount));
					inputSampleR = (iirSampleHR * dWet) + (inputSampleR * (1.0-dWet));
				}
			}
			
			if (wet !=1.0) {
				inputSampleL = (inputSampleL * wet) + (drySampleL * (1.0-wet));
				inputSampleR = (inputSampleR * wet) + (drySampleR * (1.0-wet));
			}
			//Dry/Wet control, defaults to the last slider
			fpFlip = !fpFlip;
			
			//begin 64 bit stereo floating point dither
			int expon; frexp((double)inputSampleL, &expon);
			fpd ^= fpd << 13; fpd ^= fpd >> 17; fpd ^= fpd << 5;
			inputSampleL += ((double(fpd)-uint32_t(0x7fffffff)) * 1.1e-44l * pow(2,expon+62));
			frexp((double)inputSampleR, &expon);
			fpd ^= fpd << 13; fpd ^= fpd >> 17; fpd ^= fpd << 5;
			inputSampleR += ((double(fpd)-uint32_t(0x7fffffff)) * 1.1e-44l * pow(2,expon+62));
			//end 64 bit stereo floating point dither
			
			*out1 = inputSampleL;
			*out2 = inputSampleR;
	
			*in1++;
			*in2++;
			*out1++;
			*out2++;
		}
	}
private:
    
	uint32_t fpd;
	//default stuff
	
	double iirSampleAL;
	double iirSampleBL;
	double iirSampleCL;
	double iirSampleDL;
	double iirSampleEL;
	double iirSampleFL;
	double iirSampleGL;
	double iirSampleHL;
	
	double iirSampleAR;
	double iirSampleBR;
	double iirSampleCR;
	double iirSampleDR;
	double iirSampleER;
	double iirSampleFR;
	double iirSampleGR;
	double iirSampleHR;
	
	bool fpFlip;

};
MIN_EXTERNAL(lowpass2);

