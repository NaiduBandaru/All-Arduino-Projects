int gas=A0;
int ledgreen=11;
int ledred=10;
void setup()
{
  pinMode(A0,INPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  Serial.begin(9600);
}
void loop()
{
 int a=analogRead(A0);
 Serial.println(a);
 if(a<150)
 {
  digitalWrite(11,HIGH);
  digitalWrite(10,LOW);
 }
 else
 {
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
 }
 delay(1000);
  
}
