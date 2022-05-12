#include "c74_min.h"

using namespace c74::min;

class purestair : public object<purestair>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a brightness experiment"};
	MIN_TAGS {""};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "boost", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "limit", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			last1SampleL = 0.0;
			halfwaySampleL = halfDrySampleL = halfDiffSampleL = diffSampleL = 0.0;
			lastSampleL = 0.0;
			s1L = s2L = s3L = 0.0;
			applyL = 0.0;
			last1SampleR = 0.0;
			halfwaySampleR = halfDrySampleR = halfDiffSampleR = diffSampleR = 0.0;
			lastSampleR = 0.0;
			s1R = s2R = s3R = 0.0;
			applyR = 0.0;
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

		double applyTarget = (A*2.0)-1.0;
		double threshold = pow((1-fabs(applyTarget)),3);
		if (applyTarget > 0) applyTarget *= 3;
		
		double intensity = pow(B,2)*5.0;
		double wet = C;
	    
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpd * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpd * 1.18e-43;
			long double drySampleL = inputSampleL;
			long double drySampleR = inputSampleR;
			
			halfDrySampleL = halfwaySampleL = (inputSampleL + last1SampleL) / 2.0;
			last1SampleL = inputSampleL;
			s3L = s2L;
			s2L = s1L;
			s1L = inputSampleL;
			double m1 = (s1L-s2L)*((s1L-s2L)/1.3);
			double m2 = (s2L-s3L)*((s1L-s2L)/1.3);
			double sense = fabs((m1-m2)*((m1-m2)/1.3))*intensity;
			//this will be 0 for smooth, high for SSS
			applyL += applyTarget - sense;
			applyL *= 0.5;
			if (applyL < -1.0) applyL = -1.0;
			
			double clamp = halfwaySampleL - halfDrySampleL;
			if (clamp > threshold) halfwaySampleL = lastSampleL + threshold;
			if (-clamp > threshold) halfwaySampleL = lastSampleL - threshold;
			lastSampleL = halfwaySampleL;
			
			clamp = inputSampleL - lastSampleL;
			if (clamp > threshold) inputSampleL = lastSampleL + threshold;
			if (-clamp > threshold) inputSampleL = lastSampleL - threshold;
			lastSampleL = inputSampleL;
			
			diffSampleL = *in1 - inputSampleL;
			halfDiffSampleL = halfDrySampleL - halfwaySampleL;
			
			inputSampleL = *in1 + ((diffSampleL + halfDiffSampleL)*applyL);
			//done with left channel
			
			halfDrySampleR = halfwaySampleR = (inputSampleR + last1SampleR) / 2.0;
			last1SampleR = inputSampleR;
			s3R = s2R;
			s2R = s1R;
			s1R = inputSampleR;
			m1 = (s1R-s2R)*((s1R-s2R)/1.3);
			m2 = (s2R-s3R)*((s1R-s2R)/1.3);
			sense = fabs((m1-m2)*((m1-m2)/1.3))*intensity;
			//this will be 0 for smooth, high for SSS
			applyR += applyTarget - sense;
			applyR *= 0.5;
			if (applyR < -1.0) applyR = -1.0;
			
			clamp = halfwaySampleR - halfDrySampleR;
			if (clamp > threshold) halfwaySampleR = lastSampleR + threshold;
			if (-clamp > threshold) halfwaySampleR = lastSampleR - threshold;
			lastSampleR = halfwaySampleR;
			
			clamp = inputSampleR - lastSampleR;
			if (clamp > threshold) inputSampleR = lastSampleR + threshold;
			if (-clamp > threshold) inputSampleR = lastSampleR - threshold;
			lastSampleR = inputSampleR;
			
			diffSampleR = *in2 - inputSampleR;
			halfDiffSampleR = halfDrySampleR - halfwaySampleR;
			
			inputSampleR = *in2 + ((diffSampleR + halfDiffSampleR)*applyR);
			//done with right channel
			
			if (wet !=1.0) {
				inputSampleL = (inputSampleL * wet) + (drySampleL * (1.0-wet));
				inputSampleR = (inputSampleR * wet) + (drySampleR * (1.0-wet));
			}
			
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
	long double last1SampleL;
	long double halfwaySampleL;
	long double halfDrySampleL;
	long double halfDiffSampleL;
	long double diffSampleL;
	long double lastSampleL;
	double s1L;
	double s2L;
	double s3L;
	double applyL;

	long double last1SampleR;
	long double halfwaySampleR;
	long double halfDrySampleR;
	long double halfDiffSampleR;
	long double diffSampleR;
	long double lastSampleR;
	double s1R;
	double s2R;
	double s3R;
	double applyR;
	
};
MIN_EXTERNAL(purestair);

