#include "sd_card_RT.h"
#include "BMP388_RT.h"
#include "BME680_RT.h"
#include "GPS_RT.h"
#include "BNO055_RT.h"
#include "Triple.h"
#include "Stepper_Control.h"
#include <String.h>
#include "Calculations.h"
#include "ACS_Calculations.h"
void openFile();
void printAll();
void logData();
File logger;

String fileName = "test.csv";
bool debug = TRUE;
//bool debug = FALSE;

void setup()
{
  initCalculationValues();
  if (debug)
  {
    Serial.begin(115200);
    // initSD_debug();
    initBMP388_debug();
    // initBME680_debug();
    // initGPS_debug();
    initBNO055_debug();
    // initStepper_debug();
    // testStepperMotor();
  }
  else
  {
    initSD();
    initBMP388();
    // initBME680();
    initGPS();
    initBNO055();
  }
  openFile();
  // .1875
  // .189
  //File Header
  logger.println("GPS DATA,,,,,,,,,,,BME680 DATA,,,,,BMP388 DATA,,,BNO055 DATA,,,,,,,,,,,,,,,,,");
  logger.println("Date,HH:MM:SS,Millis,Fix,Fix Quality,Satellites,Latitude,Longitude,Altitude (m),Speed (knots),Angle (degrees),Pressure (hPa),Altitude (m),Temperature (C),Humidity (%),Gas (kOhms),Pressure (hPa),Altitude (m),Temperature (C),Acceleration (m/s^2),,,Orientation (degrees),,,Gravity (m/s^2),,,Angular Velocity (rad/s),,,Linear Acceleration (m/s^2),,,Magnetism (uT),,");
  logger.println(",,,,,,,,,,,,,,,,,,,x,y,z,x,y,z,x,y,z,x,y,z,x,y,z,x,y,z");
  logger.close();
  //TODO: Set init indicator to true
}
double rocketIgnitionTime = 0;
//Each sensor has prewritten functions to get the data ex. bme680_getTemperature stored in header files
//FOR GPS: you must call GPS.getDATA() (refer to GPS_print() function in GPS_RT.h)
//gps_update(); must be called in order to update GPS data
bool engineIsCutOff = false;
void loop()
{
  //gps_update();
  if (debug)
  {
    printAll();
  }
  Triple curr_acceleration;
  curr_acceleration.x = bno055_getLinearAcceleration().x;
  curr_acceleration.y = bno055_getLinearAcceleration().y;
  curr_acceleration.z = bno055_getLinearAcceleration().z;
  Triple curr_angle;
  curr_angle.x = bno055_getOrientation().x;
  curr_angle.y = bno055_getOrientation().y;
  curr_angle.z = bno055_getOrientation().z;
  Triple curr_velocity = calcVelocity(curr_acceleration);
  Serial.println("x : " + String(curr_velocity.x) + " y : " + String(curr_velocity.y) + " z " + String(curr_velocity.z));
  // Check for initial engine cut off
  if (rocketIgnitionTime == 0 && curr_acceleration.x > 10)
  {
    Serial.println("Rocket Ignited");
    rocketIgnitionTime = millis();
  }
  if (rocketIgnitionTime != 0 && checkEngineCutOff(curr_acceleration.x) && engineIsCutOff == false)
  {
    unsigned long StartTime = millis();
    unsigned long CurrTime = millis();
    Serial.println("Engine Cutoff");
    //wait 2500 ms before getting initial conditions
    while (CurrTime - StartTime < 2500)
    {
      // logData();
      CurrTime = millis();
    }
    engineIsCutOff = true;
    Serial.println("Setting initial conditions for ACS calculations");
    double curr_altitude = bmp388_getAltitude();

    setInitialConditions(curr_velocity, curr_acceleration, bmp388_getAltitude(), curr_angle);
  }
  // Check to see if the engine has been previously cut off (cruising state)
  bool deployFins = false;
  if (engineIsCutOff && deployFins == false)
  {

    bool deployFins = checkDeployFins(curr_velocity, curr_acceleration, bmp388_getAltitude(), curr_angle);
    if (deployFins && (millis() - rocketIgnitionTime) > 4000)
    {
      Serial.println("Fins Deployed");
      // open
      stepper_rotate(560, false);
      unsigned long StartTime = millis();
      unsigned long CurrTime = millis();
      //wait 5 seconds before closing
      while (CurrTime - StartTime < 5000)
      {
        // logData();
        CurrTime = millis();
      }
      stepper_rotate(560, true);
    }
  }

  // Logs data from sensors to SD Card
  // logData();

  // Serial.println("updated!");
  // Delay needed to deal with sporatic data
  delay(100);
}

void testStepperMotor()
{
  stepper_rotate(2000, false);
}
void openFile()
{

  //If the file is new, we want to put the proper headers.

  logger = SD.open(fileName, FILE_WRITE);

  if (!logger)
  {
    Serial.println("File Unable to open!");
  }
}

