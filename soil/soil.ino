int led=12;
int soil=A0;
int ledred=10;

void setup()
{
  pinMode(12,OUTPUT);
  pinMode(A0,INPUT);
  pinMode(10,OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  int a=analogRead(A0);
  Serial.println(a);
  if(a>500)
  {
    digitalWrite(12,HIGH);  
    digitalWrite(10,LOW); 
  }
 
  else
  {
    digitalWrite(12,LOW);
    digitalWrite(10,HIGH); 
  }
 
  delay(50);
}
