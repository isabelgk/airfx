#include "c74_min.h"

using namespace c74::min;

class aquickvoiceclip : public object<aquickvoiceclip>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"softens headset mic recordings that have been super hard clipped on capture"};
	MIN_TAGS {"filter"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "highpass", 0.42, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.42;
			LataLast6Sample = LataLast5Sample = LataLast4Sample = 0.0;
			LataLast3Sample = LataLast2Sample = LataLast1Sample = 0.0;
			LataHalfwaySample = LataHalfDrySample = LataHalfDiffSample = 0.0;
			LataDrySample = LataDiffSample = LataPrevDiffSample = 0.0;
			
			RataLast6Sample = RataLast5Sample = RataLast4Sample = 0.0;
			RataLast3Sample = RataLast2Sample = RataLast1Sample = 0.0;
			RataHalfwaySample = RataHalfDrySample = RataHalfDiffSample = 0.0;
			RataDrySample = RataDiffSample = RataPrevDiffSample = 0.0;
			
			LlastSample = 0.0;
			LlastOutSample = 0.0;
			LlastOut2Sample = 0.0;
			LlastOut3Sample = 0.0;
			LlpDepth = 0.0;
			Lovershoot = 0.0;
			Loverall = 0;
			LiirSampleA = 0.0;
			LiirSampleB = 0.0;
			LiirSampleC = 0.0;
			LiirSampleD = 0.0;
		
			RlastSample = 0.0;
			RlastOutSample = 0.0;
			RlastOut2Sample = 0.0;
			RlastOut3Sample = 0.0;
			RlpDepth = 0.0;
			Rovershoot = 0.0;
			Roverall = 0;
			RiirSampleA = 0.0;
			RiirSampleB = 0.0;
			RiirSampleC = 0.0;
			RiirSampleD = 0.0;
			flip = true;
			
			ataK1 = -0.646; //first FIR shaping of interpolated sample, brightens
			ataK2 = 0.311; //second FIR shaping of interpolated sample, thickens
			ataK6 = -0.093; //third FIR shaping of interpolated sample, brings air
			ataK7 = 0.057; //fourth FIR shaping of interpolated sample, thickens
			ataK8 = -0.023; //fifth FIR shaping of interpolated sample, brings air
			ataK3 = 0.114; //add raw to interpolated dry, toughens
			ataK4 = 0.886; //remainder of interpolated dry, adds up to 1.0
			ataK5 = 0.431; //subtract this much prev. diff sample, brightens.  0.431 becomes flat
			
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
		double overallscale = 1.0;
		overallscale /= 44100.0;
		overallscale *= samplerate();

		long sampleFrames = _input.frame_count();
		
		double softness = 0.484416;
		double hardness = 1.0 - softness;
		double iirAmount = ((pow(A,3)*2070)+30)/8000.0;
		iirAmount /= overallscale;
		double altAmount = (1.0 - iirAmount);
		double cancelnew = 0.0682276;
		double cancelold = 1.0 - cancelnew;
		double lpSpeed = 0.0009;
		double cliplevel = 0.98;
		double refclip = 0.5; //preset to cut out gain quite a lot. 91%? no touchy unless clip
		
		double LmaxRecent;
		bool LclipOnset;
		double LpassThrough;
		double LoutputSample;
		double LdrySample;
		
		double RmaxRecent;
		bool RclipOnset;
		double RpassThrough;
		double RoutputSample;
		double RdrySample;
		
	
		long double inputSampleL;
		long double inputSampleR;
	
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
			LpassThrough = LataDrySample = inputSampleL;
			RpassThrough = RataDrySample = inputSampleR;
			
			LataHalfDrySample = LataHalfwaySample = (inputSampleL + LataLast1Sample + (LataLast2Sample*ataK1) + (LataLast3Sample*ataK2) + (LataLast4Sample*ataK6) + (LataLast5Sample*ataK7) + (LataLast6Sample*ataK8)) / 2.0;
			LataLast6Sample = LataLast5Sample; LataLast5Sample = LataLast4Sample; LataLast4Sample = LataLast3Sample; LataLast3Sample = LataLast2Sample; LataLast2Sample = LataLast1Sample; LataLast1Sample = inputSampleL;
			//setting up oversampled special antialiasing
			RataHalfDrySample = RataHalfwaySample = (inputSampleR + RataLast1Sample + (RataLast2Sample*ataK1) + (RataLast3Sample*ataK2) + (RataLast4Sample*ataK6) + (RataLast5Sample*ataK7) + (RataLast6Sample*ataK8)) / 2.0;
			RataLast6Sample = RataLast5Sample; RataLast5Sample = RataLast4Sample; RataLast4Sample = RataLast3Sample; RataLast3Sample = RataLast2Sample; RataLast2Sample = RataLast1Sample; RataLast1Sample = inputSampleR;
			//setting up oversampled special antialiasing
			LclipOnset = false;
			RclipOnset = false;
			
			
			LmaxRecent = fabs( LataLast6Sample );
			if (fabs( LataLast5Sample ) > LmaxRecent ) LmaxRecent = fabs( LataLast5Sample );
			if (fabs( LataLast4Sample ) > LmaxRecent ) LmaxRecent = fabs( LataLast4Sample );
			if (fabs( LataLast3Sample ) > LmaxRecent ) LmaxRecent = fabs( LataLast3Sample );
			if (fabs( LataLast2Sample ) > LmaxRecent ) LmaxRecent = fabs( LataLast2Sample );
			if (fabs( LataLast1Sample ) > LmaxRecent ) LmaxRecent = fabs( LataLast1Sample );
			if (fabs( inputSampleL ) > LmaxRecent ) LmaxRecent = fabs( inputSampleL );
			//this gives us something that won't cut out in zero crossings, to interpolate with
			
			RmaxRecent = fabs( RataLast6Sample );
			if (fabs( RataLast5Sample ) > RmaxRecent ) RmaxRecent = fabs( RataLast5Sample );
			if (fabs( RataLast4Sample ) > RmaxRecent ) RmaxRecent = fabs( RataLast4Sample );
			if (fabs( RataLast3Sample ) > RmaxRecent ) RmaxRecent = fabs( RataLast3Sample );
			if (fabs( RataLast2Sample ) > RmaxRecent ) RmaxRecent = fabs( RataLast2Sample );
			if (fabs( RataLast1Sample ) > RmaxRecent ) RmaxRecent = fabs( RataLast1Sample );
			if (fabs( inputSampleR ) > RmaxRecent ) RmaxRecent = fabs( inputSampleR );
			//this gives us something that won't cut out in zero crossings, to interpolate with
			
			LmaxRecent *= 2.0;
			RmaxRecent *= 2.0;
			//by refclip this is 1.0 and fully into the antialiasing
			if (LmaxRecent > 1.0) LmaxRecent = 1.0;
			if (RmaxRecent > 1.0) RmaxRecent = 1.0;
			//and it tops out at 1. Higher means more antialiasing, lower blends into passThrough without antialiasing
			
			LataHalfwaySample -= Loverall;
			RataHalfwaySample -= Roverall;
			//subtract dist-cancel from input after getting raw input, before doing anything
			
			LdrySample = LataHalfwaySample;
			RdrySample = RataHalfwaySample;
			
			
			//begin L channel for the clipper
			if (LlastSample >= refclip)
			{
				LlpDepth += 0.1;
				if (LataHalfwaySample < refclip)
				{
					LlastSample = ((refclip*hardness) + (LataHalfwaySample * softness));
				}
				else LlastSample = refclip;
			}
			
			if (LlastSample <= -refclip)
			{
				LlpDepth += 0.1;
				if (LataHalfwaySample > -refclip)
				{
					LlastSample = ((-refclip*hardness) + (LataHalfwaySample * softness));
				}
				else LlastSample = -refclip;
			}
			
			if (LataHalfwaySample > refclip)
			{
				LlpDepth += 0.1;
				if (LlastSample < refclip)
				{
					LataHalfwaySample = ((refclip*hardness) + (LlastSample * softness));
				}
				else LataHalfwaySample = refclip;
			}
			
			if (LataHalfwaySample < -refclip)
			{
				LlpDepth += 0.1;
				if (LlastSample > -refclip)
				{
					LataHalfwaySample = ((-refclip*hardness) + (LlastSample * softness));
				}
				else LataHalfwaySample = -refclip;
			}
			///end L channel for the clipper
			
			//begin R channel for the clipper
			if (RlastSample >= refclip)
			{
				RlpDepth += 0.1;
				if (RataHalfwaySample < refclip)
				{
					RlastSample = ((refclip*hardness) + (RataHalfwaySample * softness));
				}
				else RlastSample = refclip;
			}
			
			if (RlastSample <= -refclip)
			{
				RlpDepth += 0.1;
				if (RataHalfwaySample > -refclip)
				{
					RlastSample = ((-refclip*hardness) + (RataHalfwaySample * softness));
				}
				else RlastSample = -refclip;
			}
			
			if (RataHalfwaySample > refclip)
			{
				RlpDepth += 0.1;
				if (RlastSample < refclip)
				{
					RataHalfwaySample = ((refclip*hardness) + (RlastSample * softness));
				}
				else RataHalfwaySample = refclip;
			}
			
			if (RataHalfwaySample < -refclip)
			{
				RlpDepth += 0.1;
				if (RlastSample > -refclip)
				{
					RataHalfwaySample = ((-refclip*hardness) + (RlastSample * softness));
				}
				else RataHalfwaySample = -refclip;
			}
			///end R channel for the clipper
			
	        LoutputSample = LlastSample;
	        RoutputSample = RlastSample;
			
			LlastSample = LataHalfwaySample;
			RlastSample = RataHalfwaySample;
			
			LataHalfwaySample = LoutputSample;
			RataHalfwaySample = RoutputSample;
			//swap around in a circle for one final ADClip,
			//this time not tracking overshoot anymore
			//end interpolated sample		
			//begin raw sample- inputSample and ataDrySample handled separately here
			
			inputSampleL -= Loverall;
			inputSampleR -= Roverall;
			//subtract dist-cancel from input after getting raw input, before doing anything
			
			LdrySample = inputSampleL;
			RdrySample = inputSampleR;
			
			//begin second L clip
			if (LlastSample >= refclip)
			{
				LlpDepth += 0.1;
				if (inputSampleL < refclip)
				{
					LlastSample = ((refclip*hardness) + (inputSampleL * softness));
				}
				else LlastSample = refclip;
			}
			
			if (LlastSample <= -refclip)
			{
				LlpDepth += 0.1;
				if (inputSampleL > -refclip)
				{
					LlastSample = ((-refclip*hardness) + (inputSampleL * softness));
				}
				else LlastSample = -refclip;
			}
			
			if (inputSampleL > refclip)
			{
				LlpDepth += 0.1;
				if (LlastSample < refclip)
				{
					inputSampleL = ((refclip*hardness) + (LlastSample * softness));
				}
				else inputSampleL = refclip;
			}
			
			if (inputSampleL < -refclip)
			{
				LlpDepth += 0.1;
				if (LlastSample > -refclip)
				{
					inputSampleL = ((-refclip*hardness) + (LlastSample * softness));
				}
				else inputSampleL = -refclip;
			}		
			//end second L clip
			
			//begin second R clip
			if (RlastSample >= refclip)
			{
				RlpDepth += 0.1;
				if (inputSampleR < refclip)
				{
					RlastSample = ((refclip*hardness) + (inputSampleR * softness));
				}
				else RlastSample = refclip;
			}
			
			if (RlastSample <= -refclip)
			{
				RlpDepth += 0.1;
				if (inputSampleR > -refclip)
				{
					RlastSample = ((-refclip*hardness) + (inputSampleR * softness));
				}
				else RlastSample = -refclip;
			}
			
			if (inputSampleR > refclip)
			{
				RlpDepth += 0.1;
				if (RlastSample < refclip)
				{
					inputSampleR = ((refclip*hardness) + (RlastSample * softness));
				}
				else inputSampleR = refclip;
			}
			
			if (inputSampleR < -refclip)
			{
				RlpDepth += 0.1;
				if (RlastSample > -refclip)
				{
					inputSampleR = ((-refclip*hardness) + (RlastSample * softness));
				}
				else inputSampleR = -refclip;
			}		
			//end second R clip
			
			LoutputSample = LlastSample;
			RoutputSample = RlastSample;
			LlastSample = inputSampleL;
			RlastSample = inputSampleR;
			inputSampleL = LoutputSample;
			inputSampleR = RoutputSample;
			
			LataHalfDrySample = (LataDrySample*ataK3)+(LataHalfDrySample*ataK4);
			LataHalfDiffSample = (LataHalfwaySample - LataHalfDrySample)/2.0;
			LataLastDiffSample = LataDiffSample*ataK5;
			LataDiffSample = (inputSampleL - LataDrySample)/2.0;
			LataDiffSample += LataHalfDiffSample;
			LataDiffSample -= LataLastDiffSample;
			inputSampleL = LataDrySample;
			inputSampleL += LataDiffSample;
			
			RataHalfDrySample = (RataDrySample*ataK3)+(RataHalfDrySample*ataK4);
			RataHalfDiffSample = (RataHalfwaySample - RataHalfDrySample)/2.0;
			RataLastDiffSample = RataDiffSample*ataK5;
			RataDiffSample = (inputSampleR - RataDrySample)/2.0;
			RataDiffSample += RataHalfDiffSample;
			RataDiffSample -= RataLastDiffSample;
			inputSampleR = RataDrySample;
			inputSampleR += RataDiffSample;
			
			Loverall = (Loverall * cancelold) + (LataDiffSample * cancelnew);
			Roverall = (Roverall * cancelold) + (RataDiffSample * cancelnew);
			//apply all the diffs to a lowpassed IIR
			
			
			if (flip)
			{
				LiirSampleA = (LiirSampleA * altAmount) + (inputSampleL * iirAmount);
				inputSampleL -= LiirSampleA;
				LiirSampleC = (LiirSampleC * altAmount) + (LpassThrough * iirAmount);
				LpassThrough -= LiirSampleC;
				
				RiirSampleA = (RiirSampleA * altAmount) + (inputSampleR * iirAmount);
				inputSampleR -= RiirSampleA;
				RiirSampleC = (RiirSampleC * altAmount) + (RpassThrough * iirAmount);
				RpassThrough -= RiirSampleC;
			}
			else
			{
				LiirSampleB = (LiirSampleB * altAmount) + (inputSampleL * iirAmount);
				inputSampleL -= LiirSampleB;
				LiirSampleD = (LiirSampleD * altAmount) + (LpassThrough * iirAmount);
				LpassThrough -= LiirSampleD;
				
				RiirSampleB = (RiirSampleB * altAmount) + (inputSampleR * iirAmount);
				inputSampleR -= RiirSampleB;
				RiirSampleD = (RiirSampleD * altAmount) + (RpassThrough * iirAmount);
				RpassThrough -= RiirSampleD;
			}
			flip = !flip;
			//highpass section 
			
			LlastOut3Sample = LlastOut2Sample;
			LlastOut2Sample = LlastOutSample;
			LlastOutSample = inputSampleL;
			
			RlastOut3Sample = RlastOut2Sample;
			RlastOut2Sample = RlastOutSample;
			RlastOutSample = inputSampleR;
			
			
			LlpDepth -= lpSpeed;
			RlpDepth -= lpSpeed;
			
			if (LlpDepth > 0.0)
			{
				if (LlpDepth > 1.0) LlpDepth = 1.0;
				inputSampleL *= (1.0-LlpDepth);
				inputSampleL += (((LlastOutSample + LlastOut2Sample + LlastOut3Sample) / 3.6)*LlpDepth);
			}
			
			if (RlpDepth > 0.0)
			{
				if (RlpDepth > 1.0) RlpDepth = 1.0;
				inputSampleR *= (1.0-RlpDepth);
				inputSampleR += (((RlastOutSample + RlastOut2Sample + RlastOut3Sample) / 3.6)*RlpDepth);
			}
			
			if (LlpDepth < 0.0) LlpDepth = 0.0;
			if (RlpDepth < 0.0) RlpDepth = 0.0;
			
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
			
			inputSampleL *= (1.0-LmaxRecent);
			inputSampleR *= (1.0-RmaxRecent);
			inputSampleL += (LpassThrough * LmaxRecent);
			inputSampleR += (RpassThrough * RmaxRecent);
			//there's our raw signal, without antialiasing. Brings up low level stuff and softens more when hot
			
			if (inputSampleL > cliplevel) inputSampleL = cliplevel;
			if (inputSampleL < -cliplevel) inputSampleL = -cliplevel;
			if (inputSampleR > cliplevel) inputSampleR = cliplevel;
			if (inputSampleR < -cliplevel) inputSampleR = -cliplevel;
			//final iron bar
					
			
			*out1 = inputSampleL;
			*out2 = inputSampleR;
	
			*in1++;
			*in2++;
			*out1++;
			*out2++;
		}
	}
