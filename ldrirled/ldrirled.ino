int ldr=8;
int ir=9;
int led=12;
void setup()
{
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  pinMode(12,OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  int a=digitalRead(8);
  int b=digitalRead(9);
  if(a==1 and b==0)
  {
    digitalWrite(led,HIGH);
    Serial.println("Person Entred");
    
    
    
  }
  else
  {
    digitalWrite(led,LOW);
    
  }
  delay(1000);
  
}
