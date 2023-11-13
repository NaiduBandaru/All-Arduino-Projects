#include <SoftwareSerial.h>
SoftwareSerial sgsm(2, 3);

void setup()
{
  sgsm.begin(9600);
}

void loop()
{
  sgsm.print("AT+CMGF=1\r");
  delay(1000);
  sgsm.print("AT+CMGS=\"+919985172319\"\r");
  delay(1000);
  sgsm.println("Location of your helmet : https://goo.gl/maps/8vK12iQNEGamy4wo6 ");

  int sensorValue = analogRead(A0); // read the sensor value
  float voltage = sensorValue * (5.0 / 1023.0); // convert the sensor value to voltage
  float alcoholLevel = voltage * 1000; // calculate the alcohol level in ppm

  sgsm.print("Alcohol level: "); // include the alcohol level in the message
  sgsm.print(alcoholLevel);
  sgsm.print(" ppm");

  sgsm.write(0x1A);
  delay(10000);
}
