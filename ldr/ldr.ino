int ldr=A4;
int led=12;
void setup()
{
  pinMode(ldr,INPUT);
  pinMode(led,OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  int a=analogRead(A4)/4;
  Serial.println(led,a);
  delay(50);
}
