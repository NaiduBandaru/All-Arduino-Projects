int led=11;
void setup()
{
  pinMode(11,OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  for(int a=0; a<=255; a+=10)
  {
    analogWrite(led,a);
    Serial.println(a);
    delay(40);
  }
  for(int a=255; a>=0; a-=10)
  {
    analogWrite(led,a);
    Serial.println(a);
    delay(40);
  }
}
