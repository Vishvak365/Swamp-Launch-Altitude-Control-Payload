double init_acceleration;
double init_velocity;
double init_altitude;
double init_humidity;
double init_angle;

bool checkDeployFins(double curr_velocity, double curr_acceleration, double curr_altitude, double curr_humidity, double curr_angle)
{
}
void setInitialConditions(double velocity, double acceleration, double altitude, double humidity, double angle)
{
    init_velocity = velocity;
    init_acceleration = acceleration;
    init_altitude = altitude;
    init_humidity = humidity;
    init_angle = angle;
}