#include <NewPing.h>
#define t 8  
#define e 11
#define di 200 
#include "DHT.h"
#define DHTTYPE DHT11
#define dht_dpin 4


NewPing naidu(t, e, di);
int led=13;
int led1=12;
int led2=11;
int led3=10;
int buzz=7;
DHT dht(dht_dpin,DHTTYPE);

void setup() 
{
  pinMode(13,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(7,OUTPUT);
  Serial.begin(9600); 
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
delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(naidu.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
   int a=naidu.ping_cm();
  if (a<100)
  {
    digitalWrite(13,HIGH);
  }
  else
  {
    digitalWrite(13,LOW);
  }
    if (a<30)
   {
    digitalWrite(7,HIGH);
   }
     else
    {
    digitalWrite(7,LOW);
    }
}

  
}
