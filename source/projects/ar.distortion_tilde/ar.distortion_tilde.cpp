#include "c74_min.h"

using namespace c74::min;

class distortion : public object<distortion>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a slightly dark analog-style distortion with several presets"};
	MIN_TAGS {"audio, effect, analog, distortion"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "input", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "output", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "mix", 1.0, range {0.0, 1.0} };
    enum class modes : int { density, drive, spiral, mojo, dyno, enum_count };
    enum_map mode_range = { "density", "drive", "spiral", "mojo", "dyno" };
    attribute<modes> mode { this, "mode", modes::spiral, mode_range };
	
    message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.5;
			C = 0.5;
			D = 1.0;
			for (int x = 0; x < 9; x++) {
				previousInL[x] = 0.0; previousOutL[x] = 0.0;
				previousInR[x] = 0.0; previousOutR[x] = 0.0;
			}
			fpd = 17;
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

		int stages = (int)floor(samplerate()/25000.0);
		if (stages > 8) stages = 8;
		double input = pow(10.0,((A-0.5)*24.0)/20.0);
		double output = pow(10.0,((C-0.5)*24.0)/20.0);
		double wet = D;
	    
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-37) inputSampleL = fpd * 1.18e-37;
			if (fabs(inputSampleR)<1.18e-37) inputSampleR = fpd * 1.18e-37;
			long double drySampleL = inputSampleL;
			long double drySampleR = inputSampleR;
			
			inputSampleL *= input;
			inputSampleR *= input;
			
			for (int x = 0; x < stages; x++) {
				long double temp;
				temp = (inputSampleL+previousInL[x])*0.5;
				previousInL[x] = inputSampleL;
				inputSampleL = temp;
				temp = (inputSampleR+previousInR[x])*0.5;
				previousInR[x] = inputSampleR;
				inputSampleR = temp;
			}
			
			switch (mode)
			{
                case modes::density:
					if (inputSampleL > 1.570796326794897) inputSampleL = 1.570796326794897;
					if (inputSampleL < -1.570796326794897) inputSampleL = -1.570796326794897;
					if (inputSampleR > 1.570796326794897) inputSampleR = 1.570796326794897;
					if (inputSampleR < -1.570796326794897) inputSampleR = -1.570796326794897;
					//clip to 1.570796326794897 to reach maximum output
					inputSampleL = sin(inputSampleL);
					inputSampleR = sin(inputSampleR);
					break;
                case modes::drive:
					if (inputSampleL > 1.0) inputSampleL = 1.0;
					if (inputSampleL < -1.0) inputSampleL = -1.0;
					if (inputSampleR > 1.0) inputSampleR = 1.0;
					if (inputSampleR < -1.0) inputSampleR = -1.0;
					inputSampleL -= (inputSampleL * (fabs(inputSampleL) * 0.6) * (fabs(inputSampleL) * 0.6));
					inputSampleR -= (inputSampleR * (fabs(inputSampleR) * 0.6) * (fabs(inputSampleR) * 0.6));
					inputSampleL *= 1.5;
					inputSampleR *= 1.5;
					break;
                case modes::spiral:
					if (inputSampleL > 1.2533141373155) inputSampleL = 1.2533141373155;
					if (inputSampleL < -1.2533141373155) inputSampleL = -1.2533141373155;
					if (inputSampleR > 1.2533141373155) inputSampleR = 1.2533141373155;
					if (inputSampleR < -1.2533141373155) inputSampleR = -1.2533141373155;
					//clip to 1.2533141373155 to reach maximum output
					inputSampleL = sin(inputSampleL * fabs(inputSampleL)) / ((fabs(inputSampleL) == 0.0) ?1:fabs(inputSampleL));
					inputSampleR = sin(inputSampleR * fabs(inputSampleR)) / ((fabs(inputSampleR) == 0.0) ?1:fabs(inputSampleR));
					break;
                case modes::mojo:
					long double mojo; mojo = pow(fabs(inputSampleL),0.25);
					if (mojo > 0.0) inputSampleL = (sin(inputSampleL * mojo * M_PI * 0.5) / mojo) * 0.987654321;
					mojo = pow(fabs(inputSampleR),0.25);
					if (mojo > 0.0) inputSampleR = (sin(inputSampleR * mojo * M_PI * 0.5) / mojo) * 0.987654321;
					//mojo is the one that flattens WAAAAY out very softly before wavefolding				
					break;
                case modes::dyno:
					long double dyno; dyno = pow(fabs(inputSampleL),4);
					if (dyno > 0.0) inputSampleL = (sin(inputSampleL * dyno) / dyno) * 1.1654321;
					dyno = pow(fabs(inputSampleR),4);
					if (dyno > 0.0) inputSampleR = (sin(inputSampleR * dyno) / dyno) * 1.1654321;
					//dyno is the one that tries to raise peak energy				
					break;
			}				
			
			for (int x = 1; x < (stages/2); x++) {
				long double temp;
				temp = (inputSampleL+previousOutL[x])*0.5;
				previousOutL[x] = inputSampleL;
				inputSampleL = temp;
				temp = (inputSampleR+previousOutR[x])*0.5;
				previousOutR[x] = inputSampleR;
				inputSampleR = temp;
			}		
			
			if (output != 1.0) {
				inputSampleL *= output;
				inputSampleR *= output;
			}
			
			if (wet !=1.0) {
				inputSampleL = (inputSampleL * wet) + (drySampleL * (1.0-wet));
				inputSampleR = (inputSampleR * wet) + (drySampleR * (1.0-wet));
			}
			
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
    
	long double previousInL[9];
	long double previousOutL[9];
	long double previousInR[9];
	long double previousOutR[9];

	uint32_t fpd;
	//default stuff

};
MIN_EXTERNAL(distortion);

