/*********
  walid abdelazeem
  website at https://edafait.com/
  blog at https://blog.edafait.com/
  webxr at https://webxr.edafait.com/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*********/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncTCP.h>
#include "LittleFS.h"
//RFID -----------------------------
#include <SPI.h>
#include <MFRC522.h>
//nodemcu -----------------------------
//Led ************************************************************************
uint8_t  LED_Pin_conected= D0;

//************************************************************************
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
//************************************************************************
// Search for parameter in HTTP POST request
const char* PARAM_INPUT_1 = "ssid";
const char* PARAM_INPUT_2 = "pass";
const char* PARAM_INPUT_3 = "ip";
const char* PARAM_INPUT_4 = "gateway";
const char* PARAM_INPUT_5 = "ipserver";

//************************************************************************
#define SS_PIN  D2  //D2
#define RST_PIN D1  //D1
#define buzzer  D8  //D8
#define ledd  D4  //D8
//************************************************************************
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
//************************************************************************
//token ************************************************************************
const char* device_token  = "edafait";
//************************************************************************
String URL = ""; //computer IP or the server domain
String getData, Link;
String OldCardID = "";
unsigned long previousMillis = 0;
//************************************************************************

//Variables to save values from HTML form ******************************
String ssid;
String pass;
String ip;
String gateway;
String ipserver;

// File paths to save input values permanently ******************************
const char* ssidPath = "/ssid.txt";
const char* passPath = "/pass.txt";
const char* ipPath = "/ip.txt";
const char* gatewayPath = "/gateway.txt";
const char* ipPathserver = "/ipserver.txt";

IPAddress localIP; //IPAddress localIP(192, 168, 1, 200); // hardcoded

IPAddress localGateway;// Set your Gateway IP address 
IPAddress ipserverip;// Set your Server IP address 

IPAddress subnet(255, 255, 0, 0);

// Timer variables

const long interval = 10000;  // interval to wait for Wi-Fi connection (milliseconds)




boolean restart = false;

// Initialize LittleFS
void initFS() {
  if (!LittleFS.begin()) {
    Serial.println("An error has occurred while mounting LittleFS");
  }
  else{
    Serial.println("LittleFS mounted successfully");
  }
}


// Read File from LittleFS
String readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\r\n", path);

  File file = fs.open(path, "r");
  if(!file || file.isDirectory()){
    Serial.println("- failed to open file for reading");
    return String();
  }

  String fileContent;
  while(file.available()){
    fileContent = file.readStringUntil('\n');
    break;
  }
  file.close();
  return fileContent;
}

// Write file to LittleFS
void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\r\n", path);

  File file = fs.open(path, "w");
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file written");
  } else {
    Serial.println("- frite failed");
  }
  file.close();
}

// Initialize WiFi
bool initWiFi() {
  if(ssid=="" || ip==""){
    Serial.println("Undefined SSID or IP address.");
    return false;
  }

  WiFi.mode(WIFI_STA);
  localIP.fromString(ip.c_str());
  localGateway.fromString(gateway.c_str());
ipserverip.fromString(ipserver.c_str());
  if (!WiFi.config(localIP, localGateway, subnet)){
    Serial.println("STA Failed to configure");
    return false;
  }
  WiFi.begin(ssid.c_str(), pass.c_str());

  Serial.println("Connecting to WiFi...");
  delay(2000);
  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("Failed to connect.");
    return false;
  }

  Serial.println(WiFi.localIP());
  return true;
}

// Replaces placeholder with LED state value
String processor(const String& var) {
 // if(var == "STATE") {
   // if(!digitalRead(ledPin)) {
    //  ledState = "ON";
  //  }
  //  else {
   //   ledState = "OFF";
  //  }
  //  return ledState;
 // }
  return String();
}

