#include "c74_min.h"

using namespace c74::min;

class cojones : public object<cojones>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a kind of distortion effect"};
	MIN_TAGS {"distortion"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "breathy", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "cojones", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "body", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "output", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> E {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			storedL[0] = storedL[1] = 0.0;
			diffL[0] = diffL[1] = diffL[2] = diffL[3] = diffL[4] = diffL[5] = 0.0;
		
			storedR[0] = storedR[1] = 0.0;
			diffR[0] = diffR[1] = diffR[2] = diffR[3] = diffR[4] = diffR[5] = 0.0;
		
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

		double breathy = A*2.0;
		double cojones = B*2.0;
		double body = C*2.0;
		double output = D;
		double wet = E;
		double averageL[5];
		double averageR[5];
		
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
			
			//begin L
			storedL[1] = storedL[0];
			storedL[0] = inputSampleL;
			diffL[5] = diffL[4];
			diffL[4] = diffL[3];
			diffL[3] = diffL[2];
			diffL[2] = diffL[1];
			diffL[1] = diffL[0];
			diffL[0] = storedL[0] - storedL[1];
			
			averageL[0] = diffL[0] + diffL[1];
			averageL[1] = averageL[0] + diffL[2];
			averageL[2] = averageL[1] + diffL[3];
			averageL[3] = averageL[2] + diffL[4];
			averageL[4] = averageL[3] + diffL[5];
			
			averageL[0] /= 2.0;
			averageL[1] /= 3.0;
			averageL[2] /= 4.0;
			averageL[3] /= 5.0;
			averageL[4] /= 6.0;
			
			long double meanA = diffL[0];
			long double meanB = diffL[0];
			if (fabs(averageL[4]) < fabs(meanB)) {meanA = meanB; meanB = averageL[4];}
			if (fabs(averageL[3]) < fabs(meanB)) {meanA = meanB; meanB = averageL[3];}
			if (fabs(averageL[2]) < fabs(meanB)) {meanA = meanB; meanB = averageL[2];}
			if (fabs(averageL[1]) < fabs(meanB)) {meanA = meanB; meanB = averageL[1];}
			if (fabs(averageL[0]) < fabs(meanB)) {meanA = meanB; meanB = averageL[0];}
			long double meanOut = ((meanA+meanB)/2.0);
			storedL[0] = (storedL[1] + meanOut);
			
			long double outputSample = storedL[0]*body;
			//presubtract cojones
			outputSample += (((inputSampleL - storedL[0])-averageL[1])*cojones);
			
			outputSample += (averageL[1]*breathy);
			
			inputSampleL = outputSample;
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
			
			averageR[0] = diffR[0] + diffR[1];
			averageR[1] = averageR[0] + diffR[2];
			averageR[2] = averageR[1] + diffR[3];
			averageR[3] = averageR[2] + diffR[4];
			averageR[4] = averageR[3] + diffR[5];
			
			averageR[0] /= 2.0;
			averageR[1] /= 3.0;
			averageR[2] /= 4.0;
			averageR[3] /= 5.0;
			averageR[4] /= 6.0;
			
			meanA = diffR[0];
			meanB = diffR[0];
			if (fabs(averageR[4]) < fabs(meanB)) {meanA = meanB; meanB = averageR[4];}
			if (fabs(averageR[3]) < fabs(meanB)) {meanA = meanB; meanB = averageR[3];}
			if (fabs(averageR[2]) < fabs(meanB)) {meanA = meanB; meanB = averageR[2];}
			if (fabs(averageR[1]) < fabs(meanB)) {meanA = meanB; meanB = averageR[1];}
			if (fabs(averageR[0]) < fabs(meanB)) {meanA = meanB; meanB = averageR[0];}
			meanOut = ((meanA+meanB)/2.0);
			storedR[0] = (storedR[1] + meanOut);
			
			outputSample = storedR[0]*body;
			//presubtract cojones
			outputSample += (((inputSampleR - storedR[0])-averageR[1])*cojones);
			
			outputSample += (averageR[1]*breathy);
			
			inputSampleR = outputSample;
			//end R
			
			if (output < 1.0) {
				inputSampleL *= output;
				inputSampleR *= output;
			}
			
			if (wet < 1.0) {
				inputSampleL = (inputSampleL * wet) + (drySampleL * (1.0-wet));
				inputSampleR = (inputSampleR * wet) + (drySampleR * (1.0-wet));
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

	long double storedL[2];
	long double diffL[6];

	long double storedR[2];
	long double diffR[6];

};
MIN_EXTERNAL(cojones);

