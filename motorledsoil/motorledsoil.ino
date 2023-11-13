int ledred=10;
int ledyellow=11;
int ledgreen=13;
int high=3;
int med=5;
int low=7;
int motor=9;
int a,b,c;
void setup()
{
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(3,INPUT);
  pinMode(5,INPUT);
  pinMode(7,INPUT);
  pinMode(9,INPUT);
}
void loop()
{
  a=digitalRead(high);
  b=digitalRead(med);
  c=digitalRead(low);
  if (a==1)
  {
    digitalWrite(10,HIGH);
    Serial.println("Red Led is ON-");
  }
  else
  {
    digitalWrite(10,LOW);
    Serial.println("Red Led is OFF-");
  }
  if (b==1)
  {
    digitalWrite(11,HIGH);
    Serial.println("yellow Led is ON");
  }
  else
  {
    digitalWrite(11,LOW);
    Serial.println("Yellow led is Off");
  }
  if (c==1)
  {
    digitalWrite(13,HIGH);
    Serial.println("Green is ON");
  }
  else
  {
    digitalWrite(13,LOW);
    Serial.print("Green Is Off");
  }
  if(a==0 && c==0)
  {
    digitalWrite(motor,HIGH);
    Serial.println("Motor led is on");
  }
  else if (a==1 && c==1)
  {
    digitalWrite(motor,LOW);
    Serial.println("Motor is on");
  }
  delay(1000);
}
