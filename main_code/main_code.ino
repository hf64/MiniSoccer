/* 
 *  main.ino 
 *  Author: Hannes, Jeremy 25/9/2015
 *  
 *  Main program for the Soccer Mini Project
 */


#include <Servo.h>

#define SERVO1_PIN 5
#define SERVO2_PIN 6
#define SERVO3_PIN 3
#define RANDOM_PIN 2
#define DISTANCE_PIN 0
#define BUTTON_PIN 9
#define SENSOR_PIN 10
#define ECHO_PIN 11

#define POS1 0
#define POS2 90
#define FEED_STOP 66
#define FEED_FORWARD 0
#define FEED_REVERSE 180
#define DELAY_LONG 3000
#define DELAY_SHORT 300
#define FEED_DELAY 40
#define MARGIN 5

Servo kicker1;
Servo kicker2;
Servo feed;

void setup() {
  Serial.begin(9600);
  // Setup and initialise the Servo
  kicker1.attach(SERVO1_PIN);
  kicker2.attach(SERVO2_PIN);
  feed.attach(SERVO3_PIN);
  feed.write(FEED_STOP);
  kicker1.write(POS1);
  // Delay a short bit so that they do not interfere
  delay(100);
  kicker2.write(POS1);

  // Setup pins needed for the ultrasonic sensor and button
  pinMode(BUTTON_PIN, INPUT);
  pinMode(SENSOR_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Seed random value function using electrical noise
  randomSeed(analogRead(RANDOM_PIN));
}

int get_distance_centimeter() {
  int dt;
  int range;
  
  digitalWrite(SENSOR_PIN, HIGH);
  delayMicroseconds(1000);
  digitalWrite(SENSOR_PIN, LOW);
  dt = pulseIn(ECHO_PIN, HIGH);
  range = (dt/2)/29.1;
  return range;
}

long determine_position() {
  // Read in distance with mounting offset accounted for
  int distance = get_distance_centimeter() - 6;
  // Get position from the middle
  float pos = (float)distance - 9;
  Serial.print("Distance from the middle is: ");
  Serial.print(pos);
  Serial.print("\n");
  // If position is less than some margin, we know the goalie is on the left
  if(pos < -1 * MARGIN) {
    return 0;
  } else if (pos > MARGIN) { // If greater, it is on the right
    return 1;
  } else {
    // Otherwise the goalie is in the centre
    return -1;
  }
}

void loop() {
  // Wait for button press
  while(digitalRead(9) != 1) {
    delay(20);
  }
  /*
   * Calculate randomness by calculating 2 random values
   * and then the third one being added by a the IR sensor
   * If it is within some margins inside the middle of the field,
   * it will randomly add another constant
   * Otherwise it will add a number to the random array and
   * Skew the result
   */
  long random_val[3];
  random_val[0] = random(2);
  random_val[1] = random(2);
  int ret_val = determine_position();
  if(ret_val == 1) {
    random_val[2] = 1;
  } else if (ret_val == 0) {
    random_val[2] = 0;
  } else {
    random_val[2] = random(2);
  }
  int count = 0;

  // We count up with a 1 and down with a 0. 
  // As we have 3 numbers, we have either positive or
  // negative
  for(int i = 0; i < 3; i++) {
    if (random_val[i] == 1) {
      count++;
    } else {
      count--;
    }
  }
  // Debugging information
  Serial.print("Count is: ");
  Serial.print(count);
  Serial.print("\n");

  // Open and close the feeding mechanism, dropping one ball into the
  // required position
  feed.write(FEED_FORWARD);
  delay(FEED_DELAY);
  feed.write(FEED_REVERSE);
  delay(FEED_DELAY);
  feed.write(FEED_STOP);

  // Choose the correct kicker to activate
  if(count > 0) {
    // Kick kicker1
    kicker1.write(POS2);
    delay(DELAY_SHORT);
    kicker1.write(POS1);
  } else if (count < 0) {
    // Kick kicker2
    kicker2.write(POS2);
    delay(DELAY_SHORT);
    kicker2.write(POS1);
  } else {
    Serial.print("Program Error somewhere here!\n");
  }
  
}
