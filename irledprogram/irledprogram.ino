int ir=8;
int led=12;

void setup() 
{
 pinMode(8,INPUT);
 pinMode(12,OUTPUT);
 Serial.begin(9600);
}

void loop() 
{
 int a=digitalRead(8);
   if (a==0)
   { 
    
    digitalWrite(led,HIGH);
    Serial.println(a);
    
  }
  
  else 
  {
  digitalWrite(led,LOW);
  }
}
