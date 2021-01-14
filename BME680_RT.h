#ifndef BME680_RT
#define BME680_RT

/***************************************************************************
  This is a library for the BME680 gas, humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME680 Breakout
  ----> http://www.adafruit.com/products/3660

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include <SPI.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>

#define BME_SCK 52
#define BME_MISO 50
#define BME_MOSI 51
#define BME_CS 49

#define SEALEVELPRESSURE_HPA (1015.58)

//Adafruit_BME680 bme; // I2C
Adafruit_BME680 bme(BME_CS); // hardware SPI
//Adafruit_BME680 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);

void initBME680_debug()
{

  Serial.println(F("BME680 Initialization Debug"));

  if (!bme.begin())
  {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
  }
  else
  {
    Serial.println("BME680 sensor successfully initialized!");
  }

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
}

void initBME680()
{

  bme.begin();

  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
}
double bme680_getPressure()
{
  //Returns pressure in hPa (Pa*10^2)

  return bme.pressure / 100;
}

double bme680_getAltitude()
{
  //Get APPROXIMATE Altitude in meters
  return bme.readAltitude(SEALEVELPRESSURE_HPA);
}

double bme680_getTemperature()
{
  //Returns temperature in degrees Celcius

  return bme.temperature;
}

double bme680_getHumidity()
{
  //Returns humidity in %

  return bme.humidity;
}

double bme680_getGas()
{
  //Returns gas resistance in Kohms

  return bme.gas_resistance / 1000.0;
}
#endif
