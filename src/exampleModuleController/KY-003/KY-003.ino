#define IN3   D3   // IN1 is connected to NodeMCU pin D1 (GPIO5)
#define IN5   D5   // IN1 is connected to NodeMCU pin D1 (GPIO5)
#define IN7   D7
int val; //numeric variable

void setup()
{
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT); //set LED pin as output
  pinMode(IN5, INPUT);
  pinMode(IN7, OUTPUT);
}

void loop()
{
  val = digitalRead(IN5); //Read the sensor
  Serial.println(val);
  if(val == HIGH) //when magnetic field is detected, turn led on
  {
    digitalWrite(LED_BUILTIN, HIGH);
//    digitalWrite(IN7, HIGH);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
//    digitalWrite(IN7, LOW);
  }
}
