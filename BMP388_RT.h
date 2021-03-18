
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP3XX.h>

#define BMP_SCK 21
#define BMP_MOSI 20

#define SEALEVELPRESSURE_HPA (1015.58)

#ifndef BMP388_RT
#define BMP388_RT
//const baseline_altitude = 6;

Adafruit_BMP3XX bmp; // I2C
void initBMP388_debug()
{

  Serial.println(F("BMP388 Initialization Debug"));

  if (!bmp.begin())
  {
    Serial.println("Could not find a valid BMP388 sensor, check wiring!");
  }
  else
  {
    Serial.println("BMP388 sensor successfully initialized!");
  }

  // Set up oversampling and filter initialization
  // bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  // bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  // bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_2X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_1X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_1);
  //bmp.setOutputDataRate(BMP3_ODR_50_HZ);
}

void initBMP388()
{
  bmp.begin();
  // Set up oversampling and filter initialization
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_2X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_1X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_1);
  //bmp.setOutputDataRate(BMP3_ODR_50_HZ);
}

double bmp388_getPressure()
{
  //Returns pressure in hPa (Pa*10^2)

  return bmp.pressure / 100;
}

double bmp388_getAltitude()
{
  //Get APPROXIMATE Altitude in meters
  return bmp.readAltitude(SEALEVELPRESSURE_HPA);
}

double bmp388_getTemperature()
{
  //Returns temperature in degrees Celcius

  return bmp.temperature;
}

#endif
