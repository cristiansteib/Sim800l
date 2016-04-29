/* this library is writing by  Cristian Steib.
			steibkhriz@gmail.com

*/
#ifndef Sim800l_h
#define Sim800l_h
#include <SoftwareSerial.h>
#include "Arduino.h"


#define RX_PIN 10
#define TX_PIN 11	
#define RESET_PIN 2   // pin to the reset pin sim800l

#define LED true //for usea indicator led, in case that you don want set to false . 
#define LED_PIN 13 //pin to indicate states. 




class Sim800l		
{									
  private:
	int _timeout;
	String _buffer;
		String _readSerial();
  	
  	
  public:

 	void begin();	
 	void reset(); 

 	// Methods for calling || Funciones de llamadas. 
 	bool answerCall(); 	
 	void callNumber(char* number);
 	bool hangoffCall();
 	uint8_t getCallStatus();   
 	//Methods for sms || Funciones de SMS.
	bool sendSms(char* number,char* text);	 
	String readSms(uint8_t number); //return all the content of sms 
	String delAllSms();     // return :  OK or ERROR .. 

	void signalQuality();
	void setPhoneFunctionality();
	void activateBearerProfile();
	void deactivateBearerProfile();
	//get time with the variables by reference
	void RTCtime(int *day,int *month, int *year,int *hour,int *minute, int *second);  
	String dateNet(); //return date,time, of the network
	bool updateRtc(int utc);  //Update the RTC Clock with de Time AND Date of red-.
};

#endif 