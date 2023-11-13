#include "DHT.h"
#define DHTTYPE DHT11
#define dht_dpin 4
DHT dht(dht_dpin,DHTTYPE);
float t;
float h;
int led=13;
int led2=12;
int buzz=7;
void setup()
{
  pinMode(13,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(12,OUTPUT);
 
  Serial.begin(9600);
  dht.begin();
 
}
void loop()
{
 float h=dht.readHumidity();
 float t=dht.readTemperature();

 Serial.print("Humidity= ");
 Serial.println(h);
 
 Serial.print("temperature= ");
 Serial.println(t);
  delay(1000);
 
  
  if (h>30)
  {
    digitalWrite(7,HIGH);
  }
  else 
  {
    digitalWrite(7,LOW);
  }
  if (t>25)
  {
    digitalWrite(12,HIGH);
  }
  else
  {
    digitalWrite(12,LOW);
  }
  
}
