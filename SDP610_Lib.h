/* 
* SDP610_Lib.h
*
* Created: 09.08.2016 18:00:00
* Author: Maik Wagner
* Controlling Sensirion SDP610-125Pa Differntial Pressure Sensor
*/



#ifndef __SDP610-125PA_H__
#define __SDP610-125PA_H__

#include "Arduino.h"
#include <Wire.h>



class SDP610_Lib
{
	
private:
	//variables
	int8_t _address;						// Device Address
	//functions
	void setupI2C(void);	
  float  SensScaleFactor = 240.0;
	int16_t readingData(void);
	
	float absolut(float value);
	double absolut(double value);
	int16_t absolut(int16_t value);
	int16_t sign(int16_t value);
	double prandtlKorr(float v_prandtl);
	
	
public:
	SDP610_Lib(int8_t address);
	void begin(void);
  float density(float AmbientPressure, float AmbientTemperature);
	long velocity ( float AmbientPressure, float AmbientTemperature);
};

#endif
