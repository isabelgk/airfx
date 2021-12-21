#include "c74_min.h"

using namespace c74::min;

class vinyldither : public object<vinyldither>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a high-performance dither that converts digital noise to 'groove noise'"};
	MIN_TAGS {"dither"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "quant", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "derez", 0.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 1.0;
			B = 0.0;
			fpd = 17;
			NSOddL = 0.0;
			prevL = 0.0;
			nsL[0] = 0;
			nsL[1] = 0;
			nsL[2] = 0;
			nsL[3] = 0;
			nsL[4] = 0;
			nsL[5] = 0;
			nsL[6] = 0;
			nsL[7] = 0;
			nsL[8] = 0;
			nsL[9] = 0;
			nsL[10] = 0;
			nsL[11] = 0;
			nsL[12] = 0;
			nsL[13] = 0;
			nsL[14] = 0;
			nsL[15] = 0;
			NSOddR = 0.0;
			prevR = 0.0;
			nsR[0] = 0;
			nsR[1] = 0;
			nsR[2] = 0;
			nsR[3] = 0;
			nsR[4] = 0;
			nsR[5] = 0;
			nsR[6] = 0;
			nsR[7] = 0;
			nsR[8] = 0;
			nsR[9] = 0;
			nsR[10] = 0;
			nsR[11] = 0;
			nsR[12] = 0;
			nsR[13] = 0;
			nsR[14] = 0;
			nsR[15] = 0;
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

		double absSample;
	
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
			
			absSample = ((rand()/(double)RAND_MAX) - 0.5);
			nsL[0] += absSample; nsL[0] /= 2; absSample -= nsL[0];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsL[1] += absSample; nsL[1] /= 2; absSample -= nsL[1];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsL[2] += absSample; nsL[2] /= 2; absSample -= nsL[2];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsL[3] += absSample; nsL[3] /= 2; absSample -= nsL[3];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsL[4] += absSample; nsL[4] /= 2; absSample -= nsL[4];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsL[5] += absSample; nsL[5] /= 2; absSample -= nsL[5];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsL[6] += absSample; nsL[6] /= 2; absSample -= nsL[6];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsL[7] += absSample; nsL[7] /= 2; absSample -= nsL[7];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsL[8] += absSample; nsL[8] /= 2; absSample -= nsL[8];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsL[9] += absSample; nsL[9] /= 2; absSample -= nsL[9];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsL[10] += absSample; nsL[10] /= 2; absSample -= nsL[10];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsL[11] += absSample; nsL[11] /= 2; absSample -= nsL[11];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsL[12] += absSample; nsL[12] /= 2; absSample -= nsL[12];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsL[13] += absSample; nsL[13] /= 2; absSample -= nsL[13];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsL[14] += absSample; nsL[14] /= 2; absSample -= nsL[14];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsL[15] += absSample; nsL[15] /= 2; absSample -= nsL[15];
			//install noise and then shape it
			absSample += inputSampleL;
			
			if (NSOddL > 0) NSOddL -= 0.97;
			if (NSOddL < 0) NSOddL += 0.97;
			
			NSOddL -= (NSOddL * NSOddL * NSOddL * 0.475);
			
			NSOddL += prevL;
			absSample += (NSOddL*0.475);
			prevL = floor(absSample) - inputSampleL;
			inputSampleL = floor(absSample);
			//TenNines dither L
			
			absSample = ((rand()/(double)RAND_MAX) - 0.5);
			nsR[0] += absSample; nsR[0] /= 2; absSample -= nsR[0];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsR[1] += absSample; nsR[1] /= 2; absSample -= nsR[1];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsR[2] += absSample; nsR[2] /= 2; absSample -= nsR[2];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsR[3] += absSample; nsR[3] /= 2; absSample -= nsR[3];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsR[4] += absSample; nsR[4] /= 2; absSample -= nsR[4];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsR[5] += absSample; nsR[5] /= 2; absSample -= nsR[5];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsR[6] += absSample; nsR[6] /= 2; absSample -= nsR[6];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsR[7] += absSample; nsR[7] /= 2; absSample -= nsR[7];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsR[8] += absSample; nsR[8] /= 2; absSample -= nsR[8];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsR[9] += absSample; nsR[9] /= 2; absSample -= nsR[9];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsR[10] += absSample; nsR[10] /= 2; absSample -= nsR[10];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsR[11] += absSample; nsR[11] /= 2; absSample -= nsR[11];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsR[12] += absSample; nsR[12] /= 2; absSample -= nsR[12];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsR[13] += absSample; nsR[13] /= 2; absSample -= nsR[13];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsR[14] += absSample; nsR[14] /= 2; absSample -= nsR[14];
			absSample += ((rand()/(double)RAND_MAX) - 0.5);
			nsR[15] += absSample; nsR[15] /= 2; absSample -= nsR[15];
			//install noise and then shape it
			absSample += inputSampleR;
			
			if (NSOddR > 0) NSOddR -= 0.97;
			if (NSOddR < 0) NSOddR += 0.97;
			
			NSOddR -= (NSOddR * NSOddR * NSOddR * 0.475);
			
			NSOddR += prevR;
			absSample += (NSOddR*0.475);
			prevR = floor(absSample) - inputSampleR;
			inputSampleR = floor(absSample);
			//TenNines dither R
			
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
    
	double NSOddL;
	double prevL;
	double nsL[16];
	double NSOddR;
	double prevR;
	double nsR[16];
	uint32_t fpd;
	//default stuff
	
};
MIN_EXTERNAL(vinyldither);

