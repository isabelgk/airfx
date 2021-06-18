#include "c74_min.h"

using namespace c74::min;

class distance2 : public object<distance2>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"shape shaper for creating depth"};
	MIN_TAGS {"audio, effect"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "Atmosph", 0.85, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "Darken", 0.618, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "Dry/Wet", 0.618, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.85;
			B = 0.618;
			C = 0.618;
		
			thirdSampleL = lastSampleL = 0.0;
			thirdSampleR = lastSampleR = 0.0;
		
			lastSampleAL = 0.0;
			lastSampleBL = 0.0;
			lastSampleCL = 0.0;
			lastSampleDL = 0.0;
			lastSampleEL = 0.0;
			lastSampleFL = 0.0;
			lastSampleGL = 0.0;
			lastSampleHL = 0.0;
			lastSampleIL = 0.0;
			lastSampleJL = 0.0;
			lastSampleKL = 0.0;
			lastSampleLL = 0.0;
			lastSampleML = 0.0;
		
			lastSampleAR = 0.0;
			lastSampleBR = 0.0;
			lastSampleCR = 0.0;
			lastSampleDR = 0.0;
			lastSampleER = 0.0;
			lastSampleFR = 0.0;
			lastSampleGR = 0.0;
			lastSampleHR = 0.0;
			lastSampleIR = 0.0;
			lastSampleJR = 0.0;
			lastSampleKR = 0.0;
			lastSampleLR = 0.0;
			lastSampleMR = 0.0;
		
			thresholdA = 0.618033988749894;
			thresholdB = 0.679837387624884;
			thresholdC = 0.747821126387373;
			thresholdD = 0.82260323902611;
			thresholdE = 0.904863562928721;
			thresholdF = 0.995349919221593;
			thresholdG = 1.094884911143752;
			thresholdH = 1.204373402258128;
			thresholdI = 1.32481074248394;
			thresholdJ = 1.457291816732335;
			thresholdK = 1.603020998405568;
			thresholdL = 1.763323098246125;
			thresholdM = 1.939655408070737;
			
			fpNShapeL = 0.0;
			fpNShapeR = 0.0;
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
		thresholdA = 0.618033988749894 / overallscale;
		thresholdB = 0.679837387624884 / overallscale;
		thresholdC = 0.747821126387373 / overallscale;
		thresholdD = 0.82260323902611 / overallscale;
		thresholdE = 0.904863562928721 / overallscale;
		thresholdF = 0.995349919221593 / overallscale;
		thresholdG = 1.094884911143752 / overallscale;
		thresholdH = 1.204373402258128 / overallscale;
		thresholdI = 1.32481074248394 / overallscale;
		thresholdJ = 1.457291816732335 / overallscale;
		thresholdK = 1.603020998405568 / overallscale;
		thresholdL = 1.763323098246125 / overallscale;
		thresholdM = 1.939655408070737 / overallscale;	
		double softslew = (pow(A,3)*24)+.6;
		softslew *= overallscale;
		double filter = softslew * B;
		double secondfilter = filter / 3.0;
		double thirdfilter = filter / 5.0;
		double offsetScale = A * 0.1618;
		double levelcorrect = 1.0 + ((filter / 12.0) * A);
		//bring in top slider again to manage boost level for lower settings	
		double wet = C;
		double dry = 1.0 - wet;
	
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
	
			static int noisesourceL = 0;
			static int noisesourceR = 850010;
			int residue;
			double applyresidue;
			
			noisesourceL = noisesourceL % 1700021; noisesourceL++;
			residue = noisesourceL * noisesourceL;
			residue = residue % 170003; residue *= residue;
			residue = residue % 17011; residue *= residue;
			residue = residue % 1709; residue *= residue;
			residue = residue % 173; residue *= residue;
			residue = residue % 17;
			applyresidue = residue;
			applyresidue *= 0.00000001;
			applyresidue *= 0.00000001;
			inputSampleL += applyresidue;
			if (inputSampleL<1.2e-38 && -inputSampleL<1.2e-38) {
				inputSampleL -= applyresidue;
			}
			
			noisesourceR = noisesourceR % 1700021; noisesourceR++;
			residue = noisesourceR * noisesourceR;
			residue = residue % 170003; residue *= residue;
			residue = residue % 17011; residue *= residue;
			residue = residue % 1709; residue *= residue;
			residue = residue % 173; residue *= residue;
			residue = residue % 17;
			applyresidue = residue;
			applyresidue *= 0.00000001;
			applyresidue *= 0.00000001;
			inputSampleR += applyresidue;
			if (inputSampleR<1.2e-38 && -inputSampleR<1.2e-38) {
				inputSampleR -= applyresidue;
			}
			//for live air, we always apply the dither noise. Then, if our result is 
			//effectively digital black, we'll subtract it again. We want a 'air' hiss
			double drySampleL = inputSampleL;
			double drySampleR = inputSampleR;
			
			double offsetL = offsetScale - (lastSampleL - inputSampleL);		
			double offsetR = offsetScale - (lastSampleR - inputSampleR);		
			
			inputSampleL += (offsetL*offsetScale); //extra bit from Loud: offset air compression
			inputSampleL *= wet; //clean up w. dry introduced
			inputSampleL *= softslew; //scale into Atmosphere algorithm
			
			inputSampleR += (offsetR*offsetScale); //extra bit from Loud: offset air compression
			inputSampleR *= wet; //clean up w. dry introduced
			inputSampleR *= softslew; //scale into Atmosphere algorithm
			
			//left
			long double clamp = inputSampleL - lastSampleAL;
			if (clamp > thresholdA) inputSampleL = lastSampleAL + thresholdA;
			if (-clamp > thresholdA) inputSampleL = lastSampleAL - thresholdA;
			
			clamp = inputSampleL - lastSampleBL;
			if (clamp > thresholdB) inputSampleL = lastSampleBL + thresholdB;
			if (-clamp > thresholdB) inputSampleL = lastSampleBL - thresholdB;
			
			clamp = inputSampleL - lastSampleCL;
			if (clamp > thresholdC) inputSampleL = lastSampleCL + thresholdC;
			if (-clamp > thresholdC) inputSampleL = lastSampleCL - thresholdC;
			
			clamp = inputSampleL - lastSampleDL;
			if (clamp > thresholdD) inputSampleL = lastSampleDL + thresholdD;
			if (-clamp > thresholdD) inputSampleL = lastSampleDL - thresholdD;
			
			clamp = inputSampleL - lastSampleEL;
			if (clamp > thresholdE) inputSampleL = lastSampleEL + thresholdE;
			if (-clamp > thresholdE) inputSampleL = lastSampleEL - thresholdE;
			
			clamp = inputSampleL - lastSampleFL;
			if (clamp > thresholdF) inputSampleL = lastSampleFL + thresholdF;
			if (-clamp > thresholdF) inputSampleL = lastSampleFL - thresholdF;
			
			clamp = inputSampleL - lastSampleGL;
			if (clamp > thresholdG) inputSampleL = lastSampleGL + thresholdG;
			if (-clamp > thresholdG) inputSampleL = lastSampleGL - thresholdG;
			
			clamp = inputSampleL - lastSampleHL;
			if (clamp > thresholdH) inputSampleL = lastSampleHL + thresholdH;
			if (-clamp > thresholdH) inputSampleL = lastSampleHL - thresholdH;
			
			clamp = inputSampleL - lastSampleIL;
			if (clamp > thresholdI) inputSampleL = lastSampleIL + thresholdI;
			if (-clamp > thresholdI) inputSampleL = lastSampleIL - thresholdI;
			
			clamp = inputSampleL - lastSampleJL;
			if (clamp > thresholdJ) inputSampleL = lastSampleJL + thresholdJ;
			if (-clamp > thresholdJ) inputSampleL = lastSampleJL - thresholdJ;
			
			clamp = inputSampleL - lastSampleKL;
			if (clamp > thresholdK) inputSampleL = lastSampleKL + thresholdK;
			if (-clamp > thresholdK) inputSampleL = lastSampleKL - thresholdK;
			
			clamp = inputSampleL - lastSampleLL;
			if (clamp > thresholdL) inputSampleL = lastSampleLL + thresholdL;
			if (-clamp > thresholdL) inputSampleL = lastSampleLL - thresholdL;
			
			clamp = inputSampleL - lastSampleML;
			if (clamp > thresholdM) inputSampleL = lastSampleML + thresholdM;
			if (-clamp > thresholdM) inputSampleL = lastSampleML - thresholdM;
			
			//right
			clamp = inputSampleR - lastSampleAR;
			if (clamp > thresholdA) inputSampleR = lastSampleAR + thresholdA;
			if (-clamp > thresholdA) inputSampleR = lastSampleAR - thresholdA;
			
			clamp = inputSampleR - lastSampleBR;
			if (clamp > thresholdB) inputSampleR = lastSampleBR + thresholdB;
			if (-clamp > thresholdB) inputSampleR = lastSampleBR - thresholdB;
			
			clamp = inputSampleR - lastSampleCR;
			if (clamp > thresholdC) inputSampleR = lastSampleCR + thresholdC;
			if (-clamp > thresholdC) inputSampleR = lastSampleCR - thresholdC;
			
			clamp = inputSampleR - lastSampleDR;
			if (clamp > thresholdD) inputSampleR = lastSampleDR + thresholdD;
			if (-clamp > thresholdD) inputSampleR = lastSampleDR - thresholdD;
			
			clamp = inputSampleR - lastSampleER;
			if (clamp > thresholdE) inputSampleR = lastSampleER + thresholdE;
			if (-clamp > thresholdE) inputSampleR = lastSampleER - thresholdE;
			
			clamp = inputSampleR - lastSampleFR;
			if (clamp > thresholdF) inputSampleR = lastSampleFR + thresholdF;
			if (-clamp > thresholdF) inputSampleR = lastSampleFR - thresholdF;
			
			clamp = inputSampleR - lastSampleGR;
			if (clamp > thresholdG) inputSampleR = lastSampleGR + thresholdG;
			if (-clamp > thresholdG) inputSampleR = lastSampleGR - thresholdG;
			
			clamp = inputSampleR - lastSampleHR;
			if (clamp > thresholdH) inputSampleR = lastSampleHR + thresholdH;
			if (-clamp > thresholdH) inputSampleR = lastSampleHR - thresholdH;
			
			clamp = inputSampleR - lastSampleIR;
			if (clamp > thresholdI) inputSampleR = lastSampleIR + thresholdI;
			if (-clamp > thresholdI) inputSampleR = lastSampleIR - thresholdI;
			
			clamp = inputSampleR - lastSampleJR;
			if (clamp > thresholdJ) inputSampleR = lastSampleJR + thresholdJ;
			if (-clamp > thresholdJ) inputSampleR = lastSampleJR - thresholdJ;
			
			clamp = inputSampleR - lastSampleKR;
			if (clamp > thresholdK) inputSampleR = lastSampleKR + thresholdK;
			if (-clamp > thresholdK) inputSampleR = lastSampleKR - thresholdK;
			
			clamp = inputSampleR - lastSampleLR;
			if (clamp > thresholdL) inputSampleR = lastSampleLR + thresholdL;
			if (-clamp > thresholdL) inputSampleR = lastSampleLR - thresholdL;
			
			clamp = inputSampleR - lastSampleMR;
			if (clamp > thresholdM) inputSampleR = lastSampleMR + thresholdM;
			if (-clamp > thresholdM) inputSampleR = lastSampleMR - thresholdM;
			
			
			lastSampleML = lastSampleLL;
			lastSampleLL = lastSampleKL;
			lastSampleKL = lastSampleJL;
			lastSampleJL = lastSampleIL;
			lastSampleIL = lastSampleHL;
			lastSampleHL = lastSampleGL;
			lastSampleGL = lastSampleFL;
			lastSampleFL = lastSampleEL;
			lastSampleEL = lastSampleDL;
			lastSampleDL = lastSampleCL;
			lastSampleCL = lastSampleBL;
			lastSampleBL = lastSampleAL;
			lastSampleAL = drySampleL;
			//store the raw input sample again for use next time
			
			lastSampleMR = lastSampleLR;
			lastSampleLR = lastSampleKR;
			lastSampleKR = lastSampleJR;
			lastSampleJR = lastSampleIR;
			lastSampleIR = lastSampleHR;
			lastSampleHR = lastSampleGR;
			lastSampleGR = lastSampleFR;
			lastSampleFR = lastSampleER;
			lastSampleER = lastSampleDR;
			lastSampleDR = lastSampleCR;
			lastSampleCR = lastSampleBR;
			lastSampleBR = lastSampleAR;
			lastSampleAR = drySampleR;
			//store the raw input sample again for use next time
			
			inputSampleL *= levelcorrect;
			inputSampleL /= softslew;
			inputSampleL -= (offsetL*offsetScale);
			//begin IIR stage
			inputSampleR *= levelcorrect;
			inputSampleR /= softslew;
			inputSampleR -= (offsetR*offsetScale);
			//begin IIR stage
			
			inputSampleL += (thirdSampleL * thirdfilter);
			inputSampleL /= (thirdfilter + 1.0);
			inputSampleL += (lastSampleL * secondfilter);
			inputSampleL /= (secondfilter + 1.0);
			//do an IIR like thing to further squish superdistant stuff
			inputSampleR += (thirdSampleR * thirdfilter);
			inputSampleR /= (thirdfilter + 1.0);
			inputSampleR += (lastSampleR * secondfilter);
			inputSampleR /= (secondfilter + 1.0);
			//do an IIR like thing to further squish superdistant stuff
			
			thirdSampleL = lastSampleL;
			lastSampleL = inputSampleL;		
			inputSampleL *= levelcorrect;
			
			thirdSampleR = lastSampleR;
			lastSampleR = inputSampleR;		
			inputSampleR *= levelcorrect;
			
			if (wet !=1.0) {
				inputSampleL = (inputSampleL * wet) + (drySampleL * dry);
				inputSampleR = (inputSampleR * wet) + (drySampleR * dry);
			}
			
			//stereo 64 bit dither, made small and tidy.
			int expon; frexp((double)inputSampleL, &expon);
			long double dither = (rand()/(RAND_MAX*7.737125245533627e+25))*pow(2,expon+62);
			dither /= 536870912.0; //needs this to scale to 64 bit zone
			inputSampleL += (dither-fpNShapeL); fpNShapeL = dither;
			frexp((double)inputSampleR, &expon);
			dither = (rand()/(RAND_MAX*7.737125245533627e+25))*pow(2,expon+62);
			dither /= 536870912.0; //needs this to scale to 64 bit zone
			inputSampleR += (dither-fpNShapeR); fpNShapeR = dither;
			//end 64 bit dither
			
			*out1 = inputSampleL;
			*out2 = inputSampleR;
	
			*in1++;
			*in2++;
			*out1++;
			*out2++;
		}
	}
