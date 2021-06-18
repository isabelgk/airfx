#include "c74_min.h"

using namespace c74::min;

class dehiss : public object<dehiss>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"hiss gate"};
	MIN_TAGS {"audio, effect"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "Thresh", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "Dry/Wet", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.0;
			B = 1.0;
			
			storedL[0] = storedL[1] = 0.0;
			diffL[0] = diffL[1] = diffL[2] = diffL[3] = diffL[4] = diffL[5] = 0.0;
			gateL = 1.0;
			rawL = 2.0;
		
			storedR[0] = storedR[1] = 0.0;
			diffR[0] = diffR[1] = diffR[2] = diffR[3] = diffR[4] = diffR[5] = 0.0;
			gateR = 1.0;
			rawR = 2.0;	
			
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
		
		double meanAL;
		double meanBL;
		double meanOutL = 0;
		double meanLastL;
		double averageL[5];
		
		double meanAR;
		double meanBR;
		double meanOutR = 0;
		double meanLastR;
		double averageR[5];
		
		double threshold = pow(A,9);
		double wet = B;
	    
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpd * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpd * 1.18e-43;
			long double drySampleL = inputSampleL;
			long double drySampleR = inputSampleR;
			
			//begin L
			storedL[1] = storedL[0];
			storedL[0] = inputSampleL;
			diffL[5] = diffL[4];
			diffL[4] = diffL[3];
			diffL[3] = diffL[2];
			diffL[2] = diffL[1];
			diffL[1] = diffL[0];
			diffL[0] = storedL[0] - storedL[1];
			
			averageL[4] = (diffL[0] + diffL[1] + diffL[2] + diffL[3] + diffL[4] + diffL[5])/6.0;
			averageL[3] = (diffL[0] + diffL[1] + diffL[2] + diffL[3] + diffL[4])/5.0;
			averageL[2] = (diffL[0] + diffL[1] + diffL[2] + diffL[3])/4.0;
			averageL[1] = (diffL[0] + diffL[1] + diffL[2])/3.0;
			averageL[0] = (diffL[0] + diffL[1])/2.0;
			
			meanAL = diffL[0];
			meanBL = diffL[0];
			if (fabs(averageL[4]) < fabs(meanBL)) {meanAL = meanBL; meanBL = averageL[4];}
			if (fabs(averageL[3]) < fabs(meanBL)) {meanAL = meanBL; meanBL = averageL[3];}
			if (fabs(averageL[2]) < fabs(meanBL)) {meanAL = meanBL; meanBL = averageL[2];}
			if (fabs(averageL[1]) < fabs(meanBL)) {meanAL = meanBL; meanBL = averageL[1];}
			if (fabs(averageL[0]) < fabs(meanBL)) {meanAL = meanBL; meanBL = averageL[0];}
			meanLastL = meanOutL;
			meanOutL = ((meanAL+meanBL)/2.0);
			
			if (rawL > 0) rawL -= 0.001;
			if (fabs(inputSampleL) > threshold) {gateL = 1.0; rawL = 2.0;}
			else {gateL = (gateL * 0.999); if (threshold > 0) gateL += ((fabs(inputSampleL)/threshold) * 0.001);}
			
			if ((fabs(meanOutL) > threshold) || (fabs(meanLastL) > threshold)){}
			else storedL[0] = storedL[1] + (meanOutL * gateL);
			
			if (rawL < 1) inputSampleL = (inputSampleL * rawL) + (storedL[0] * (1-rawL));
			//end L
			
			//begin R
			storedR[1] = storedR[0];
			storedR[0] = inputSampleR;
			diffR[5] = diffR[4];
			diffR[4] = diffR[3];
			diffR[3] = diffR[2];
			diffR[2] = diffR[1];
			diffR[1] = diffR[0];
			diffR[0] = storedR[0] - storedR[1];
			
			averageR[4] = (diffR[0] + diffR[1] + diffR[2] + diffR[3] + diffR[4] + diffR[5])/6.0;
			averageR[3] = (diffR[0] + diffR[1] + diffR[2] + diffR[3] + diffR[4])/5.0;
			averageR[2] = (diffR[0] + diffR[1] + diffR[2] + diffR[3])/4.0;
			averageR[1] = (diffR[0] + diffR[1] + diffR[2])/3.0;
			averageR[0] = (diffR[0] + diffR[1])/2.0;
			
			meanAR = diffR[0];
			meanBR = diffR[0];
			if (fabs(averageR[4]) < fabs(meanBR)) {meanAR = meanBR; meanBR = averageR[4];}
			if (fabs(averageR[3]) < fabs(meanBR)) {meanAR = meanBR; meanBR = averageR[3];}
			if (fabs(averageR[2]) < fabs(meanBR)) {meanAR = meanBR; meanBR = averageR[2];}
			if (fabs(averageR[1]) < fabs(meanBR)) {meanAR = meanBR; meanBR = averageR[1];}
			if (fabs(averageR[0]) < fabs(meanBR)) {meanAR = meanBR; meanBR = averageR[0];}
			meanLastR = meanOutR;
			meanOutR = ((meanAR+meanBR)/2.0);
			
			if (rawR > 0) rawR -= 0.001;
			if (fabs(inputSampleR) > threshold) {gateR = 1.0; rawR = 2.0;}
			else {gateR = (gateR * 0.999); if (threshold > 0) gateR += ((fabs(inputSampleR)/threshold) * 0.001);}
			
			if ((fabs(meanOutR) > threshold) || (fabs(meanLastR) > threshold)){}
			else storedR[0] = storedR[1] + (meanOutR * gateR);
			
			if (rawR < 1) inputSampleR = (inputSampleR * rawR) + (storedR[0] * (1-rawR));
			//end R
			
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
	double storedL[2];
	double diffL[6];
	double gateL;
	double rawL;

	double storedR[2];
	double diffR[6];
	double gateR;
	double rawR;

};
MIN_EXTERNAL(dehiss);

