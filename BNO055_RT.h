#ifndef BNO055_RT
#define BNO055_RT
#include <Wire.h>
#include "Triple.h"

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

//To calibrate rotate and leave in different orientations for several seconds

// Possible vector values can be:
// - VECTOR_ACCELEROMETER - m/s^2
// - VECTOR_MAGNETOMETER  - uT
// - VECTOR_GYROSCOPE     - rad/s
// - VECTOR_EULER         - degrees
// - VECTOR_LINEARACCEL   - m/s^2
// - VECTOR_GRAVITY       - m/s^2

bool calibrate();
bool calibrateDebug();

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

void initBNO055_debug(void)
{
  Serial.println(F("BNO055 Initialization Debug"));

  /* Initialise the sensor */
  if (!bno.begin())
  {
    Serial.println("Could not find a valid BNO055 sensor, check wiring!");
  }
  else
  {
    Serial.println("Calibrating, please wait...");
    while (!calibrateDebug())
      ;
    Serial.println("BNO055 sensor successfully initialized!");
  }
}

void initBNO055(void)
{
  bno.begin();
  while (!calibrate())
    ;
}

bool calibrateDebug()
{
  uint8_t sys, gyro, accel, mag;
  sys = gyro = accel = mag = 0;
  bno.getCalibration(&sys, &gyro, &accel, &mag);

  /* The data should be ignored until the system calibration is 3 */
  Serial.print("\t");
  if (!sys)
  {
    Serial.print("! ");
  }

  /* Display the individual values */
  Serial.print("Sys:");
  Serial.print(sys, DEC);
  Serial.print(" G:");
  Serial.print(gyro, DEC);
  Serial.print(" A:");
  Serial.print(accel, DEC);
  Serial.print(" M:");
  Serial.println(mag, DEC);
  delay(100);
  if (sys == 3)
    return true;
  else
    return false;
}

bool calibrate()
{
  uint8_t sys, gyro, accel, mag;
  sys = gyro = accel = mag = 0;
  bno.getCalibration(&sys, &gyro, &accel, &mag);
  delay(100);

  /* The data should be ignored until the system calibration is 3 */

  if (sys == 3)
    return true;
  else
    return false;
}

Triple bno055_getAcceleration()
{
  imu::Vector<3> temp = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  Triple output;
  output.x = (double)temp.x();
  output.y = (double)temp.y();
  output.z = (double)temp.z();

  return output;
}

Triple bno055_getMagnetism()
{
  imu::Vector<3> temp = bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);
  Triple output;
  output.x = (double)temp.x();
  output.y = (double)temp.y();
  output.z = (double)temp.z();

  return output;
}

Triple bno055_getAngularVelocity()
{
  imu::Vector<3> temp = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  Triple output;
  output.x = (double)temp.x();
  output.y = (double)temp.y();
  output.z = (double)temp.z();

  return output;
}

Triple bno055_getOrientation()
{
  imu::Vector<3> temp = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  Triple output;
  output.x = (double)temp.x();
  output.y = (double)temp.y();
  output.z = (double)temp.z();

  return output;
}

Triple bno055_getLinearAcceleration()
{
  imu::Vector<3> temp = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);
  Triple output;
  output.x = (double)temp.x();
  output.y = (double)temp.y();
  output.z = (double)temp.z();

  return output;
}

Triple bno055_getGravity()
{
  imu::Vector<3> temp = bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);
  Triple output;
  output.x = (double)temp.x();
  output.y = (double)temp.y();
  output.z = (double)temp.z();

  return output;
}

#endif
