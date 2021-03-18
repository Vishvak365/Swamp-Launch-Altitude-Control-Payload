#include "BNO055_RT.h"
#include "Triple.h"
double alpha = .05;
double maxAcceleration = 0;
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

Triple prevVelocity = 0;
double prevTime = millis();
/*
  @returns Triple velocity
*/
Triple calcVelocity(Triple acceleration)
{
    Triple velocity;
    velocity.x = prevVelocity_X + ((acceleration().x) * (millis() - prevTime));
    velocity.y = prevVelocity_Y + ((acceleration().y) * (millis() - prevTime));
    velocity.z = prevVelocity_Z + ((acceleration().z) * (millis() - prevTime));

    prevTime = millis();
    double prevVelocity_X = velocity.x;
    double prevVelocity_Y = velocity.y;
    double prevVelocity_Z = velocity.z;
    return velocity;
}