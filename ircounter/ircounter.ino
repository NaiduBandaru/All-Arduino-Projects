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
  if (a==1 && laststate==0)
  {
    ircounter++;
    Serial.print(ircounter);
    Serial.println("Person Enter");
  
    digitalWrite(led,HIGH);
    delay(500);
  
    digitalWrite(led,LOW);
    delay(50);
    laststate=1;
  }
  else if(a==0)
  {
    laststate=0;
  }
}
