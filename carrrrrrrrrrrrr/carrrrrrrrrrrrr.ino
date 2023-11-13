#include <SoftwareSerial.h>
SoftwareSerial BT(0,1); 
int input1 = 8;
int input2 = 9;
int input3 = 10;
int input4 = 11;
String data;
void setup() 
{
  BT.begin(9600);
  pinMode(input1,OUTPUT);
  pinMode(input2,OUTPUT);
  pinMode(input3,OUTPUT);
  pinMode(input4,OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  while (BT.available() > 0) {
    data = BT.readStringUntil('\n');
    data.trim();
    Serial.println(data);
    if(data == "forward") {
      digitalWrite(input1,HIGH);
      digitalWrite(input3,HIGH);
      digitalWrite(input2,LOW);
      digitalWrite(input4,LOW);
    }
    else if(data == "backward") {
      digitalWrite(input1,LOW);
      digitalWrite(input3,LOW);
      digitalWrite(input2,HIGH);
      digitalWrite(input4,HIGH);
    }
    else if(data == "left") {
      digitalWrite(input1,LOW);
      digitalWrite(input2,HIGH);
      digitalWrite(input3,HIGH);
      digitalWrite(input4,LOW);
    }
    else if(data == "right") {
      digitalWrite(input1,HIGH);
      digitalWrite(input2,LOW);
      digitalWrite(input3,LOW);
      digitalWrite(input4,HIGH);
    }
    else if(data == "stop") {
      digitalWrite(input1,LOW);
      digitalWrite(input2,LOW);
      digitalWrite(input3,LOW);
      digitalWrite(input4,LOW);
    }
  }
}
