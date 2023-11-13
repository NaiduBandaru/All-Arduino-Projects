#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(10,11); //SIM800L Tx & Rx is connected to Arduino #11 & #10

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  mySerial.println("AT+CFUN = 0");
  updateSerial();
  delay(5000);
  mySerial.println("AT+CFUN = 1");
  updateSerial();
  delay(1000);
  mySerial.println("AT+CREG?"); //Check whether it has registered in the network. (0,1) means registered
  updateSerial();
   
   mySerial.println("AT"); 
  updateSerial();
  mySerial.println("AT+CMGF=1");
  updateSerial();
  mySerial.println("AT+CMGS=\"+919985172319\"");
  delay(1000);
  mySerial.print("SMS FROM SIM 800L"); 
  updateSerial();
  mySerial.write(26);
  delay(3000);
  
}

void loop()
{
 updateSerial();
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
