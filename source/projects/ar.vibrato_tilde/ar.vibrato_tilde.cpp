#include "c74_min.h"

using namespace c74::min;

class vibrato : public object<vibrato>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"vibrato, chorus, flange, and make odd FM noises"};
	MIN_TAGS {"vibrato, chorus"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "speed", 0.3, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "depth", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "fmspeed", 0.4, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "fmdepth", 0.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> E {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.3;
			B = 0.0;
			C = 0.4;
			D = 0.0;
			E = 1.0;
			
			for(int count = 0; count < 16385; count++) {pL[count] = 0.0; pR[count] = 0.0;}
			sweep = 3.141592653589793238 / 2.0;
			sweepB = 3.141592653589793238 / 2.0;
			gcount = 0;
			
			airPrevL = 0.0;
			airEvenL = 0.0;
			airOddL = 0.0;
			airFactorL = 0.0;
			airPrevR = 0.0;
			airEvenR = 0.0;
			airOddR = 0.0;
			airFactorR = 0.0;
			
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
		long sampleFrames = _input.frame_count();

		double speed = pow(0.1+A,6);
		double depth = (pow(B,3) / sqrt(speed))*4.0;
		double speedB = pow(0.1+C,6);
		double depthB = pow(D,3) / sqrt(speedB);
		double tupi = 3.141592653589793238 * 2.0;
		double wet = (E*2.0)-1.0; //note: inv/dry/wet
	    
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpd * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpd * 1.18e-43;
			double drySampleL = inputSampleL;
			double drySampleR = inputSampleR;
			
			airFactorL = airPrevL - inputSampleL;
			airFactorR = airPrevR - inputSampleR;
			
			if (flip) {
				airEvenL += airFactorL; airOddL -= airFactorL; airFactorL = airEvenL;
				airEvenR += airFactorR; airOddR -= airFactorR; airFactorR = airEvenR;
			} else {
				airOddL += airFactorL; airEvenL -= airFactorL; airFactorL = airOddL;
				airOddR += airFactorR; airEvenR -= airFactorR; airFactorR = airOddR;
			}
			
			airOddL = (airOddL - ((airOddL - airEvenL)/256.0)) / 1.0001;
			airOddR = (airOddR - ((airOddR - airEvenR)/256.0)) / 1.0001;
			airEvenL = (airEvenL - ((airEvenL - airOddL)/256.0)) / 1.0001;
			airEvenR = (airEvenR - ((airEvenR - airOddR)/256.0)) / 1.0001;
			airPrevL = inputSampleL;
			airPrevR = inputSampleR;
			inputSampleL += airFactorL;
			inputSampleR += airFactorR;
			
			flip = !flip;
			//air, compensates for loss of highs in the interpolation
			
			if (gcount < 1 || gcount > 8192) {gcount = 8192;}
			int count = gcount;
			pL[count+8192] = pL[count] = inputSampleL;
			pR[count+8192] = pR[count] = inputSampleR;
			
			double offset = depth + (depth * sin(sweep));
			count += (int)floor(offset);
			
			inputSampleL = pL[count] * (1.0-(offset-floor(offset))); //less as value moves away from .0
			inputSampleL += pL[count+1]; //we can assume always using this in one way or another?
			inputSampleL += pL[count+2] * (offset-floor(offset)); //greater as value moves away from .0
			inputSampleL -= ((pL[count]-pL[count+1])-(pL[count+1]-pL[count+2]))/50.0; //interpolation hacks 'r us
			inputSampleL *= 0.5; // gain trim
			
			inputSampleR = pR[count] * (1.0-(offset-floor(offset))); //less as value moves away from .0
			inputSampleR += pR[count+1]; //we can assume always using this in one way or another?
			inputSampleR += pR[count+2] * (offset-floor(offset)); //greater as value moves away from .0
			inputSampleR -= ((pR[count]-pR[count+1])-(pR[count+1]-pR[count+2]))/50.0; //interpolation hacks 'r us
			inputSampleR *= 0.5; // gain trim
			
			sweep += (speed + (speedB * sin(sweepB) * depthB));
			sweepB += speedB;
			if (sweep > tupi){sweep -= tupi;}
			if (sweep < 0.0){sweep += tupi;} //through zero FM
			if (sweepB > tupi){sweepB -= tupi;}
			gcount--;
			//still scrolling through the samples, remember
			
			if (wet !=1.0) {
				inputSampleL = (inputSampleL * wet) + (drySampleL * (1.0-fabs(wet)));
				inputSampleR = (inputSampleR * wet) + (drySampleR * (1.0-fabs(wet)));
			}
			//Inv/Dry/Wet control
			
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
    
	double pL[16386]; //this is processed, not raw incoming samples
	double pR[16386]; //this is processed, not raw incoming samples
	double sweep;
	double sweepB;
	int gcount;
	
	double airPrevL;
	double airEvenL;
	double airOddL;
	double airFactorL;
	double airPrevR;
	double airEvenR;
	double airOddR;
	double airFactorR;

	bool flip;
	uint32_t fpd;
	//default stuff

};
MIN_EXTERNAL(vibrato);

