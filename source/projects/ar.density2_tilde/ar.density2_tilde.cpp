#include "c74_min.h"

using namespace c74::min;

class density2 : public object<density2>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a different color of Density for saturation/antisaturation"};
	MIN_TAGS {"saturation"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "density", 0.2, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "highpass", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "output", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.2;
			B = 0.0;
			C = 1.0;
			D = 1.0;
		
			ataAL = ataBL = ataCL = lastDiffSampleL = 0.0;
			iirSampleAL = iirSampleBL = last3SampleL = last2SampleL = last1SampleL = 0.0;
			ataAR = ataBR = ataCR = lastDiffSampleR = 0.0;
			iirSampleAR = iirSampleBR = last3SampleR = last2SampleR = last1SampleR = 0.0;
		
			fpdL = 1.0; while (fpdL < 16386) fpdL = rand()*UINT32_MAX;
			fpdR = 1.0; while (fpdR < 16386) fpdR = rand()*UINT32_MAX;
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
		double density = (A*5.0)-1.0;
		double out = fabs(density);
		while (out > 1.0) out = out - 1.0;
		density = density * fabs(density);
		double iirAmount = pow(B,3)/overallscale;
		double output = C;
		double wet = D;
		
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpdL * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpdR * 1.18e-43;
			long double drySampleL = inputSampleL;
			long double drySampleR = inputSampleR;
			
			long double halfwaySampleL = (inputSampleL + last1SampleL + ((-last2SampleL + last3SampleL) * 0.0414213562373095048801688)) / 2.0;
			long double halfDrySampleL = halfwaySampleL;
			
			long double halfwaySampleR = (inputSampleR + last1SampleR + ((-last2SampleR + last3SampleR) * 0.0414213562373095048801688)) / 2.0;
			long double halfDrySampleR = halfwaySampleR;
			
			last3SampleL = last2SampleL; last2SampleL = last1SampleL; last1SampleL = inputSampleL;
			last3SampleR = last2SampleR; last2SampleR = last1SampleR; last1SampleR = inputSampleR;
			
			iirSampleBL = (iirSampleBL * (1.0 - iirAmount)) + (halfwaySampleL * iirAmount); halfwaySampleL -= iirSampleBL; //highpass section
			iirSampleBR = (iirSampleBR * (1.0 - iirAmount)) + (halfwaySampleR * iirAmount); halfwaySampleR -= iirSampleBR; //highpass section
			
			long double bridgerectifier;
			
			double count = density;
			while (count > 1.0) {
				bridgerectifier = fabs(halfwaySampleL)*1.57079633;
				if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
				bridgerectifier = sin(bridgerectifier);
				if (halfwaySampleL > 0.0) halfwaySampleL = bridgerectifier;
				else halfwaySampleL = -bridgerectifier;
				count = count - 1.0;
			}
			bridgerectifier = fabs(halfwaySampleL)*1.57079633;
			if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
			if (density > 0) bridgerectifier = sin(bridgerectifier);
			else bridgerectifier = 1-cos(bridgerectifier); //produce either boosted or starved version
			if (halfwaySampleL > 0) halfwaySampleL = (halfwaySampleL*(1.0-out))+(bridgerectifier*out);
			else halfwaySampleL = (halfwaySampleL*(1.0-out))-(bridgerectifier*out); //blend according to density control
			
			count = density;
			while (count > 1.0) {
				bridgerectifier = fabs(halfwaySampleR)*1.57079633;
				if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
				bridgerectifier = sin(bridgerectifier);
				if (halfwaySampleR > 0.0) halfwaySampleR = bridgerectifier;
				else halfwaySampleR = -bridgerectifier;
				count = count - 1.0;
			}
			bridgerectifier = fabs(halfwaySampleR)*1.57079633;
			if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
			if (density > 0) bridgerectifier = sin(bridgerectifier);
			else bridgerectifier = 1-cos(bridgerectifier); //produce either boosted or starved version
			if (halfwaySampleR > 0) halfwaySampleR = (halfwaySampleR*(1.0-out))+(bridgerectifier*out);
			else halfwaySampleR = (halfwaySampleR*(1.0-out))-(bridgerectifier*out); //blend according to density control
			
			ataCL = halfwaySampleL - halfDrySampleL;
			ataAL *= 0.915965594177219015; ataBL *= 0.915965594177219015;
			ataBL += ataCL; ataAL -= ataCL; ataCL = ataBL;
			long double halfDiffSampleL = ataCL * 0.915965594177219015;
			
			ataCR = halfwaySampleR - halfDrySampleR;
			ataAR *= 0.915965594177219015; ataBR *= 0.915965594177219015;
			ataBR += ataCR; ataAR -= ataCR; ataCR = ataBR;
			long double halfDiffSampleR = ataCR * 0.915965594177219015;
			
			iirSampleAL = (iirSampleAL * (1.0 - iirAmount)) + (inputSampleL * iirAmount); inputSampleL -= iirSampleAL; //highpass section
			iirSampleAR = (iirSampleAR * (1.0 - iirAmount)) + (inputSampleR * iirAmount); inputSampleR -= iirSampleAR; //highpass section
			
			count = density;
			while (count > 1.0) {
				bridgerectifier = fabs(inputSampleL)*1.57079633;
				if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
				bridgerectifier = sin(bridgerectifier);
				if (inputSampleL > 0.0) inputSampleL = bridgerectifier;
				else inputSampleL = -bridgerectifier;
				count = count - 1.0;
			}
			bridgerectifier = fabs(inputSampleL)*1.57079633;
			if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
			if (density > 0) bridgerectifier = sin(bridgerectifier);
			else bridgerectifier = 1-cos(bridgerectifier); //produce either boosted or starved version
			if (inputSampleL > 0) inputSampleL = (inputSampleL*(1-out))+(bridgerectifier*out);
			else inputSampleL = (inputSampleL*(1-out))-(bridgerectifier*out); //blend according to density control
			
			count = density;
			while (count > 1.0) {
				bridgerectifier = fabs(inputSampleR)*1.57079633;
				if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
				bridgerectifier = sin(bridgerectifier);
				if (inputSampleR > 0.0) inputSampleR = bridgerectifier;
				else inputSampleR = -bridgerectifier;
				count = count - 1.0;
			}
			bridgerectifier = fabs(inputSampleR)*1.57079633;
			if (bridgerectifier > 1.57079633) bridgerectifier = 1.57079633;
			if (density > 0) bridgerectifier = sin(bridgerectifier);
			else bridgerectifier = 1-cos(bridgerectifier); //produce either boosted or starved version
			if (inputSampleR > 0) inputSampleR = (inputSampleR*(1-out))+(bridgerectifier*out);
			else inputSampleR = (inputSampleR*(1-out))-(bridgerectifier*out); //blend according to density control
			
			ataCL = inputSampleL - drySampleL;
			ataAL *= 0.915965594177219015; ataBL *= 0.915965594177219015;
			ataAL += ataCL; ataBL -= ataCL; ataCL = ataAL;
			long double diffSampleL = ataCL * 0.915965594177219015; 
			
			ataCR = inputSampleR - drySampleR;
			ataAR *= 0.915965594177219015; ataBR *= 0.915965594177219015;
			ataAR += ataCR; ataBR -= ataCR; ataCR = ataAR;
			long double diffSampleR = ataCR * 0.915965594177219015; 
			
			inputSampleL = drySampleL + ((diffSampleL + halfDiffSampleL + lastDiffSampleL) / 1.187);
			lastDiffSampleL = diffSampleL / 2.0;
			inputSampleL *= output;
			inputSampleL = (drySampleL*(1.0-wet))+(inputSampleL*wet);
			
			inputSampleR = drySampleR + ((diffSampleR + halfDiffSampleR + lastDiffSampleR) / 1.187);
			lastDiffSampleR = diffSampleR / 2.0;
			inputSampleR *= output;
			inputSampleR = (drySampleR*(1.0-wet))+(inputSampleR*wet);
			
			//begin 64 bit stereo floating point dither
			int expon; frexp((double)inputSampleL, &expon);
			fpdL ^= fpdL << 13; fpdL ^= fpdL >> 17; fpdL ^= fpdL << 5;
			inputSampleL += ((double(fpdL)-uint32_t(0x7fffffff)) * 1.1e-44l * pow(2,expon+62));
			frexp((double)inputSampleR, &expon);
			fpdR ^= fpdR << 13; fpdR ^= fpdR >> 17; fpdR ^= fpdR << 5;
			inputSampleR += ((double(fpdR)-uint32_t(0x7fffffff)) * 1.1e-44l * pow(2,expon+62));
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
    
	uint32_t fpdL;
	uint32_t fpdR;
	//default stuff

	long double last3SampleL;
	long double last2SampleL;
	long double last1SampleL;
	long double ataAL;
	long double ataBL;
	long double ataCL;
	long double lastDiffSampleL;
	long double iirSampleAL;
	long double iirSampleBL;

	long double last3SampleR;
	long double last2SampleR;
	long double last1SampleR;
	long double ataAR;
	long double ataBR;
	long double ataCR;
	long double lastDiffSampleR;
	long double iirSampleAR;
	long double iirSampleBR;
	
};
MIN_EXTERNAL(density2);

