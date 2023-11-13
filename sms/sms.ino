#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // Define software serial on pins 10 (RX) and 11 (TX)

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(1000);

  // Check if SIM800L is responsive
  sendATCommand("AT");

  // Set SMS text mode
  sendATCommand("AT+CMGF=1");

  // Set phone number to which you want to send the SMS
  sendATCommand("AT+CMGS=\"+919985172319\"");
  delay(1000);

  // Enter the SMS text followed by Ctrl+Z (ASCII 26) to send the message
  mySerial.println("SMS FROM SIM800L");
  mySerial.write(26);
  delay(1000);
}

void loop() {
  // Empty loop
}

void sendATCommand(String command) {
  mySerial.println(command);
  delay(1000);
  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
}
