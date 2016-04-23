#ifndef sim800l_h
#define sim800l_h
#include <SoftwareSerial.h>
#include "Arduino.h"

class sim800l		
{									
  private:
  	String _readSerial();
  	bool _recvFind(String target,String Data);


  public:
 	void begin();										
	bool sendSms(char* number,char* text);	
	void activateBearerProfile();
  


};

#endif 