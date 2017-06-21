/*
BMA280 library
not every function is implemented, just the needed one

*/

/*
  created: 13.07.2016
  Author: Maik Wagner
  E-Mail: Maik.Wagner@gmx.eu
*/

#ifndef BMA280_H
#define BMA280_H

#include "Arduino.h"


class BMA280
{
    private:
        //This is a list of some of the registers available on the BMA280.
        //To learn more about these and the rest of the registers on the BMA280, read the datasheet!
        //Register
         char DATA_FORMAT = 0x0f; // (PMU_RANGE register)
         char DATAX0 = 0x02;    //(ACCD_X_LSB register) start register for the readout of the acceleration data, starts with the x axes
         char BW_Rate = 0x10;    //Set bandwith (PMU_BW register)
         char INT_MAP_1 = 0x1a;    // 0x01 for Int1 or 0x80 for Int2 (INT_MAP_1 register) ((for data ready interrupt)
         char INT_EN_1 = 0x17; //Enables interrupt (INT_EN_1 register)
        //Register settings
         char RANGE_16G = 0x0c;
         char RANGE_02G = 0x03;
         char RANGE_8G = 0x08;
         char BW250HZ = 0x0d;
         char BW500HZ = 0x0E;
         char BW2000HZ = 0x10;
        
        float g16_multiplier = 1.953125; // to convert from  14-bit to mg in +-16g range
        float g2_multiplier =  0.244140625;// to convert from  14-bit to mg in +-2g range
        float g8_multiplier =  0.9765625;// to convert from  14-bit to mg in +-2g range
        int CS_BMa280; //Acceleration Sensor = 10
        int intPin;    //interrupt recognition pin (can be every digital Input)
        void readRegister(char _registerAddress, int _numBytes, char * _values, int _CS_deviceName);
        void writeRegister(char _registerAddress, char _value, int _CS_deviceName);
        
    public:
        BMA280(int _CS_BMA280, int _intPin);
        void readSensor(int * _accValues);
        void begin(void);
        char readID(void);

        
};//BMA280

#endif
