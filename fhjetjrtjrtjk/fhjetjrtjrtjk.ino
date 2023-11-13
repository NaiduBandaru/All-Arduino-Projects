#include <TinyGPS++.h>
#include <SoftwareSerial.h>

SoftwareSerial GPS(8,9);

String latitude,logitude;

TinyGPSPlus gps;

void setup() 
{
  Serial.begin(9600);
  GPS.begin(9600);
}

void loop() 
{
  bool newData = false;
  unsigned long chars; 
  unsigned short sentences, failed;
 
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (GPS.available())
    {
      char c = GPS.read();
      //GPS.print(c);
      if (gps.encode(c)) 
      newData = true;  
    }
  }
   if (gps.location.isValid())
  {
    Serial.print("Location : ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(",");
    Serial.println(gps.location.lng(), 6);
   }
}
