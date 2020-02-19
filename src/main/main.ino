#include <Stepper.h>

#define IN1   D1
#define IN2   D2
#define IN3   D3
#define IN4   D4
#define IN5   D5
#define IN7   D7

const int stepsPerRevolution = 2048; // change this to fit the number of steps per revolution
// initialize the stepper library
Stepper myStepper(stepsPerRevolution, IN4, IN2, IN3, IN1);

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN5, INPUT);
  myStepper.setSpeed(13);
}

void loop() {
  int val = digitalRead(IN5);
  
  if(val == HIGH) //when magnetic field is detected, turn led on
  {
    digitalWrite(IN7, HIGH);
    myStepper.step(10);
  }
  else
  {
    digitalWrite(IN7, LOW);
    myStepper.step(-10);
  }
  val = LOW;
}
