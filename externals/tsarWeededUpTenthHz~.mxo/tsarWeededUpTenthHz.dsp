declare name "tsarWeededUpTenthHz"; // courtesy of Romain Michon's STK Modal Bar

// _,_ = stickHardness, gate = inputs for audio rate control from chuck (both are 0-1 range)

import("music.lib");
import("instrument.lib");


nPartials = 61;		// must agree with e.g., tsarCFweeded.h -- at least not exceed

// Stick impact table. CCinstrument.h has a synthesized strike rather than the stock instrument.h which is a force hammer
readMarmstk1 = ffunction(float readMarmstk1 (int), <CCinstrument.h>,"");
//marmstk1TableSize = 246; // instrument.h
marmstk1TableSize = 251; // CCinstrument.h

gain = nentry("h:Basic_Parameters/gain [1][tooltip:Gain (value between 0 and 1)]",0.0002,0,1,0.0001);
uiGate = button("h:Basic_Parameters/gate [1][tooltip:noteOn = 1, noteOff = 0]");
stickHardness = hslider("h:Physical/v:Physical_Parameters/stickHardness
[2][tooltip:A value between 0 and 1]",0.3,0,1,0.001);
whackBoost = hslider("h:Physical/v:Physical_Parameters/whackBoost
[2][tooltip:excitation strength, from exponent of partial amp, a value between 0 and 1, <1 hits low amplitudes harder]",0.9,0,1,0.0001);
loExc = hslider("h:Physical/v:Physical_Parameters/loExc
[2][tooltip:excitation scaling]",0.5,0,1,0.0001);
hiExc = hslider("h:Physical/v:Physical_Parameters/hiExc
[2][tooltip:excitation scaling]",0.5,0,1,0.0001);

loDamping = hslider("h:Physical/v:Physical_Parameters/loDamping
[2][tooltip:value 0.99997 to 0.999999]",0.99999,0.99997,0.999999,0.0000001);
hiDamping = hslider("h:Physical/v:Physical_Parameters/hiDamping
[2][tooltip:value 0.99997 to 0.999999]",0.99999,0.99997,0.999999,0.0000001);

loadCF = ffunction(float loadCF (int), <tsarCFweeded.h>,"");
loadX = ffunction(float loadX (int), <tsarXweeded.h>,"");
loadY = ffunction(float loadY (int), <tsarYweeded.h>,"");
loadZ = ffunction(float loadZ (int), <tsarZweeded.h>,"");

LOGTWO = 0.69314718055994528623;
ftom(f) = (log(f/440.0) / LOGTWO) * 12.0 + 69;
loKey = 31.31; 
hiKey = 92.31;
difKey = hiKey - loKey;

excTilt(f) = xxx
  with {
    k = ftom(f);
    interp = ( (k - loKey) / difKey );
    xxx = (interp*(hiExc-loExc))+loExc;
};

dampTilt(f) = xxx
  with {
    k = ftom(f);
    interp = ( (k - loKey) / difKey );
    xxx = (interp*(hiDamping-loDamping))+loDamping;
};

//0.999995, long carrilon before mar25
//0.99999, long tsar mar25
// 0.99998, // 5sec for dinnerbell

skip = 0; // 10
keep = nPartials-skip; // 200

biquadBankX = _ <: sum(i, keep, oneFilter(i+skip)) 
  with{
    oneFilter(j,exc) =  ( loadCF(j) + 0.1), dampTilt(loadCF(j)), excTilt(loadCF(j))*exc*(pow(loadX(j),whackBoost)): bandPassH; 
  };
biquadBankY = _ <: sum(i, keep, oneFilter(i+skip)) 
  with{
    oneFilter(j,exc) =  ( loadCF(j) + 0.1), dampTilt(loadCF(j)), excTilt(loadCF(j))*exc*(pow(loadY(j),whackBoost)): bandPassH; 
  };
biquadBankZ = _ <: sum(i, keep, oneFilter(i+skip)) 
  with{
    oneFilter(j,exc) =  ( loadCF(j) + 0.1), dampTilt(loadCF(j)), excTilt(loadCF(j))*exc*(pow(loadZ(j),whackBoost)): bandPassH; 
  };


//one pole filter with pole set at 0.9 for pre-filtering, onePole is declared in instrument.lib
sourceFilter = onePole(b0,a1)
	with{
		b0 = 1 - 0.9;
		a1 = -0.9;
	};

//excitation signal
excitation (sh,gate) = counterSamples < (marmstk1TableSize*rate) : *(marmstk1Wave*(tmpGate))
	   with{
tmpGate = gate+uiGate;
		//readMarmstk1 and marmstk1TableSize are both declared in instrument.lib
		marmstk1 = time%marmstk1TableSize : int : readMarmstk1;

		dataRate(readRate) = readRate : (+ : decimal) ~ _ : *(float(marmstk1TableSize));

		//the reading rate of the stick table is defined in function of the stickHardness
		rate = 0.25*pow(4,sh);

		counterSamples = (*(tmpGate)+1)~_ : -(1);
		marmstk1Wave = rdtable(marmstk1TableSize,marmstk1,int(dataRate(rate)*tmpGate));
	   };

process = stickHardness,_ : excitation : sourceFilter : *(gain) <:biquadBankX,biquadBankY,biquadBankZ;