/*
  Given a velocity, at velocity x deploy the blades
  Given an altitude, 
*/
void printAll()
{

  // Serial.println("----------GPS DATA----------");
  // gps_print();
  // Serial.println("----------BME680 DATA----------");
  // Serial.println("Pressure: " + String(bme680_getPressure()) + " hPa");
  // Serial.println("Altitude: " + String(bme680_getAltitude()) + " m");
  // Serial.println("Temperature: " + String(bme680_getTemperature()) + " C");
  // Serial.println("Humidity: " + String(bme680_getHumidity()) + "%");
  // Serial.println("Gas: " + String(bme680_getGas()) + " kOm/s^2m hms");

  // Serial.println("----------BMP388 DATA----------");
  // Serial.println("Pressure: " + String(bmp388_getPressure()) + " hPa");
  // Serial.println("Altitude: " + String(bmp388_getAltitude()) + " m");
  // Serial.println("Temperature: " + String(bmp388_getTemperature()) + " C");

  // Serial.println("----------BNO055 DATA----------");
  // Serial.println("Acceleration: x: " + String(bno055_getAcceleration().x) + " y: " + String(bno055_getAcceleration().y) + " z: " + String(bno055_getAcceleration().z) + " m/s^2");
  // Serial.println("Orientation: x: " + String(bno055_getOrientation().x) + " y: " + String(bno055_getOrientation().y) + " z: " + String(bno055_getOrientation().z) + " degrees");
  // Serial.println("Gravity: x: " + String(bno055_getGravity().x) + " y: " + String(bno055_getGravity().y) + " z: " + String(bno055_getGravity().z) + " m/s^2");
  // Serial.println("Angular Velocity: x: " + String(bno055_getAngularVelocity().x) + " y: " + String(bno055_getAngularVelocity().y) + " z: " + String(bno055_getAngularVelocity().z) + " rad/s");
  // Serial.println("Linear Acceleration: x: " + String(bno055_getLinearAcceleration().x) + " y: " + String(bno055_getLinearAcceleration().y) + " z: " + String(bno055_getLinearAcceleration().z) + " m/s^2");
  // Serial.println("Magnetism: x: " + String(bno055_getMagnetism().x) + " y: " + String(bno055_getMagnetism().y) + " z: " + String(bno055_getMagnetism().z) + " uT");
  // //
  // Serial.println("----------END DATA----------");
  // Serial.println();
  // Serial.println("Orientation: x: " + String(bno055_getOrientation().x) + " y: " + String(bno055_getOrientation().y) + " z: " + String(bno055_getOrientation().z) + " degrees");
  // Serial.println("Linear Acceleration: x: " + String(bno055_getLinearAcceleration().x) + " y: " + String(bno055_getLinearAcceleration().y) + " z: " + String(bno055_getLinearAcceleration().z) + " m/s^2");
}

void logData()
{
  //GPS DATA
  openFile();

  logger.print(GPS.month, DEC);
  logger.print('/');
  logger.print(GPS.day, DEC);
  logger.print("/20");
  logger.print(GPS.year, DEC);
  logger.print(",");
  if (GPS.hour < 10)
  {
    logger.print('0');
  }
  logger.print(GPS.hour, DEC);
  logger.print(':');

  if (GPS.minute < 10)
  {
    logger.print('0');
  }
  logger.print(GPS.minute, DEC);
  logger.print(':');

  if (GPS.seconds < 10)
  {
    logger.print('0');
  }
  logger.print(GPS.seconds, DEC);
  logger.print(',');

  if (GPS.milliseconds < 10)
  {
    logger.print("00");
  }
  else if (GPS.milliseconds > 9 && GPS.milliseconds < 100)
  {
    logger.print("0");
  }
  logger.print(GPS.milliseconds);
  logger.print(",");

  logger.print((int)GPS.fix);
  logger.print(",");
  logger.print((int)GPS.fixquality);
  logger.print(",");
  logger.print((int)GPS.satellites);
  logger.print(",");

  logger.print(GPS.latitude, 4);
  logger.print(GPS.lat);
  logger.print(",");
  logger.print(GPS.longitude, 4);
  logger.print(GPS.lon);
  logger.print(",");
  logger.print(GPS.altitude);
  logger.print(",");
  logger.print(GPS.speed);
  logger.print(",");
  logger.print(GPS.angle);
  logger.print(",");

  //BME680 DATA
  // logger.print(String(bme680_getPressure()));
  // logger.print(",");
  // logger.print(String(bme680_getAltitude()));
  // logger.print(",");
  // logger.print(String(bme680_getTemperature()));
  // logger.print(",");
  // logger.print(String(bme680_getHumidity()));
  // logger.print(",");
  // logger.print(String(bme680_getGas()));
  // logger.print(",");
  logger.print("0");
  logger.print(",");
  logger.print("0");
  logger.print(",");
  logger.print("0");
  logger.print(",");
  logger.print("0");
  logger.print(",");
  logger.print("0");
  logger.print(",");

  //BMP388 DATA
  logger.print(String(bmp388_getPressure()));
  logger.print(",");
  logger.print(String(bmp388_getAltitude()));
  logger.print(",");
  logger.print(String(bmp388_getTemperature()));
  logger.print(",");

  //BNO055
  logger.print(String(bno055_getAcceleration().x) + "," + String(bno055_getAcceleration().y) + "," + String(bno055_getAcceleration().z) + ",");
  logger.print(String(bno055_getOrientation().x) + "," + String(bno055_getOrientation().y) + "," + String(bno055_getOrientation().z) + ",");
  logger.print(String(bno055_getGravity().x) + "," + String(bno055_getGravity().y) + "," + String(bno055_getGravity().z) + ",");
  logger.print(String(bno055_getAngularVelocity().x) + "," + String(bno055_getAngularVelocity().y) + "," + String(bno055_getAngularVelocity().z) + ",");
  logger.print(String(bno055_getLinearAcceleration().x) + "," + String(bno055_getLinearAcceleration().y) + "," + String(bno055_getLinearAcceleration().z) + ",");
  logger.print(String(bno055_getMagnetism().x) + "," + String(bno055_getMagnetism().y) + "," + String(bno055_getMagnetism().z) + ",");

  logger.println("");

  logger.close();

  //DONE
}
