#include "c74_min.h"

using namespace c74::min;

class adt : public object<adt>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"double short delay tap with saturation"};
	MIN_TAGS {"delay, saturation"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "headroom", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "adelay", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "alevel", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "bdelay", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> E {this, "blevel", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> F {this, "output", 0.5, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			for(int count = 0; count < 9999; count++) {pL[count] = 0; pR[count] = 0;}
			offsetA = 9001;
			offsetB = 9001;  //  :D
			gcount = 0;	
			
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

		double gain = A * 1.272;
		double targetA = pow(B,4) * 4790.0;
		double fractionA;
		double minusA;
		double intensityA = C-0.5;
		//first delay
		double targetB = (pow(D,4) * 4790.0);
		double fractionB;
		double minusB;
		double intensityB = E-0.5;
		//second delay
		double output = F*2.0;
		
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
	
			if (fabs(inputSampleL)<1.18e-43) inputSampleL = fpd * 1.18e-43;
			if (fabs(inputSampleR)<1.18e-43) inputSampleR = fpd * 1.18e-43;
	
			
			if (fabs(offsetA - targetA) > 1000) offsetA = targetA;
			offsetA = ((offsetA*999.0)+targetA)/1000.0;
			fractionA = offsetA - floor(offsetA);
			minusA = 1.0 - fractionA;
			
			if (fabs(offsetB - targetB) > 1000) offsetB = targetB;
			offsetB = ((offsetB*999.0)+targetB)/1000.0;
			fractionB = offsetB - floor(offsetB);
			minusB = 1.0 - fractionB;
			//chase delay taps for smooth action
			
			if (gain > 0) {inputSampleL /= gain; inputSampleR /= gain;}
			
			if (inputSampleL > 1.2533141373155) inputSampleL = 1.2533141373155;
			if (inputSampleL < -1.2533141373155) inputSampleL = -1.2533141373155;
			if (inputSampleR > 1.2533141373155) inputSampleR = 1.2533141373155;
			if (inputSampleR < -1.2533141373155) inputSampleR = -1.2533141373155;
			
			inputSampleL = sin(inputSampleL * fabs(inputSampleL)) / ((fabs(inputSampleL) == 0.0) ?1:fabs(inputSampleL));
			inputSampleR = sin(inputSampleR * fabs(inputSampleR)) / ((fabs(inputSampleR) == 0.0) ?1:fabs(inputSampleR));
			//Spiral: lean out the sound a little when decoded by ConsoleBuss
			
			if (gcount < 1 || gcount > 4800) {gcount = 4800;}
			int count = gcount;
			double totalL = 0.0;
			double totalR = 0.0;
			double tempL;
			double tempR;
			pL[count+4800] = pL[count] = inputSampleL;
			pR[count+4800] = pR[count] = inputSampleR;
			//double buffer
			
			if (intensityA != 0.0)
			{
				count = (int)(gcount+floor(offsetA));
				
				tempL = (pL[count] * minusA); //less as value moves away from .0
				tempL += pL[count+1]; //we can assume always using this in one way or another?
				tempL += (pL[count+2] * fractionA); //greater as value moves away from .0
				tempL -= (((pL[count]-pL[count+1])-(pL[count+1]-pL[count+2]))/50); //interpolation hacks 'r us
				totalL += (tempL * intensityA);
				
				tempR = (pR[count] * minusA); //less as value moves away from .0
				tempR += pR[count+1]; //we can assume always using this in one way or another?
				tempR += (pR[count+2] * fractionA); //greater as value moves away from .0
				tempR -= (((pR[count]-pR[count+1])-(pR[count+1]-pR[count+2]))/50); //interpolation hacks 'r us
				totalR += (tempR * intensityA);
			}
			
			if (intensityB != 0.0)
			{
				count = (int)(gcount+floor(offsetB));
				
				tempL = (pL[count] * minusB); //less as value moves away from .0
				tempL += pL[count+1]; //we can assume always using this in one way or another?
				tempL += (pL[count+2] * fractionB); //greater as value moves away from .0
				tempL -= (((pL[count]-pL[count+1])-(pL[count+1]-pL[count+2]))/50); //interpolation hacks 'r us
				totalL += (tempL * intensityB);
				
				tempR = (pR[count] * minusB); //less as value moves away from .0
				tempR += pR[count+1]; //we can assume always using this in one way or another?
				tempR += (pR[count+2] * fractionB); //greater as value moves away from .0
				tempR -= (((pR[count]-pR[count+1])-(pR[count+1]-pR[count+2]))/50); //interpolation hacks 'r us
				totalR += (tempR * intensityB);
			}
			
			gcount--;
			//still scrolling through the samples, remember
			
			inputSampleL += totalL;
			inputSampleR += totalR;
			
			if (inputSampleL > 1.0) inputSampleL = 1.0;
			if (inputSampleL < -1.0) inputSampleL = -1.0;
			if (inputSampleR > 1.0) inputSampleR = 1.0;
			if (inputSampleR < -1.0) inputSampleR = -1.0;
			//without this, you can get a NaN condition where it spits out DC offset at full blast!
			
			inputSampleL = asin(inputSampleL);
			inputSampleR = asin(inputSampleR);
			//amplitude aspect
			
			inputSampleL *= gain;
			inputSampleR *= gain;
			
			if (output < 1.0) {inputSampleL *= output; inputSampleR *= output;}
			
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
    
	double pL[10000];
	double pR[10000];
	int gcount;
	double offsetA;
	double offsetB;
	
	
		uint32_t fpd;
	//default stuff

};
MIN_EXTERNAL(adt);

