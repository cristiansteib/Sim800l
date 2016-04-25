/* this library is writing by  Cristian Steib.
			steibkhriz@gmail.com

*/
#include "Arduino.h"
#include "Sim800l.h"
#include <SoftwareSerial.h>

SoftwareSerial SIM(RX_PIN,TX_PIN);
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
  while  (!SIM.available() && timeout < 5000000  ) 
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

void Sim800l::reset(){
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
  SIM.print (F(" AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\" \r\n" ));buffer=_readSerial();  // set bearer parameter 
  SIM.print (F(" AT+SAPBR=3,1,\"APN\",\"internet\" \r\n" ));buffer=_readSerial(); // set apn  
  SIM.print (F(" AT+SAPBR=1,1 \r\n"));delay(1200);buffer=_readSerial();// activate bearer context
  SIM.print (F(" AT+SAPBR=2,1\r\n "));delay(3000);buffer=_readSerial(); // get context ip address
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


String Sim800l::delAllSms(){ 
  SIM.print(F("at+cmgda=\"del all\"\n\r"));
  return _readSerial();  
}


void Sim800l::RTCtime(int *day,int *month, int *year,int *hour,int *minute, int *second){
  SIM.print(F("at+cclk?\r\n"));
  // if respond with ERROR try one more time. 
  buffer=_readSerial();
  if ((buffer.indexOf("ERR"))!=-1){
    delay(50);
    SIM.print(F("at+cclk?\r\n"));
  } 
  if ((buffer.indexOf("ERR"))==-1){
    buffer=buffer.substring(buffer.indexOf("\"")+1,buffer.lastIndexOf("\"")-1);  
    *year=buffer.substring(0,2).toInt();
    *month= buffer.substring(3,5).toInt();
    *day=buffer.substring(6,8).toInt();
    *hour=buffer.substring(9,11).toInt();
    *minute=buffer.substring(12,14).toInt();
    *second=buffer.substring(15,17).toInt();
 }
}

//Get the time  of the base of network
String Sim800l::dateNet() {
  SIM.print(F("AT+CIPGSMLOC=2,1\r\n "));
  buffer=_readSerial();

  if (buffer.indexOf("OK")!=-1 ){
    return buffer.substring(buffer.indexOf(":")+2,(buffer.indexOf("OK")-4));
  } else
  return "0";      
}

// Update the RTC of the module with the date of network. 
bool Sim800l::updateRtc(){
  
  activateBearerProfile();
  buffer=dateNet();
  deactivateBearerProfile();
  
  buffer=buffer.substring(buffer.indexOf(",")+1,buffer.length());
  String dt=buffer.substring(0,buffer.indexOf(","));
  String tm=buffer.substring(buffer.indexOf(",")+1,buffer.length()) ;

  int hour = tm.substring(0,2).toInt();
  int day = dt.substring(8,10).toInt();

  hour=hour+WORLDCLOCK;

  String tmp_hour;
  String tmp_day;
  //TODO : fix if the day is 0, this occur when day is 1 then decrement to 1, 
  //       will need to check the last month what is the last day .  
  if (hour<0){
    hour+=24;
    day-=1;
  }
  if (hour<10){

      tmp_hour="0"+String(hour);
  }else{
    tmp_hour=String(hour);
  }
  if (day<10){
    tmp_day="0"+String(day);    
  }else{
    tmp_day=String(day);
  }
    //for debugging
  //Serial.println("at+cclk=\""+dt.substring(2,4)+"/"+dt.substring(5,7)+"/"+tmp_day+","+tmp_hour+":"+tm.substring(3,5)+":"+tm.substring(6,8)+"-03\"\r\n");
  SIM.print("at+cclk=\""+dt.substring(2,4)+"/"+dt.substring(5,7)+"/"+tmp_day+","+tmp_hour+":"+tm.substring(3,5)+":"+tm.substring(6,8)+"-03\"\r\n");
  if ( (_readSerial().indexOf("ER"))!=-1) {return false;}else return true;

   
  }
