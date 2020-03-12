#include <Stepper.h>

int counter = 0;
int val;
int initStatus;
int controller = 32;

const int stepsPerRevolution = 2048; // change this to fit the number of steps per revolution
// initialize the stepper library
Stepper myStepper(stepsPerRevolution, IN4, IN2, IN3, IN1);

void setup() {
  Serial.begin(115200);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);
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
    int timeDeff = timeCal(12, 30);
    stapToTime(timeDeff);
    Serial.println(timeDeff);
  }
  delay(100);
}


int timeCal(int hour, int min) {
  int hourDeffToMin = (hour - 12) * 60;
  int timeDeff = min + hourDeffToMin;
  return timeDeff;
}

void stapToTime(int min) {
  for(int i=0; i < min; i++){
    delay(200);
    myStepper.step(39);
    Serial.println(i);
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
