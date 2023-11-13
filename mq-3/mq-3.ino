int sensorPin = A0;    // define analog input pin for MQ-3 sensor
int buzzerPin = 6;     // define digital output pin for buzzer
int threshold = 400;   // define gas concentration threshold

void setup() {
  pinMode(buzzerPin, OUTPUT); // set buzzer pin as output
  Serial.begin(9600);         // initialize serial communication at 9600 baud
}

void loop() {
  int sensorValue = analogRead(sensorPin); // read analog value from MQ-3 sensor
  Serial.print("Sensor value: ");
  Serial.println(sensorValue);              // print sensor value to serial monitor
  
  if(sensorValue > threshold){              // check if gas concentration is above threshold
    digitalWrite(buzzerPin, HIGH);          // turn buzzer on
    delay(500);                             // wait for 0.5 second
    digitalWrite(buzzerPin, LOW);           // turn buzzer off
    delay(500);                             // wait for 0.5 second
  }
  
  delay(1000);                              // wait for 1 second before taking next reading
}
