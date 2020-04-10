#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Config Firebase
#define FIREBASE_HOST "smart-wall-clock-c5a79.firebaseio.com"
#define FIREBASE_AUTH "mXCGAFDe6mcweyuiJcSWcvO9ViM5sNy2zVvlOwtT"

// Config connect WiFi
#define WIFI_SSID "waroo"
#define WIFI_PASSWORD "t11w24j18j31"

int i = 0;

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  Serial.println(Firebase.getInt("number"));
//  Firebase.setInt("number", i);
  if (Firebase.failed()) {
      Serial.print("Firebase Error");
      Serial.println(Firebase.error());  
      return;
  }
//  Serial.print("set /number to ");
//  Serial.println(Firebase.getInt("number"));
//  
//  i++;
//  delay(500);
}
