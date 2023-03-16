#include "c74_min.h"

using namespace c74::min;

class cliponly2 : public object<cliponly2>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"ClipOnly2 suppresses the brightness of digital clipping without affecting unclipped samples, at any sample rate."};
	MIN_TAGS {"clipper"};
	MIN_AUTHOR {"Christopher Herb"};

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
		for (int x = 0; x < 16; x++) {intermediateL[x] = 0.0; intermediateR[x] = 0.0;}
		//fpdL = 1.0; while (fpdL < 16386) fpdL = rand()*UINT32_MAX;
		//fpdR = 1.0; while (fpdR < 16386) fpdR = rand()*UINT32_MAX; //leave off for ClipOnly
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
		
		int spacing = floor(overallscale); //should give us working basic scaling, usually 2 or 4
		if (spacing < 1) spacing = 1; if (spacing > 16) spacing = 16;
		//double hardness = 0.7390851332151606; // x == cos(x)
		//double softness = 0.260914866784839; // 1.0 - hardness
		//double refclip = 0.9549925859; // -0.2dB we're making all this pure raw code
		//refclip*hardness = 0.705820822569392  to use ClipOnly as a prefab code-chunk.
		//refclip*softness = 0.249171763330607	Seven decimal places is plenty as it's
		//not related to the original sound much: it's an arbitrary position in softening.
		//This is where the numbers come from, referencing the code of the original ClipOnly
		
		while (--sampleFrames >= 0)
		{
			double inputSampleL = *in1;
			double inputSampleR = *in2;
	//		if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpdL * 1.18e-43;
	//		if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpdR * 1.18e-43;
			//do NOT use on ClipOnly, it is almost always a pure bypass
			
			//begin ClipOnly2 stereo as a little, compressed chunk that can be dropped into code
			if (inputSampleL > 4.0) inputSampleL = 4.0; if (inputSampleL < -4.0) inputSampleL = -4.0;
			if (wasPosClipL == true) { //current will be over
				if (inputSampleL<lastSampleL) lastSampleL=0.7058208+(inputSampleL*0.2609148);
				else lastSampleL = 0.2491717+(lastSampleL*0.7390851);
			} wasPosClipL = false;
			if (inputSampleL>0.9549925859) {wasPosClipL=true;inputSampleL=0.7058208+(lastSampleL*0.2609148);}
			if (wasNegClipL == true) { //current will be -over
				if (inputSampleL > lastSampleL) lastSampleL=-0.7058208+(inputSampleL*0.2609148);
				else lastSampleL=-0.2491717+(lastSampleL*0.7390851);
			} wasNegClipL = false;
			if (inputSampleL<-0.9549925859) {wasNegClipL=true;inputSampleL=-0.7058208+(lastSampleL*0.2609148);}
			intermediateL[spacing] = inputSampleL;
			inputSampleL = lastSampleL; //Latency is however many samples equals one 44.1k sample
			for (int x = spacing; x > 0; x--) intermediateL[x-1] = intermediateL[x];
			lastSampleL = intermediateL[0]; //run a little buffer to handle this
			
			if (inputSampleR > 4.0) inputSampleR = 4.0; if (inputSampleR < -4.0) inputSampleR = -4.0;
			if (wasPosClipR == true) { //current will be over
				if (inputSampleR<lastSampleR) lastSampleR=0.7058208+(inputSampleR*0.2609148);
				else lastSampleR = 0.2491717+(lastSampleR*0.7390851);
			} wasPosClipR = false;
			if (inputSampleR>0.9549925859) {wasPosClipR=true;inputSampleR=0.7058208+(lastSampleR*0.2609148);}
			if (wasNegClipR == true) { //current will be -over
				if (inputSampleR > lastSampleR) lastSampleR=-0.7058208+(inputSampleR*0.2609148);
				else lastSampleR=-0.2491717+(lastSampleR*0.7390851);
			} wasNegClipR = false;
			if (inputSampleR<-0.9549925859) {wasNegClipR=true;inputSampleR=-0.7058208+(lastSampleR*0.2609148);}
			intermediateR[spacing] = inputSampleR;
			inputSampleR = lastSampleR; //Latency is however many samples equals one 44.1k sample
			for (int x = spacing; x > 0; x--) intermediateR[x-1] = intermediateR[x];
			lastSampleR = intermediateR[0]; //run a little buffer to handle this
			//end ClipOnly2 stereo as a little, compressed chunk that can be dropped into code
			
			//begin 64 bit stereo floating point dither
	//		int expon; frexp((double)inputSampleL, &expon);
	//		fpdL ^= fpdL << 13; fpdL ^= fpdL >> 17; fpdL ^= fpdL << 5;
	//		inputSampleL += ((double(fpdL)-uint32_t(0x7fffffff)) * 1.1e-44l * pow(2,expon+62));
	//		frexp((double)inputSampleR, &expon);
	//		fpdR ^= fpdR << 13; fpdR ^= fpdR >> 17; fpdR ^= fpdR << 5;
	//		inputSampleR += ((double(fpdR)-uint32_t(0x7fffffff)) * 1.1e-44l * pow(2,expon+62));
			//end 64 bit stereo floating point dither
			//do NOT use on ClipOnly, it is almost always a pure bypass
			
			*out1 = inputSampleL;
			*out2 = inputSampleR;

			in1++;
			in2++;
			out1++;
			out2++;
		}
	}
private:
	double lastSampleL;
	double intermediateL[16];
	bool wasPosClipL;
	bool wasNegClipL;
	double lastSampleR;
	double intermediateR[16];
	bool wasPosClipR;
	bool wasNegClipR; //Stereo ClipOnly2
};

MIN_EXTERNAL(cliponly2);

