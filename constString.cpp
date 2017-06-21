/*
* constString.cpp
*
* created: 08.09.2015
* Author: Maik Wagner
* E-Mail: Wagner@mf.tu-berlin.de
* alternative E-Mail: Maik.Wagner@gmx.eu
* 
* for constant String length during serial communication
* and hence constant output data rate
*/


#include "constString.h"

String constStringLength(long value, int valueSize){
	char charBuffer[valueSize+2];
	sprintf(charBuffer,"%*ld",valueSize,value);
	return String(charBuffer);
}

String constStringLength(unsigned long value, int valueSize){
	char charBuffer[valueSize+2];
	sprintf(charBuffer,"%*lu",valueSize,value);
	return String(charBuffer);
}

String constStringLength(uint8_t value, int valueSize){
	char charBuffer[valueSize+2];
	sprintf(charBuffer,"%*u",valueSize,value);
	return String(charBuffer);
}

String constStringLength(uint16_t value, int valueSize){
	char charBuffer[valueSize+2];
	sprintf(charBuffer,"%*u",valueSize,value);
	return String(charBuffer);
}
String constStringLength(int8_t value, int valueSize){
	char charBuffer[valueSize+2];
	sprintf(charBuffer,"%*d",valueSize,value);
	return String(charBuffer);
}

String constStringLength(int16_t value, int valueSize){
	char charBuffer[valueSize+2];
	sprintf(charBuffer,"%*d",valueSize,value);
	return String(charBuffer);
}
