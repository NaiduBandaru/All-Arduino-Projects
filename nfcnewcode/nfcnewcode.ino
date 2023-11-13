// Include the necessary libraries
#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define SS_PIN  D2
#define RST_PIN D1

MFRC522 mfrc522(SS_PIN, RST_PIN);

const char *ssid = "Officeroom";
const char *password = "omsrisairam5*";
const char *device_token = "4e8027bce77233e8";

String URL = "http://192.168.0.8/rfidattendance/getdata.php";
String getData, Link;
String OldCardID = "";
unsigned long previousMillis = 0;

void setup() {
  delay(1000);
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
  connectToWiFi();
}

void loop() {
  if (!WiFi.isConnected()) {
    connectToWiFi();
  }

  if (millis() - previousMillis >= 15000) {
    previousMillis = millis();
    OldCardID = "";
  }
  delay(50);

  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  String CardID = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    CardID += mfrc522.uid.uidByte[i];
  }
  
  if (CardID == OldCardID) {
    return;
  } else {
    OldCardID = CardID;
  }
  
  Serial.println(CardID);
  SendCardID(CardID);
  delay(1000);
}

void SendCardID(String Card_uid) {
  Serial.println("Sending the Card ID");
  
  if (WiFi.isConnected()) {
    HTTPClient http;
    getData = "?card_uid=" + String(Card_uid) + "&device_token=" + String(device_token);
    Link = URL + getData;
    
    WiFiClient client; // Create a WiFiClient object
    if (http.begin(client, Link)) {
      int httpCode = http.GET();
      String payload = http.getString();
      http.end();

      Serial.println(httpCode);
      Serial.println(Card_uid);
      Serial.println(payload);
    }
  }
}

void connectToWiFi() {
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(1000);
}
