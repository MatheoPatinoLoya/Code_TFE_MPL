#include "Peripherique.h"


void setup() {
  Serial.begin(9600);

  Pin_Mode();
  Initi_Radio();
  Initi_I2S();
  Lire_CLK();
  Initi_SPI();
  Initi_RTC();
}

void loop() {
  Volume();
  Station();
  Audio();
    // Date_Heure_Jour();
 
}