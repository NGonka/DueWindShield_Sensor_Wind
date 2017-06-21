/*
BMA280 library
not every function is implemented, just the needed one

*/

/*
  created: 13.07.2016
  Author: Maik Wagner
  E-Mail: Maik.Wagner@gmx.eu
*/

#include "Arduino.h"
#include "BMA280.h"

#include <SPI.h>
BMA280::BMA280(int _CS_BMA280, int _intPin){
    CS_BMa280=_CS_BMA280;
    intPin=_intPin;
}

void BMA280::begin(void){
  pinMode(intPin,INPUT);
  // Serial.println("1");
  //SPI Setup
  SPI.begin(CS_BMa280);
  //SPI set Clockspeed to 7 MHz with clockdivider 12 (84MHz/12)
  SPI.setClockDivider(CS_BMa280, 12);
  //Configure the SPI connection
  SPI.setDataMode(SPI_MODE3);
  
  // Setting up the sensor
  writeRegister(DATA_FORMAT, RANGE_16G, CS_BMa280);
  //Serial.println("2");
  //Set the Bandwidth to 250Hz
  writeRegister(BW_Rate, BW250HZ, CS_BMa280);
  //Serial.println("3");
  //map data ready interupt to pin INT1
  writeRegister(INT_MAP_1, 0x01, CS_BMa280);
  //Serial.println("4");
  //enables data ready interrupt on pin INT1
  writeRegister(INT_EN_1, 0x10, CS_BMa280);
  //Serial.println("5");
    
}

void BMA280::readRegister(char _registerAddress, int _numBytes, char * _values, int _CS_deviceName){
    //Since we're performing a read operation, the most significant bit of the register address should be set.
  char _address = _registerAddress | 0x80;
  //If we're doing a multi-word read, bit 6 needs to be set as well.
 // if (numBytes > 1)address = address | 0x40;

  //Set the Chip select pin low to start an SPI packet.
  // digitalWrite(CS_BMA280, LOW); //not necessary, because we are using a due
  //Transfer the starting register address that needs to be read.
  SPI.transfer( _CS_deviceName, _address, SPI_CONTINUE);
  //Continue to read registers until we've read the number specified, storing the results to the input buffer.

  if (_numBytes > 1) {
    for (int i = 0; i < _numBytes - 1; i++) {
      _values[i] = SPI.transfer(_CS_deviceName, 0x00, SPI_CONTINUE);
    }
    _values[_numBytes] = SPI.transfer(_CS_deviceName, 0x00);
    
  }
  else if (_numBytes == 1) {
    _values[0] = SPI.transfer(_CS_deviceName, 0x00);
  }
}
void BMA280::writeRegister(char _registerAddress, char _value, int _CS_deviceName){
    //Set Chip Select pin low to signal the beginning of an SPI packet.
  //digitalWrite(CS_BMA280, LOW); //not necessary, because we are using a due
  //Transfer the register address over SPI.
  SPI.transfer(_CS_deviceName, _registerAddress, SPI_CONTINUE);
  //Transfer the desired register value over SPI.
  SPI.transfer(_CS_deviceName, _value);
  //Set the Chip Select pin high to signal the end of an SPI packet.
  //digitalWrite(CS_BMA280, HIGH); //not necessary, because we are using a due
}

void BMA280::readSensor(int * _accValues){
    if(digitalRead(intPin)) {//checks, if the Buffer from the BMA280 is full indicated by a HIGH from pin int1 of the BMA280 board
    int16_t xAxis, yAxis, zAxis;
    int8_t temp;
    int16_t xAxisTemp, yAxisTemp, zAxisTemp;
    
    char values[7];
    readRegister(DATAX0, 7, values,CS_BMa280);
    //14bit to 16 bit conversion, cause of reasons...
    xAxisTemp = (((int16_t)values[0]>>2)<<2);
    //Serial.println(xAxisTemp,BIN);
    xAxis = (((int16_t)values[1] << 8 )| xAxisTemp);    
    yAxisTemp = (((int16_t)values[2]>>2)<<2);
    //Serial.println(yAxisTemp,BIN);
    yAxis = (((int16_t)values[3] << 8) | yAxisTemp);
    zAxisTemp = (((int16_t)values[4]>>2)<<2);
   // Serial.println(zAxisTemp,BIN);
    zAxis = (((int16_t)values[5] << 8) | zAxisTemp);
//    xAxis/=4;
//    yAxis/=4;
//    zAxis/=4;
    //temp = values[6];
    _accValues[0]= int(xAxis/4)*g16_multiplier;
    _accValues[1]= int(yAxis/4)*g16_multiplier;
    _accValues[2]= int(zAxis/4)*g16_multiplier;
    //_accValues[3]= int((temp*0.5+23.0)*100);
    }
    
}

 char BMA280::readID(void){
  char _ID[1];
  readRegister(0x00,1,_ID,CS_BMa280);
  return _ID[0];
  
}

