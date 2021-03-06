#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiUdp.h>

// Decalre ntp client
long thaiOffset = 25200;

WiFiUDP myClient;
NTPClient timeClient(myClient, "time2.navy.mi.th", thaiOffset);

const char* ssid = "Chanhom";
const char* password = "029959866";

void setup() {
  HTTPClient http;
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting..\n");
 }
 Serial.print("Connected!\n");
 timeClient.begin();
}

void loop() {
  timeClient.update();

  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());

  delay(1000);
}
