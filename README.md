## Library SIM800l Module for Arduino UNO
The Purpose of This library is to use the module in the most easy way and transparent.

To download. click the DOWNLOAD ZIP button, rename the uncompressed folder **Sim800l**. 
  Check that the *Sim800l* folder contains Sim800l.cpp and Sim800l.h

Go to arduino IDE Sketch >> Import Library >> add library... Select the folder Sim800l

OR 

Place the Sim800l library folder your arduinosketchfolder/libraries/ folder. 
You may need to create the libraries subfolder if its your first library. Restart the IDE.


## connections & pinouts
Arduino Uno  |   Sim800l   |    Notes  
-------------|-------------|------------
+5v| (3.8v)~(4.4v)!| Power supply input
10 RX_PIN | TX |  
11 TX_PIN | RX |
2   RESET_PIN | RST| Reset Pin
GND | GND | 


You can regulate the voltage to the desired with this, is not the best,
but for start it's easy.

![alt text](https://github.com/cristiansteib/Sim800l/blob/master/images/power_supply.png "LM317")



For the **reset pin** they need NPN transistor, this is an example circuit that you can use.

![alt text](https://github.com/cristiansteib/Sim800l/blob/master/images/RESET.png "reset_circuit")
