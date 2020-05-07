#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

#include <NTPClient.h>
#include <ESP8266HTTPClient.h>
#include <WiFiUdp.h>

#define SW_PIN D7

long thaiOffset = 21600;

WiFiUDP myClient;
NTPClient timeClient(myClient, "time.navy.mi.th", thaiOffset);

void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    
    pinMode(SW_PIN, INPUT_PULLUP);  
    
    //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;

    Serial.println("Reset wifi config?:");
    for(int i=5; i>0; i--){
      Serial.print(String(i)+" "); 
      delay(1000);
    }
    
    //reset saved settings
    if(digitalRead(SW_PIN) == LOW) // Press button
    {
      Serial.println();
      Serial.println("Reset wifi config");
      wifiManager.resetSettings(); 
    }
  
    wifiManager.autoConnect("SWC WIFI CONFIG");

    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");

    timeClient.begin();
}

void loop() {
  delay(500);
  timeClient.update();
  
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
}
