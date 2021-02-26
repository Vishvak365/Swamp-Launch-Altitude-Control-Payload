#include <Stepper.h>
// In the above website use this wiring color translation
// Red -> Black
// Green -> Green
// Yellow -> Red
// Blue -> Blue
// Number of steps per output rotation
int stepsPerRevolution = 100;
int defaultSpeed = 200;

Stepper stepper(stepsPerRevolution, 12, 11, 10, 9);
void initStepper()
{
    stepper.setSpeed(defaultSpeed);
    Serial.begin(9600);
}
void initStepper(int speed)
{
    stepper.setSpeed(speed);
    Serial.begin(9600);
}
void initStepper_debug()
{
    Serial.println(F("Stepper motor initialized with default speed"));
    stepper.setSpeed(defaultSpeed);
    Serial.begin(9600);
}
void initStepper_debug(int speed)
{
    Serial.println(F("Stepper motor initialized with custom speed"));
    stepper.setSpeed(speed);
    Serial.begin(9600);
}
void stepper_setStepsPerRevolution(int steps)
{
    stepsPerRevolution = steps;
}
void stepper_rotate(int duration, bool counterClockWise)
{
    if (counterClockWise)
    {
        stepper.step(stepsPerRevolution);
    }
    else
    {
        stepper.step(-stepsPerRevolution);
    }
}