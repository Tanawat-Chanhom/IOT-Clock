#include <Stepper.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiUdp.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>

// MT meaning is "MotorSerial"
#define MS1   D1
#define MS2   D2
#define MS3   D3
#define MS4   D4

// SS meaning is "Sensor"
#define SS1   D5
#define SS2   D6

// IN meaning is "buttom"
#define IN1   D7 
#define IN2   D8

// Config Firebase
#define FIREBASE_HOST "smart-wall-clock-c5a79.firebaseio.com"
#define FIREBASE_AUTH "mXCGAFDe6mcweyuiJcSWcvO9ViM5sNy2zVvlOwtT"

// initialize variable
const String clockId = "123";
const String firebasePath = "Clocks/" + clockId + "/";
String clockStatus = "";
int clockBattery = 0;
int roomTemperature = 0;

int val;
int initStatus;
int initTime;
int controller = 32;
int start_hour = 12;
int start_min = 20;
int counter_stap = 1;
long thaiOffset = 25200;
const int stepsPerRevolution = 2048;
const int steps = 60;

// initialize library
Stepper myStepper(stepsPerRevolution, MS4, MS2, MS3, MS1);
WiFiUDP myClient;
NTPClient timeClient(myClient, "time2.navy.mi.th", thaiOffset);

void setup() {
  Serial.begin(9600);
  
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  pinMode(MS4, OUTPUT);

  pinMode(SS1, INPUT);
  pinMode(SS2, INPUT);
  
  pinMode(IN1, INPUT);
  pinMode(IN2, INPUT);

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  Serial.println("Reset wifi config?:");
  for(int i=5; i>0; i--){
    Serial.print(String(i)+" "); 
    delay(1000);
  }
  //reset saved settings
  if(digitalRead(IN1) == HIGH) // Press button
  {
    Serial.println();
    Serial.println("Reset wifi config");
    wifiManager.resetSettings(); 
  }
  wifiManager.autoConnect("SWC WIFI CONFIG");
  Serial.println("connected...");

  // initialize Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  timeClient.begin();
  timeClient.update();
  myStepper.setSpeed(12);
//  initStatus = _init();
}

void _update(String variableName = "", String value = "") {
  if (variableName == "clockBattery") {
    clockBattery = value.toInt();
  } else if (variableName == "roomTemperature") {
    roomTemperature = value.toInt();
  } else if (variableName == "clockStatus") {
    clockStatus = value;
  }
  Firebase.setInt(firebasePath+"clockBattery", clockBattery);
  Firebase.setInt(firebasePath+"roomTemperature", roomTemperature);
  Firebase.setString(firebasePath+"clockStatus", clockStatus);
}

void clockFunction(int number) {
  switch (number) {
  case 1: // Reset
    _init();
    Firebase.setInt(firebasePath+"clockFunction", 0);
    break;
  case 2: // Move Steper motor to right
    myStepper.step(-20);
    Serial.println("Step -");
    break;
  case 3: // Move Steper motor to left
    myStepper.step(20);
    Serial.println("Step -");
    break;
  default:
    Serial.println("Function Error");
    break;
  }
}

int timeCal(int hour, int min) {
  int hourDeffToMin = (hour - 18) * 60;
  int timeDeff = min + hourDeffToMin;
  return timeDeff;
}

void stapToTime(int min) {
  if (min < 0) {
    min = abs(min);
    for(int i=0; i < min; i++){
      delay(10);
      myStepper.step(-steps);
      if (counter_stap == 60) {
        delay(500);
        myStepper.step(-22);
        delay(500);
        counter_stap = 1;
      } else {
        counter_stap++;
      }
    }
  } else {
    for(int i=0; i < min; i++){
      delay(10);
      myStepper.step(steps);
      if (counter_stap == 60) {
        delay(500);
        myStepper.step(30);
        delay(500);
        counter_stap = 1;
      } else {
        counter_stap++;
      }
    }  
  }
  
}

int _init() {
  _update("clockStatus", "Init...");
  delay(500);
  while(true) {
    byte minute = digitalRead(SS1);
    byte hour = digitalRead(SS2);
    if (minute == LOW && hour == LOW) {
      delay(500);
      _initTime();
      _update("clockStatus", "Contention");
      return 1;
    } else {
      myStepper.step(39);
      delay(10);
    }
  }
}

int _initTime() {
  _update("clockStatus", "Init Time");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  
  int timeDeff = timeCal(timeClient.getHours(), timeClient.getMinutes());
  stapToTime(timeDeff);
}

void loop() {
  int number = Firebase.getInt(firebasePath+"clockFunction");
  if (number != 0) {
    clockFunction(number);
  }
}
