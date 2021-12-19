#include "c74_min.h"

using namespace c74::min;

class focus : public object<focus>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"brings out clarity by distorting"};
	MIN_TAGS {"audio, effect"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	enum class modes : int { density, drive, spiral, mojo, dyno, enum_count };
	enum_map mode_range = { "density", "drive", "spiral", "mojo", "dyno" };
	attribute<modes> mode { this, "mode", modes::density, mode_range };
	
    attribute<number, threadsafe::no, limit::clamp> A {this, "boost", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "focus", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "output", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> E {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.0;
			B = 0.5;
			D = 1.0;
			E = 1.0;
			for (int x = 0; x < 9; x++) {figureL[x] = 0.0;figureR[x] = 0.0;}
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

		//[0] is frequency: 0.000001 to 0.499999 is _near-zero to _near-Nyquist
		//[1] is resonance, 0.7071 is Butterworth. Also can't be zero
		double boost = pow(10.0,(A*12.0)/20.0);
		figureL[0] = figureR[0] = 3515.775/samplerate(); //fixed frequency, 3.515775k
		figureL[1] = figureR[1] = pow(pow(B,3)*2,2)+0.0001; //resonance
		double output = D;
		double wet = E;
		
		double K = tan(M_PI * figureR[0]);
		double norm = 1.0 / (1.0 + K / figureR[1] + K * K);
		figureL[2] = figureR[2] = K / figureR[1] * norm;
		figureL[4] = figureR[4] = -figureR[2];
		figureL[5] = figureR[5] = 2.0 * (K * K - 1.0) * norm;
		figureL[6] = figureR[6] = (1.0 - K / figureR[1] + K * K) * norm;
		
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpd * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpd * 1.18e-43;
			long double drySampleL = inputSampleL;
			long double drySampleR = inputSampleR;
			
			inputSampleL = sin(inputSampleL);
			inputSampleR = sin(inputSampleR);
			//encode Console5: good cleanness
			
			long double tempSample = (inputSampleL * figureL[2]) + figureL[7];
			figureL[7] = -(tempSample * figureL[5]) + figureL[8];
			figureL[8] = (inputSampleL * figureL[4]) - (tempSample * figureL[6]);
			inputSampleL = tempSample;
			
			tempSample = (inputSampleR * figureR[2]) + figureR[7];
			figureR[7] = -(tempSample * figureR[5]) + figureR[8];
			figureR[8] = (inputSampleR * figureR[4]) - (tempSample * figureR[6]);
			inputSampleR = tempSample;
			
			if (inputSampleL > 1.0) inputSampleL = 1.0;
			if (inputSampleL < -1.0) inputSampleL = -1.0;
			if (inputSampleR > 1.0) inputSampleR = 1.0;
			if (inputSampleR < -1.0) inputSampleR = -1.0;
			//without this, you can get a NaN condition where it spits out DC offset at full blast!
			inputSampleL = asin(inputSampleL);
			inputSampleR = asin(inputSampleR);
			//decode Console5
			
			long double groundSampleL = drySampleL - inputSampleL; //set up UnBox
			long double groundSampleR = drySampleR - inputSampleR; //set up UnBox
			inputSampleL *= boost; //now, focussed area gets cranked before distort
			inputSampleR *= boost; //now, focussed area gets cranked before distort
			
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
					inputSampleL *= 1.6;
					inputSampleR *= 1.6;
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
			
			if (output != 1.0) {
				inputSampleL *= output;
				inputSampleR *= output;
			}
			
			inputSampleL += groundSampleL; //effectively UnBox
			inputSampleR += groundSampleR; //effectively UnBox
			
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
    
	long double figureL[9];
	long double figureR[9];
	uint32_t fpd;
	//default stuff

};
MIN_EXTERNAL(focus);

