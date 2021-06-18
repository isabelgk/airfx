#include "c74_min.h"

using namespace c74::min;

class derez2 : public object<derez2>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"retro-digital hardware effect"};
	MIN_TAGS {"audio, effect"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "Rate", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "Rez", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "Hard", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "Dry/Wet", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 1.0;
			B = 1.0;
			C = 1.0;
			D = 1.0;
			lastSampleL = 0.0;
			heldSampleL = 0.0;
			lastDrySampleL = 0.0;
			lastOutputSampleL = 0.0;
		
			lastSampleR = 0.0;
			heldSampleR = 0.0;
			lastDrySampleR = 0.0;
			lastOutputSampleR = 0.0;
		
			position = 0.0;
			incrementA = 0.0;
			incrementB = 0.0;
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

		double targetA = pow(A,3)+0.0005;
		if (targetA > 1.0) targetA = 1.0;
		double soften = (1.0 + targetA)/2;
		double targetB = pow(1.0-B,3) / 3;
		double hard = C;
		double wet = D;	
		
		double overallscale = 1.0;
		overallscale /= 44100.0;
		overallscale *= samplerate();
		targetA /= overallscale;	
	    
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpd * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpd * 1.18e-43;
			long double drySampleL = inputSampleL;
			long double drySampleR = inputSampleR;
			
			
			incrementA = ((incrementA*999.0)+targetA)/1000.0;
			incrementB = ((incrementB*999.0)+targetB)/1000.0;
			//incrementA is the frequency derez
			//incrementB is the bit depth derez
			position += incrementA;
			
			long double outputSampleL = heldSampleL;
			long double outputSampleR = heldSampleR;
			if (position > 1.0)
			{
				position -= 1.0;
				heldSampleL = (lastSampleL * position) + (inputSampleL * (1.0-position));
				outputSampleL = (outputSampleL * (1.0-soften)) + (heldSampleL * soften);
				//softens the edge of the derez
				heldSampleR = (lastSampleR * position) + (inputSampleR * (1.0-position));
				outputSampleR = (outputSampleR * (1.0-soften)) + (heldSampleR * soften);
				//softens the edge of the derez
			}
			inputSampleL = outputSampleL;
			inputSampleR = outputSampleR;
			
			long double tempL = inputSampleL;
			long double tempR = inputSampleR;
			
			if (inputSampleL != lastOutputSampleL) {
				tempL = inputSampleL;
				inputSampleL = (inputSampleL * hard) + (lastDrySampleL * (1.0-hard));
				//transitions get an intermediate dry sample
				lastOutputSampleL = tempL; //only one intermediate sample
			} else {
				lastOutputSampleL = inputSampleL;
			}
			
			if (inputSampleR != lastOutputSampleR) {
				tempR = inputSampleR;
				inputSampleR = (inputSampleR * hard) + (lastDrySampleR * (1.0-hard));
				//transitions get an intermediate dry sample
				lastOutputSampleR = tempR; //only one intermediate sample
			} else {
				lastOutputSampleR = inputSampleR;
			}
			
			lastDrySampleL = drySampleL;
			lastDrySampleR = drySampleR;
			//freq section of soft/hard interpolates dry samples
			
			tempL = inputSampleL;
			tempR = inputSampleR;
			
			if (inputSampleL > 1.0) inputSampleL = 1.0;
			if (inputSampleL < -1.0) inputSampleL = -1.0;
			
			if (inputSampleR > 1.0) inputSampleR = 1.0;
			if (inputSampleR < -1.0) inputSampleR = -1.0;
			
			if (inputSampleL > 0) inputSampleL = log(1.0+(255*fabs(inputSampleL))) / log(256);
			if (inputSampleL < 0) inputSampleL = -log(1.0+(255*fabs(inputSampleL))) / log(256);
			
			if (inputSampleR > 0) inputSampleR = log(1.0+(255*fabs(inputSampleR))) / log(256);
			if (inputSampleR < 0) inputSampleR = -log(1.0+(255*fabs(inputSampleR))) / log(256);
			
			inputSampleL = (tempL * hard) + (inputSampleL * (1.0-hard));
			inputSampleR = (tempR * hard) + (inputSampleR * (1.0-hard)); //uLaw encode as part of soft/hard
			
			tempL = inputSampleL;
			tempR = inputSampleR;
			
			if (incrementB > 0.0005)
			{
				if (inputSampleL > 0)
				{
					tempL = inputSampleL;
					while (tempL > 0) {tempL -= incrementB;}
					inputSampleL -= tempL;
					//it's below 0 so subtracting adds the remainder
				}
				if (inputSampleR > 0)
				{
					tempR = inputSampleR;
					while (tempR > 0) {tempR -= incrementB;}
					inputSampleR -= tempR;
					//it's below 0 so subtracting adds the remainder
				}
				
				if (inputSampleL < 0)
				{
					tempL = inputSampleL;
					while (tempL < 0) {tempL += incrementB;}
					inputSampleL -= tempL;
					//it's above 0 so subtracting subtracts the remainder
				}
				if (inputSampleR < 0)
				{
					tempR = inputSampleR;
					while (tempR < 0) {tempR += incrementB;}
					inputSampleR -= tempR;
					//it's above 0 so subtracting subtracts the remainder
				}
				
				inputSampleL *= (1.0 - incrementB);
				inputSampleR *= (1.0 - incrementB);
			}
			
			tempL = inputSampleL;
			tempR = inputSampleR;
			
			if (inputSampleL > 1.0) inputSampleL = 1.0;
			if (inputSampleL < -1.0) inputSampleL = -1.0;
			
			if (inputSampleR > 1.0) inputSampleR = 1.0;
			if (inputSampleR < -1.0) inputSampleR = -1.0;
			
			if (inputSampleL > 0) inputSampleL = (pow(256,fabs(inputSampleL))-1.0) / 255;
			if (inputSampleL < 0) inputSampleL = -(pow(256,fabs(inputSampleL))-1.0) / 255;
			
			if (inputSampleR > 0) inputSampleR = (pow(256,fabs(inputSampleR))-1.0) / 255;
			if (inputSampleR < 0) inputSampleR = -(pow(256,fabs(inputSampleR))-1.0) / 255;
			
			inputSampleL = (tempL * hard) + (inputSampleL * (1.0-hard));
			inputSampleR = (tempR * hard) + (inputSampleR * (1.0-hard)); //uLaw decode as part of soft/hard
			
			if (wet !=1.0) {
				inputSampleL = (inputSampleL * wet) + (drySampleL * (1.0-wet));
				inputSampleR = (inputSampleR * wet) + (drySampleR * (1.0-wet));
			}
			//Dry/Wet control, defaults to the last slider
			
			lastSampleL = drySampleL;
			lastSampleR = drySampleR;
			
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
    
	double lastSampleL;
	double heldSampleL;
	double lastDrySampleL;
	double lastOutputSampleL;

	double lastSampleR;
	double heldSampleR;
	double lastDrySampleR;
	double lastOutputSampleR;

	double position;
	double incrementA;
	double incrementB;
	
	uint32_t fpd;
	//default stuff

};
MIN_EXTERNAL(derez2);

