#include <Servo.h>

Servo motor;

int deger;
int derece;

void setup() {
  motor.attach(3);

}

void loop() {

  deger = analogRead(A0);
  derece = map(deger, 0,1023,0,180);
  motor.write(derece);

}
