#include <Stepper.h>

#define IN1   D1
#define IN2   D2
#define IN3   D3
#define IN4   D4

#define IN5   D5

#define IN6   D6 
#define IN7   D7

int counter = 0;
int val;
int initStatus;
int controller = 32;

int start_hour = 11;
int start_min = 0;

int counter_stap = 1;

const int stepsPerRevolution = 2048; // change this to fit the number of steps per revolution
// initialize the stepper library
Stepper myStepper(stepsPerRevolution, IN4, IN2, IN3, IN1);

void setup() {
  Serial.begin(9600);
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  pinMode(IN6, INPUT);
  pinMode(IN7, INPUT);
  myStepper.setSpeed(12);
//  initStatus = _init();
}

void loop() {
  byte val = digitalRead(IN6);
  byte val2 = digitalRead(IN7);

  if (val == HIGH) {
    myStepper.step(34);
  } else if (val2 == HIGH) {
    delay(500);
    int timeDeff = timeCal(start_hour, start_min);
    stapToTime(timeDeff);
  }
}

int timeCal(int hour, int min) {
  int hourDeffToMin = (hour - 12) * 60;
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
        Serial.println("In");
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
        Serial.println("In");
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
    val = digitalRead(IN5);
    Serial.println(val);
    myStepper.step(-36);
    if (val == LOW) {
      counter = 0;
      return 1;
    }
    delay(10);
  }
}
