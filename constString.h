/*
* constString.h
*
* created: 08.09.2015
* Author: Maik Wagner
* E-Mail: Wagner@mf.tu-berlin.de
* alternative E-Mail: Maik.Wagner@gmx.eu
*
* for constant String length during serial communication
* and hence constant output data rate
*/

#ifndef _CONSTSTRING_h
#define _CONSTSTRING_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

String constStringLength(long value, int valueSize);
String constStringLength(unsigned long value, int valueSize);

String constStringLength(uint8_t value, int valueSize);
String constStringLength(uint16_t value, int valueSize);
String constStringLength(uint32_t value, int valueSize);

String constStringLength(int8_t value, int valueSize);
String constStringLength(int16_t value, int valueSize);


#endif

