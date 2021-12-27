#include "c74_min.h"

using namespace c74::min;

class slew3 : public object<slew3>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a new approach to slew clipping meant for a more analog-like darkening effect"};
	MIN_TAGS {"clipper, analog"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "clamping", 0.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.0;
			lastSampleAL = lastSampleBL = lastSampleCL = 0.0;
			lastSampleAR = lastSampleBR = lastSampleCR = 0.0;
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

		double overallscale = 1.0;
		overallscale /= 44100.0;
		overallscale *= samplerate();
		
		double threshold = pow((1-A),4)/overallscale;
	    
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpd * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpd * 1.18e-43;
			
			//begin L
			double clamp = (lastSampleBL - lastSampleCL) * 0.381966011250105;
			clamp -= (lastSampleAL - lastSampleBL) * 0.6180339887498948482045;
			clamp += inputSampleL - lastSampleAL; //regular slew clamping added
			
			lastSampleCL = lastSampleBL;
			lastSampleBL = lastSampleAL;
			lastSampleAL = inputSampleL; //now our output relates off lastSampleB
			
			if (clamp > threshold)
				inputSampleL = lastSampleBL + threshold;
			if (-clamp > threshold)
				inputSampleL = lastSampleBL - threshold;
			
			lastSampleAL = (lastSampleAL*0.381966011250105)+(inputSampleL*0.6180339887498948482045); //split the difference between raw and smoothed for buffer
			//end L
			
			//begin R
			clamp = (lastSampleBR - lastSampleCR) * 0.381966011250105;
			clamp -= (lastSampleAR - lastSampleBR) * 0.6180339887498948482045;
			clamp += inputSampleR - lastSampleAR; //regular slew clamping added
			
			lastSampleCR = lastSampleBR;
			lastSampleBR = lastSampleAR;
			lastSampleAR = inputSampleR; //now our output relates off lastSampleB
			
			if (clamp > threshold)
				inputSampleR = lastSampleBR + threshold;
			if (-clamp > threshold)
				inputSampleR = lastSampleBR - threshold;
			
			lastSampleAR = (lastSampleAR*0.381966011250105)+(inputSampleR*0.6180339887498948482045); //split the difference between raw and smoothed for buffer
			//end R
			
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
	double lastSampleAL;
	double lastSampleBL;
	double lastSampleCL;
	double lastSampleAR;
	double lastSampleBR;
	double lastSampleCR;
	//default stuff

};
MIN_EXTERNAL(slew3);

