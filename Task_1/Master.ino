#include <Wire.h>

const int button1 = 2;
const int button2 = 3;

void setup() {
    Wire.begin();
    pinMode(button1, INPUT_PULLUP);
    pinMode(button2, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop() {
    byte b1 = digitalRead(button1);
    byte b2 = digitalRead(button2);
	
    Wire.beginTransmission(8);
    Wire.write(b1);
    Wire.write(b2);
    Wire.endTransmission();

    delay(100);
}