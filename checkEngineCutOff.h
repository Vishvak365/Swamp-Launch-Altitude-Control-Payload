double alpha = .05;
double maxAcceleration = 0;
/*
    @description : checks acceleration to see if engine has been cut off
    @returns : true if engine cutoff detected; false if if not
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