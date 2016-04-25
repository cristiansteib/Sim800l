/* this library is writing by  Cristian Steib.
			steibkhriz@gmail.com

*/
#ifndef Sim800l_h
#define Sim800l_h
#include <SoftwareSerial.h>
#include "Arduino.h"

#define RESET_PIN 2   // pin to the reset pin sim800l
#define LED_ERROR_PIN A0 //pin to indicate errors
#define LED_NOTIFICATION_PIN A1 

class Sim800l		
{									
  private:
  	String _readSerial();
  	
  public:
 	void begin();	
 	void Reset();  									
	bool sendSms(char* number,char* text);	 
	String readSms(uint8_t number); //return all the content of sms 
	String delAllSms();     // return :  OK or ERROR .. 
	void activateBearerProfile();
	void deactivateBearerProfile();
  


};

#endif 