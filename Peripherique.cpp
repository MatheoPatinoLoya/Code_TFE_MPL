#include "Peripherique.h"

RDA5807M radio;
int dernierEtatCLK = 0;
int dernierEtatCLK1 = 0;
int stationActuelle = STATION_INITIALE;

int volume = 15;

void Volume(void) {
  int etatComparateur = digitalRead(CLK);

  if (etatComparateur != dernierEtatCLK) {

    if (digitalRead(DT) != etatComparateur) {
      if (volume < MAX_VOLUME) volume++;
    } else {
      if (volume > 0) volume--;
    }

    radio.setVolume(volume);
    afficherVolume(volume);
  }

  dernierEtatCLK = etatComparateur;
}
void Station(void) {
  int etatComparateur1 = digitalRead(CLK1);
  if (etatComparateur1 != dernierEtatCLK1) {
    if (digitalRead(DT1) != etatComparateur1) {
      stationActuelle = (stationActuelle < MAX_STATION) ? stationActuelle + 10 : MIN_STATION;
    } else {
      stationActuelle = (stationActuelle > MIN_STATION) ? stationActuelle - 10 : MAX_STATION;
    }
    radio.setBandFrequency(FIX_BAND, stationActuelle);
    afficherStation();
  }
  dernierEtatCLK1 = etatComparateur1;
}
void Audio(void) {
  int16_t audioSampleLeft = (analogRead(ADC_PIN_LEFT) - 300) * 64;    // son de qualitée 300 pas 512
  int16_t audioSampleRight = (analogRead(ADC_PIN_RIGHT) - 300) * 64;  // son de qualitée 300 pas 512
  I2S.write(audioSampleLeft);
  I2S.write(audioSampleRight);
  delayMicroseconds(22);
}
////////////////////////////////////////////////////////////////
void afficherVolume(int vol) {
  Serial.print("Volume actuel : ");
  Serial.println(vol);
}
int afficherStation(void) {
  Serial.print("Nouvelle station : ");
  Serial.println(stationActuelle / 100.0, 1);
  return stationActuelle;
}
void Initi_Radio(void) {
  radio.initWire(Wire);
  radio.setup(RADIO_FMSPACING, RADIO_FMSPACING_100);   // Espacement pour l'Europe
  radio.setup(RADIO_DEEMPHASIS, RADIO_DEEMPHASIS_50);  // Déaccentuation pour l'Europe
  radio.setBandFrequency(FIX_BAND, STATION_INITIALE);  // Fixer la station
  radio.setVolume(volume);
  radio.setMono(true);
  radio.setMute(true);
}
void Pin_Mode(void) {
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(CLK1, INPUT);
  pinMode(DT1, INPUT);
}
void Lire_CLK(void) {
  dernierEtatCLK = digitalRead(CLK);
  dernierEtatCLK1 = digitalRead(CLK1);
}

///////////////////////////////////////////////////////////////
void Initi_I2S(void) {
  I2S.begin(I2S_PHILIPS_MODE, 44100, 16);  // Initialisation de l'I²S mode Philips, 44.1 kHz, 16 bits44100
}