private:
    
	long double fpNShapeL;
	long double fpNShapeR;
	//default stuff
	
	long double lastSampleAL;
	long double lastSampleBL;
	long double lastSampleCL;
	long double lastSampleDL;
	long double lastSampleEL;
	long double lastSampleFL;
	long double lastSampleGL;
	long double lastSampleHL;
	long double lastSampleIL;
	long double lastSampleJL;
	long double lastSampleKL;
	long double lastSampleLL;
	long double lastSampleML;

	long double lastSampleAR;
	long double lastSampleBR;
	long double lastSampleCR;
	long double lastSampleDR;
	long double lastSampleER;
	long double lastSampleFR;
	long double lastSampleGR;
	long double lastSampleHR;
	long double lastSampleIR;
	long double lastSampleJR;
	long double lastSampleKR;
	long double lastSampleLR;
	long double lastSampleMR;

	long double thresholdA;
	long double thresholdB;
	long double thresholdC;
	long double thresholdD;
	long double thresholdE;
	long double thresholdF;
	long double thresholdG;
	long double thresholdH;
	long double thresholdI;
	long double thresholdJ;
	long double thresholdK;
	long double thresholdL;
	long double thresholdM;
	
	double thirdSampleL;
	double lastSampleL;
	
	double thirdSampleR;
	double lastSampleR;
	
};
MIN_EXTERNAL(distance2);