void setup() {
  // Serial port for debugging purposes
 Serial.begin(115200);
  SPI.begin();  // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
  initFS();

  // Set GPIO 2 as an OUTPUT
  pinMode(LED_Pin_conected, OUTPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(ledd, OUTPUT);
 // digitalWrite(ledPin, LOW);
  digitalWrite(LED_Pin_conected, LOW); 

  // Load values saved in LittleFS
  ssid = readFile(LittleFS, ssidPath);
  pass = readFile(LittleFS, passPath);
  ip = readFile(LittleFS, ipPath);
  gateway = readFile (LittleFS, gatewayPath);
    ipserver = readFile(LittleFS, ipPathserver);
  Serial.println(ssid);
  Serial.println(pass);
  Serial.println(ip);
  Serial.println(gateway);
    Serial.println(ipserver);
URL =ipserver+"/rfidattendance/getdata.php";
  if(initWiFi()) {
    // digitalWrite(LED_Pin_conected,HIGH);
  
   
  //  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
  //    request->send(LittleFS, "/index.html", "text/html", false, processor);
  //  });
    
  //  server.serveStatic("/", LittleFS, "/");
    
 
  //  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request) {

   //   request->send(LittleFS, "/index.html", "text/html", false, processor);
  //  });

   
   // server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request) {

   //   request->send(LittleFS, "/index.html", "text/html", false, processor);
  //  });
  //  server.begin();
  }
  else {

      digitalWrite(LED_Pin_conected,LOW);
    // Connect to Wi-Fi network with SSID and password
    Serial.println("Setting AP (Access Point)");
    // NULL sets an open Access Point
    WiFi.softAP("ESP-WIFI-MANAGER", NULL);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP); 

    // Web Server Root URL
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(LittleFS, "/wifimanager.html", "text/html");
    });
    
    server.serveStatic("/", LittleFS, "/");
    
    server.on("/", HTTP_POST, [](AsyncWebServerRequest *request) {
      int params = request->params();
      for(int i=0;i<params;i++){
        AsyncWebParameter* p = request->getParam(i);
        if(p->isPost()){
          // HTTP POST ssid value
          if (p->name() == PARAM_INPUT_1) {
            ssid = p->value().c_str();
            Serial.print("SSID set to: ");
            Serial.println(ssid);
            // Write file to save value
            writeFile(LittleFS, ssidPath, ssid.c_str());
          }
          // HTTP POST pass value
          if (p->name() == PARAM_INPUT_2) {
            pass = p->value().c_str();
            Serial.print("Password set to: ");
            Serial.println(pass);
            // Write file to save value
            writeFile(LittleFS, passPath, pass.c_str());
          }
          // HTTP POST ip value
          if (p->name() == PARAM_INPUT_3) {
            ip = p->value().c_str();
            Serial.print("IP Address set to: ");
            Serial.println(ip);
            // Write file to save value
            writeFile(LittleFS, ipPath, ip.c_str());
          }
          // HTTP POST gateway value
          if (p->name() == PARAM_INPUT_4) {
            gateway = p->value().c_str();
            Serial.print("Gateway set to: ");
            Serial.println(gateway);
            // Write file to save value
            writeFile(LittleFS, gatewayPath, gateway.c_str());
          }
            if (p->name() == PARAM_INPUT_5) {
            ipserver = p->value().c_str();
            Serial.print("ipserver set to: ");
            Serial.println(ipserver);
            // Write file to save value
            writeFile(LittleFS, ipPathserver, ipserver.c_str());
          }
          //Serial.printf("POST[%s]: %s\n", p->name().c_str(), p->value().c_str());
        }
      }
      restart = true;
      request->send(200, "text/plain", "Done. ESP will restart, connect to your router and go to IP address: " + ip);
    });
    server.begin();
     SPI.begin();  // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
  //---------------------------------------------
  }
     SPI.begin();  // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
}

void loop() {
 //---------------------------------------------
  if (millis() - previousMillis >= 15000) {
    previousMillis = millis();
    OldCardID="";
  }
  delay(50);
  //---------------------------------------------
  //look for new card
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;//got to start of loop if there is no card present
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;//if read card serial(0) returns 1, the uid struct contians the ID of the read card.
  }
  String CardID ="";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    CardID += mfrc522.uid.uidByte[i];
  }
  //---------------------------------------------
  if( CardID == OldCardID ){
    return;
  }
  else{
    OldCardID = CardID;
  }
  //---------------------------------------------
//  Serial.println(CardID);
  SendCardID(CardID);
  delay(1000);

 
  
 
}

//************send the Card UID to the website*************
void SendCardID( String Card_uid ){
  Serial.println("Sending the Card ID");
  if(WiFi.isConnected())
  {
    HTTPClient http;    //Declare object of class HTTPClient
    //GET Data
    getData = "?card_uid=" + String(Card_uid) + "&device_token=" + String(device_token); // Add the Card ID to the GET array in order to send it
    //GET methode
    Link = URL + getData;
    http.begin(Link); //initiate HTTP request   //Specify content-type header
    
    int httpCode = http.GET();   //Send the request
    String payload = http.getString();    //Get the response payload

    Serial.println(Link);   //Print HTTP return code
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(Card_uid);     //Print Card ID
    Serial.println(payload);    //Print request response payload

    if (httpCode == 200) {
      if (payload.substring(0, 5) == "login") {
        String user_name = payload.substring(5);
    Serial.println(user_name);
    pinMode(ledd, HIGH);
     digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(200);  

      }
      else if (payload.substring(0, 6) == "logout") {
        String user_name = payload.substring(6);
    Serial.println(user_name);
     pinMode(ledd, LOW);
     digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);  
        
      }
      else if (payload == "succesful") {
            pinMode(ledd, HIGH);
 digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(200);  
  
      }
      else if (payload == "available") {
            pinMode(ledd, LOW);
 digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);  
      }
      delay(100);
      http.end();  //Close connection
    }
  }
}
