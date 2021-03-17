double[] init_acceleration;
double[] init_velocity;
double init_altitude;
double init_angle;

bool checkDeployFins(double[] curr_velocity, double[] curr_acceleration, double curr_altitude, double curr_angle)
{
    //Dimensions and Properties
    double rho = 1.225;               // [kg*km^-3*s^-2]Constant for now, but should be from sensor, and should vary
    double S = 0.0192898;             // [m ^ 2] Reference Area of Rocket(without blades)
    double cd = 0.5;                  // [] Coefficient of Drag(without blades)
    double m = 3.6868;                // [kg] Mass of Rocket at burnout(empty) double tAlt = 10000 * .3048;
    double tAlt = 10000 * .3048;      // [m] - Target Altitude
    double g = 9.81;                  // [m * s ^ -2] - Gravity Acceleration
    double dy = tAlt - init_altitude; // [m] Difference between Current and Target altitudes
    double ext = 5;                   // [s] Time fins are deployed
    double e = 2.71828;               // [] euler's number

    //Calculate Target Velocity
    double W = m * g;              // [N] Weight
    double B = 0.5 * rho * S * cd; // [m^2*s^-2] Drag Constant

    double a = B * init_velocity * init_velocity;
    double b = pow(e, (2 * B) / (m * dy));

    double targetV2 = (a - b) / B;
    double targetV = sqrt(targetV2); //targetV = sqrt((((m*g+B*Vo^2)/exp(2*B*tAlt/m))-m*g)/B);
    double DelA = targetV / ext;     //Acceleration Required to Slow velocity by ext seconds

    //Calculate Deploy Velocity
    double cd = cd + 0.09;
    double S = 0.03293858;
    double Vd = sqrt((2 * DelA * m) / (rho * S * cd));
    if (Vd > 200)
    {
        Vd = 200;
    }

    //Deploy Fins if Deploy Velocity is within error bounds
    double errorValue = .05;
    if (curr_velocity >= Vd * (1 - errorValue) && curr_velocity <= Vd * (1 + errorValue))
    {
        return true;
    }
    else
    {
        return false;
    }
}
void setInitialConditions(double[] curr_velocity, double[] curr_acceleration, double curr_altitude, double curr_angle)
{
    init_velocity = velocity;
    init_acceleration = acceleration;
    init_altitude = altitude;
    init_angle = angle;
}