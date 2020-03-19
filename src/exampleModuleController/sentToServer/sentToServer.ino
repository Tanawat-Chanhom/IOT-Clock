#include "ESP8266HTTPClient.h"
#include "ESP8266WiFi.h"
#include "ArduinoJson.h"
#include <WiFiClientSecure.h>

#define IN6   D6 
 
const char* ssid = "WhiteOak2018_2A";
const char* password =  "0864491608";
const char* host = "us-central1-smart-wall-clock-c5a79.cloudfunctions.net";
const int httpsPort = 443;
const char* FIREBASE_FINGERPRINT =  "058b82bcfeb3f43afa4f7745d2d048e36e29bdce";
const String CLOCK_ID = "dw";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(IN6, INPUT);
 
  WiFi.begin(ssid, password); 
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
}

void loop() {
  byte val = digitalRead(IN6);
  
  if(WiFi.status()== WL_CONNECTED){
    delay(1000);
    if (val == HIGH){
      
      String respone = sending();
      Serial.println(respone);
       
    }
  } else {
    Serial.println("Error in WiFi connection");
  }
}

String sending() {
  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host);

  Serial.printf("Using fingerprint '%s'\n", FIREBASE_FINGERPRINT);
  client.setFingerprint(FIREBASE_FINGERPRINT);

  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return "false";
  }

  String url = "/node/update/dw";
  String data = "{\"tem\": 0,\"battery\": 0}";
  Serial.print("requesting URL: ");
  Serial.println(url);
  Serial.print("Data: ");
  Serial.println(data);

  client.print(String("PUT ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Content-Type: application/json\r\n" +
               data);

  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line.startsWith("{\"state\":\"success\"")) {
    Serial.println("esp8266/Arduino CI successfull!");
  } else {
    Serial.println("esp8266/Arduino CI has failed");
  }
  Serial.println("reply was:");
  Serial.println("==========");
  Serial.println(line);
  Serial.println("==========");
  Serial.println("closing connection");
  return line;
}
