/* 
* MCP4726.cpp
*
* Created: 13.08.2015 13:58:39
* Author: Maik Wagner
* Controlling the DAC MCP4726
*/

#include "Arduino.h"
#include "Wire.h"
#include "MCP4726.h"


// default constructor
MCP4726::MCP4726(uint8_t address)
{
	_address = address;	
} //MCP4726

void MCP4726::begin(void){
	//setupI2C();
	Wire.begin();
}

void MCP4726::setVoltage(uint16_t vBit){ 
	// Transmits vBit to the DAC and he sets the according Voltage; depends on Vref
	Wire.beginTransmission(_address);
	Wire.write(MCP4726_CMD_WRITEDAC);
	Wire.write(HByte(vBit));
	Wire.write(LByte(vBit));
	Wire.endTransmission();
}

void MCP4726::setupI2C(void){
	Wire.setClock(400000);	//Setup for fast I2C
}

byte MCP4726::LByte(uint16_t sendByte){
	return (sendByte<<4)&255;	//Sends the lower 8bits of 16bits
}

byte MCP4726::HByte(uint16_t sendByte){
	return (sendByte>>4);	//Sends the upper 8 bits of 16 bits
}
