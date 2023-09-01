#include <Wire.h>

const int led = 9;

void setup() {
    Wire.begin(8);
  	Wire.onReceive(receiveEvent);
    pinMode(led, OUTPUT);
    Serial.begin(9600);
}

void loop() {
  delay(100);
}

void receiveEvent(int number)
{
    if (Wire.available() >= 2) {
        byte b1 = Wire.read();
        byte b2 = Wire.read();
      	
        if (b1 == 0 && b2 == 0) {
            digitalWrite(led, LOW);
            Serial.println("");
        } else if (b1 == 1 && b2 == 0) {
            analogWrite(led, 128);  // 50% effiiciency
            Serial.println("Vector Focused");
        } else if (b1 == 0 && b2 == 1) {
            analogWrite(led, 191);  // 75% efficiency
            Serial.println("Vector distracted");
        } else if (b1 == 1 && b2 == 1) {
            analogWrite(led, 255);  // 100% efficiency
            Serial.println("Glitch");
        }
    }
}
