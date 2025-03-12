#include "Peripherique.h"

void setup() {
  Serial.begin(9600);

  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(CLK1, INPUT);
  pinMode(DT1, INPUT);

  if (!radio.initWire(Wire)) {  // Initialisation du module RDA5807M
    Serial.println("Erreur : module radio non détecté !");
    while (1)
      ;
  }

  // Configuration de la radio
  radio.setup(RADIO_FMSPACING, RADIO_FMSPACING_100);   // Espacement pour l'Europe
  radio.setup(RADIO_DEEMPHASIS, RADIO_DEEMPHASIS_50);  // Déaccentuation pour l'Europe
  radio.setBandFrequency(FIX_BAND, STATION_INITIALE);  // Fixer la station
  radio.setVolume(volume);
  radio.setMono(true);
  radio.setMute(false);
  Serial.println("RDA5807M configuré.");

  if (!I2S.begin(I2S_PHILIPS_MODE, 44100, 16)) {  // Initialisation de l'I²S mode Philips, 44.1 kHz, 16 bits44100
    Serial.println("Erreur : impossible d'initialiser l'I²S.");
    while (1)
      ;
  }

  Serial.println("I²S initialisé.");
  dernierEtatCLK = digitalRead(CLK);
  dernierEtatCLK1 = digitalRead(CLK1);
}

void loop() 
{
  Volume ();
  Station();
  Audio();
}