#include "c74_min.h"

using namespace c74::min;

class slew : public object<slew>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a slew clipper which darkens treble in an unusual way"};
	MIN_TAGS {""};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};


	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			gain = 0.0;
			lastSampleL = 0.0;
			lastSampleR = 0.0;
		
		// TODO: uncomment canDo entries according to your plugin's capabilities
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
	
		double inputSampleL;
		double inputSampleR;    
		double outputSampleL;
		double outputSampleR;
	
		double clamp;
		double threshold = pow((1-gain),4)/overallscale;
	
	
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
	
			clamp = inputSampleL - lastSampleL;
			outputSampleL = inputSampleL;
			if (clamp > threshold)
				outputSampleL = lastSampleL + threshold;
			if (-clamp > threshold)
				outputSampleL = lastSampleL - threshold;
			lastSampleL = outputSampleL;
			
			clamp = inputSampleR - lastSampleR;
			outputSampleR = inputSampleR;
			if (clamp > threshold)
				outputSampleR = lastSampleR + threshold;
			if (-clamp > threshold)
				outputSampleR = lastSampleR - threshold;
			lastSampleR = outputSampleR;
			
			*out1 = outputSampleL;
			*out2 = outputSampleR;
	
			*in1++;
			*in2++;
			*out1++;
			*out2++;
		}
	}
private:
    
	float gain;
	double lastSampleL;
	double lastSampleR;
};

MIN_EXTERNAL(slew);

