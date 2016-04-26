## Library SIM800l Module for Arduino UNO
The Purpose of This library is to use the module in the most easy way and transparent.

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



For the **reset pin** they need npn transistor, this is an example circuit that you can use.

![alt text](https://github.com/cristiansteib/Sim800l/blob/master/images/RESET.png "reset_circuit")
