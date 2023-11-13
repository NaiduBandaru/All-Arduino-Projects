#include <SoftwareSerial.h>
#include <TinyGPS.h>
int state = 0;
const int pin = 12;
float gpslat, gpslon;
TinyGPS gps;
SoftwareSerial sgps(4, 5);
SoftwareSerial sgsm(2, 3);

#define trigPin 8
#define echoPin 9
#define buzzerPin 6
int sensorPin = A0;    // define analog input pin for MQ-3 sensor
int threshold = 400;   // define gas concentration threshold
void setup() {
  sgsm.begin(9600);
  sgps.begin(9600);
  Serial.begin(9600); // Initialize serial communication at 9600 baud
  pinMode(A0, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}
void loop() {
  sgps.listen();
  while (sgps.available())
  {
    int c = sgps.read();
    if (gps.encode(c))
    {
      gps.f_get_position(&gpslat, &gpslon);
    }
  }
    if (digitalRead(pin) == HIGH && state == 0) {
      sgsm.listen();
      sgsm.print("\r");
      delay(1000);
      sgsm.print("AT+CMGF=1\r");
      delay(1000);
      /*Replace XXXXXXXXXX to 10 digit mobile number &
        ZZ to 2 digit country code*/
      sgsm.print("AT+CMGS=\"+919985172319\"\r");
      delay(1000);
      //The text of the message to be sent.
      sgsm.print("Latitude :");
      sgsm.println(gpslat, 6);
      sgsm.print("Longitude:");
      sgsm.println(gpslon, 6);
      delay(1000);
      sgsm.write(0x1A);
      delay(1000);
      state = 1;
    }
  if (digitalRead(pin) == LOW) {
      state = 0;
    }
    delay(1000);
  digitalWrite(trigPin, LOW); // Set the trigger pin to low
  delayMicroseconds(2); // Wait for 2 microseconds
  digitalWrite(trigPin, HIGH); // Set the trigger pin to high
  delayMicroseconds(10); // Wait for 10 microseconds
  digitalWrite(trigPin, LOW); // Set the trigger pin to low
  long duration = pulseIn(echoPin, HIGH); // Measure the duration of the echo pulse
  float distance = duration * 0.034 / 2; // Calculate the distance in centimeters
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  if (distance < 100) { // If the distance is less than 10 cm, turn on the buzzer
    digitalWrite(buzzerPin, HIGH);
  } else { // Otherwise, turn off the buzzer
    digitalWrite(buzzerPin, LOW);
  }
  delay(500); // Wait for 500 milliseconds before measuring again
  int sensorValue = analogRead(sensorPin); // read analog value from MQ-3 sensor
  Serial.print("Sensor value: ");
  Serial.println(sensorValue);              // print sensor value to serial monitor
  if(sensorValue > threshold){              // check if gas concentration is above threshold
    digitalWrite(buzzerPin, HIGH);          // turn buzzer on                            // wait for 0.5 second
  }
  delay(1000);                              // wait for 1 second before taking next reading
}
