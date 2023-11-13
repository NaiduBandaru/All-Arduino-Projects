#include <SoftwareSerial.h>

// Configure software serial communication with GSM and GPS modules
SoftwareSerial gsmSerial(2, 3); // RX, TX for GSM module
SoftwareSerial gpsSerial(4, 5); // RX, TX for GPS module

// Define variables for GPS data
String latitude, longitude;
float speed, altitude;

void setup() {
  // Start serial communication with the computer
  Serial.begin(9600);

  // Start software serial communication with GSM and GPS modules
  gsmSerial.begin(9600);
  gpsSerial.begin(9600);

  // Send AT commands to GSM module to check its functionality
  gsmSerial.println("AT");
  delay(1000);
  gsmSerial.println("AT+CPIN?");
  delay(1000);
  gsmSerial.println("AT+CREG?");
  delay(1000);

  // Send AT commands to GPS module to configure it
  gpsSerial.println("$PMTK220,1000"); // Set update rate to 1 Hz
  gpsSerial.println("$PMTK300,200,0,0,0,0"); // Enable only GPRMC sentence

  // Wait for GPS module to start sending data
  while (!gpsSerial.available()) {
    delay(1000);
  }
}

void loop() {
  // Read GPS data
  if (gpsSerial.find("$GPRMC")) {
    // Extract latitude, longitude, speed, and altitude from GPRMC sentence
    String data = gpsSerial.readStringUntil('\r');
    latitude = data.substring(20, 29);
    longitude = data.substring(32, 42);
    speed = data.substring(45, 50).toFloat();
    altitude = data.substring(52, 57).toFloat();
  }

  // Send GPS data to GSM module as an SMS message
  gsmSerial.print("AT+CMGF=1\r"); // Set SMS text mode
  delay(1000);
  gsmSerial.print("AT+CMGS=\"+91xxxxxxxxxx\"\r"); // Replace with recipient's phone number
  delay(1000);
  gsmSerial.print("Latitude: ");
  gsmSerial.println(latitude);
  gsmSerial.print("Longitude: ");
  gsmSerial.println(longitude);
  gsmSerial.print("Speed: ");
  gsmSerial.print(speed);
  gsmSerial.println(" knots");
  gsmSerial.print("Altitude: ");
  gsmSerial.print(altitude);
  gsmSerial.println(" m");
  delay(1000);
  gsmSerial.write(0x1A); // End message
  delay(1000);
}
