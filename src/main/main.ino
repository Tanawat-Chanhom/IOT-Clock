#include <Stepper.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiUdp.h>

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

int val;
int initStatus;
int initTime;
int controller = 32;

int start_hour = 12;
int start_min = 20;

int counter_stap = 1;

long thaiOffset = 21600;

const char* ssid = "Chanhom";
const char* password = "029959866";

const int stepsPerRevolution = 2048; // change this to fit the number of steps per revolution
// initialize the stepper library
Stepper myStepper(stepsPerRevolution, MS4, MS2, MS3, MS1);

WiFiUDP myClient;
NTPClient timeClient(myClient, "time.navy.mi.th", thaiOffset);

void setup() {
  Serial.begin(9600);
  
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  pinMode(MS4, OUTPUT);
  
  pinMode(IN1, INPUT);
  pinMode(IN2, INPUT);

  HTTPClient http;
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("Connecting..\n");
  }
  Serial.print("Connected!\n");
  timeClient.begin();
  
  myStepper.setSpeed(12);
  initStatus = _init();
  initTime = _initTime();
}

void loop() {
  byte val = digitalRead(IN1);
  byte val2 = digitalRead(IN2);

  if (val == HIGH) {
    myStepper.step(34);
  } else if (val2 == HIGH) {
    myStepper.step(-34);
  }
  delay(10);
}

int timeCal(int hour, int min) {
  int hourDeffToMin = (hour+1 - 18) * 60;
  int timeDeff = min + hourDeffToMin;
  return timeDeff;
}

void stapToTime(int min) {
  if (min < 0) {
    min = abs(min);
    for(int i=0; i < min; i++){
      delay(10);
      myStepper.step(-39);
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
      myStepper.step(39);
      if (counter_stap == 60) {
        delay(500);
        myStepper.step(22);
        delay(500);
        counter_stap = 1;
      } else {
        counter_stap++;
      }
    }  
  }
  
}

int _init() {
  while(true) {
    byte minute = digitalRead(SS1);
    byte hour = digitalRead(SS2);
    if (minute == LOW && hour == LOW) {
      delay(500);
      Serial.println("Init Done....");
      return 1;
    } else {
      myStepper.step(10);
    }
    delay(10);
  }
}

int _initTime() {
  delay(500);
  timeClient.update();
  
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  
  int timeDeff = timeCal(timeClient.getHours(), timeClient.getMinutes());
  stapToTime(timeDeff);
  return 1;
}
