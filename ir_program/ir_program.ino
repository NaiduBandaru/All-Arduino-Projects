int ir=8;

void setup() 
{
 pinMode(8,INPUT);
 Serial.begin(9600);
}

void loop()
{
 
  int a=digitalRead(8);
  Serial.print("Digital Value= ");
  Serial.println(a);
  
  delay(1000);
}
