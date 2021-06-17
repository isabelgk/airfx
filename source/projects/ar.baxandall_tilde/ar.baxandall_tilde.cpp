#include "c74_min.h"

using namespace c74::min;

class baxandall : public object<baxandall>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a killer general-purpose EQ"};
	MIN_TAGS {"audio, effect"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "Treble", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "Bass", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "Output", 0.5, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.5;
			B = 0.5;
			C = 0.5;
			for (int x = 0; x < 9; x++) {
				trebleAL[x] = 0.0;
				trebleBL[x] = 0.0;
				bassAL[x] = 0.0;
				bassBL[x] = 0.0;
				trebleAR[x] = 0.0;
				trebleBR[x] = 0.0;
				bassAR[x] = 0.0;
				bassBR[x] = 0.0;
			}
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
		double overallscale = 1.0;
		overallscale /= 44100.0;
		overallscale *= samplerate();

		long sampleFrames = _input.frame_count();

		double trebleGain = pow(10.0,((A*30.0)-15.0)/20.0);
		double trebleFreq = (4410.0*trebleGain)/samplerate();
		if (trebleFreq > 0.45) trebleFreq = 0.45;
		trebleAL[0] = trebleBL[0] = trebleAR[0] = trebleBR[0] = trebleFreq;
		double bassGain = pow(10.0,((B*30.0)-15.0)/20.0);
		double bassFreq = pow(10.0,-((B*30.0)-15.0)/20.0);
		bassFreq = (8820.0*bassFreq)/samplerate();
		if (bassFreq > 0.45) bassFreq = 0.45;
		bassAL[0] = bassBL[0] = bassAR[0] = bassBR[0] = bassFreq;
	    trebleAL[1] = trebleBL[1] = trebleAR[1] = trebleBR[1] = 0.4;
	    bassAL[1] = bassBL[1] = bassAR[1] = bassBR[1] = 0.2;
		double output = pow(10.0,((C*30.0)-15.0)/20.0);
		
		double K = tan(M_PI * trebleAL[0]);
		double norm = 1.0 / (1.0 + K / trebleAL[1] + K * K);
		trebleBL[2] = trebleAL[2] = trebleBR[2] = trebleAR[2] = K * K * norm;
		trebleBL[3] = trebleAL[3] = trebleBR[3] = trebleAR[3] = 2.0 * trebleAL[2];
		trebleBL[4] = trebleAL[4] = trebleBR[4] = trebleAR[4] = trebleAL[2];
		trebleBL[5] = trebleAL[5] = trebleBR[5] = trebleAR[5] = 2.0 * (K * K - 1.0) * norm;
		trebleBL[6] = trebleAL[6] = trebleBR[6] = trebleAR[6] = (1.0 - K / trebleAL[1] + K * K) * norm;
		
		K = tan(M_PI * bassAL[0]);
		norm = 1.0 / (1.0 + K / bassAL[1] + K * K);
		bassBL[2] = bassAL[2] = bassBR[2] = bassAR[2] = K * K * norm;
		bassBL[3] = bassAL[3] = bassBR[3] = bassAR[3] = 2.0 * bassAL[2];
		bassBL[4] = bassAL[4] = bassBR[4] = bassAR[4] = bassAL[2];
		bassBL[5] = bassAL[5] = bassBR[5] = bassAR[5] = 2.0 * (K * K - 1.0) * norm;
		bassBL[6] = bassAL[6] = bassBR[6] = bassAR[6] = (1.0 - K / bassAL[1] + K * K) * norm;
	    
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpd * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpd * 1.18e-43;
			
			if (output != 1.0) {
				inputSampleL *= output;
				inputSampleR *= output;
			}//gain trim in front of plugin, in case Console stage clips
			
			inputSampleL = sin(inputSampleL);
			inputSampleR = sin(inputSampleR);
			//encode Console5: good cleanness
			
			long double trebleSampleL;
			long double bassSampleL;
			long double trebleSampleR;
			long double bassSampleR;
			
			if (flip)
			{
				trebleSampleL = (inputSampleL * trebleAL[2]) + trebleAL[7];
				trebleAL[7] = (inputSampleL * trebleAL[3]) - (trebleSampleL * trebleAL[5]) + trebleAL[8];
				trebleAL[8] = (inputSampleL * trebleAL[4]) - (trebleSampleL * trebleAL[6]);
				trebleSampleL = inputSampleL - trebleSampleL;
				
				bassSampleL = (inputSampleL * bassAL[2]) + bassAL[7];
				bassAL[7] = (inputSampleL * bassAL[3]) - (bassSampleL * bassAL[5]) + bassAL[8];
				bassAL[8] = (inputSampleL * bassAL[4]) - (bassSampleL * bassAL[6]);
				
				trebleSampleR = (inputSampleR * trebleAR[2]) + trebleAR[7];
				trebleAR[7] = (inputSampleR * trebleAR[3]) - (trebleSampleR * trebleAR[5]) + trebleAR[8];
				trebleAR[8] = (inputSampleR * trebleAR[4]) - (trebleSampleR * trebleAR[6]);
				trebleSampleR = inputSampleR - trebleSampleR;
				
				bassSampleR = (inputSampleR * bassAR[2]) + bassAR[7];
				bassAR[7] = (inputSampleR * bassAR[3]) - (bassSampleR * bassAR[5]) + bassAR[8];
				bassAR[8] = (inputSampleR * bassAR[4]) - (bassSampleR * bassAR[6]);
			}
			else
			{
				trebleSampleL = (inputSampleL * trebleBL[2]) + trebleBL[7];
				trebleBL[7] = (inputSampleL * trebleBL[3]) - (trebleSampleL * trebleBL[5]) + trebleBL[8];
				trebleBL[8] = (inputSampleL * trebleBL[4]) - (trebleSampleL * trebleBL[6]);
				trebleSampleL = inputSampleL - trebleSampleL;
				
				bassSampleL = (inputSampleL * bassBL[2]) + bassBL[7];
				bassBL[7] = (inputSampleL * bassBL[3]) - (bassSampleL * bassBL[5]) + bassBL[8];
				bassBL[8] = (inputSampleL * bassBL[4]) - (bassSampleL * bassBL[6]);
				
				trebleSampleR = (inputSampleR * trebleBR[2]) + trebleBR[7];
				trebleBR[7] = (inputSampleR * trebleBR[3]) - (trebleSampleR * trebleBR[5]) + trebleBR[8];
				trebleBR[8] = (inputSampleR * trebleBR[4]) - (trebleSampleR * trebleBR[6]);
				trebleSampleR = inputSampleR - trebleSampleR;
				
				bassSampleR = (inputSampleR * bassBR[2]) + bassBR[7];
				bassBR[7] = (inputSampleR * bassBR[3]) - (bassSampleR * bassBR[5]) + bassBR[8];
				bassBR[8] = (inputSampleR * bassBR[4]) - (bassSampleR * bassBR[6]);
			}
			flip = !flip;
			
			trebleSampleL *= trebleGain;
			bassSampleL *= bassGain;
			inputSampleL = bassSampleL + trebleSampleL; //interleaved biquad
			trebleSampleR *= trebleGain;
			bassSampleR *= bassGain;
			inputSampleR = bassSampleR + trebleSampleR; //interleaved biquad
			
			if (inputSampleL > 1.0) inputSampleL = 1.0;
			if (inputSampleL < -1.0) inputSampleL = -1.0;
			//without this, you can get a NaN condition where it spits out DC offset at full blast!
			inputSampleL = asin(inputSampleL);
			//amplitude aspect
			
			if (inputSampleR > 1.0) inputSampleR = 1.0;
			if (inputSampleR < -1.0) inputSampleR = -1.0;
			//without this, you can get a NaN condition where it spits out DC offset at full blast!
			inputSampleR = asin(inputSampleR);
			//amplitude aspect
			
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
	long double trebleAL[9];
	long double trebleBL[9];
	long double bassAL[9];
	long double bassBL[9];
	
	long double trebleAR[9];
	long double trebleBR[9];
	long double bassAR[9];
	long double bassBR[9];
	bool flip;
	
};
MIN_EXTERNAL(baxandall);

