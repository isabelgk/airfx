#include "c74_min.h"

using namespace c74::min;

class mojo : public object<mojo>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a biggenator that also works as a loudenator"};
	MIN_TAGS {"dynamics"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "input", 0.5, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
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
		double overallscale = 1.0;
		overallscale /= 44100.0;
		overallscale *= samplerate();

		long sampleFrames = _input.frame_count();

		double gain = pow(10.0,((A*24.0)-12.0)/20.0);
	
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpd * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpd * 1.18e-43;
			
			if (gain != 1.0) {
				inputSampleL *= gain;
				inputSampleR *= gain;
			}		
			
			long double mojo = pow(fabs(inputSampleL),0.25);
			if (mojo > 0.0) inputSampleL = (sin(inputSampleL * mojo * M_PI * 0.5) / mojo) * 0.987654321;
			//mojo is the one that flattens WAAAAY out very softly before wavefolding
			mojo = pow(fabs(inputSampleR),0.25);
			if (mojo > 0.0) inputSampleR = (sin(inputSampleR * mojo * M_PI * 0.5) / mojo) * 0.987654321;
			//mojo is the one that flattens WAAAAY out very softly before wavefolding
					
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

};
MIN_EXTERNAL(mojo);

