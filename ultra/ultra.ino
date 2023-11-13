#define trigPin 8
#define echoPin 9
#define buzzerPin 6

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
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
}
