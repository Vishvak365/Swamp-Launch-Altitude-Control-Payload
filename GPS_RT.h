#ifndef GPS_RT
#define GPS_RT

#include <Adafruit_GPS.h>

#define GPSSerial Serial1

Adafruit_GPS GPS(&GPSSerial);
void gps_update();
void gps_print();

void initGPS_debug()
{

  Serial.println(F("GPS Initialization Debug"));

  GPS.begin(9600);
  //if (!GPS.begin(9600)){
  //Serial.println("Could not find a valid GPS sensor, check wiring!");
  //}
  //else{
  // turn on RMC (recommended minimum) and GGA (fix data) including altitude

  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz

  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
                                             // For the parsing code to work nicely and have time to sort thru the data, and
                                             // print it out we don't suggest using anything higher than 1 Hz
                                             //Wait for GPS to get satelite fix

  //Wait for GPS to get satelite fix
  Serial.println("Waiting for GPS to connect to satellite...");
  /*(gps_update();
    while(!GPS.fix){
      gps_update();
    }*/
  gps_print();

  Serial.println("GPS sensor successfully initialized!");
}

//}

void initGPS()
{

  GPS.begin(9600);

  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  //UPDATE BAUD RATE
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz
  //Wait for GPS to get satelite fix

  /*gps_update();
    while(!GPS.fix){
      gps_update();
    }*/
}

void gps_update()
{
  Serial.println("updating");
  bool success = false;
  while (!success)
  {
    char c = GPS.read();

    // if a sentence is received, we can check the checksum, parse it...
    if (GPS.newNMEAreceived())
    {
      // a tricky thing here is if we print the NMEA sentence, or data
      // we end up not listening and catching other sentences!
      // so be very wary if using OUTPUT_ALLDATA and trying to print out data
      //Serial.println(GPS.lastNMEA()); // this also sets the newNMEAreceived() flag to false
      Serial.println(GPS.lastNMEA());
      if (GPS.parse(GPS.lastNMEA())) // this also sets the newNMEAreceived() flag to false
        success = true;              // we can fail to parse a sentence in which case we should just wait for another
    }
  }
}
void gps_print()
{
  Serial.print("\nTime: ");
  if (GPS.hour < 10)
  {
    Serial.print('0');
  }
  Serial.print(GPS.hour, DEC);
  Serial.print(':');
  if (GPS.minute < 10)
  {
    Serial.print('0');
  }
  Serial.print(GPS.minute, DEC);
  Serial.print(':');
  if (GPS.seconds < 10)
  {
    Serial.print('0');
  }
  Serial.print(GPS.seconds, DEC);
  Serial.print('.');
  if (GPS.milliseconds < 10)
  {
    Serial.print("00");
  }
  else if (GPS.milliseconds > 9 && GPS.milliseconds < 100)
  {
    Serial.print("0");
  }
  Serial.println(GPS.milliseconds);
  Serial.print("Date: ");
  Serial.print(GPS.month, DEC);
  Serial.print('/');
  Serial.print(GPS.day, DEC);
  Serial.print("/20");
  Serial.println(GPS.year, DEC);
  Serial.print("Fix: ");
  Serial.print((int)GPS.fix);
  Serial.print(" quality: ");
  Serial.println((int)GPS.fixquality);

  Serial.print("Location: ");
  Serial.print(GPS.latitude, 4);
  Serial.print(GPS.lat);
  Serial.print(", ");
  Serial.print(GPS.longitude, 4);
  Serial.println(GPS.lon);
  Serial.print("Speed (knots): ");
  Serial.println(GPS.speed);
  Serial.print("Angle: ");
  Serial.println(GPS.angle);
  Serial.print("Altitude: ");
  Serial.println(GPS.altitude);
  Serial.print("Satellites: ");
  Serial.println((int)GPS.satellites);
}

#endif
