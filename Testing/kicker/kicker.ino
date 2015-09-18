/* 
 *  kicker.ino 
 *  Author: Hannes 17/9/2015
 *  
 *  Program to test the feasability of kicking the ball using a long
 *  rod attached to a servo.
 */


#include <Servo.h>

#define SERVO_PIN 9
#define POS1 0
#define POS2 90
#define DELAY 1000

Servo kicker;

void setup() {
  // put your setup code here, to run once:
  kicker.attach(SERVO_PIN);
  kicker.write(POS1);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(DELAY);
  kicker.write(POS2);
  delay(DELAY);
  kicker.write(POS1);
}
