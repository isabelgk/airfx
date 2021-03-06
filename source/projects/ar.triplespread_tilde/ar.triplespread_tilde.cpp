#include "c74_min.h"

using namespace c74::min;

class triplespread : public object<triplespread>, public vector_operator<> {
public:
	MIN_DESCRIPTION {"a stereo tripler with extra wideness and GlitchShifter processing"};
	MIN_TAGS {""};
	MIN_AUTHOR {"Isabel Kaspriskie"};

	inlet<> in1 {this, "(signal) Input1"};
	inlet<> in2 {this, "(signal) Input2"};
	outlet<> out1 {this, "(signal) Output1", "signal"};
	outlet<> out2 {this, "(signal) Output2", "signal"};

	attribute<number, threadsafe::no, limit::clamp> A {this, "spread", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> B {this, "tightness", 1.0, range {0.0, 1.0} };
	attribute<number, threadsafe::no, limit::clamp> C {this, "mix", 1.0, range {0.0, 1.0} };

	message<> dspsetup {this, "dspsetup",
		MIN_FUNCTION {
			for (int count = 0; count < 131074; count++) {pL[count] = 0; pR[count] = 0;}
			for (int count = 0; count < 257; count++) {
				offsetL[count] = 0; pastzeroL[count] = 0; previousL[count] = 0; thirdL[count] = 0; fourthL[count] = 0;
				offsetR[count] = 0; pastzeroR[count] = 0; previousR[count] = 0; thirdR[count] = 0; fourthR[count] = 0;
			}
			crossesL = 0;
			realzeroesL = 0;
			tempL = 0;
			lasttempL = 0;
			thirdtempL = 0;
			fourthtempL = 0;
			sincezerocrossL = 0;
			airPrevL = 0.0;
			airEvenL = 0.0;
			airOddL = 0.0;
			airFactorL = 0.0;
			positionL = 0.0;
			splicingL = false;	
			
			crossesR = 0;
			realzeroesR = 0;
			tempR = 0;
			lasttempR = 0;
			thirdtempR = 0;
			fourthtempR = 0;
			sincezerocrossR = 0;
			airPrevR = 0.0;
			airEvenR = 0.0;
			airOddR = 0.0;
			airFactorR = 0.0;
			positionR = 0.0;
			splicingR = false;	
			
			gcount = 0;
			lastwidth = 16386;
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

		double speed = ((A*2.0)-1.0)*0.041666666666667;
		int width = (int)(65536-((1-pow(1-B,2))*65530.0));
		double bias = pow(B,3);
		double wet = C;
		
	    while (--sampleFrames >= 0)
	    {
			long double inputSampleL = *in1;
			long double inputSampleR = *in2;
			if (fabs(inputSampleL)<1.18e-37) inputSampleL = fpd * 1.18e-37;
			if (fabs(inputSampleR)<1.18e-37) inputSampleR = fpd * 1.18e-37;
			long double drySampleL = inputSampleL;
			long double drySampleR = inputSampleR;
			
			airFactorL = airPrevL - inputSampleL;
			if (flip) {airEvenL += airFactorL; airOddL -= airFactorL; airFactorL = airEvenL;}
			else {airOddL += airFactorL; airEvenL -= airFactorL; airFactorL = airOddL;}
			airOddL = (airOddL - ((airOddL - airEvenL)/256.0)) / 1.0001;
			airEvenL = (airEvenL - ((airEvenL - airOddL)/256.0)) / 1.0001;
			airPrevL = inputSampleL;
			inputSampleL += airFactorL;
			
			airFactorR = airPrevR - inputSampleR;
			if (flip) {airEvenR += airFactorR; airOddR -= airFactorR; airFactorR = airEvenR;}
			else {airOddR += airFactorR; airEvenR -= airFactorR; airFactorR = airOddR;}
			airOddR = (airOddR - ((airOddR - airEvenR)/256.0)) / 1.0001;
			airEvenR = (airEvenR - ((airEvenR - airOddR)/256.0)) / 1.0001;
			airPrevR = inputSampleR;
			inputSampleR += airFactorR;
			
			flip = !flip;
			//air, compensates for loss of highs of interpolation
			
			if (lastwidth != width){crossesL = 0; realzeroesL = 0; crossesR = 0; realzeroesR = 0; lastwidth = width;}
			//global: changing this resets both channels
			
			gcount++;
			if (gcount < 0 || gcount > width) {gcount = 0;}
			int count = gcount;
			int countone = count-1;
			int counttwo = count-2;
			while (count < 0){count += width;}
			while (countone < 0){countone += width;}
			while (counttwo < 0){counttwo += width;}
			while (count > width){count -= width;} //this can only happen with very insane variables
			while (countone > width){countone -= width;}
			while (counttwo > width){counttwo -= width;}
			//yay sanity checks
			//now we have counts zero, one, two, none of which have sanity checked values
			//we are tracking most recent samples and must SUBTRACT.
			//this is a wrap on the overall buffers, so count, one and two are also common to both channels
			
			pL[count+width] = pL[count] = (int)((inputSampleL*8388352.0));
			pR[count+width] = pR[count] = (int)((inputSampleR*8388352.0));
			//double buffer -8388352 to 8388352 is equal to 24 bit li_near space
			
			if ((pL[countone] > 0 && pL[count] < 0)||(pL[countone] < 0 && pL[count] > 0)) //source crossed zero
			{
				crossesL++;
				realzeroesL++;
				if (crossesL > 256) {crossesL = 0;} //wrap crosses to keep adding new crosses
				if (realzeroesL > 256) {realzeroesL = 256;} //don't wrap realzeroes, full buffer, use all
				offsetL[crossesL] = count;
				pastzeroL[crossesL] = pL[count];
				previousL[crossesL] = pL[countone];
				thirdL[crossesL] = pL[counttwo];
				//we load the zero crosses register with crosses to examine
			} //we just put in a source zero cross in the registry
			
			if ((pR[countone] > 0 && pR[count] < 0)||(pR[countone] < 0 && pR[count] > 0)) //source crossed zero
			{
				crossesR++;
				realzeroesR++;
				if (crossesR > 256) {crossesR = 0;} //wrap crosses to keep adding new crosses
				if (realzeroesR > 256) {realzeroesR = 256;} //don't wrap realzeroes, full buffer, use all
				offsetR[crossesR] = count;
				pastzeroR[crossesR] = pR[count];
				previousR[crossesR] = pR[countone];
				thirdR[crossesR] = pR[counttwo];
				//we load the zero crosses register with crosses to examine
			} //we just put in a source zero cross in the registry
			//in this we don't update count at all, so we can run them one after another because this is
			//feeding the system, not tracking the output of two parallel but non-matching output taps
			
			positionL -= speed; //this is individual to each channel!
			
			if (positionL > width) { //we just caught up to the buffer end
				if (realzeroesL > 0) { //we just caught up to the buffer end with zero crosses in the bin
					positionL = 0;
					double diff = 99999999.0; 
					int best = 0; //these can be local, I think
					int scan;
					for(scan = (realzeroesL-1); scan >= 0; scan--) {
						int scanone = scan + crossesL;
						if (scanone > 256){scanone -= 256;}
						//try to track the real most recent ones more closely
						double howdiff = (double)((tempL - pastzeroL[scanone]) + (lasttempL - previousL[scanone]) + (thirdtempL - thirdL[scanone]) + (fourthtempL - fourthL[scanone]));
						//got difference factor between things
						howdiff -= (double)(scan*bias);
						//try to bias in favor of more recent crosses
						if (howdiff < diff) {diff = howdiff; best = scanone;}
					} //now we have 'best' as the closest match to the current rate of zero cross and positioning- a splice.
					positionL = offsetL[best]-sincezerocrossL;
					crossesL = 0;
					realzeroesL = 0;
					splicingL = true; //we just kicked the delay tap back, changing positionL
				} else { //we just caught up to the buffer end with no crosses- glitch speeds.
					positionL -= width;
					crossesL = 0;
					realzeroesL = 0;
					splicingL = true; //so, hard splice it.
				}
			}
			
			if (positionL < 0) { //we just caught up to the dry tap.
				if (realzeroesL > 0) { //we just caught up to the dry tap with zero crosses in the bin
					positionL = 0;
					double diff = 99999999.0; 
					int best = 0; //these can be local, I think
					int scan;
					for(scan = (realzeroesL-1); scan >= 0; scan--) {
						int scanone = scan + crossesL;
						if (scanone > 256){scanone -= 256;}
						//try to track the real most recent ones more closely
						double howdiff = (double)((tempL - pastzeroL[scanone]) + (lasttempL - previousL[scanone]) + (thirdtempL - thirdL[scanone]) + (fourthtempL - fourthL[scanone]));
						//got difference factor between things
						howdiff -= (double)(scan*bias);
						//try to bias in favor of more recent crosses
						if (howdiff < diff) {diff = howdiff; best = scanone;}
					} //now we have 'best' as the closest match to the current rate of zero cross and positioning- a splice.
					positionL = offsetL[best]-sincezerocrossL;
					crossesL = 0;
					realzeroesL = 0;
					splicingL = true; //we just kicked the delay tap back, changing positionL
				} else { //we just caught up to the dry tap with no crosses- glitch speeds.
					positionL += width;
					crossesL = 0;
					realzeroesL = 0;
					splicingL = true; //so, hard splice it.
				}
			}
			
			positionR += speed; //this is individual to each channel and inverted for R!
			
			if (positionR > width) { //we just caught up to the buffer end
				if (realzeroesR > 0) { //we just caught up to the buffer end with zero crosses in the bin
					positionR = 0;
					double diff = 99999999.0; 
					int best = 0; //these can be local, I think
					int scan;
					for(scan = (realzeroesR-1); scan >= 0; scan--) {
						int scanone = scan + crossesR;
						if (scanone > 256){scanone -= 256;}
						//try to track the real most recent ones more closely
						double howdiff = (double)((tempR - pastzeroR[scanone]) + (lasttempR - previousR[scanone]) + (thirdtempR - thirdR[scanone]) + (fourthtempR - fourthR[scanone]));
						//got difference factor between things
						howdiff -= (double)(scan*bias);
						//try to bias in favor of more recent crosses
						if (howdiff < diff) {diff = howdiff; best = scanone;}
					} //now we have 'best' as the closest match to the current rate of zero cross and positioning- a splice.
					positionR = offsetR[best]-sincezerocrossR;
					crossesR = 0;
					realzeroesR = 0;
					splicingR = true; //we just kicked the delay tap back, changing positionL
				} else { //we just caught up to the buffer end with no crosses- glitch speeds.
					positionR -= width;
					crossesR = 0;
					realzeroesR = 0;
					splicingR = true; //so, hard splice it.
				}
			}
			
			if (positionR < 0) { //we just caught up to the dry tap.
				if (realzeroesR > 0) { //we just caught up to the dry tap with zero crosses in the bin
					positionR = 0;
					double diff = 99999999.0; 
					int best = 0; //these can be local, I think
					int scan;
					for(scan = (realzeroesR-1); scan >= 0; scan--) {
						int scanone = scan + crossesR;
						if (scanone > 256){scanone -= 256;}
						//try to track the real most recent ones more closely
						double howdiff = (double)((tempR - pastzeroR[scanone]) + (lasttempR - previousR[scanone]) + (thirdtempR - thirdR[scanone]) + (fourthtempR - fourthR[scanone]));
						//got difference factor between things
						howdiff -= (double)(scan*bias);
						//try to bias in favor of more recent crosses
						if (howdiff < diff) {diff = howdiff; best = scanone;}
					} //now we have 'best' as the closest match to the current rate of zero cross and positioning- a splice.
					positionR = offsetR[best]-sincezerocrossR;
					crossesR = 0;
					realzeroesR = 0;
					splicingR = true; //we just kicked the delay tap back, changing positionL
				} else { //we just caught up to the dry tap with no crosses- glitch speeds.
					positionR += width;
					crossesR = 0;
					realzeroesR = 0;
					splicingR = true; //so, hard splice it.
				}
			}
			
			
			count = gcount - (int)floor(positionL);
			//we go back because the buffer goes forward this time
			countone = count+1; 
			counttwo = count+2;
			//now we have counts zero, one, two, none of which have sanity checked values
			//we are interpolating, we ADD
			while (count < 0){count += width;}
			while (countone < 0){countone += width;}
			while (counttwo < 0){counttwo += width;}
			while (count > width){count -= width;} //this can only happen with very insane variables
			while (countone > width){countone -= width;}
			while (counttwo > width){counttwo -= width;}
			
			//here's where we do our shift against the rotating buffer
			tempL = 0;
			tempL += (int)(pL[count] * (1-(positionL-floor(positionL)))); //less as value moves away from .0
			tempL += pL[count+1]; //we can assume always using this in one way or another?
			tempL += (int)(pL[count+2] * (positionL-floor(positionL))); //greater as value moves away from .0
			tempL -= (int)(((pL[count]-pL[count+1])-(pL[count+1]-pL[count+2]))/50); //interpolation hacks 'r us		
			tempL /= 2; //gotta make temp be the same level scale as buffer
			//now we have our delay tap, which is going to do our pitch shifting
			if (fabs(tempL) > 8388352.0){tempL = (lasttempL + (lasttempL - thirdtempL));}
			//kill ticks of bad buffer mojo by sticking with the trajectory. Ugly hack *shrug*
			
			sincezerocrossL++;
			if (sincezerocrossL < 0 || sincezerocrossL > width){sincezerocrossL = 0;} //just a sanity check
			if (splicingL){tempL = (tempL + (lasttempL + (lasttempL - thirdtempL)))/2; splicingL = false;}
			//do a smoother transition by taking the sample of transition and going half with it
			
			if ((lasttempL > 0 && tempL < 0)||(lasttempL < 0 && tempL > 0)) //delay tap crossed zero
			{
				sincezerocrossL = 0;
			} //we just restarted counting from the delay tap zero cross
			
			count = gcount - (int)floor(positionR);
			//we go back because the buffer goes forward this time
			countone = count+1; 
			counttwo = count+2;
			//now we have counts zero, one, two, none of which have sanity checked values
			//we are interpolating, we ADD
			while (count < 0){count += width;}
			while (countone < 0){countone += width;}
			while (counttwo < 0){counttwo += width;}
			while (count > width){count -= width;} //this can only happen with very insane variables
			while (countone > width){countone -= width;}
			while (counttwo > width){counttwo -= width;}
			
			
			tempR = 0;
			tempR += (int)(pR[count] * (1-(positionR-floor(positionR)))); //less as value moves away from .0
			tempR += pR[count+1]; //we can assume always using this in one way or another?
			tempR += (int)(pR[count+2] * (positionR-floor(positionR))); //greater as value moves away from .0
			tempR -= (int)(((pR[count]-pR[count+1])-(pR[count+1]-pR[count+2]))/50); //interpolation hacks 'r us		
			tempR /= 2; //gotta make temp be the same level scale as buffer
			//now we have our delay tap, which is going to do our pitch shifting
			if (fabs(tempR) > 8388352.0){tempR = (lasttempR + (lasttempR - thirdtempR));}
			//kill ticks of bad buffer mojo by sticking with the trajectory. Ugly hack *shrug*
			
			sincezerocrossR++;
			if (sincezerocrossR < 0 || sincezerocrossR > width){sincezerocrossR = 0;} //just a sanity check
			if (splicingR){tempR = (tempR + (lasttempR + (lasttempR - thirdtempR)))/2; splicingR = false;}
			//do a smoother transition by taking the sample of transition and going half with it
			
			if ((lasttempR > 0 && tempR < 0)||(lasttempR < 0 && tempR > 0)) //delay tap crossed zero
			{
				sincezerocrossR = 0;
			} //we just restarted counting from the delay tap zero cross
			
			fourthtempL = thirdtempL;
			thirdtempL = lasttempL;
			lasttempL = tempL;
			
			fourthtempR = thirdtempR;
			thirdtempR = lasttempR;
			lasttempR = tempR;
			
			long double mid = (inputSampleL + inputSampleR)*(1-wet);
			long double side = inputSampleL - inputSampleR;
			//assign mid and side.Between these sections, you can do mid/side processing
			inputSampleL = (mid+side)/2.0;
			inputSampleR = (mid-side)/2.0;
			//unassign mid and side		
			
			inputSampleL = ( drySampleL * (1-wet))+((double)(tempL/(8388352.0))*wet);
			if (inputSampleL > 4.0) inputSampleL = 4.0;
			if (inputSampleL < -4.0) inputSampleL = -4.0;
			
			inputSampleR = ( drySampleR * (1-wet))+((double)(tempR/(8388352.0))*wet);
			if (inputSampleR > 4.0) inputSampleR = 4.0;
			if (inputSampleR < -4.0) inputSampleR = -4.0;
			//this plugin can throw insane outputs so we'll put in a hard clip
			
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
    
	uint32_t pL[131076];
	uint32_t offsetL[258];
	uint32_t pastzeroL[258];
	uint32_t previousL[258];
	uint32_t thirdL[258];
	uint32_t fourthL[258];
	uint32_t tempL;
	uint32_t lasttempL;
	uint32_t thirdtempL;
	uint32_t fourthtempL;
	uint32_t sincezerocrossL;
	int crossesL;
	int realzeroesL;
	double positionL;
	bool splicingL;
	
	double airPrevL;
	double airEvenL;
	double airOddL;
	double airFactorL;
	
	uint32_t pR[131076];
	uint32_t offsetR[258];
	uint32_t pastzeroR[258];
	uint32_t previousR[258];
	uint32_t thirdR[258];
	uint32_t fourthR[258];
	uint32_t tempR;
	uint32_t lasttempR;
	uint32_t thirdtempR;
	uint32_t fourthtempR;
	uint32_t sincezerocrossR;
	int crossesR;
	int realzeroesR;
	double positionR;
	bool splicingR;
	
	double airPrevR;
	double airEvenR;
	double airOddR;
	double airFactorR;
	
	int gcount;
	uint32_t lastwidth;
	bool flip;
	uint32_t fpd;
	//default stuff

};
MIN_EXTERNAL(triplespread);

