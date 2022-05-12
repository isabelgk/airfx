#include "c74_min.h"

using namespace c74::min;

class dark : public object<dark>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a wordlength reducer that gives your music a blacker backdrop"};
	MIN_TAGS {""};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "quant", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "derez", 0.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			fpd = 17;
			for(int count = 0; count < 99; count++) {
				lastSampleL[count] = 0;
				lastSampleR[count] = 0;
			}
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
		int depth = (int)(17.0*overallscale);
		if (depth < 3) depth = 3;
		if (depth > 98) depth = 98;
		
		int processing = (uint32_t)( A * 1.999 );
		bool highres = false;
		if (processing == 1) highres = true;
		float scaleFactor;
		if (highres) scaleFactor = 8388608.0;
		else scaleFactor = 32768.0;
		float derez = B;
		if (derez > 0.0) scaleFactor *= pow(1.0-derez,6);
		if (scaleFactor < 0.0001) scaleFactor = 0.0001;
		float outScale = scaleFactor;
		if (outScale < 8.0) outScale = 8.0;
		
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpd * 1.18e-43;
			fpd ^= fpd << 13; fpd ^= fpd >> 17; fpd ^= fpd << 5;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpd * 1.18e-43;
			fpd ^= fpd << 13; fpd ^= fpd >> 17; fpd ^= fpd << 5;
			
			inputSampleL *= scaleFactor;
			inputSampleR *= scaleFactor;
			//0-1 is now one bit, now we dither
	
			//We are doing it first Left, then Right, because the loops may run faster if
			//they aren't too jammed full of variables. This means re-running code.
			
			//begin left
			int quantA = floor(inputSampleL);
			int quantB = floor(inputSampleL+1.0);
			//to do this style of dither, we quantize in either direction and then
			//do a reconstruction of what the result will be for each choice.
			//We then evaluate which one we like, and keep a history of what we previously had
			
			float expectedSlew = 0;
			for(int x = 0; x < depth; x++) {
				expectedSlew += (lastSampleL[x+1] - lastSampleL[x]);
			}
			expectedSlew /= depth; //we have an average of all recent slews
			//we are doing that to voice the thing down into the upper mids a bit
			//it mustn't just soften the brightest treble, it must smooth high mids too
			
			float testA = fabs((lastSampleL[0] - quantA) - expectedSlew);
			float testB = fabs((lastSampleL[0] - quantB) - expectedSlew);
			
			if (testA < testB) inputSampleL = quantA;
			else inputSampleL = quantB;
			//select whichever one departs LEAST from the vector of averaged
			//reconstructed previous final samples. This will force a kind of dithering
			//as it'll make the output end up as smooth as possible
			
			for(int x = depth; x >=0; x--) {
				lastSampleL[x+1] = lastSampleL[x];
			}
			lastSampleL[0] = inputSampleL;
			//end left
			
			//begin right
			quantA = floor(inputSampleR);
			quantB = floor(inputSampleR+1.0);
			//to do this style of dither, we quantize in either direction and then
			//do a reconstruction of what the result will be for each choice.
			//We then evaluate which one we like, and keep a history of what we previously had
			
			expectedSlew = 0;
			for(int x = 0; x < depth; x++) {
				expectedSlew += (lastSampleR[x+1] - lastSampleR[x]);
			}
			expectedSlew /= depth; //we have an average of all recent slews
			//we are doing that to voice the thing down into the upper mids a bit
			//it mustn't just soften the brightest treble, it must smooth high mids too
			
			testA = fabs((lastSampleR[0] - quantA) - expectedSlew);
			testB = fabs((lastSampleR[0] - quantB) - expectedSlew);
			
			if (testA < testB) inputSampleR = quantA;
			else inputSampleR = quantB;
			//select whichever one departs LEAST from the vector of averaged
			//reconstructed previous final samples. This will force a kind of dithering
			//as it'll make the output end up as smooth as possible
			
			for(int x = depth; x >=0; x--) {
				lastSampleR[x+1] = lastSampleR[x];
			}
			lastSampleR[0] = inputSampleR;
			//end right
			
			inputSampleL /= outScale;
			inputSampleR /= outScale;
			
			*out1 = inputSampleL;
			*out2 = inputSampleR;
	
			*in1++;
			*in2++;
			*out1++;
			*out2++;
		}
	}
private:
    
	float lastSampleL[100];
	float lastSampleR[100];
	uint32_t fpd;
	//default stuff

};
MIN_EXTERNAL(dark);

