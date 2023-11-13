#include <SoftwareSerial.h>
SoftwareSerial sgsm(2, 3);
#define trigPin 8
#define echoPin 9
#define buzzerPin 6
int sensorPin = A0;    // define analog input pin for MQ-3 sensor
int threshold = 400;   // define gas concentration threshold
void setup() {
  sgsm.begin(9600);
  pinMode(A0, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}
void loop() {
  sgsm.print("AT+CMGF=1\r");
  delay(1000);
  /*Replace XXXXXXXXXX to 10 digit mobile number & ZZ to 2 digit country code*/
  sgsm.print("AT+CMGS=\"+919985172319\"\r");
  delay(1000);
  sgsm.print("Location:");
  delay(1000); 
  digitalWrite(trigPin, LOW); // Set the trigger pin to low
  delayMicroseconds(2); // Wait for 2 microseconds
  digitalWrite(trigPin, HIGH); // Set the trigger pin to high
  delayMicroseconds(10); // Wait for 10 microseconds
  digitalWrite(trigPin, LOW); // Set the trigger pin to low
  long duration = pulseIn(echoPin, HIGH); // Measure the duration of the echo pulse
  float distance = duration * 0.034 / 2; // Calculate the distance in centimeters
  sgsm.print("Distance: ");
  sgsm.print(distance);
  sgsm.println(" cm");
  if (distance < 100) { // If the distance is less than 10 cm, turn on the buzzer
    digitalWrite(buzzerPin, HIGH);
  } else { // Otherwise, turn off the buzzer
    digitalWrite(buzzerPin, LOW);
  }
  delay(500); // Wait for 500 milliseconds before measuring again
  int sensorValue = analogRead(sensorPin); // read analog value from MQ-3 sensor
  sgsm.print("Sensor value: ");
  sgsm.println(sensorValue);              // print sensor value to serial monitor
  if(sensorValue > threshold){              // check if gas concentration is above threshold
    digitalWrite(buzzerPin, HIGH);          // turn buzzer on                            // wait for 0.5 second
  }
  delay(1000);                              // wait for 1 second before taking next reading
}
