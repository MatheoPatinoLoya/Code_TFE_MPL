#include "Peripherique.h"
void setup() {
  Serial.begin(9600);
  Pin_Mode();

  if (!initi_radio(true, false)) {
    while (1)
      ;
  }
 
  if (!I2S.begin(I2S_PHILIPS_MODE, 44100, 16)) {  // Initialisation de l'I²S mode Philips, 44.1 kHz, 16 bits44100
    Serial.println("Erreur : impossible d'initialiser l'I²S.");
    while (1)
      ;
  }

  Serial.println("I²S initialisé.");
  dernierEtatCLK = digitalRead(CLK);
  dernierEtatCLK1 = digitalRead(CLK1);
}

void loop() {
  Volume();
  Station();
  Audio();
}