private:
    
	
	double LataLast6Sample;
	double LataLast5Sample;
	double LataLast4Sample;
	double LataLast3Sample;
	double LataLast2Sample;
	double LataLast1Sample;
	double LataHalfwaySample;
	double LataHalfDrySample;
	double LataHalfDiffSample;
	double LataLastDiffSample;
	double LataDrySample;
	double LataDiffSample;
	double LataPrevDiffSample;
	
	double RataLast6Sample;
	double RataLast5Sample;
	double RataLast4Sample;
	double RataLast3Sample;
	double RataLast2Sample;
	double RataLast1Sample;
	double RataHalfwaySample;
	double RataHalfDrySample;
	double RataHalfDiffSample;
	double RataLastDiffSample;
	double RataDrySample;
	double RataDiffSample;
	double RataPrevDiffSample;
	
	double ataK1;
	double ataK2;
	double ataK3;
	double ataK4;
	double ataK5;
	double ataK6;
	double ataK7;
	double ataK8; //end antialiasing variables

	double LlastSample;
	double LlastOutSample;
	double LlastOut2Sample;
	double LlastOut3Sample;
	double LlpDepth;
	double Lovershoot;
	double Loverall;
	double LiirSampleA;
	double LiirSampleB;
	double LiirSampleC;
	double LiirSampleD;

	double RlastSample;
	double RlastOutSample;
	double RlastOut2Sample;
	double RlastOut3Sample;
	double RlpDepth;
	double Rovershoot;
	double Roverall;
	double RiirSampleA;
	double RiirSampleB;
	double RiirSampleC;
	double RiirSampleD;
	bool flip;
		
	long double fpNShapeL;
	long double fpNShapeR;
	//default stuff

};
MIN_EXTERNAL(aquickvoiceclip);

