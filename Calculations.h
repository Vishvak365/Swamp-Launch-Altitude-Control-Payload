#include "BNO055_RT.h"
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

double prevVelocity_X = 0;
double prevVelocity_Y = 0;
double prevVelocity_Z = 0;
double prevTime = millis();
/*
  @returns [currVelocity_X, currVelocity_Y, currVelocity_Z]
*/
double *calcVelocity()
{
    double currVelocity_X = prevVelocity_X + ((bno055_getAcceleration().x) * (millis() - prevTime));
    double currVelocity_Y = prevVelocity_Y + ((bno055_getAcceleration().y) * (millis() - prevTime));
    double currVelocity_Z = prevVelocity_Z + ((bno055_getAcceleration().z) * (millis() - prevTime));
    prevTime = millis();
    double prevVelocity_X = currVelocity_X;
    double prevVelocity_Y = currVelocity_Y;
    double prevVelocity_Z = currVelocity_Z;
    static double velocity_array[] = {currVelocity_X, currVelocity_Y, currVelocity_Z};
    return velocity_array;
}