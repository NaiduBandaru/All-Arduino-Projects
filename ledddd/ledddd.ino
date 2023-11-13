#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial bluetooth(10, 11); // RX, TX pins for Bluetooth module
LiquidCrystal_I2C lcd(0x27, 16, 2); // Address, columns, rows for LCD

const int irSensorPins[] = {2, 3, 4, 5}; // IR sensor pins
const int buzzerPin = 6; // Buzzer pin
int availableSlots = 4; // Total number of parking slots

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(irSensorPins[i], INPUT);
  }
  pinMode(buzzerPin, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.print("Available: " + String(availableSlots));
  bluetooth.begin(9600);
}

void loop() {
  int filledSlots = 0;
  
  for (int i = 0; i < 4; i++) {
    if (digitalRead(irSensorPins[i]) == LOW) {
      filledSlots++;
    }
  }

  int emptySlots = availableSlots - filledSlots;
  lcd.setCursor(0, 1);
  lcd.print("Empty: " + String(emptySlots) + " ");
  
  if (emptySlots == 0) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  // Send data to mobile device via Bluetooth
  if (bluetooth.available()) {
    char command = bluetooth.read();
    
    if (command == 'A') { // Request for available slots
      bluetooth.print(emptySlots);
    }
  }
}
