#include <SoftwareSerial.h>
SoftwareSerial BT(0,1);
String i;
void setup()
{
  BT.begin(9600);
  Serial.begin(9600);
}
void loop()
{
  while(BT.available())
  {
    delay(10);
    char c=BT.read();
    i+=c;
  }
  if(i.length()>0)
  {
    Serial.println(i);



   i="";}}
  
  
 
