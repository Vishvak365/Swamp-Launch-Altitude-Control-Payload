// Include the Arduino Stepper Library
#include <Stepper.h>
//  
// In the above website use this wiring color translation
// Red -> Black
// Green -> Green
// Yellow -> Red
// Blue -> Blue
// Number of steps per output rotation
const int stepsPerRevolution = 200;

// Create Instance of Stepper library
Stepper myStepper(stepsPerRevolution, 12, 11, 10, 9);


void setup()
{
  // set the speed at 20 rpm:
  myStepper.setSpeed(20);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() 
{
  // step one revolution in one direction:
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(500);
//
//  // step one revolution in the other direction:
//  Serial.println("counterclockwise");
//  myStepper.step(-stepsPerRevolution);
//  delay(500);
}
