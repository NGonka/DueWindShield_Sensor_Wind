/* 
* SDP610_Lib.cpp
*
* Created: 09.08.2016 18:00:00
* Author: Maik Wagner
* Controlling Sensirion SDP610-125Pa Differntial Pressure Sensor
*/


#include "Arduino.h"
#include "Wire.h"
#include "SDP610_Lib.h"

SDP610_Lib::SDP610_Lib(int8_t address){
	_address = address;
}//SDP610_Lib

void SDP610_Lib::begin(void){
	//setupI2C();
	Wire.begin();
 delay(300);
}

void SDP610_Lib::setupI2C(void){
	Wire.setClock(100000);	//Setup for fast I2C
}

int16_t SDP610_Lib::readingData(void) {

  int16_t reading[2] = {0, 0};
  Wire.beginTransmission(_address);
  delay(1);
  Wire.write(0xf1); //trigger differential pressure measurement
  Wire.endTransmission();
  delay(1);
  Wire.requestFrom(_address, 3);
  if (3 == Wire.available()) // slave may send less than requested
  {
    //delay(1);
    reading[0] = Wire.read(); // read MSB
    //delay(1);
    reading[1] = Wire.read(); // read LSB
    Wire.read();              // requesting checkbyte and ignoring it
  }
  // Serial.print("Msb: ");
  // Serial.print(reading[0]);
  // Serial.print(", ");
  // Serial.print("Lsb: ");
  // Serial.print(reading[1]);
  // Serial.print(", ");

  return ((reading[0] << 8) | reading[1]); // converting 2 bytes into 1 word (16-bit)
}



float SDP610_Lib::density(float AmbientPressure, float AmbientTemperature) {
  return AmbientPressure / (287.0 * (273.15 + AmbientTemperature));
}


float SDP610_Lib::absolut(float value) {
  if (value >= 0) {
    return value;
  } else if  (value < 0) {
    return (-1) * value;
  }
}

double SDP610_Lib::absolut(double value) {
  if (value >= 0) {
    return value;
  } else if  (value < 0) {
    return (-1) * value;
  }
}

int16_t SDP610_Lib::sign(int16_t value) {
  if (value > 0) {
    return 1;
  } else if ( value < 0) {
    return -1;
  }
  return 0;
}

double SDP610_Lib::prandtlKorr(float v_prandtl){
  //y = -0.0906x2 + 3.0645x
  return (-0.0906*pow(v_prandtl,2)+3.0645*v_prandtl);
}

long SDP610_Lib::velocity ( float AmbientPressure, float AmbientTemperature) {
  
  int16_t readData = readingData();
  float airDensity = density(AmbientPressure, AmbientTemperature);
  long v = long((sign(readData)) * (sqrt(( 2 * (absolut((double)readData / SensScaleFactor) / airDensity)))));

  //return (double)(sqrt( 2 * (absolut((double)readData / SensScaleFactor)) / airDensity) ); //velocity in cm/s
  return (prandtlKorr(v)*100); //velocity in cm/s
}


int16_t SDP610_Lib::absolut(int16_t value) {
  if (value >= 0) {
    return value;
  } else if  (value < 0) {
    return (-1) * value;
  }
}
