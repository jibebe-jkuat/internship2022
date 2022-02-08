#include <Servo.h>

Servo ESC;  // create new servo object

int potValue; // Value from the analog pin - Potentiometer

void setup(){
  //Attach the ESC on pin 9
  ESC.attach(9, 1000, 2000); // (pin, min pulse width, max pulse width)
}

void loop(){
  potValue = analogRead(A0); // read the value of potentiometer (range 0 -1023)
  potValue = map(potValue, 0, 1023, 0, 180); // scale it to use it with the servo library(range 0 -180)
  ESC.write(potValue);
}
