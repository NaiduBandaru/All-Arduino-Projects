#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <inetGSM.h>
static const int RXPin = 4, TXPin = 3;
InetGSM inet;
TinyGPSPlus gps;
SoftwareSerial serialGps(RXPin, TXPin);
char msg[50];
boolean started = false;
const char* dataCoord = "";
void setup() {
  // Serial connection.
  Serial.begin(19200);
  Serial.print(F("------------------------------------------------- \r\n"));
  Serial.println(F("Starting App Tracking Arduino"));
  Serial.print(F("------------------------------------------------- \r\n"));
  // Turn on GPRS
  powerUpGprs();
  // Start configuration of shield SIM900 with baudrate.
  if (gsm.begin(2400)) {
    Serial.println(F("\nstatus=READY"));
    started = true;
  } else Serial.println(F("\nstatus=IDLE"));
  if (started)
    connectToInternet();
  // Start configuration of shield GPS NEO-6M with baudrate.
  serialGps.begin(9600);
}
void loop() {
  // This sketch displays information every time a new sentence is correctly encoded.
  while (serialGps.available() > 0)
    if (gps.encode(serialGps.read())) getGpsPosition();
}
/**
  Power up
*/
void powerUpGprs() {
  pinMode(9, OUTPUT);
  delay(100);
  digitalWrite(9, HIGH);
  Serial.println(F("\nPower Up SIM900!"));
}
/**
  Connect to Internet via GSM
*/
void connectToInternet() {
  Serial.print(F("\r\n"));
  Serial.print(F("------------------------------------------------- \r\n"));
  Serial.print(F(" CONNECT TO INTERNET \r\n"));
  Serial.print(F("------------------------------------------------- \r\n"));
  //GPRS attach, put in order APN, username and password.
  if (inet.attachGPRS("zap.vivo.com.br", "vivo", "vivo"))
    Serial.println(F("status=ATTACHED"));
  else
    Serial.println(F("status=ERROR"));
  delay(1000);
  //Read IP address.
  gsm.SimpleWriteln("AT+CIFSR");
}
/**
  Get GPS position
*/
void getGpsPosition() {
  Serial.print(F("\r\n\r\n"));
  Serial.print(F("------------------------------------------------- \r\n"));
  Serial.print(F(" GET POSITON \r\n"));
  Serial.print(F("------------------------------------------------- \r\n"));
  // geolocation
  TinyGPSDate &d = gps.date;
  TinyGPSTime &t = gps.time;
  char* timestamp;
  if (!d.isValid()) {
    timestamp = "00/00/0000 00:00:00";
  } else {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d %02d:%02d:%02d",
      d.day(), d.month(), d.year(),
      t.hour(), t.minute(), t.second());
    timestamp = sz;
  }
  String position = String("");
  position.concat(String("timestamp=") + String(timestamp));
  position.concat(String("&latitude=") + String(gps.location.lat(), 6));
  position.concat(String("&longitude=") + String(gps.location.lng(), 6));
  position.concat(String("&altitude=") + String(gps.altitude.meters()));
  position.concat(String("&speed=") + String(gps.speed.kmph()));
  Serial.println(dataCoord);
  send2Api();
}
/**
  Send To API, The function inet.httpPOST(),
  this is submit method POST via http request
*/
void send2Api() {
  Serial.print(F("\r\n\r\n"));
  Serial.print(F("------------------------------------------------- \r\n"));
  Serial.print(F(" SEND TO API\r\n"));
  Serial.print(F("------------------------------------------------- \r\n"));
  // Read until serial buffer is emapty.
  gsm.WhileSimpleRead();
  // TCP Client HTTP, send a POST request to the server and save the reply.
  int numdata = inet.httpPOST("api.myapp.com.br", 80, "/geolocations ", dataCoord, msg, 100);
  // Print the results.
  Serial.print(F("\nNumber of data received: "));
  Serial.println(numdata);
  Serial.print(F("\nData received: "));
  Serial.println(msg);
};