#include <NewPing.h>
#define TRIGGER_PIN 2
#define ECHO_PIN 3
#define MAX_DISTANCE 200
#define FLAME_SENSOR_PIN A0
#define MOTOR_PIN1 4
#define MOTOR_PIN2 5
#define MOTOR_PIN3 6
#define MOTOR_PIN4 7
#define WATER_PUMP_PIN 8
#define FLAME_THRESHOLD 600
NewPing ultrasonicSensor(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void moveForward() {
  digitalWrite(MOTOR_PIN1, HIGH);
  digitalWrite(MOTOR_PIN2, LOW);
  digitalWrite(MOTOR_PIN3, HIGH);
  digitalWrite(MOTOR_PIN4, LOW);
}

void moveBackward() {
  digitalWrite(MOTOR_PIN1, LOW);
  digitalWrite(MOTOR_PIN2, HIGH);
  digitalWrite(MOTOR_PIN3, LOW);
  digitalWrite(MOTOR_PIN4, HIGH);
}

void stopRobot() {
  digitalWrite(MOTOR_PIN1, LOW);
  digitalWrite(MOTOR_PIN2, LOW);
  digitalWrite(MOTOR_PIN3, LOW);
  digitalWrite(MOTOR_PIN4, LOW);
}

void turnOnWaterPump() {
  digitalWrite(WATER_PUMP_PIN, HIGH);
}

void turnOffWaterPump() {
  digitalWrite(WATER_PUMP_PIN, LOW);
}

void setup() {
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(MOTOR_PIN3, OUTPUT);
  pinMode(MOTOR_PIN4, OUTPUT);
  pinMode(WATER_PUMP_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned int distance = ultrasonicSensor.ping_cm();
  int flameValue = analogRead(FLAME_SENSOR_PIN);
  if (flameValue > FLAME_THRESHOLD) {
    stopRobot();
    turnOnWaterPump();
    Serial.println("Fire detected! Activating water pump.");
  } else {
    if (distance <= 20) {
      moveBackward();
      delay(500);
      stopRobot();
    } else {
      moveForward();
    }
    turnOffWaterPump();
  }
}
