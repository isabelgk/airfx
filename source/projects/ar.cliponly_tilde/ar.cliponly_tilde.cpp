#include "c74_min.h"

using namespace c74::min;

class cliponly : public object<cliponly>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a clipper that suppresses the brightness of digital clipping without affecting unclipped samples"};
	MIN_TAGS {"audio, effect, clipper"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};


	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			lastSampleL = 0.0;
			wasPosClipL = false;
			wasNegClipL = false;
		
			lastSampleR = 0.0;
			wasPosClipR = false;
			wasNegClipR = false;
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

		double hardness = 0.7390851332151606; // x == cos(x)
		double softness = 1.0 - hardness;
		double refclip = 0.9549925859; // -0.2dB
		
		double inputSampleL;
		double inputSampleR;
	
	    while (--sampleFrames >= 0)
	    {
			inputSampleL = *in1;
			inputSampleR = *in2;
	
			if (inputSampleL > 4.0) inputSampleL = 4.0;
			if (inputSampleL < -4.0) inputSampleL = -4.0;
			if (inputSampleR > 4.0) inputSampleR = 4.0;
			if (inputSampleR < -4.0) inputSampleR = -4.0;
			
			if (wasPosClipL == true) { //current will be over
				if (inputSampleL < lastSampleL) { //next one will NOT be over
					lastSampleL = ((refclip*hardness) + (inputSampleL * softness));
				}
				else { //still clipping, still chasing the target
					lastSampleL = ((lastSampleL*hardness) + (refclip * softness));
				}
			}
			wasPosClipL = false;
			if (inputSampleL > refclip) { //next will be over the true clip level. otherwise we directly use it
				wasPosClipL = true; //set the clip flag
				inputSampleL = ((refclip*hardness) + (lastSampleL * softness));
			}
			
			if (wasNegClipL == true) { //current will be -over
				if (inputSampleL > lastSampleL) { //next one will NOT be -over
					lastSampleL = ((-refclip*hardness) + (inputSampleL * softness));
				}
				else { //still clipping, still chasing the target
					lastSampleL = ((lastSampleL*hardness) + (-refclip * softness));
				}
			}
			wasNegClipL = false;
			if (inputSampleL < -refclip) { //next will be -refclip.  otherwise we directly use it
				wasNegClipL = true; //set the clip flag
				inputSampleL = ((-refclip*hardness) + (lastSampleL * softness));
			}
			
			if (wasPosClipR == true) { //current will be over
				if (inputSampleR < lastSampleR) { //next one will NOT be over
					lastSampleR = ((refclip*hardness) + (inputSampleR * softness));
				}
				else { //still clipping, still chasing the target
					lastSampleR = ((lastSampleR*hardness) + (refclip * softness));
				}
			}
			wasPosClipR = false;
			if (inputSampleR > refclip) { //next will be over the true clip level. otherwise we directly use it
				wasPosClipR = true; //set the clip flag
				inputSampleR = ((refclip*hardness) + (lastSampleR * softness));
			}
			
			if (wasNegClipR == true) { //current will be -over
				if (inputSampleR > lastSampleR) { //next one will NOT be -over
					lastSampleR = ((-refclip*hardness) + (inputSampleR * softness));
				}
				else { //still clipping, still chasing the target
					lastSampleR = ((lastSampleR*hardness) + (-refclip * softness));
				}
			}
			wasNegClipR = false;
			if (inputSampleR < -refclip) { //next will be -refclip.  otherwise we directly use it
				wasNegClipR = true; //set the clip flag
				inputSampleR = ((-refclip*hardness) + (lastSampleR * softness));
			}
			
			*out1 = lastSampleL;
			*out2 = lastSampleR;
			lastSampleL = inputSampleL;
			lastSampleR = inputSampleR;
			
			*in1++;
			*in2++;
			*out1++;
			*out2++;
		}
	}
private:
    
	double lastSampleL;
	bool wasPosClipL;
	bool wasNegClipL;

	double lastSampleR;
	bool wasPosClipR;
	bool wasNegClipR;

};

MIN_EXTERNAL(cliponly);

