/* 
* speed_enc.cpp
*
* Created: 09.07.2015 14:30:45
* Author: Maik Wagner
* E-Mail: Wagner@mf.tu-berlin.de
* alternative E-Mail: Maik.Wagner@gmx.eu
* Source: http://forum.arduino.cc/index.php?topic=140205.55
* -converted the source into a library
** The inputs are 2 and 13 (and optionally A6 for the index).
*/


#include "speed_enc.h"

// default constructor
speed_enc::speed_enc(const int enc_edges_per_rev, const int enc_samples_per_sec)
{
	//sets up the SAM3XE for hardware quadrature encoding
	_EncEdg_Rev	= enc_edges_per_rev;
	_EncS_Sec	= enc_samples_per_sec;
	
	REG_PMC_PCER0 = PMC_PCER0_PID27
	| PMC_PCER0_PID28
	| PMC_PCER0_PID29;

	// Setup a channel in waveform mode (eg an input into the encoder to trigger the time based sampling)
	// Note some of the choices here impact calculations below and if you change them, you need to change
	// the next section to suit.
	// Section 36.7.3 p883 (also refer to Section 36.6.14.5 p877 for detail of what to set)
	REG_TC0_CMR2 = TC_CMR_TCCLKS_TIMER_CLOCK4
	| TC_CMR_WAVE
	| TC_CMR_ACPC_TOGGLE
	| TC_CMR_WAVSEL_UP_RC;

	// Now define the sample period, using the clock chosen above as the basis
	// Note that REG_TC0_CMR2 above is using CLOCK4; this is an 128 divisor. You need to change the
	// divisor below if you change the clock above. You could change the input clock and the RC mode to
	// suit your app (eg how many pulses are you  expecting - depends on encoder type
	// and slowest/normal/fastest rotation speed and what you want to do with the result).
	// Section 36.6.14.5 p877 notes you need to set this up, otherwise 0 comes out all the time :-)
	REG_TC0_RC2 = F_CPU / 128 / _EncS_Sec;
	
	// Setup a channel in capture mode
	// Section 36.7.2 p904 (also refer to Section 36.6.14.4f p876f for detail of what to set)
	REG_TC0_CMR0 = TC_CMR_ABETRG
	| TC_CMR_LDRA_EDGE
	| TC_CMR_LDRB_EDGE
	| TC_CMR_ETRGEDG_EDGE
	| TC_CMR_CPCTRG;

	// Enable features, noting Speed not Position is chosen
	// Section 3.7.14 p901 (also refer to Section 36.6.14.5 p877 for detail of what to set)
	REG_TC0_BMR = TC_BMR_QDEN
	| TC_BMR_SPEEDEN
	| TC_BMR_EDGPHA;
	
	// Set everything going (Section36.7.1 p880)
	REG_TC0_CCR0 = TC_CCR_CLKEN | TC_CCR_SWTRG;
	REG_TC0_CCR1 = TC_CCR_CLKEN | TC_CCR_SWTRG;
	REG_TC0_CCR2 = TC_CCR_CLKEN | TC_CCR_SWTRG;
	
} //speed_enc

long speed_enc::speed()
{
	// read the Pulses per Sampling Periode from the register and calculates the rpm
	_SpeedPPP = REG_TC0_RA0;
	_SpeedRPS = (( _SpeedPPP / (_EncEdg_Rev*1.0)) * _EncS_Sec);
	Speed = long(_SpeedRPS *60*(-1)); //rpm
	return Speed;
} //speed

int speed_enc::direction()
{
	// read the direction from the register
		_IndexCount = REG_TC0_CV1;
		Dir = _IndexCount;
		return Dir;
} //direction

