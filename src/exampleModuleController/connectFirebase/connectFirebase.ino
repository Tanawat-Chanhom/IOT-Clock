#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Config Firebase
#define FIREBASE_HOST "smart-wall-clock-c5a79.firebaseio.com"
#define FIREBASE_AUTH "mXCGAFDe6mcweyuiJcSWcvO9ViM5sNy2zVvlOwtT"

// Config connect WiFi
#define WIFI_SSID "Chanhom"
#define WIFI_PASSWORD "029959866"

// IN meaning is "buttom"
#define IN1   D7 
#define IN2   D8

int i = 0;
const String clockId = "-M3Ri7PNcCDtgyq8tbDz/";
const String firebasePath = "Clocks/" + clockId;
int clockBattery = 0;
int roomTemperature = 32;

void setup() {
  Serial.begin(9600);
  pinMode(IN1, INPUT);
  pinMode(IN2, INPUT);

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
  if (digitalRead(IN1) == HIGH) {
    Serial.println(Firebase.getInt(firebasePath+"clockBattery"));
  }

  if (digitalRead(IN2) == HIGH) {
      Firebase.setInt(firebasePath+"clockBattery", i);
      i++;
  }
  if (Firebase.failed()) {
      Serial.print("Firebase Error");
      Serial.println(Firebase.error());  
      return;
  }
}
