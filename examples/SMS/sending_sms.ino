/*

Example for Sim800l library
by Cristian Steib , < steibkhriz@gmail.com >

Demonstrate the use of the library
for send a sms. 


Created 24 April 2016

*/

#include <Sim800l.h>
#include <SoftwareSerial.h> //is necesary for the library!! 
Sim800l Sim800l;  //to declare the library
char* text;
char* number;
bool error; //to catch the response of sendSms


void setup(){
	Sim800l.begin(); // initializate the library. 
	text="Testing Sms";  //text for the message. 
	number="2926451386"; //change to a valid number.
	error=Sim800l.sendSms(number,text);
	// OR 
	//Sim800l.sendSms("+540111111111","the text go here")


}

void loop(){
	//do nothing
}
