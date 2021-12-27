#include "c74_min.h"

using namespace c74::min;

class slew2 : public object<slew2>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"works like a de-esser or acceleration limiter: controls extreme highs"};
	MIN_TAGS {"deess"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "clamping", 0.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.0;
		
			LataLast3Sample = LataLast2Sample = LataLast1Sample = 0.0;
			LataHalfwaySample = LataHalfDrySample = LataHalfDiffSample = 0.0;
			LataA = LataB = LataC = LataDrySample = LataDiffSample = LataPrevDiffSample = 0.0;
			LataUpsampleHighTweak = 0.0414213562373095048801688; //more adds treble to upsampling
			LataDecay = 0.915965594177219015; //Catalan's constant, more adds focus and clarity
			lastSampleL = 0.0;
		
			RataLast3Sample = RataLast2Sample = RataLast1Sample = 0.0;
			RataHalfwaySample = RataHalfDrySample = RataHalfDiffSample = 0.0;
			RataA = RataB = RataC = RataDrySample = RataDiffSample = RataPrevDiffSample = 0.0;
			RataUpsampleHighTweak = 0.0414213562373095048801688; //more adds treble to upsampling
			RataDecay = 0.915965594177219015; //CRatalan's constant, more adds focus and clarity
			LataFlip = false; //end reset of antialias parameters
			RataFlip = false; //end reset of antialias parameters
			lastSampleR = 0.0;
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

		double overallscale = 2.0;
		overallscale /= 44100.0;
		overallscale *= samplerate();
		double clamp;
		double threshold = pow((1-A),4)/overallscale;
		double inputSampleL;
		double inputSampleR;
	
	    while (--sampleFrames >= 0)
	    {
			inputSampleL = *in1;
			inputSampleR = *in2;
			if (inputSampleL<1.2e-38 && -inputSampleL<1.2e-38) {
				static int noisesource = 0;
				//this declares a variable before anything else is compiled. It won't keep assigning
				//it to 0 for every sample, it's as if the declaration doesn't exist in this context,
				//but it lets me add this denormalization fix in a single place rather than updating
				//it in three different locations. The variable isn't thread-safe but this is only
				//a random seed and we can share it with whatever.
				noisesource = noisesource % 1700021; noisesource++;
				int residue = noisesource * noisesource;
				residue = residue % 170003; residue *= residue;
				residue = residue % 17011; residue *= residue;
				residue = residue % 1709; residue *= residue;
				residue = residue % 173; residue *= residue;
				residue = residue % 17;
				double applyresidue = residue;
				applyresidue *= 0.00000001;
				applyresidue *= 0.00000001;
				inputSampleL = applyresidue;
			}
			if (inputSampleR<1.2e-38 && -inputSampleR<1.2e-38) {
				static int noisesource = 0;
				noisesource = noisesource % 1700021; noisesource++;
				int residue = noisesource * noisesource;
				residue = residue % 170003; residue *= residue;
				residue = residue % 17011; residue *= residue;
				residue = residue % 1709; residue *= residue;
				residue = residue % 173; residue *= residue;
				residue = residue % 17;
				double applyresidue = residue;
				applyresidue *= 0.00000001;
				applyresidue *= 0.00000001;
				inputSampleR = applyresidue;
				//this denormalization routine produces a white noise at -300 dB which the noise
				//shaping will interact with to produce a bipolar output, but the noise is actually
				//all positive. That should stop any variables from going denormal, and the routine
				//only kicks in if digital black is input. As a final touch, if you save to 24-bit
				//the silence will return to being digital black again.
			}
			
			LataDrySample = inputSampleL;
			RataDrySample = inputSampleR;
			
			LataHalfDrySample = LataHalfwaySample = (inputSampleL + LataLast1Sample + ((-LataLast2Sample + LataLast3Sample) * LataUpsampleHighTweak)) / 2.0;
			LataLast3Sample = LataLast2Sample; LataLast2Sample = LataLast1Sample; LataLast1Sample = inputSampleL;
			//setting up oversampled special antialiasing
			//begin first half- change inputSample -> LataHalfwaySample, LataDrySample -> LataHalfDrySample
			clamp = LataHalfwaySample - LataHalfDrySample;
			if (clamp > threshold)
				LataHalfwaySample = lastSampleL + threshold;
			if (-clamp > threshold)
				LataHalfwaySample = lastSampleL - threshold;
			lastSampleL = LataHalfwaySample;
			//end first half
			//begin antialiasing section for halfway sample
			LataC = LataHalfwaySample - LataHalfDrySample;
			if (LataFlip) {LataA *= LataDecay; LataB *= LataDecay; LataA += LataC; LataB -= LataC; LataC = LataA;}
			else {LataB *= LataDecay; LataA *= LataDecay; LataB += LataC; LataA -= LataC; LataC = LataB;}
			LataHalfDiffSample = (LataC * LataDecay); LataFlip = !LataFlip;
			//end antialiasing section for halfway sample
			//begin second half- inputSample and LataDrySample handled separately here
			clamp = inputSampleL - lastSampleL;
			if (clamp > threshold)
				inputSampleL = lastSampleL + threshold;
			if (-clamp > threshold)
				inputSampleL = lastSampleL - threshold;
			lastSampleL = inputSampleL;
			//end second half
			//begin antialiasing section for input sample
			LataC = inputSampleL - LataDrySample;
			if (LataFlip) {LataA *= LataDecay; LataB *= LataDecay; LataA += LataC; LataB -= LataC; LataC = LataA;}
			else {LataB *= LataDecay; LataA *= LataDecay; LataB += LataC; LataA -= LataC; LataC = LataB;}
			LataDiffSample = (LataC * LataDecay); LataFlip = !LataFlip;
			//end antialiasing section for input sample
			inputSampleL = LataDrySample; inputSampleL += ((LataDiffSample + LataHalfDiffSample + LataPrevDiffSample) / 0.734);
			LataPrevDiffSample = LataDiffSample / 2.0;
			//apply processing as difference to non-oversampled raw input
			
			
			
			
			RataHalfDrySample = RataHalfwaySample = (inputSampleR + RataLast1Sample + ((-RataLast2Sample + RataLast3Sample) * RataUpsampleHighTweak)) / 2.0;
			RataLast3Sample = RataLast2Sample; RataLast2Sample = RataLast1Sample; RataLast1Sample = inputSampleR;
			//setting up oversampled special antialiasing
			//begin first half- change inputSample -> RataHalfwaySample, RataDrySample -> RataHalfDrySample
			clamp = RataHalfwaySample - RataHalfDrySample;
			if (clamp > threshold)
				RataHalfwaySample = lastSampleR + threshold;
			if (-clamp > threshold)
				RataHalfwaySample = lastSampleR - threshold;
			lastSampleR = RataHalfwaySample;
			//end first half
			//begin antialiasing section for halfway sample
			RataC = RataHalfwaySample - RataHalfDrySample;
			if (RataFlip) {RataA *= RataDecay; RataB *= RataDecay; RataA += RataC; RataB -= RataC; RataC = RataA;}
			else {RataB *= RataDecay; RataA *= RataDecay; RataB += RataC; RataA -= RataC; RataC = RataB;}
			RataHalfDiffSample = (RataC * RataDecay); RataFlip = !RataFlip;
			//end antialiasing section for halfway sample
			//begin second half- inputSample and RataDrySample handled separately here
			clamp = inputSampleR - lastSampleR;
			if (clamp > threshold)
				inputSampleR = lastSampleR + threshold;
			if (-clamp > threshold)
				inputSampleR = lastSampleR - threshold;
			lastSampleR = inputSampleR;
			//end second half
			//begin antialiasing section for input sample
			RataC = inputSampleR - RataDrySample;
			if (RataFlip) {RataA *= RataDecay; RataB *= RataDecay; RataA += RataC; RataB -= RataC; RataC = RataA;}
			else {RataB *= RataDecay; RataA *= RataDecay; RataB += RataC; RataA -= RataC; RataC = RataB;}
			RataDiffSample = (RataC * RataDecay); RataFlip = !RataFlip;
			//end antialiasing section for input sample
			inputSampleR = RataDrySample; inputSampleR += ((RataDiffSample + RataHalfDiffSample + RataPrevDiffSample) / 0.734);
			RataPrevDiffSample = RataDiffSample / 2.0;
			//apply processing as difference to non-oversampled raw input
			
			*out1 = inputSampleL;
			*out2 = inputSampleR;
	
			*in1++;
			*in2++;
			*out1++;
			*out2++;
		}
	}
private:
    
	double LataLast3Sample;
	double LataLast2Sample;
	double LataLast1Sample;
	double LataHalfwaySample;
	double LataHalfDrySample;
	double LataHalfDiffSample;
	double LataA;
	double LataB;
	double LataC;
	double LataDecay;
	double LataUpsampleHighTweak;
	double LataDrySample;
	double LataDiffSample;
	double LataPrevDiffSample;
	
	double RataLast3Sample;
	double RataLast2Sample;
	double RataLast1Sample;
	double RataHalfwaySample;
	double RataHalfDrySample;
	double RataHalfDiffSample;
	double RataA;
	double RataB;
	double RataC;
	double RataDecay;
	double RataUpsampleHighTweak;
	double RataDrySample;
	double RataDiffSample;
	double RataPrevDiffSample;
	
	bool LataFlip; //end defining of antialiasing variables
	bool RataFlip; //end defining of antialiasing variables

	double lastSampleL;
	double lastSampleR;
	
};
MIN_EXTERNAL(slew2);

