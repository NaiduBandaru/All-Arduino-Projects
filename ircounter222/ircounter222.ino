const int ir=2;
const int led=12;
int a;
int ircounter=0;
int laststate=0;
void setup()
{
  pinMode(ir,INPUT);
  pinMode(led,OUTPUT);
  Serial.begin(9600);
  
}
void loop()
{
  a=digitalRead(ir);
  if(a!=laststate)
  {
    if(a==1)
    {
      ircounter++;
      Serial.println(ircounter);
    }
    
  }
laststate=a;
if(ircounter>3)
{
  digitalWrite(led,HIGH);
  delay(10);
}
else
{
  digitalWrite(led,LOW);
  delay(10);
  
}
}
