#include <math.h>

double D0 = 3.0;
double D90 = 4.0;

double x, y;

void setup() {

  Serial.begin(9600);

  x = sqrt(pow(D0, 2) - pow(y, 2));
  y = sqrt(pow(D90, 2) - pow(x, 2));

  Serial.print("Estimated position: ");
  Serial.print(x);
  Serial.print(", ");
  Serial.println(y);
}

void loop() {
}
