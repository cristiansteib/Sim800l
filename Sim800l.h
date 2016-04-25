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
#define LED_ERROR_PIN A0 //pin to indicate errors
#define LED_NOTIFICATION_PIN A1 
#define WORLDCLOCK -3  //for the clock

class Sim800l		
{									
  private:
  	String _readSerial();
  	
  public:
 	void begin();	
 	void reset();  									
	bool sendSms(char* number,char* text);	 
	String readSms(uint8_t number); //return all the content of sms 
	String delAllSms();     // return :  OK or ERROR .. 
	void activateBearerProfile();
	void deactivateBearerProfile();
	//get time with the variables by reference
	void RTCtime(int *day,int *month, int *year,int *hour,int *minute, int *second);  
	String dateNet(); //return date,time, of the network
	bool updateRtc();  //Update the RTC Clock with de Time AND Date of red-.
};

#endif 