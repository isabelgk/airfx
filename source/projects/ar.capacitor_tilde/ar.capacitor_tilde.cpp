#include "c74_min.h"

using namespace c74::min;

class capacitor : public object<capacitor>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a lowpass/highpass filter"};
	MIN_TAGS {"audio, effect, filter"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "lowpass", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "highpass", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 1.0;
			B = 0.0;
			C = 1.0;
			iirHighpassAL = 0.0;
			iirHighpassBL = 0.0;
			iirHighpassCL = 0.0;
			iirHighpassDL = 0.0;
			iirHighpassEL = 0.0;
			iirHighpassFL = 0.0;
			iirLowpassAL = 0.0;
			iirLowpassBL = 0.0;
			iirLowpassCL = 0.0;
			iirLowpassDL = 0.0;
			iirLowpassEL = 0.0;
			iirLowpassFL = 0.0;
		
			iirHighpassAR = 0.0;
			iirHighpassBR = 0.0;
			iirHighpassCR = 0.0;
			iirHighpassDR = 0.0;
			iirHighpassER = 0.0;
			iirHighpassFR = 0.0;
			iirLowpassAR = 0.0;
			iirLowpassBR = 0.0;
			iirLowpassCR = 0.0;
			iirLowpassDR = 0.0;
			iirLowpassER = 0.0;
			iirLowpassFR = 0.0;
			count = 0;
			lowpassChase = 0.0;
			highpassChase = 0.0;
			wetChase = 0.0;
			lowpassAmount = 1.0;
			highpassAmount = 0.0;
			wet = 1.0;
			lastLowpass = 1000.0;
			lastHighpass = 1000.0;
			lastWet = 1000.0;
			
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

		lowpassChase = pow(A,2);
		highpassChase = pow(B,2);
		wetChase = C;
		//should not scale with sample rate, because values reaching 1 are important
		//to its ability to bypass when set to max
		double lowpassSpeed = 300 / (fabs( lastLowpass - lowpassChase)+1.0);
		double highpassSpeed = 300 / (fabs( lastHighpass - highpassChase)+1.0);
		double wetSpeed = 300 / (fabs( lastWet - wetChase)+1.0);
		lastLowpass = lowpassChase;
		lastHighpass = highpassChase;
		lastWet = wetChase;
		
		double invLowpass;
		double invHighpass;
		double dry;
		
		
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
	
			lowpassAmount = (((lowpassAmount*lowpassSpeed)+lowpassChase)/(lowpassSpeed + 1.0)); invLowpass = 1.0 - lowpassAmount;
			highpassAmount = (((highpassAmount*highpassSpeed)+highpassChase)/(highpassSpeed + 1.0)); invHighpass = 1.0 - highpassAmount;
			wet = (((wet*wetSpeed)+wetChase)/(wetSpeed+1.0)); dry = 1.0 - wet;
			
			count++; if (count > 5) count = 0; switch (count)
			{
				case 0:
					iirHighpassAL = (iirHighpassAL * invHighpass) + (inputSampleL * highpassAmount); inputSampleL -= iirHighpassAL;
					iirLowpassAL = (iirLowpassAL * invLowpass) + (inputSampleL * lowpassAmount); inputSampleL = iirLowpassAL;
					iirHighpassBL = (iirHighpassBL * invHighpass) + (inputSampleL * highpassAmount); inputSampleL -= iirHighpassBL;
					iirLowpassBL = (iirLowpassBL * invLowpass) + (inputSampleL * lowpassAmount); inputSampleL = iirLowpassBL;
					iirHighpassDL = (iirHighpassDL * invHighpass) + (inputSampleL * highpassAmount); inputSampleL -= iirHighpassDL;
					iirLowpassDL = (iirLowpassDL * invLowpass) + (inputSampleL * lowpassAmount); inputSampleL = iirLowpassDL;
					iirHighpassAR = (iirHighpassAR * invHighpass) + (inputSampleR * highpassAmount); inputSampleR -= iirHighpassAR;
					iirLowpassAR = (iirLowpassAR * invLowpass) + (inputSampleR * lowpassAmount); inputSampleR = iirLowpassAR;
					iirHighpassBR = (iirHighpassBR * invHighpass) + (inputSampleR * highpassAmount); inputSampleR -= iirHighpassBR;
					iirLowpassBR = (iirLowpassBR * invLowpass) + (inputSampleR * lowpassAmount); inputSampleR = iirLowpassBR;
					iirHighpassDR = (iirHighpassDR * invHighpass) + (inputSampleR * highpassAmount); inputSampleR -= iirHighpassDR;
					iirLowpassDR = (iirLowpassDR * invLowpass) + (inputSampleR * lowpassAmount); inputSampleR = iirLowpassDR;
					break;
				case 1:
					iirHighpassAL = (iirHighpassAL * invHighpass) + (inputSampleL * highpassAmount); inputSampleL -= iirHighpassAL;
					iirLowpassAL = (iirLowpassAL * invLowpass) + (inputSampleL * lowpassAmount); inputSampleL = iirLowpassAL;
					iirHighpassCL = (iirHighpassCL * invHighpass) + (inputSampleL * highpassAmount); inputSampleL -= iirHighpassCL;
					iirLowpassCL = (iirLowpassCL * invLowpass) + (inputSampleL * lowpassAmount); inputSampleL = iirLowpassCL;
					iirHighpassEL = (iirHighpassEL * invHighpass) + (inputSampleL * highpassAmount); inputSampleL -= iirHighpassEL;
					iirLowpassEL = (iirLowpassEL * invLowpass) + (inputSampleL * lowpassAmount); inputSampleL = iirLowpassEL;
					iirHighpassAR = (iirHighpassAR * invHighpass) + (inputSampleR * highpassAmount); inputSampleR -= iirHighpassAR;
					iirLowpassAR = (iirLowpassAR * invLowpass) + (inputSampleR * lowpassAmount); inputSampleR = iirLowpassAR;
					iirHighpassCR = (iirHighpassCR * invHighpass) + (inputSampleR * highpassAmount); inputSampleR -= iirHighpassCR;
					iirLowpassCR = (iirLowpassCR * invLowpass) + (inputSampleR * lowpassAmount); inputSampleR = iirLowpassCR;
					iirHighpassER = (iirHighpassER * invHighpass) + (inputSampleR * highpassAmount); inputSampleR -= iirHighpassER;
					iirLowpassER = (iirLowpassER * invLowpass) + (inputSampleR * lowpassAmount); inputSampleR = iirLowpassER;
					break;
				case 2:
					iirHighpassAL = (iirHighpassAL * invHighpass) + (inputSampleL * highpassAmount); inputSampleL -= iirHighpassAL;
					iirLowpassAL = (iirLowpassAL * invLowpass) + (inputSampleL * lowpassAmount); inputSampleL = iirLowpassAL;
					iirHighpassBL = (iirHighpassBL * invHighpass) + (inputSampleL * highpassAmount); inputSampleL -= iirHighpassBL;
					iirLowpassBL = (iirLowpassBL * invLowpass) + (inputSampleL * lowpassAmount); inputSampleL = iirLowpassBL;
					iirHighpassFL = (iirHighpassFL * invHighpass) + (inputSampleL * highpassAmount); inputSampleL -= iirHighpassFL;
					iirLowpassFL = (iirLowpassFL * invLowpass) + (inputSampleL * lowpassAmount); inputSampleL = iirLowpassFL;
					iirHighpassAR = (iirHighpassAR * invHighpass) + (inputSampleR * highpassAmount); inputSampleR -= iirHighpassAR;
					iirLowpassAR = (iirLowpassAR * invLowpass) + (inputSampleR * lowpassAmount); inputSampleR = iirLowpassAR;
					iirHighpassBR = (iirHighpassBR * invHighpass) + (inputSampleR * highpassAmount); inputSampleR -= iirHighpassBR;
					iirLowpassBR = (iirLowpassBR * invLowpass) + (inputSampleR * lowpassAmount); inputSampleR = iirLowpassBR;
					iirHighpassFR = (iirHighpassFR * invHighpass) + (inputSampleR * highpassAmount); inputSampleR -= iirHighpassFR;
					iirLowpassFR = (iirLowpassFR * invLowpass) + (inputSampleR * lowpassAmount); inputSampleR = iirLowpassFR;
					break;
				case 3:
					iirHighpassAL = (iirHighpassAL * invHighpass) + (inputSampleL * highpassAmount); inputSampleL -= iirHighpassAL;
					iirLowpassAL = (iirLowpassAL * invLowpass) + (inputSampleL * lowpassAmount); inputSampleL = iirLowpassAL;
					iirHighpassCL = (iirHighpassCL * invHighpass) + (inputSampleL * highpassAmount); inputSampleL -= iirHighpassCL;
					iirLowpassCL = (iirLowpassCL * invLowpass) + (inputSampleL * lowpassAmount); inputSampleL = iirLowpassCL;
					iirHighpassDL = (iirHighpassDL * invHighpass) + (inputSampleL * highpassAmount); inputSampleL -= iirHighpassDL;
					iirLowpassDL = (iirLowpassDL * invLowpass) + (inputSampleL * lowpassAmount); inputSampleL = iirLowpassDL;
					iirHighpassAR = (iirHighpassAR * invHighpass) + (inputSampleR * highpassAmount); inputSampleR -= iirHighpassAR;
					iirLowpassAR = (iirLowpassAR * invLowpass) + (inputSampleR * lowpassAmount); inputSampleR = iirLowpassAR;
					iirHighpassCR = (iirHighpassCR * invHighpass) + (inputSampleR * highpassAmount); inputSampleR -= iirHighpassCR;
					iirLowpassCR = (iirLowpassCR * invLowpass) + (inputSampleR * lowpassAmount); inputSampleR = iirLowpassCR;
					iirHighpassDR = (iirHighpassDR * invHighpass) + (inputSampleR * highpassAmount); inputSampleR -= iirHighpassDR;
					iirLowpassDR = (iirLowpassDR * invLowpass) + (inputSampleR * lowpassAmount); inputSampleR = iirLowpassDR;
					break;
				case 4:
					iirHighpassAL = (iirHighpassAL * invHighpass) + (inputSampleL * highpassAmount); inputSampleL -= iirHighpassAL;
					iirLowpassAL = (iirLowpassAL * invLowpass) + (inputSampleL * lowpassAmount); inputSampleL = iirLowpassAL;
					iirHighpassBL = (iirHighpassBL * invHighpass) + (inputSampleL * highpassAmount); inputSampleL -= iirHighpassBL;
					iirLowpassBL = (iirLowpassBL * invLowpass) + (inputSampleL * lowpassAmount); inputSampleL = iirLowpassBL;
					iirHighpassEL = (iirHighpassEL * invHighpass) + (inputSampleL * highpassAmount); inputSampleL -= iirHighpassEL;
					iirLowpassEL = (iirLowpassEL * invLowpass) + (inputSampleL * lowpassAmount); inputSampleL = iirLowpassEL;
					iirHighpassAR = (iirHighpassAR * invHighpass) + (inputSampleR * highpassAmount); inputSampleR -= iirHighpassAR;
					iirLowpassAR = (iirLowpassAR * invLowpass) + (inputSampleR * lowpassAmount); inputSampleR = iirLowpassAR;
					iirHighpassBR = (iirHighpassBR * invHighpass) + (inputSampleR * highpassAmount); inputSampleR -= iirHighpassBR;
					iirLowpassBR = (iirLowpassBR * invLowpass) + (inputSampleR * lowpassAmount); inputSampleR = iirLowpassBR;
					iirHighpassER = (iirHighpassER * invHighpass) + (inputSampleR * highpassAmount); inputSampleR -= iirHighpassER;
					iirLowpassER = (iirLowpassER * invLowpass) + (inputSampleR * lowpassAmount); inputSampleR = iirLowpassER;
					break;
				case 5:
					iirHighpassAL = (iirHighpassAL * invHighpass) + (inputSampleL * highpassAmount); inputSampleL -= iirHighpassAL;
					iirLowpassAL = (iirLowpassAL * invLowpass) + (inputSampleL * lowpassAmount); inputSampleL = iirLowpassAL;
					iirHighpassCL = (iirHighpassCL * invHighpass) + (inputSampleL * highpassAmount); inputSampleL -= iirHighpassCL;
					iirLowpassCL = (iirLowpassCL * invLowpass) + (inputSampleL * lowpassAmount); inputSampleL = iirLowpassCL;
					iirHighpassFL = (iirHighpassFL * invHighpass) + (inputSampleL * highpassAmount); inputSampleL -= iirHighpassFL;
					iirLowpassFL = (iirLowpassFL * invLowpass) + (inputSampleL * lowpassAmount); inputSampleL = iirLowpassFL;
					iirHighpassAR = (iirHighpassAR * invHighpass) + (inputSampleR * highpassAmount); inputSampleR -= iirHighpassAR;
					iirLowpassAR = (iirLowpassAR * invLowpass) + (inputSampleR * lowpassAmount); inputSampleR = iirLowpassAR;
					iirHighpassCR = (iirHighpassCR * invHighpass) + (inputSampleR * highpassAmount); inputSampleR -= iirHighpassCR;
					iirLowpassCR = (iirLowpassCR * invLowpass) + (inputSampleR * lowpassAmount); inputSampleR = iirLowpassCR;
					iirHighpassFR = (iirHighpassFR * invHighpass) + (inputSampleR * highpassAmount); inputSampleR -= iirHighpassFR;
					iirLowpassFR = (iirLowpassFR * invLowpass) + (inputSampleR * lowpassAmount); inputSampleR = iirLowpassFR;
					break;
			}
			//Highpass Filter chunk. This is three poles of IIR highpass, with a 'gearbox' that progressively
			//steepens the filter after minimizing artifacts.
			
			inputSampleL = (drySampleL * dry) + (inputSampleL * wet);
			inputSampleR = (drySampleR * dry) + (inputSampleR * wet);
			
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
    
	double iirHighpassAL;
	double iirHighpassBL;
	double iirHighpassCL;
	double iirHighpassDL;
	double iirHighpassEL;
	double iirHighpassFL;
	double iirLowpassAL;
	double iirLowpassBL;
	double iirLowpassCL;
	double iirLowpassDL;
	double iirLowpassEL;
	double iirLowpassFL;

	double iirHighpassAR;
	double iirHighpassBR;
	double iirHighpassCR;
	double iirHighpassDR;
	double iirHighpassER;
	double iirHighpassFR;
	double iirLowpassAR;
	double iirLowpassBR;
	double iirLowpassCR;
	double iirLowpassDR;
	double iirLowpassER;
	double iirLowpassFR;

	int count;
	
	double lowpassChase;
	double highpassChase;
	double wetChase;
	
	double lowpassAmount;
	double highpassAmount;
	double wet;
	
	double lastLowpass;
	double lastHighpass;
	double lastWet;

	long double fpNShapeL;
	long double fpNShapeR;
	//default stuff

};
MIN_EXTERNAL(capacitor);

