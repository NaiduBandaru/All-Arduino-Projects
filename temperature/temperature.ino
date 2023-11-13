int temerature=A0;
int led=11;
float tempc;
float tempf;

void setup()
{
  pinMode(led,OUTPUT);
  Serial.begin(9600); 
}
 void loop()
{
  float a=analogRead(A0);
  float analogWrite(A0);
  a=(a*500)/1023;
  tempc=a;
  tempf=(a*1.8)+32;
  Serial.print("Temparature Celcius= ");
  Serial.println(tempc);
  if (a>30)
  {
    digitalWrite(led,HIGH);
  }
  else
  {
    digitalWrite(led,LOW);
  }
  Serial.print("Temparature Fahren= ");
  Serial.println(tempf);
  delay(1000);
  
}
