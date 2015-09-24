/* 
 *  kicker.ino 
 *  Author: Hannes 17/9/2015
 *  
 *  Program to test the feasability of kicking the ball using a long
 *  rod attached to a servo.
 */


#include <Servo.h>

#define SERVO_PIN 6
#define POS1 0
#define POS2 90
#define DELAY 2000

Servo kicker;
Servo kicker2;

void setup() {
  // put your setup code here, to run once:
  kicker.attach(SERVO_PIN);
  kicker2.attach(5);
  kicker.write(POS1);
  delay(100);
  kicker2.write(POS1);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(DELAY);
  kicker.write(POS1);
  delay(500);
  kicker.write(POS2);
}
