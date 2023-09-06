const int PIN_A = 4;
const int PIN_B = 5;

volatile long counter = 0;

void encoder_PinA()
{
  if (digitalRead(PIN_A) == digitalRead(PIN_B))
    counter--;
  else
    counter++;
}

void encoder_PinB()
{
  if (digitalRead(PIN_A) == digitalRead(PIN_B))
    counter++;
  else
    counter--;
}
void setup()
{
  Serial.begin(9600);
  pinMode(PIN_A, INPUT_PULLUP);
  pinMode(PIN_B, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(PIN_A), encoder_PinA , CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_B), encoder_PinB , CHANGE);
}

void loop()
{
  Serial.print("Counter: ");
  Serial.println(counter);
  delay(100);
}