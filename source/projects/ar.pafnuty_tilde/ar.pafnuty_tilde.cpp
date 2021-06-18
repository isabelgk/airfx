#include "c74_min.h"

using namespace c74::min;

class pafnuty : public object<pafnuty>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a Chebyshev filter that adds harmonics"};
	MIN_TAGS {"audio, effect"};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "Second", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "Third", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "Fourth", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> D {this, "Fifth", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> E {this, "Sixth", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> F {this, "Seventh", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> G {this, "Eighth", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> H {this, "Ninth", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> I {this, "Tenth", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> J {this, "Elevnth", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> K {this, "Twelvth", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> L {this, "Thirtnh", 0.5, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> M {this, "Inv/Wet", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			A = 0.5;
			B = 0.5;
			C = 0.5;
			D = 0.5;
			E = 0.5;
			F = 0.5;
			G = 0.5;
			H = 0.5;
			I = 0.5;
			J = 0.5;
			K = 0.5;
			L = 0.5;
			M = 1.0;
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

		long double chebyshev;
		long double effxct; //this highlighted when spelled 'effect', might be a reserved word for VST
		long double inP2;
		long double inP3;
		long double inP4;
		long double inP5;
		long double inP6;
		long double inP7;
		long double inP8;
		long double inP9;
		long double inP10;
		long double inP11;
		long double inP12;
		long double inP13;
		long double second = (((A*2.0)-1.0)*1.0);
		second = second * fabs(second);
		long double third = -(((B*2.0)-1.0)*0.60);
		third = third * fabs(third);
		long double fourth = -(((C*2.0)-1.0)*0.60);
		fourth = fourth * fabs(fourth);
		long double fifth = (((D*2.0)-1.0)*0.45);
		fifth = fifth * fabs(fifth);
		long double sixth = (((E*2.0)-1.0)*0.45);
		sixth = sixth * fabs(sixth);
		long double seventh = -(((F*2.0)-1.0)*0.38);
		seventh = seventh * fabs(seventh);
		long double eighth = -(((G*2.0)-1.0)*0.38);
		eighth = eighth * fabs(eighth);
		long double ninth = (((H*2.0)-1.0)*0.35);
		ninth = ninth * fabs(ninth);
		long double tenth = (((I*2.0)-1.0)*0.35);
		tenth = tenth * fabs(tenth);
		long double eleventh = -(((J*2.0)-1.0)*0.32);
		eleventh = eleventh * fabs(eleventh);
		long double twelvth = -(((K*2.0)-1.0)*0.32);
		twelvth = twelvth * fabs(twelvth);
		long double thirteenth = (((L*2.0)-1.0)*0.30);
		thirteenth = thirteenth * fabs(thirteenth);
		long double amount = (M*2.0)-1.0;
		amount = amount * fabs(amount);
		//setting up
		
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
			
			//left channel
			effxct = 0.0;
			inP2 = inputSampleL * inputSampleL;
			inP3 = inP2 * inputSampleL;
			inP4 = inP3 * inputSampleL;
			inP5 = inP4 * inputSampleL;
			inP6 = inP5 * inputSampleL;
			inP7 = inP6 * inputSampleL;
			inP8 = inP7 * inputSampleL;
			inP9 = inP8 * inputSampleL;
			inP10 = inP9 * inputSampleL;
			inP11 = inP10 * inputSampleL;
			inP12 = inP11 * inputSampleL;
			inP13 = inP12 * inputSampleL;
			//let's do the powers ahead of time and see how we do.
			if (second != 0.0)
			{
				chebyshev = (2 * inP2);
				effxct += (chebyshev * second);
			}
			if (third != 0.0)
			{
				chebyshev = (4 * inP3) - (3*inputSampleL);
				effxct += (chebyshev * third);
			}
			if (fourth != 0.0)
			{
				chebyshev = (8 * inP4) - (8 * inP2);
				effxct += (chebyshev * fourth);
			}
			if (fifth != 0.0)
			{
				chebyshev = (16 * inP5) - (20 * inP3) + (5*inputSampleL);
				effxct += (chebyshev * fifth);
			}
			if (sixth != 0.0)
			{
				chebyshev = (32 * inP6) - (48 * inP4) + (18 * inP2);
				effxct += (chebyshev * sixth);
			}
			if (seventh != 0.0)
			{
				chebyshev = (64 * inP7) - (112 * inP5) + (56 * inP3) - (7*inputSampleL);
				effxct += (chebyshev * seventh);
			}
			if (eighth != 0.0)
			{
				chebyshev = (128 * inP8) - (256 * inP6) + (160 * inP4) - (32 * inP2);
				effxct += (chebyshev * eighth);
			}
			if (ninth != 0.0)
			{
				chebyshev = (256 * inP9) - (576 * inP7) + (432 * inP5) - (120 * inP3) + (9*inputSampleL);
				effxct += (chebyshev * ninth);
			}
			if (tenth != 0.0)
			{
				chebyshev = (512 * inP10) - (1280 * inP8) + (1120 * inP6) - (400 * inP4) + (50 * inP2);
				effxct += (chebyshev * tenth);
			}
			if (eleventh != 0.0)
			{
				chebyshev = (1024 * inP11) - (2816 * inP9) + (2816 * inP7) - (1232 * inP5) +  (220 * inP3) - (11*inputSampleL);
				effxct += (chebyshev * eleventh);
			}
			if (twelvth != 0.0)
			{
				chebyshev = (2048 * inP12) - (6144 * inP10) + (6912 * inP8) - (3584 * inP6) + (840 * inP4) - (72 * inP2);
				effxct += (chebyshev * twelvth);
			}
			if (thirteenth != 0.0)
			{
				chebyshev = (4096 * inP13) - (13312 * inP11) + (16640 * inP9) - (9984 * inP7) + (2912 * inP5) - (364 * inP3) + (13*inputSampleL);
				effxct += (chebyshev * thirteenth);
			}
			//Yowza! Aren't we glad we're testing to see if we can skip these little bastards?
			inputSampleL += (effxct * amount);
			//You too can make a horrible graunch and then SUBTRACT it leaving only the refreshing smell of pine...
			//end left channel
			
			//right channel
			effxct = 0.0;
			inP2 = inputSampleR * inputSampleR;
			inP3 = inP2 * inputSampleR;
			inP4 = inP3 * inputSampleR;
			inP5 = inP4 * inputSampleR;
			inP6 = inP5 * inputSampleR;
			inP7 = inP6 * inputSampleR;
			inP8 = inP7 * inputSampleR;
			inP9 = inP8 * inputSampleR;
			inP10 = inP9 * inputSampleR;
			inP11 = inP10 * inputSampleR;
			inP12 = inP11 * inputSampleR;
			inP13 = inP12 * inputSampleR;
			//let's do the powers ahead of time and see how we do.
			if (second != 0.0)
			{
				chebyshev = (2 * inP2);
				effxct += (chebyshev * second);
			}
			if (third != 0.0)
			{
				chebyshev = (4 * inP3) - (3*inputSampleR);
				effxct += (chebyshev * third);
			}
			if (fourth != 0.0)
			{
				chebyshev = (8 * inP4) - (8 * inP2);
				effxct += (chebyshev * fourth);
			}
			if (fifth != 0.0)
			{
				chebyshev = (16 * inP5) - (20 * inP3) + (5*inputSampleR);
				effxct += (chebyshev * fifth);
			}
			if (sixth != 0.0)
			{
				chebyshev = (32 * inP6) - (48 * inP4) + (18 * inP2);
				effxct += (chebyshev * sixth);
			}
			if (seventh != 0.0)
			{
				chebyshev = (64 * inP7) - (112 * inP5) + (56 * inP3) - (7*inputSampleR);
				effxct += (chebyshev * seventh);
			}
			if (eighth != 0.0)
			{
				chebyshev = (128 * inP8) - (256 * inP6) + (160 * inP4) - (32 * inP2);
				effxct += (chebyshev * eighth);
			}
			if (ninth != 0.0)
			{
				chebyshev = (256 * inP9) - (576 * inP7) + (432 * inP5) - (120 * inP3) + (9*inputSampleR);
				effxct += (chebyshev * ninth);
			}
			if (tenth != 0.0)
			{
				chebyshev = (512 * inP10) - (1280 * inP8) + (1120 * inP6) - (400 * inP4) + (50 * inP2);
				effxct += (chebyshev * tenth);
			}
			if (eleventh != 0.0)
			{
				chebyshev = (1024 * inP11) - (2816 * inP9) + (2816 * inP7) - (1232 * inP5) +  (220 * inP3) - (11*inputSampleR);
				effxct += (chebyshev * eleventh);
			}
			if (twelvth != 0.0)
			{
				chebyshev = (2048 * inP12) - (6144 * inP10) + (6912 * inP8) - (3584 * inP6) + (840 * inP4) - (72 * inP2);
				effxct += (chebyshev * twelvth);
			}
			if (thirteenth != 0.0)
			{
				chebyshev = (4096 * inP13) - (13312 * inP11) + (16640 * inP9) - (9984 * inP7) + (2912 * inP5) - (364 * inP3) + (13*inputSampleR);
				effxct += (chebyshev * thirteenth);
			}
			//Yowza! Aren't we glad we're testing to see if we can skip these little bastards?
			inputSampleR += (effxct * amount);
			//You too can make a horrible graunch and then SUBTRACT it leaving only the refreshing smell of pine...
			//end right channel
	
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

};
MIN_EXTERNAL(pafnuty);

