#include <SoftwareSerial.h>
#include <TinyGPS++.h>
// Define pins for GPS module
#define GPS_RX 2
#define GPS_TX 3
// Define pins for GSM module
#define GSM_RX 4
#define GSM_TX 5
// Define pins for MQ sensor and buzzer
#define MQ_PIN A0
#define BUZZER_PIN 6
// Define pins for ultrasonic sensor
#define TRIG_PIN 7
#define ECHO_PIN 8
// Create software serial objects for GPS and GSM
SoftwareSerial gpsSerial(GPS_RX, GPS_TX);
SoftwareSerial gsmSerial(GSM_RX, GSM_TX);
// Create a TinyGPS++ object
TinyGPSPlus gps;
void setup() {
  // Initialize serial communication with a baud rate of 9600
  Serial.begin(9600);
  gpsSerial.begin(9600);
  gsmSerial.begin(9600);
  // Configure GPS module
  gpsSerial.println("$PMTK220,1000*1F"); // Set update rate to 1 Hz
  gpsSerial.println("$PMTK300,100,0,0,0,0*2C"); // Set NMEA sentence output to GGA only
  // Configure MQ sensor and buzzer
  pinMode(MQ_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  // Configure ultrasonic sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}
void loop() {
  // Update GPS data
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
        // Print latitude and longitude
        Serial.print("Latitude: ");
        Serial.print(gps.location.lat(), 6);
        Serial.print(" Longitude: ");
        Serial.println(gps.location.lng(), 6);
        // Check MQ sensor value
        int mqValue = analogRead(MQ_PIN);
        Serial.print("MQ sensor value: ");
        Serial.println(mqValue);
        // Check distance with ultrasonic sensor
        digitalWrite(TRIG_PIN, LOW);
        delayMicroseconds(2);
        digitalWrite(TRIG_PIN, HIGH);
        delayMicroseconds(10);
        digitalWrite(TRIG_PIN, LOW);
        long duration = pulseIn(ECHO_PIN, HIGH);
        float distance = duration * 0.034 / 2;
        Serial.print("Distance: ");
        Serial.println(distance);
        // Send SMS message with location data if MQ sensor value is above threshold and distance is less than 50 cm
        if (mqValue > 500 && distance < 50) {
          sendSMS(gps.location.lat(), gps.location.lng());
          digitalWrite(BUZZER_PIN, HIGH);
          delay(1000);
          digitalWrite(BUZZER_PIN, LOW);
        }
      }
    }
  }
}
void sendSMS(float lat, float lng) {
  // Construct SMS message with location data
  String message = "Current location: http://maps.google.com/maps?q=" + String(lat, 6) + "," + String(lng, 6);
  // Send SMS message
  Serial.println("Sending SMS...");
  gsmSerial.println("AT+CMGF=1"); // Set SMS text mode
  delay(100);
  gsmSerial.println("AT+CMGS=\"+919985172319\""); // Replace with the recipient's phone number
  delay(100);
  gsmSerial.println(message);
  delay(100);
  gsmSerial.println((char)26);
}
