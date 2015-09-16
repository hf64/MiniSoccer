/* 
 * ultrasonic.ino 
 * Author: Hannes 
 *
 * Code to read ultrasonic sensor for the Mini Soccer Project 
 */

#define ANALOG_PIN 0
long distance1;

void setup() {
  Serial.begin(9600);  // sets the serial port to 9600
}

void read_sensors(){
  /*
  Scale factor is (Vcc/512) per inch. A 5V supply yields ~9.8mV/in
  Arduino analog pin goes from 0 to 1024, so the value has to be divided by 2 to get the actual inches
  */
  distance1 = analogRead(ANALOG_PIN)/2;
}

void print_all(){
  Serial.print("S1");
  Serial.print(" ");
  Serial.print(distance1);
  Serial.print("inches");
  Serial.println();
}

void loop() {
  read_sensors();
  print_all();
  delay(50); 
}
