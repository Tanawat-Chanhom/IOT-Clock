#define IN3   D3   // IN1 is connected to NodeMCU pin D1 (GPIO5)
#define IN5   D5   // IN1 is connected to NodeMCU pin D1 (GPIO5)
int val; //numeric variable

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT); //set LED pin as output
  pinMode(IN5, OUTPUT);
  pinMode(IN3, INPUT); //set sensor pin as input
}

void loop()
{
  val = digitalRead(IN3); //Read the sensor
  if(val == LOW) //when magnetic field is detected, turn led on
  {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(IN5, HIGH);
  }
  else
  {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(IN5, LOW);
  }
}
