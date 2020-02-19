#include <Stepper.h>

#define IN1   D1   // IN1 is connected to NodeMCU pin D1 (GPIO5)
#define IN2   D2   // IN2 is connected to NodeMCU pin D2 (GPIO4)
#define IN3   D3   // IN3 is connected to NodeMCU pin D3 (GPIO0)
#define IN4   D4   // IN4 is connected to NodeMCU pin D4 (GPIO2)
#define IN6   D6   // IN4 is connected to NodeMCU pin D4 (GPIO2)
#define IN7   D7   // IN4 is connected to NodeMCU pin D4 (GPIO2)

const int stepsPerRevolution = 2048; // change this to fit the number of steps per revolution

// initialize the stepper library
Stepper myStepper(stepsPerRevolution, IN4, IN2, IN3, IN1);

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN6, INPUT);
  pinMode(IN7, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  myStepper.setSpeed(13);
}
 
void loop() {
  byte val = digitalRead(IN6);
  byte val2 = digitalRead(IN7);

  if (val == HIGH) {
    myStepper.step(10);
  } else if (val2 == HIGH) {
    myStepper.step(-10);
  }
}
