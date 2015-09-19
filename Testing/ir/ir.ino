/* 
 * ir.ino 
 * Author: Hannes
 *
 * Code to read IR sensor for the Mini Soccer Project 
 * Easier if you use the example with the following library
 * https://jeroendoggen.wordpress.com/2011/12/20/arduino-library-for-the-sharp-gp2y0a21yk-ir-distance-sensor/
 */

// Constant Definitions
#define IR 0
#define INCH_TO_MM_FACTOR 25.4f

// Function Prototypes
int read_ir_raw (int pin);
long read_irc_mm (int pin);
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
  delay(200); 
}

// Returns the raw reading from the ultrasonic sensor
int read_ir_raw (int pin) {
  return analogRead(pin);
}

// Returns the ultrasonic sensor distance in mm
long read_ir_mm (int pin) {
  return (analogRead(pin) * 5 / 1024);
}

void read_sensors(){
  /*
  Scale factor is (Vcc/512) per inch. A 5V supply yields ~9.8mV/in
  Arduino analog pin goes from 0 to 1024, so the value has to be divided by 2 to get the actual inches
  */
  raw = read_ir_raw(IR);
  // Note: values can be different, as analogRead function gets called twice
  distance1 = read_ir_mm(IR);
}

void print_all(){
  Serial.print("S1");
  Serial.print(" ");
  Serial.print(distance1);
  Serial.print("mm       Raw: ");
  Serial.print(raw);
  Serial.println();
}
