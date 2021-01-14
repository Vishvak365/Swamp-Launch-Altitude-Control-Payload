#include <SD.h>
#include <SPI.h>
#define CS_PORT 53
#define DI_PORT 51
#define DO_PORT 50
#define CLK_PORT 52

#ifndef SD_CARD_RT
#define SD_CARD_RT

void initSD_debug()
{

  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output
  // or the SD library functions will not work.
  pinMode(CS_PORT, OUTPUT);

  if (!SD.begin(CS_PORT))
  {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
}

void initSD()
{
  pinMode(CS_PORT, OUTPUT);

  if (!SD.begin(CS_PORT))
  {
    //TODO: FAILURE INDICATOR
    return;
  }
}

#endif
