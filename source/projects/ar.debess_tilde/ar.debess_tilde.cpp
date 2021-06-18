#include "c74_min.h"

using namespace c74::min;

class debess : public object<debess>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"an improved de-esser"};
	MIN_TAGS {"audio, effect"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "Intense", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "Sharp", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "Depth", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "Filter", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> E {this, "Sense", 0.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.0;
			B = 0.5;
			C = 0.5;
			D = 0.5;
			E = 0.0;
			for (int x = 0; x < 41; x++) {
				sL[x] = 0.0; mL[x] = 0.0; cL[x] = 0.0;
				sR[x] = 0.0; mR[x] = 0.0; cR[x] = 0.0;
			}
			ratioAL = ratioBL = 1.0;
			iirSampleAL = 0.0;
			iirSampleBL = 0.0;
			ratioAR = ratioBR = 1.0;
			iirSampleAR = 0.0;
			iirSampleBR = 0.0;
			
			flip = false;	
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
		
		double intensity = pow(A,5)*(8192/overallscale);
		double sharpness = B*40.0;
		if (sharpness < 2) sharpness = 2;
		double speed = 0.1 / sharpness;
		double depth = 1.0 / (C+0.0001);
		double iirAmount = D;
		float monitoring = E;
		
		while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpd * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpd * 1.18e-43;
			
			sL[0] = inputSampleL; //set up so both [0] and [1] will be input sample
			sR[0] = inputSampleR; //set up so both [0] and [1] will be input sample
			//we only use the [1] so this is just where samples come in
			for (int x = sharpness; x > 0; x--) {
				sL[x] = sL[x-1];
				sR[x] = sR[x-1];
			} //building up a set of slews
			
			mL[1] = (sL[1]-sL[2])*((sL[1]-sL[2])/1.3);
			mR[1] = (sR[1]-sR[2])*((sR[1]-sR[2])/1.3);
			for (int x = sharpness-1; x > 1; x--) {
				mL[x] = (sL[x]-sL[x+1])*((sL[x-1]-sL[x])/1.3);
				mR[x] = (sR[x]-sR[x+1])*((sR[x-1]-sR[x])/1.3);
			} //building up a set of slews of slews
			
			double senseL = fabs(mL[1] - mL[2]) * sharpness * sharpness;
			double senseR = fabs(mR[1] - mR[2]) * sharpness * sharpness;
			for (int x = sharpness-1; x > 0; x--) {
				double multL = fabs(mL[x] - mL[x+1]) * sharpness * sharpness;
				if (multL < 1.0) senseL *= multL;
				double multR = fabs(mR[x] - mR[x+1]) * sharpness * sharpness;
				if (multR < 1.0) senseR *= multR;
			} //sense is slews of slews times each other
			
			senseL = 1.0+(intensity*intensity*senseL);
			if (senseL > intensity) {senseL = intensity;}
			senseR= 1.0+(intensity*intensity*senseR);
			if (senseR > intensity) {senseR = intensity;}
			
			if (flip) {
				iirSampleAL = (iirSampleAL * (1 - iirAmount)) + (inputSampleL * iirAmount);
				iirSampleAR = (iirSampleAR * (1 - iirAmount)) + (inputSampleR * iirAmount);
				ratioAL = (ratioAL * (1.0-speed))+(senseL * speed);
				ratioAR = (ratioAR * (1.0-speed))+(senseR * speed);
				if (ratioAL > depth) ratioAL = depth;
				if (ratioAR > depth) ratioAR = depth;
				if (ratioAL > 1.0) inputSampleL = iirSampleAL+((inputSampleL-iirSampleAL)/ratioAL);
				if (ratioAR > 1.0) inputSampleR = iirSampleAR+((inputSampleR-iirSampleAR)/ratioAR);
			}
			else {
				iirSampleBL = (iirSampleBL * (1 - iirAmount)) + (inputSampleL * iirAmount);	
				iirSampleBR = (iirSampleBR * (1 - iirAmount)) + (inputSampleR * iirAmount);	
				ratioBL = (ratioBL * (1.0-speed))+(senseL * speed);			
				ratioBR = (ratioBR * (1.0-speed))+(senseR * speed);			
				if (ratioBL > depth) ratioBL = depth;
				if (ratioBR > depth) ratioBR = depth;
				if (ratioAL > 1.0) inputSampleL = iirSampleBL+((inputSampleL-iirSampleBL)/ratioBL);
				if (ratioAR > 1.0) inputSampleR = iirSampleBR+((inputSampleR-iirSampleBR)/ratioBR);
			}
			flip = !flip;
			
			if (monitoring > 0.49999) {
				inputSampleL = *in1 - inputSampleL;
				inputSampleR = *in2 - inputSampleR;
			}
			//sense monitoring
			
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
    
	long double sL[41], mL[41], cL[41];		
	double ratioAL;
	double ratioBL;
	double iirSampleAL;
	double iirSampleBL;
	
	long double sR[41], mR[41], cR[41];		
	double ratioAR;
	double ratioBR;
	double iirSampleAR;
	double iirSampleBR;
	
	
	bool flip;	
	uint32_t fpd;
	//default stuff

};
MIN_EXTERNAL(debess);

