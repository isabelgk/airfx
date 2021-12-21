#include "c74_min.h"

using namespace c74::min;

class air : public object<air>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"add air to your mix"};
	MIN_TAGS {"eq"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<>  in1 {this, "(signal) Input 1"};
	inlet<>  in2 {this, "(signal) Input 2"};
	outlet<> out1 {this, "(signal) Left Output", "signal"};
	outlet<> out2 {this, "(signal) Right Output", "signal"};
    
    
    attribute<number, threadsafe::no, limit::clamp> A { this, "hightap", 0.5, range {0.0, 1.0} };
    attribute<number, threadsafe::no, limit::clamp> B { this, "midtap", 0.5, range {0.0, 1.0} };
    attribute<number, threadsafe::no, limit::clamp> C { this, "lowtap", 0.5, range {0.0, 1.0} };
    attribute<number, threadsafe::no, limit::clamp> D { this, "filterq", 0.0, range {0.0, 1.0} };
    attribute<number, threadsafe::no, limit::clamp> E { this, "output", 1.0, range {0.0, 1.0} };
    attribute<number, threadsafe::no, limit::clamp> F { this, "mix", 1.0, range {0.0, 1.0} };


    message<> dspsetup {this, "dspsetup",   
        MIN_FUNCTION {
            airPrevAL      = 0.0;
            airEvenAL      = 0.0;
            airOddAL       = 0.0;
            airFactorAL    = 0.0;
            airPrevBL      = 0.0;
            airEvenBL      = 0.0;
            airOddBL       = 0.0;
            airFactorBL    = 0.0;
            airPrevCL      = 0.0;
            airEvenCL      = 0.0;
            airOddCL       = 0.0;
            airFactorCL    = 0.0;
            tripletPrevL   = 0.0;
            tripletMidL    = 0.0;
            tripletAL      = 0.0;
            tripletBL      = 0.0;
            tripletCL      = 0.0;
            tripletFactorL = 0.0;

            airPrevAR      = 0.0;
            airEvenAR      = 0.0;
            airOddAR       = 0.0;
            airFactorAR    = 0.0;
            airPrevBR      = 0.0;
            airEvenBR      = 0.0;
            airOddBR       = 0.0;
            airFactorBR    = 0.0;
            airPrevCR      = 0.0;
            airEvenCR      = 0.0;
            airOddCR       = 0.0;
            airFactorCR    = 0.0;
            tripletPrevR   = 0.0;
            tripletMidR    = 0.0;
            tripletAR      = 0.0;
            tripletBR      = 0.0;
            tripletCR      = 0.0;
            tripletFactorR = 0.0;

            flipA = false;
            flipB = false;
            flop  = false;
            count = 1;


            fpNShapeL = 0.0;
            fpNShapeR = 0.0;
           return {};
       }
    };

	void operator()(audio_bundle input, audio_bundle output) {
		double* in1  = input.samples(0);
		double* in2  = input.samples(1);
		double* out1 = output.samples(0);
		double* out2 = output.samples(1);

		double hiIntensity      = -pow(((A * 2.0) - 1.0), 3) * 2;
		double tripletintensity = -pow(((B * 2.0) - 1.0), 3);
		double airIntensity     = -pow(((C * 2.0) - 1.0), 3) / 2;
		double filterQ          = 2.1 - D;
		double _output           = E;
		double wet              = F;
		double dry              = 1.0 - wet;


		long double inputSampleL;
		long double inputSampleR;
		double      drySampleL;
		double      drySampleR;
		double      correctionL;
		double      correctionR;

        long sampleFrames = input.frame_count();

		while (--sampleFrames >= 0) {
			inputSampleL = *in1;
			inputSampleR = *in2;
			if (inputSampleL < 1.2e-38 && -inputSampleL < 1.2e-38) {
				static int noisesource = 0;
				// this declares a variable before anything else is compiled. It won't keep assigning
				// it to 0 for every sample, it's as if the declaration doesn't exist in this context,
				// but it lets me add this denormalization fix in a single place rather than updating
				// it in three different locations. The variable isn't thread-safe but this is only
				// a random seed and we can share it with whatever.
				noisesource = noisesource % 1700021;
				noisesource++;
				int residue = noisesource * noisesource;
				residue     = residue % 170003;
				residue *= residue;
				residue = residue % 17011;
				residue *= residue;
				residue = residue % 1709;
				residue *= residue;
				residue = residue % 173;
				residue *= residue;
				residue             = residue % 17;
				double applyresidue = residue;
				applyresidue *= 0.00000001;
				applyresidue *= 0.00000001;
				inputSampleL = applyresidue;
			}
			if (inputSampleR < 1.2e-38 && -inputSampleR < 1.2e-38) {
				static int noisesource = 0;
				noisesource            = noisesource % 1700021;
				noisesource++;
				int residue = noisesource * noisesource;
				residue     = residue % 170003;
				residue *= residue;
				residue = residue % 17011;
				residue *= residue;
				residue = residue % 1709;
				residue *= residue;
				residue = residue % 173;
				residue *= residue;
				residue             = residue % 17;
				double applyresidue = residue;
				applyresidue *= 0.00000001;
				applyresidue *= 0.00000001;
				inputSampleR = applyresidue;
				// this denormalization routine produces a white noise at -300 dB which the noise
				// shaping will interact with to produce a bipolar output, but the noise is actually
				// all positive. That should stop any variables from going denormal, and the routine
				// only kicks in if digital black is input. As a final touch, if you save to 24-bit
				// the silence will return to being digital black again.
			}
			drySampleL = inputSampleL;
			drySampleR = inputSampleR;

			correctionL = 0.0;
			correctionR = 0.0;    // from here on down, please add L and R to the code

			if (count < 1 || count > 3)
				count = 1;
			tripletFactorL = tripletPrevL - inputSampleL;
			tripletFactorR = tripletPrevR - inputSampleR;
			switch (count) {
				case 1:
					tripletAL += tripletFactorL;
					tripletCL -= tripletFactorL;
					tripletFactorL = tripletAL * tripletintensity;
					tripletPrevL   = tripletMidL;
					tripletMidL    = inputSampleL;

					tripletAR += tripletFactorR;
					tripletCR -= tripletFactorR;
					tripletFactorR = tripletAR * tripletintensity;
					tripletPrevR   = tripletMidR;
					tripletMidR    = inputSampleR;
					break;
				case 2:
					tripletBL += tripletFactorL;
					tripletAL -= tripletFactorL;
					tripletFactorL = tripletBL * tripletintensity;
					tripletPrevL   = tripletMidL;
					tripletMidL    = inputSampleL;

					tripletBR += tripletFactorR;
					tripletAR -= tripletFactorR;
					tripletFactorR = tripletBR * tripletintensity;
					tripletPrevR   = tripletMidR;
					tripletMidR    = inputSampleR;
					break;
				case 3:
					tripletCL += tripletFactorL;
					tripletBL -= tripletFactorL;
					tripletFactorL = tripletCL * tripletintensity;
					tripletPrevL   = tripletMidL;
					tripletMidL    = inputSampleL;

					tripletCR += tripletFactorR;
					tripletBR -= tripletFactorR;
					tripletFactorR = tripletCR * tripletintensity;
					tripletPrevR   = tripletMidR;
					tripletMidR    = inputSampleR;
					break;
			}
			tripletAL /= filterQ;
			tripletBL /= filterQ;
			tripletCL /= filterQ;
			correctionL = correctionL + tripletFactorL;

			tripletAR /= filterQ;
			tripletBR /= filterQ;
			tripletCR /= filterQ;
			correctionR = correctionR + tripletFactorR;

			count++;
			// finished Triplet section- 15K

			if (flop) {
				airFactorAL = airPrevAL - inputSampleL;
				airFactorAR = airPrevAR - inputSampleR;
				if (flipA) {
					airEvenAL += airFactorAL;
					airOddAL -= airFactorAL;
					airFactorAL = airEvenAL * airIntensity;

					airEvenAR += airFactorAR;
					airOddAR -= airFactorAR;
					airFactorAR = airEvenAR * airIntensity;
				}
				else {
					airOddAL += airFactorAL;
					airEvenAL -= airFactorAL;
					airFactorAL = airOddAL * airIntensity;

					airOddAR += airFactorAR;
					airEvenAR -= airFactorAR;
					airFactorAR = airOddAR * airIntensity;
				}
				airOddAL    = (airOddAL - ((airOddAL - airEvenAL) / 256.0)) / filterQ;
				airEvenAL   = (airEvenAL - ((airEvenAL - airOddAL) / 256.0)) / filterQ;
				airPrevAL   = inputSampleL;
				correctionL = correctionL + airFactorAL;

				airOddAR    = (airOddAR - ((airOddAR - airEvenAR) / 256.0)) / filterQ;
				airEvenAR   = (airEvenAR - ((airEvenAR - airOddAR) / 256.0)) / filterQ;
				airPrevAR   = inputSampleR;
				correctionR = correctionR + airFactorAR;

				flipA = !flipA;
			}
			else {
				airFactorBL = airPrevBL - inputSampleL;
				airFactorBR = airPrevBR - inputSampleR;
				if (flipB) {
					airEvenBL += airFactorBL;
					airOddBL -= airFactorBL;
					airFactorBL = airEvenBL * airIntensity;

					airEvenBR += airFactorBR;
					airOddBR -= airFactorBR;
					airFactorBR = airEvenBR * airIntensity;
				}
				else {
					airOddBL += airFactorBL;
					airEvenBL -= airFactorBL;
					airFactorBL = airOddBL * airIntensity;

					airOddBR += airFactorBR;
					airEvenBR -= airFactorBR;
					airFactorBR = airOddBR * airIntensity;
				}
				airOddBL    = (airOddBL - ((airOddBL - airEvenBL) / 256.0)) / filterQ;
				airEvenBL   = (airEvenBL - ((airEvenBL - airOddBL) / 256.0)) / filterQ;
				airPrevBL   = inputSampleL;
				correctionL = correctionL + airFactorBL;

				airOddBR    = (airOddBR - ((airOddBR - airEvenBR) / 256.0)) / filterQ;
				airEvenBR   = (airEvenBR - ((airEvenBR - airOddBR) / 256.0)) / filterQ;
				airPrevBR   = inputSampleR;
				correctionR = correctionR + airFactorBR;

				flipB = !flipB;
			}
			// 11K one
			airFactorCL = airPrevCL - inputSampleL;
			airFactorCR = airPrevCR - inputSampleR;
			if (flop) {
				airEvenCL += airFactorCL;
				airOddCL -= airFactorCL;
				airFactorCL = airEvenCL * hiIntensity;

				airEvenCR += airFactorCR;
				airOddCR -= airFactorCR;
				airFactorCR = airEvenCR * hiIntensity;
			}
			else {
				airOddCL += airFactorCL;
				airEvenCL -= airFactorCL;
				airFactorCL = airOddCL * hiIntensity;

				airOddCR += airFactorCR;
				airEvenCR -= airFactorCR;
				airFactorCR = airOddCR * hiIntensity;
			}
			airOddCL    = (airOddCL - ((airOddCL - airEvenCL) / 256.0)) / filterQ;
			airEvenCL   = (airEvenCL - ((airEvenCL - airOddCL) / 256.0)) / filterQ;
			airPrevCL   = inputSampleL;
			correctionL = correctionL + airFactorCL;

			airOddCR    = (airOddCR - ((airOddCR - airEvenCR) / 256.0)) / filterQ;
			airEvenCR   = (airEvenCR - ((airEvenCR - airOddCR) / 256.0)) / filterQ;
			airPrevCR   = inputSampleR;
			correctionR = correctionR + airFactorCR;

			flop = !flop;

			inputSampleL += correctionL;
			inputSampleR += correctionR;

			if (_output < 1.0) {
				inputSampleL *= _output;
				inputSampleR *= _output;
			}
			if (wet < 1.0) {
				inputSampleL = (drySampleL * dry) + (inputSampleL * wet);
				inputSampleR = (drySampleR * dry) + (inputSampleR * wet);
			}
			// nice little output stage template: if we have another scale of floating point
			// number, we really don't want to meaninglessly multiply that by 1.0.

			// stereo 64 bit dither, made small and tidy.
			int expon;
			frexp((double)inputSampleL, &expon);
			long double dither = (rand() / (RAND_MAX * 7.737125245533627e+25)) * pow(2, expon + 62);
			dither /= 536870912.0;    // needs this to scale to 64 bit zone
			inputSampleL += (dither - fpNShapeL);
			fpNShapeL = dither;
			frexp((double)inputSampleR, &expon);
			dither = (rand() / (RAND_MAX * 7.737125245533627e+25)) * pow(2, expon + 62);
			dither /= 536870912.0;    // needs this to scale to 64 bit zone
			inputSampleR += (dither - fpNShapeR);
			fpNShapeR = dither;
			// end 64 bit dither

			*out1 = inputSampleL;
			*out2 = inputSampleR;

			*in1++;
			*in2++;
			*out1++;
			*out2++;
		}
	}

private:
	double airPrevAL;
	double airEvenAL;
	double airOddAL;
	double airFactorAL;
	double airPrevBL;
	double airEvenBL;
	double airOddBL;
	double airFactorBL;
	double airPrevCL;
	double airEvenCL;
	double airOddCL;
	double airFactorCL;
	double tripletPrevL;
	double tripletMidL;
	double tripletAL;
	double tripletBL;
	double tripletCL;
	double tripletFactorL;

	double airPrevAR;
	double airEvenAR;
	double airOddAR;
	double airFactorAR;
	double airPrevBR;
	double airEvenBR;
	double airOddBR;
	double airFactorBR;
	double airPrevCR;
	double airEvenCR;
	double airOddCR;
	double airFactorCR;
	double tripletPrevR;
	double tripletMidR;
	double tripletAR;
	double tripletBR;
	double tripletCR;
	double tripletFactorR;

	bool flipA;
	bool flipB;
	bool flop;
	int  count;

	long double fpNShapeL;
	long double fpNShapeR;
	// default stuff
};

MIN_EXTERNAL(air);
