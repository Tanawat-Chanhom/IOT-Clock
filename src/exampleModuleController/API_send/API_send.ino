#include "ESP8266HTTPClient.h"
#include "ESP8266WiFi.h"
 
const char* ssid = "WhiteOak2018_2A";
const char* password =  "0864491608";
 
void setup() {
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password); 
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
 
}
 
void loop() {
 
 if(WiFi.status()== WL_CONNECTED){
  Serial.println("WiFi connection");
 
//   HTTPClient http;   
// 
//   http.begin("http://jsonplaceholder.typicode.com/posts/1");
//   http.addHeader("Content-Type", "application/json");            
// 
//   int httpResponseCode = http.PUT("https://us-central1-smart-wall-clock-c5a79.cloudfunctions.net/node/update/dw");   
// 
//   if(httpResponseCode>0){
// 
//    String response = http.getString();   
// 
//    Serial.println(httpResponseCode);
//    Serial.println(response);          
// 
//   }else{
// 
//    Serial.print("Error on sending PUT Request: ");
//    Serial.println(httpResponseCode);
// 
//   }
// 
//   http.end();
 
 }else{
    Serial.println("Error in WiFi connection");
 }
 
  delay(10000);
}
