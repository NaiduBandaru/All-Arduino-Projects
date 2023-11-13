const int sensorPin = A0;    // define analog input pin for MQ-3 sensor
const int buzzerPin = 6;     // define digital output pin for buzzer
const int trigPin = 8;       // define digital output pin for ultrasonic sensor trigger
const int echoPin = 9;      // define digital input pin for ultrasonic sensor echo
const int threshold = 400;   // define gas concentration threshold
long duration, distance;     // variables for ultrasonic sensor measurement

void setup() {
  pinMode(buzzerPin, OUTPUT); // set buzzer pin as output
  pinMode(trigPin, OUTPUT);   // set ultrasonic sensor trigger pin as output
  pinMode(echoPin, INPUT);    // set ultrasonic sensor echo pin as input
  Serial.begin(9600);         // initialize serial communication at 9600 baud
}

void loop() {
  // measure distance using ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0343;
  
  // read gas concentration using MQ-3 sensor
  int sensorValue = analogRead(sensorPin);
  Serial.print("Gas concentration: ");
  Serial.print(sensorValue);
  Serial.print(", Distance: ");
  Serial.println(distance);
  
  // trigger buzzer if gas concentration is above threshold and distance is less than 50cm
  if(sensorValue > threshold && distance > 50){
    digitalWrite(buzzerPin, HIGH);          // turn buzzer on
    delay(500);                             // wait for 0.5 second
    digitalWrite(buzzerPin, LOW);           // turn buzzer off
    delay(500);                             // wait for 0.5 second
  }
  
  delay(1000);                              // wait for 1 second before taking next reading
}
