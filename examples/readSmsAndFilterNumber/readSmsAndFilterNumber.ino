/* this library is writing by  Cristian Steib.
 *      steibkhriz@gmail.com
 *
 *
 *   The next example show how easy is to manage sms, and filtering the number  
 *
 *
 *  Designed to work with the GSM Sim800l,maybe work with SIM900L
 *  
 *     This library use SoftwareSerial, you can define de RX and TX pin
 *     in the header "Sim800l.h" ,by default the pin is RX=10 TX=11..
 *     be sure that gnd is attached to arduino too. 
 *     You can also change the other preferred RESET_PIN
 *    
 *     Esta libreria usa SoftwareSerial, se pueden cambiar los pines de RX y TX
 *     en el archivo header, "Sim800l.h", por defecto los pines vienen configurado en
 *     RX=10 TX=11.  
 *     Tambien se puede cambiar el RESET_PIN por otro que prefiera
 *     
 *    PINOUT: 
 *        _____________________________
 *       |  ARDUINO UNO >>>   SIM800L  |
 *        -----------------------------
 *            GND      >>>   GND
 *        RX  10       >>>   TX    
 *        TX  11       >>>   RX
 *       RESET 2       >>>   RST 
 *                 
 *   POWER SOURCE 4.2V >>> VCC
 *
 *    Created on: April 20, 2016
 *        Author: Cristian Steib
 *        
 *
*/

#include <Sim800l.h>
#include <SoftwareSerial.h> //is necesary for the library!! 
Sim800l Sim800l;  //to declare the library



String textSms,numberSms;
uint8_t index1;
uint8_t LED2=13; // use what you need 
bool error;



void setup(){
 
pinMode(LED2,OUTPUT); 
digitalWrite(LED2,HIGH);

    Serial.begin(9600); // only for debug the results . 
    Sim800l.begin(); // initializate the library. 
    Sim800l.reset();
    //don't forget to catch the return of the function delAllSms! 
    error=Sim800l.delAllSms(); //clean memory of sms;
    
}

void loop(){
    textSms=Sim800l.readSms(1); //read the first sms
    
    if (textSms.indexOf("OK")!=-1) //first we need to know if the messege is correct. NOT an ERROR
        {           
        if (textSms.length() > 7)  // optional you can avoid SMS empty
            {
                
                numberSms=Sim800l.getNumberSms(1);  // Here you have the number
                //for debugin
                Serial.println(numberSms); 
                textSms.toUpperCase();  // set all char to mayus ;)

                if (textSms.indexOf("TURNON")!=-1){
                    Serial.println("LED TURN ON");
                    digitalWrite(LED2,1);
                }
                else if (textSms.indexOf("TURNOFF")!=-1){
                    Serial.println("LED TURN OFF");
                    digitalWrite(LED2,0);

                }
                else{
                    Serial.println("Not Compatible ...sorry.. :D");
                }


            Sim800l.delAllSms(); //do only if the message is not empty,in other case is not necesary
             //delete all sms..so when receive a new sms always will be in first position
            } 



        }
    }
 
