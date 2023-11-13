#include "DHT.h"
#define DHTTYPE DHT11
#define dht_dpin 4


#include <NewPing.h>
#define t  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define e  11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define di 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

DHT dht(dht_dpin,DHTTYPE);

float temp;
float h;
int led=13;
int led2 =10;
int led3 =8;
int buzz=7;
NewPing surya(t, e, di); // NewPing setup of pins and maximum distance.

void setup() 
{
  pinMode(10,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(7,OUTPUT);
  Serial.begin(9600); 
}

void loop() 
{ 

delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(surya.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
   int a=surya.ping_cm();
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
float h=dht.readHumidity();
float temp=dht.readTemperature();
Serial.print("Humidity= ");
Serial.println(h);
Serial.print("temperature= ");
Serial.println(temp);
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
