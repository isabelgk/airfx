#include "c74_min.h"

using namespace c74::min;

class unbox : public object<unbox>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a distortion where only the harmonics that don't alias are allowed to distort"};
	MIN_TAGS {"distortion"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "input", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "unbox", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "output", 0.5, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			for(int count = 0; count < 5; count++) {aL[count] = 0.0; bL[count] = 0.0; aR[count] = 0.0; bR[count] = 0.0; e[count] = 0.0;}
			for(int count = 0; count < 11; count++) {cL[count] = 0.0; cR[count] = 0.0; f[count] = 0.0;}
			iirSampleAL = 0.0;
			iirSampleBL = 0.0;
			iirSampleAR = 0.0;
			iirSampleBR = 0.0;
			
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
		
		double input = A*2.0;
		double unbox = B+1.0;
		unbox *= unbox; //let's get some more gain into this
		double iirAmount = (unbox*0.00052)/overallscale;
		double output = C*2.0;
		
		double treble = unbox; //averaging taps 1-4
		double gain = treble;
		if (gain > 1.0) {e[0] = 1.0; gain -= 1.0;} else {e[0] = gain; gain = 0.0;}
		if (gain > 1.0) {e[1] = 1.0; gain -= 1.0;} else {e[1] = gain; gain = 0.0;}
		if (gain > 1.0) {e[2] = 1.0; gain -= 1.0;} else {e[2] = gain; gain = 0.0;}
		if (gain > 1.0) {e[3] = 1.0; gain -= 1.0;} else {e[3] = gain; gain = 0.0;}
		if (gain > 1.0) {e[4] = 1.0; gain -= 1.0;} else {e[4] = gain; gain = 0.0;}
		//there, now we have a neat little moving average with remainders
		if (treble < 1.0) treble = 1.0;
		e[0] /= treble;
		e[1] /= treble;
		e[2] /= treble;
		e[3] /= treble;
		e[4] /= treble;
		//and now it's neatly scaled, too
		
		treble = unbox*2.0; //averaging taps 1-8
		gain = treble;
		if (gain > 1.0) {f[0] = 1.0; gain -= 1.0;} else {f[0] = gain; gain = 0.0;}
		if (gain > 1.0) {f[1] = 1.0; gain -= 1.0;} else {f[1] = gain; gain = 0.0;}
		if (gain > 1.0) {f[2] = 1.0; gain -= 1.0;} else {f[2] = gain; gain = 0.0;}
		if (gain > 1.0) {f[3] = 1.0; gain -= 1.0;} else {f[3] = gain; gain = 0.0;}
		if (gain > 1.0) {f[4] = 1.0; gain -= 1.0;} else {f[4] = gain; gain = 0.0;}
		if (gain > 1.0) {f[5] = 1.0; gain -= 1.0;} else {f[5] = gain; gain = 0.0;}
		if (gain > 1.0) {f[6] = 1.0; gain -= 1.0;} else {f[6] = gain; gain = 0.0;}
		if (gain > 1.0) {f[7] = 1.0; gain -= 1.0;} else {f[7] = gain; gain = 0.0;}
		if (gain > 1.0) {f[8] = 1.0; gain -= 1.0;} else {f[8] = gain; gain = 0.0;}
		if (gain > 1.0) {f[9] = 1.0; gain -= 1.0;} else {f[9] = gain; gain = 0.0;}
		//there, now we have a neat little moving average with remainders
		if (treble < 1.0) treble = 1.0;
		f[0] /= treble;
		f[1] /= treble;
		f[2] /= treble;
		f[3] /= treble;
		f[4] /= treble;
		f[5] /= treble;
		f[6] /= treble;
		f[7] /= treble;
		f[8] /= treble;
		f[9] /= treble;
		//and now it's neatly scaled, too
	    
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
	
			if (input != 1.0) {inputSampleL *= input; inputSampleR *= input;}
	
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpd * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpd * 1.18e-43;
	
			long double drySampleL = inputSampleL;
			long double drySampleR = inputSampleR;
			
			aL[4] = aL[3]; aL[3] = aL[2]; aL[2] = aL[1];
			aL[1] = aL[0]; aL[0] = inputSampleL;
			inputSampleL *= e[0];
			inputSampleL += (aL[1] * e[1]);
			inputSampleL += (aL[2] * e[2]);
			inputSampleL += (aL[3] * e[3]);
			inputSampleL += (aL[4] * e[4]);
			//this is now an average of inputSampleL
			
			aR[4] = aR[3]; aR[3] = aR[2]; aR[2] = aR[1];
			aR[1] = aR[0]; aR[0] = inputSampleR;
			inputSampleR *= e[0];
			inputSampleR += (aR[1] * e[1]);
			inputSampleR += (aR[2] * e[2]);
			inputSampleR += (aR[3] * e[3]);
			inputSampleR += (aR[4] * e[4]);
			//this is now an average of inputSampleR
			
			bL[4] = bL[3]; bL[3] = bL[2]; bL[2] = bL[1];
			bL[1] = bL[0]; bL[0] = inputSampleL;
			inputSampleL *= e[0];
			inputSampleL += (bL[1] * e[1]);
			inputSampleL += (bL[2] * e[2]);
			inputSampleL += (bL[3] * e[3]);
			inputSampleL += (bL[4] * e[4]);
			//this is now an average of an average of inputSampleL. Two poles
			
			bR[4] = bR[3]; bR[3] = bR[2]; bR[2] = bR[1];
			bR[1] = bR[0]; bR[0] = inputSampleR;
			inputSampleR *= e[0];
			inputSampleR += (bR[1] * e[1]);
			inputSampleR += (bR[2] * e[2]);
			inputSampleR += (bR[3] * e[3]);
			inputSampleR += (bR[4] * e[4]);
			//this is now an average of an average of inputSampleR. Two poles
			
			inputSampleL *= unbox;
			inputSampleR *= unbox;
			//clip to 1.2533141373155 to reach maximum output
			if (inputSampleL > 1.2533141373155) inputSampleL = 1.2533141373155;
			if (inputSampleL < -1.2533141373155) inputSampleL = -1.2533141373155;
			inputSampleL = sin(inputSampleL * fabs(inputSampleL)) / ((fabs(inputSampleL) == 0.0) ?1:fabs(inputSampleL));
			
			if (inputSampleR > 1.2533141373155) inputSampleR = 1.2533141373155;
			if (inputSampleR < -1.2533141373155) inputSampleR = -1.2533141373155;
			inputSampleR = sin(inputSampleR * fabs(inputSampleR)) / ((fabs(inputSampleR) == 0.0) ?1:fabs(inputSampleR));
			
			inputSampleL /= unbox;	
			inputSampleR /= unbox;	
			//now we have a distorted inputSample at the correct volume relative to drySample
			
			long double accumulatorSampleL = (drySampleL - inputSampleL);
			cL[9] = cL[8]; cL[8] = cL[7]; cL[7] = cL[6]; cL[6] = cL[5];
			cL[5] = cL[4]; cL[4] = cL[3]; cL[3] = cL[2]; cL[2] = cL[1];
			cL[1] = cL[0]; cL[0] = accumulatorSampleL;
			accumulatorSampleL *= f[0];
			accumulatorSampleL += (cL[1] * f[1]);
			accumulatorSampleL += (cL[2] * f[2]);
			accumulatorSampleL += (cL[3] * f[3]);
			accumulatorSampleL += (cL[4] * f[4]);
			accumulatorSampleL += (cL[5] * f[5]);
			accumulatorSampleL += (cL[6] * f[6]);
			accumulatorSampleL += (cL[7] * f[7]);
			accumulatorSampleL += (cL[8] * f[8]);
			accumulatorSampleL += (cL[9] * f[9]);
			//this is now an average of all the recent variances from dry
			
			long double accumulatorSampleR = (drySampleR - inputSampleR);
			cR[9] = cR[8]; cR[8] = cR[7]; cR[7] = cR[6]; cR[6] = cR[5];
			cR[5] = cR[4]; cR[4] = cR[3]; cR[3] = cR[2]; cR[2] = cR[1];
			cR[1] = cR[0]; cR[0] = accumulatorSampleR;
			accumulatorSampleR *= f[0];
			accumulatorSampleR += (cR[1] * f[1]);
			accumulatorSampleR += (cR[2] * f[2]);
			accumulatorSampleR += (cR[3] * f[3]);
			accumulatorSampleR += (cR[4] * f[4]);
			accumulatorSampleR += (cR[5] * f[5]);
			accumulatorSampleR += (cR[6] * f[6]);
			accumulatorSampleR += (cR[7] * f[7]);
			accumulatorSampleR += (cR[8] * f[8]);
			accumulatorSampleR += (cR[9] * f[9]);
			//this is now an average of all the recent variances from dry
			
			iirSampleAL = (iirSampleAL * (1 - iirAmount)) + (accumulatorSampleL * iirAmount);
			accumulatorSampleL -= iirSampleAL;
			//two poles of IIR
			
			iirSampleAR = (iirSampleAR * (1 - iirAmount)) + (accumulatorSampleR * iirAmount);
			accumulatorSampleR -= iirSampleAR;
			//two poles of IIR
			
			iirSampleBL = (iirSampleBL * (1 - iirAmount)) + (accumulatorSampleL * iirAmount);
			accumulatorSampleL -= iirSampleBL;
			//highpass section
			
			iirSampleBR = (iirSampleBR * (1 - iirAmount)) + (accumulatorSampleR * iirAmount);
			accumulatorSampleR -= iirSampleBR;
			//highpass section
			//this is now a highpassed average of all the recent variances from dry
			
			inputSampleL = drySampleL - accumulatorSampleL;
			inputSampleR = drySampleR - accumulatorSampleR;
			//we apply it as one operation, to get the result.
			
			if (output != 1.0) {inputSampleL *= output; inputSampleR *= output;}
			
			//begin 64 bit stereo floating point dither
			int expon; frexp((double)inputSampleL, &expon);
			fpd ^= fpd << 13; fpd ^= fpd >> 17; fpd ^= fpd << 5;
			inputSampleL += static_cast<int32_t>(fpd) * 1.110223024625156e-44L * pow(2,expon+62);
			frexp((double)inputSampleR, &expon);
			fpd ^= fpd << 13; fpd ^= fpd >> 17; fpd ^= fpd << 5;
			inputSampleR += static_cast<int32_t>(fpd) * 1.110223024625156e-44L * pow(2,expon+62);
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
	long double aL[5];
	long double bL[5];
	long double cL[11];
	long double aR[5];
	long double bR[5];
	long double cR[11];
	long double e[5];
	long double f[11];
	long double iirSampleAL;
	long double iirSampleBL;
	long double iirSampleAR;
	long double iirSampleBR;
	

};
MIN_EXTERNAL(unbox);

