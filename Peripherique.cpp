 #include "Peripherique.h"


RDA5807M radio;
int dernierEtatCLK , dernierEtatCLK1 ;
int stationActuelle = STATION_INITIALE;
int volume = 12;


void Volume(void) {
    int etatComparateur = digitalRead(CLK);
    if (etatComparateur != dernierEtatCLK) {
        if (digitalRead(DT) != etatComparateur) {
            if (volume < MAX_VOLUME) volume++;
        } else {
            if (volume > 0) volume--;
        }
        radio.setVolume(volume);
        Serial.print("Volume actuel: ");
        Serial.println(volume);
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
        Serial.print("Nouvelle station: ");
        Serial.println(stationActuelle / 100.0, 1);
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
