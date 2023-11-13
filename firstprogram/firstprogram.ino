#include<SoftwareSerial.h>
SoftwareSerial BT(0,1);
String i;
int m1p=2;
int m1n=3;
int m2p=4;
int m2n=5;
void setup()
{
  BT.begin(9600);
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
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
  if(i=="forward")
  {
    digitalWrite(m1p,HIGH);
    digitalWrite(m1n,LOW);
    digitalWrite(m2p,HIGH);
    digitalWrite(m2n,LOW);
  }
  else if(i=="backward")
  {
    digitalWrite(m1p,LOW);
    digitalWrite(m1n,HIGH);
    digitalWrite(m2p,LOW);
    digitalWrite(m2n,HIGH);
  }
   
  else if(i=="right")
  {
    digitalWrite(m1p,LOW);
    digitalWrite(m1n,HIGH);
    digitalWrite(m2p,HIGH);
    digitalWrite(m2n,LOW);
  }
 
  else if(i=="left")
  {
    digitalWrite(m1p,HIGH);
    digitalWrite(m1n,LOW);
    digitalWrite(m2p,LOW);
    digitalWrite(m2n,HIGH);
  }
   else if(i=="stop")
   {
    digitalWrite(m1p,LOW);
    digitalWrite(m1n,LOW);
    digitalWrite(m2p,LOW);
    digitalWrite(m2n,LOW);
  } 
  i=""; 
}
