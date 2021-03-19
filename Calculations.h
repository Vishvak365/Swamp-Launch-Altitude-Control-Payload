#include "BNO055_RT.h"
#include "Triple.h"
// Check engine cuttoff values
double alpha;           // = .05;
double maxAcceleration; // = 0;
// calcVelocity() values
Triple prevVelocity;
double prevTime;
/*
    @description : checks acceleration to see if engine has been cut off
    @returns : true if engine cutoff detected; false if if not
    @acceleration : current acceleration
*/
bool checkEngineCutOff(double acceleration)
{
    if (acceleration > maxAcceleration)
    {
        maxAcceleration = acceleration;
    }
    // Checks to see if acceleration has dipped with a leniancy value
    else if (acceleration < maxAcceleration - (maxAcceleration * alpha))
    {
        return true;
    }
}

void initCalculationValues()
{
    prevVelocity.x = 0;
    prevVelocity.y = 0;
    prevVelocity.z = 0;
    prevTime = millis();
    
    alpha = .05;
    maxAcceleration = 0;
}
/*
  @returns Triple velocity
*/
Triple calcVelocity(Triple acceleration)
{
    Triple velocity;
    velocity.x = prevVelocity.x + ((acceleration.x) * (millis() - prevTime));
    velocity.y = prevVelocity.y + ((acceleration.y) * (millis() - prevTime));
    velocity.z = prevVelocity.z + ((acceleration.z) * (millis() - prevTime));

    prevTime = millis();
    double prevVelocity_X = velocity.x;
    double prevVelocity_Y = velocity.y;
    double prevVelocity_Z = velocity.z;
    return velocity;
}