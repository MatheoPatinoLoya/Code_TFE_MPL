#include "Peripherique.h"
void setup() {
  Serial.begin(9600);
  Pin_Mode();

  if (!initi_radio(true, false)) {
    while (1)
      ;
  }

  if (!I2S.begin(I2S_PHILIPS_MODE, 44100, 16))  // Initialisation de l'I²S mode Philips, 44.1 kHz, 16 bits44100
  {
    while (1)
      ;
  }
  Lire_CLK();
}

void loop() {
  Volume();
  Station();
  Audio();
}