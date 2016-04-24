/* this library is writing by  Cristian Steib.
			steibkhriz@gmail.com

*/
#ifndef Sim800l_h
#define Sim800l_h
#include <SoftwareSerial.h>
#include "Arduino.h"

class Sim800l		
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