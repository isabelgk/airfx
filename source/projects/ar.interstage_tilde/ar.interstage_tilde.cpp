#include "c74_min.h"

using namespace c74::min;

class interstage : public object<interstage>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a subtle and sophisticated analogifier"};
	MIN_TAGS {"analog"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};


	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			iirSampleAL = 0.0;
			iirSampleBL = 0.0;
			iirSampleCL = 0.0;
			iirSampleDL = 0.0;
			iirSampleEL = 0.0;
			iirSampleFL = 0.0;
			lastSampleL = 0.0;
			iirSampleAR = 0.0;
			iirSampleBR = 0.0;
			iirSampleCR = 0.0;
			iirSampleDR = 0.0;
			iirSampleER = 0.0;
			iirSampleFR = 0.0;
			lastSampleR = 0.0;
			fpd = 17;
			flip = true;
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
		
		double firstStage = 0.381966011250105 / overallscale;
		double iirAmount = 0.00295 / overallscale;
		double threshold = 0.381966011250105;
		
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpd * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpd * 1.18e-43;
			long double drySampleL = inputSampleL;
			long double drySampleR = inputSampleR;
	
			inputSampleL = (inputSampleL+lastSampleL)*0.5;
			inputSampleR = (inputSampleR+lastSampleR)*0.5; //start the lowpassing with an average
			
			if (flip) {
				iirSampleAL = (iirSampleAL * (1 - firstStage)) + (inputSampleL * firstStage); inputSampleL = iirSampleAL;
				iirSampleCL = (iirSampleCL * (1 - iirAmount)) + (inputSampleL * iirAmount); inputSampleL = iirSampleCL;
				iirSampleEL = (iirSampleEL * (1 - iirAmount)) + (inputSampleL * iirAmount); inputSampleL = iirSampleEL;
				inputSampleL = drySampleL - inputSampleL;
				//make highpass
				if (inputSampleL - iirSampleAL > threshold) inputSampleL = iirSampleAL + threshold;
				if (inputSampleL - iirSampleAL < -threshold) inputSampleL = iirSampleAL - threshold;
				//slew limit against lowpassed reference point
				
				iirSampleAR = (iirSampleAR * (1 - firstStage)) + (inputSampleR * firstStage); inputSampleR = iirSampleAR;
				iirSampleCR = (iirSampleCR * (1 - iirAmount)) + (inputSampleR * iirAmount); inputSampleR = iirSampleCR;
				iirSampleER = (iirSampleER * (1 - iirAmount)) + (inputSampleR * iirAmount); inputSampleR = iirSampleER;
				inputSampleR = drySampleR - inputSampleR;
				//make highpass
				if (inputSampleR - iirSampleAR > threshold) inputSampleR = iirSampleAR + threshold;
				if (inputSampleR - iirSampleAR < -threshold) inputSampleR = iirSampleAR - threshold;
				//slew limit against lowpassed reference point
			} else {
				iirSampleBL = (iirSampleBL * (1 - firstStage)) + (inputSampleL * firstStage); inputSampleL = iirSampleBL;
				iirSampleDL = (iirSampleDL * (1 - iirAmount)) + (inputSampleL * iirAmount); inputSampleL = iirSampleDL;
				iirSampleFL = (iirSampleFL * (1 - iirAmount)) + (inputSampleL * iirAmount); inputSampleL = iirSampleFL;
				inputSampleL = drySampleL - inputSampleL;
				//make highpass
				if (inputSampleL - iirSampleBL > threshold) inputSampleL = iirSampleBL + threshold;
				if (inputSampleL - iirSampleBL < -threshold) inputSampleL = iirSampleBL - threshold;
				//slew limit against lowpassed reference point
				
				iirSampleBR = (iirSampleBR * (1 - firstStage)) + (inputSampleR * firstStage); inputSampleR = iirSampleBR;
				iirSampleDR = (iirSampleDR * (1 - iirAmount)) + (inputSampleR * iirAmount); inputSampleR = iirSampleDR;
				iirSampleFR = (iirSampleFR * (1 - iirAmount)) + (inputSampleR * iirAmount); inputSampleR = iirSampleFR;
				inputSampleR = drySampleR - inputSampleR;
				//make highpass
				if (inputSampleR - iirSampleBR > threshold) inputSampleR = iirSampleBR + threshold;
				if (inputSampleR - iirSampleBR < -threshold) inputSampleR = iirSampleBR - threshold;
				//slew limit against lowpassed reference point
			}
			flip = !flip;
			lastSampleL = inputSampleL;
			lastSampleR = inputSampleR;
			
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
    
	double iirSampleAL;
	double iirSampleBL;
	double iirSampleCL;
	double iirSampleDL;
	double iirSampleEL;
	double iirSampleFL;
	long double lastSampleL;
	double iirSampleAR;
	double iirSampleBR;
	double iirSampleCR;
	double iirSampleDR;
	double iirSampleER;
	double iirSampleFR;
	long double lastSampleR;
	uint32_t fpd;
	bool flip;
};

MIN_EXTERNAL(interstage);

