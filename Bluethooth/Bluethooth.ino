#include<SoftwareSerial.h>
SoftwareSerial BT(0,1);
String i;
int led=13;
int fan=12;
void setup()
{
  BT.begin(9600);
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
}
void loop()
{
  while(BT.available())
  {
    delay(10);
    char c=BT.read();
    i +=c;
  }
  if(i.length()>0)
  {
    Serial.println(i);
  }
  {
    if (i=="fan on")
    {
      digitalWrite(fan,HIGH);
    }
    else if (i=="fan off")
    {
      digitalWrite(fan,LOW);
    }
    if (i=="light on")
    {
      digitalWrite(led,HIGH);
    }
    else if (i=="light off")
    {
      digitalWrite(led,LOW);
    }
    i="";
  }
}
