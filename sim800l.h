#ifndef sim800l_h
#define sim800l_h
#include <SoftwareSerial.h>
#include "Arduino.h"

class sim800l		
{									
  public:
 	void begin();										
	bool sendSms(char* number,char* text);	
	void activateBearerProfile();
};

#endif 