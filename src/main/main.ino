#include <Stepper.h>

#define IN1   D1
#define IN2   D2
#define IN3   D3
#define IN4   D4

#define IN5   D5
#define IN7   D7

int counter = 0;
int val;
int initStatus;

const int stepsPerRevolution = 2048; // change this to fit the number of steps per revolution
// initialize the stepper library
Stepper myStepper(stepsPerRevolution, IN4, IN2, IN3, IN1);

void setup() {
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN5, INPUT);
  myStepper.setSpeed(10);
  initStatus = _init();
}

void loop() {
  if (initStatus == 1) {
    
      if (counter >= 60) {
        myStepper.step(-36);
        if (counter == 120) {
          counter = 0;
        }
      } else {
        myStepper.step(36);
      }

//      myStepper.step(36);
      counter++;
      Serial.print(counter);
      val = digitalRead(IN5);
      Serial.println(val);
      delay(10);
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
