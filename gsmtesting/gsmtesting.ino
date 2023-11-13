#include <SoftwareSerial.h>

SoftwareSerial sim800l(10, 11); // RX, TX pins of SIM800L module

void setup() {
  Serial.begin(9600); // initialize serial communication with PC
  sim800l.begin(9600); // initialize software serial communication with SIM800L module
  delay(1000); // wait for SIM800L module to initialize
}

void loop() {
  // send SMS message
  sim800l.println("AT+CMGF=1\r"); // set SMS text mode
  delay(100);
  sim800l.println("AT+CNMI=2,2,0,0,0"); // set SMS notification mode
  delay(100);
  sim800l.println("AT+CMGS=\"+919985172319\""); // replace with phone number to send SMS
  delay(100);
  sim800l.print("Hello, this is a test SMS message!"); // replace with your message
  delay(100);
  sim800l.write(26); // send Ctrl+Z to terminate SMS message
  delay(1000); // wait for SIM800L module to send SMS message
}
