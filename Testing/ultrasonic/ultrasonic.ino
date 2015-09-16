/* 
 * ultrasonic.ino 
 * Author: Hannes/Sample code provided by Maxbotics
 *
 * Code to read ultrasonic sensor for the Mini Soccer Project 
 */

// Constant Definitions
#define ULTRASONIC 0
#define INCH_TO_MM_FACTOR 25.4f

// Function Prototypes
int read_ultrasonic_raw (int pin);
long read_ultrasonic_mm (int pin);
void read_sensors(void);
void print_all(void);

// Global Variable Definition
long distance1;
int raw;

void setup() {
  Serial.begin(9600);  // sets the serial port to 9600
}

void loop() {
  read_sensors();
  print_all();
  delay(50); 
}

// Returns the raw reading from the ultrasonic sensor
int read_ultrasonic_raw (int pin) {
  return analogRead(pin);
}

// Returns the ultrasonic sensor distance in mm
long read_ultrasonic_mm (int pin) {
  return (analogRead(pin) / 2 * INCH_TO_MM_FACTOR);
}

void read_sensors(){
  /*
  Scale factor is (Vcc/512) per inch. A 5V supply yields ~9.8mV/in
  Arduino analog pin goes from 0 to 1024, so the value has to be divided by 2 to get the actual inches
  */
  raw = read_ultrasonic_raw(ULTRASONIC);
  // Note: values can be different, as analogRead function gets called twice
  distance1 = read_ultrasonic_mm(ULTRASONIC);
}

void print_all(){
  Serial.print("S1");
  Serial.print(" ");
  Serial.print(distance1);
  Serial.print("mm       Raw: ");
  Serial.print(raw);
  Serial.println();
}
