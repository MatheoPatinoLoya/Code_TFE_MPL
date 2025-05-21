//*******************************************************************
//  Programme : Fonctionnement de la Radio
//  Auteur : MATHEO PATINO LOYA 6ème Electronique INRACI
//  Hardware : Faether M0 Express + RDA5807M + PCF 8523 + MAX 98357A + KY-040 + 2.8 TFT 240*320 +
//  Date : 04/07/2024
//********************************************************************

#include "Peripherique.h"

void setup() {
  Serial.begin(9600);
  pinMode(BP, INPUT_PULLUP);
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
  Date_Heure_Jour();
}