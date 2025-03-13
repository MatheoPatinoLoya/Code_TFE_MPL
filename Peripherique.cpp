#include "Peripherique.h"

RDA5807M radio;
int dernierEtatCLK, dernierEtatCLK1;
int stationActuelle = STATION_INITIALE;
int volume = 15;
 bool modeMono = true;
 bool modeMute = false;

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
  int16_t audioSampleLeft = (analogRead(ADC_PIN_LEFT) - 512) * 64;
  int16_t audioSampleRight = (analogRead(ADC_PIN_RIGHT) - 512) * 64;
  I2S.write(audioSampleLeft);
  I2S.write(audioSampleRight);
  delayMicroseconds(22);
}
////////////////////////////////////////////////////////////////
void afficherVolume(int vol) {
  Serial.print("Volume actuel : ");
  Serial.println(vol);
}
int afficherStation() {
  Serial.print("Nouvelle station : ");
  Serial.println(stationActuelle / 100.0, 1);
  return stationActuelle;
}
bool initi_radio(bool mono, bool mute){
  if (!radio.initWire(Wire)) {
    Serial.println("Erreur : module radio non détecté !");
    return false;
  }
  radio.setup(RADIO_FMSPACING, RADIO_FMSPACING_100);   // Espacement pour l'Europe
  radio.setup(RADIO_DEEMPHASIS, RADIO_DEEMPHASIS_50);  // Déaccentuation pour l'Europe
  radio.setBandFrequency(FIX_BAND, STATION_INITIALE);           // Fixer la station
  radio.setVolume(volume);
  radio.setMono(mono);
  radio.setMute(mute);

  Serial.println("RDA5807M configuré.");
  return true;
}
void Pin_Mode(void){
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(CLK1, INPUT);
  pinMode(DT1, INPUT);
}
///////////////////////////////////////////////////////////////