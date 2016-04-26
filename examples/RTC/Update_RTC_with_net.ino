/*

Example for Sim800l library
by Cristian Steib , < steibkhriz@gmail.com >

Demonstrate the use of the library
for get the time with the RTC of the module and Update with the net. 


Created 25 April 2016

*/

#include <Sim800l.h>
#include <SoftwareSerial.h> //is necesary for the library!! 
Sim800l Sim800l;  //to declare the library

int day,month,year,minute,second,hour;



void setup(){
	Serial.begin(9600); // only for debug the results . 
	Sim800l.begin(); // initializate the library.

	// the parameter to send is UTC of your country
	Sim800l.updateRtc(-3); //

}

void loop(){
	Sim800l.RTCtime(&day,&month,&year,&hour,&minute,&second);
	//at this moment the variables have the real time. 
	Serial.print(day);
	Serial.print('/');
	Serial.print(month);
	Serial.print('/');
	Serial.print(year);
	Serial.print(' ');
	Serial.print(hour);
	Serial.print(':');
	Serial.print(minute);
	Serial.print(':');
	Serial.print(second);
	Serial.println();
}
