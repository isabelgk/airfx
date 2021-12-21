#include "c74_min.h"

using namespace c74::min;

class powersag2 : public object<powersag2>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"emulating power supply limitations in analog modeling, version 2"};
	MIN_TAGS {"analog"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "range", 0.3, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "mix", 0.5, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.3;
			B = 0.5;
		
			for(int count = 0; count < 16385; count++) {dL[count] = 0; dR[count] = 0;}
			controlL = 0;
			controlR = 0;
			gcount = 0;	
			
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

		double depth = pow(A,4);
		int offset = (int)(depth * 16383) + 1;	
		double wet = (B*2.0)-1.0;
		
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpd * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpd * 1.18e-43;
			long double drySampleL = inputSampleL;
			long double drySampleR = inputSampleR;
			
			if (gcount < 0 || gcount > 16384) {gcount = 16384;}		
			dL[gcount] = fabs(inputSampleL);
			dR[gcount] = fabs(inputSampleR);
			controlL += dL[gcount];
			controlR += dR[gcount];
			controlL -= dL[gcount+offset-((gcount+offset > 16384)?16384:0)];
			controlR -= dR[gcount+offset-((gcount+offset > 16384)?16384:0)];
			gcount--;
			
			if (controlL > offset) controlL = offset; if (controlL < 0.0) controlL = 0.0;				
			if (controlR > offset) controlR = offset; if (controlR < 0.0) controlR = 0.0;				
			
			double burst = inputSampleL * (controlL / sqrt(offset));
			double clamp = inputSampleL / ((burst == 0.0)?1.0:burst);
			
			if (clamp > 1.0) clamp = 1.0; if (clamp < 0.0) clamp = 0.0;
			inputSampleL *= clamp;
			double difference = drySampleL - inputSampleL;
			if (wet < 0.0) drySampleL *= (wet+1.0);
			inputSampleL = drySampleL - (difference * wet);
			
			burst = inputSampleR * (controlR / sqrt(offset));
			clamp = inputSampleR / ((burst == 0.0)?1.0:burst);
			
			if (clamp > 1.0) clamp = 1.0; if (clamp < 0.0) clamp = 0.0;
			inputSampleR *= clamp;
			difference = drySampleR - inputSampleR;
			if (wet < 0.0) drySampleR *= (wet+1.0);
			inputSampleR = drySampleR - (difference * wet);
			
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
    
	double dL[16386];
	double dR[16386];
	double controlL;
	double controlR;
	int gcount;		
	
	uint32_t fpd;
	//default stuff

};
MIN_EXTERNAL(powersag2);

