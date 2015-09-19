/* 
 *  main.ino 
 *  Author: Hannes 19/9/2015
 *  
 *  Main program for the Soccer Mini Project
 */


#include <Servo.h>

#define SERVO1_PIN 9
#define SERVO2_PIN 10
#define RANDOM_PIN 2
#define POS1 0
#define POS2 90
#define DELAY_LONG 3000
#define DELAY_SHORT 200

Servo kicker1;
Servo kicker2;

void setup() {
  Serial.begin(9600);
  // Setup and initialise the Servo
  kicker1.attach(SERVO1_PIN);
  kicker2.attach(SERVO2_PIN);
  kicker1.write(POS2);
  kicker2.write(POS2);

  // Seed random value function
  randomSeed(analogRead(RANDOM_PIN));
}

void loop() {
  // put your main code here, to run repeatedly:
  long random_val = random(2);
  Serial.print(random_val);
  if(random_val) {
    // Kick kicker1
    kicker1.write(POS1);
    delay(DELAY_SHORT);
    kicker1.write(POS2);
  } else {
    // Kick kicker2
    kicker2.write(POS1);
    delay(DELAY_SHORT);
    kicker2.write(POS2);
  }
  delay(DELAY_LONG);
}
