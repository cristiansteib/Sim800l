/* this library is writing by  Cristian Steib.
			steibkhriz@gmail.com

*/
#include "Arduino.h"
#include "Sim800l.h"
#include <SoftwareSerial.h>

SoftwareSerial SIM(10,11);
long int timeout;
String buffer;


void Sim800l::begin(){
	SIM.begin(9600);

}


//
//PRIVATE METHODS
//
String Sim800l::_readSerial(){
  timeout=0;
  while  (!SIM.available() && timeout < 900000  ) 
  {
    timeout++;
  }
  if (SIM.available()) {
 	return SIM.readString();
  }
}


//
//PUBLIC METHODS
//

void Sim800l::Reset(){
  analogWrite(LED_ERROR_PIN,255);
  analogWrite(LED_NOTIFICATION_PIN,255);
  digitalWrite(RESET_PIN,1);
  delay(1000);
  digitalWrite(RESET_PIN,0);
  delay(1000);

  // wait for the module response
  SIM.print(F("AT\r\n"));
  while (_readSerial().indexOf("OK")==-1 ){
    SIM.print(F("AT\r\n"));
  }
  //wait for sms ready
  while (_readSerial().indexOf("SMS")==-1 ){
  }
  analogWrite(LED_NOTIFICATION_PIN,0);
  analogWrite(LED_ERROR_PIN,0);
}


void Sim800l::activateBearerProfile(){
  // set bearer parameter 
  SIM.print (F(" AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\" \r\n" ));delay(1000);
  SIM.print (F(" AT+SAPBR=3,1,\"APN\",\"internet\" \r\n" ));delay(1000);  // set apn  
  SIM.print (F(" AT+SAPBR=1,1 \r\n")); delay(1000);// activate bearer context
  SIM.print (F(" AT+SAPBR=2,1\r\n ")); delay(1000);// get context ip address
}


void Sim800l::deactivateBearerProfile(){
  SIM.print (F("AT+SAPBR=0,1\r\n "));
  delay(1500);
}


bool Sim800l::sendSms(char* number,char* text){
    SIM.print (F("AT+CMGF=1\r")); //set sms to text mode  
    delay(1000);  // #TODO: wait for OK response or expect that.
    SIM.print (F("AT+CMGS=\""));  // command to send sms
    SIM.print (number);           
    SIM.print(F("\"\r"));       
    delay(1200); 
    SIM.print (text);
    SIM.print ("\r"); 
    delay(1000);
    SIM.print((char)26);
    delay(1000);
    // verify if the buffer have some notification, that they don't need for this
    while ( ((_readSerial().indexOf("+CMTI") ) != -1 ) || ((_readSerial().indexOf("RING") ) != -1 )  ){
    }
    //expect CMGS:xxx   , where xxx is a number,for the sending sms.
    if (((_readSerial().indexOf("CMGS") ) != -1 ) ){
      return true;
    }
    else {
      return false;
    }
}


String Sim800l::readSms(uint8_t number){
  SIM.print (F("AT+CMGF=1\r")); 
  if (( _readSerial().indexOf("ER")) ==-1) {
    SIM.print (F("AT+CMGR="));
    SIM.print (number);
    SIM.print("\r");
    return _readSerial();
  }
  else
    return "";
}

