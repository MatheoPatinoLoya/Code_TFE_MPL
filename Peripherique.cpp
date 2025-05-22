#include "Peripherique.h"

RDA5807M radio;
RTC_PCF8523 rtc;
//*******************Variable Globale*******************************

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

int Enregistre_CLK;
int Enregistre2_CLK;

int FREQUENCE_RADIO = 9000;
int VOLUME_RADIO = 12;

void Lecture_CLK(void) {
  Enregistre_CLK = digitalRead(CLK);
  Enregistre2_CLK = digitalRead(CLK1);
}

void Pin_Mode(void) {
  pinMode(CLK, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  pinMode(CLK1, INPUT_PULLUP);
  pinMode(DT1, INPUT_PULLUP);
}

void Initi_Radio(void) {//librairie
  radio.initWire(Wire);
  radio.setup(RADIO_FMSPACING, RADIO_FMSPACING_100);
  radio.setup(RADIO_DEEMPHASIS, RADIO_DEEMPHASIS_50);

  radio.setBandFrequency(BANDE_RADIO, FREQUENCE_RADIO);  /// parametre pas fixe
  radio.setVolume(VOLUME_RADIO);                         //  parametre pas fixe
  radio.setMute(false);
  radio.setMono(false);
}

void Station(void) {  //mon idée correction de la syntaxte(;.,)avec chat gpt
  int Enregistre1_CLK = digitalRead(CLK);

  if (Enregistre1_CLK != Enregistre_CLK) {
    if (digitalRead(DT) != Enregistre1_CLK) {
      FREQUENCE_RADIO += 10;
      if (FREQUENCE_RADIO > 10800)
        FREQUENCE_RADIO = 8700;

    } else {
      FREQUENCE_RADIO -= 10;
      if (FREQUENCE_RADIO < 8700)
        FREQUENCE_RADIO = 10800;
    }

    radio.setBandFrequency(BANDE_RADIO, FREQUENCE_RADIO);
    Serial.print("Fréquence: ");  //TEST
    Serial.println(FREQUENCE_RADIO);
  }

  Enregistre_CLK = Enregistre1_CLK;
}
void Volume(void) {  /// MOI SEUL
  int Enregistre3_CLK = digitalRead(CLK1);
  if (Enregistre3_CLK != Enregistre2_CLK) {
    if (digitalRead(DT1) != Enregistre2_CLK) {
      VOLUME_RADIO += 1;
      if (VOLUME_RADIO > 15)
        VOLUME_RADIO = 15;
    } else {
      VOLUME_RADIO -= 1;
      if (VOLUME_RADIO < 0)
        VOLUME_RADIO = 0;
    }
    radio.setVolume(VOLUME_RADIO);
    Serial.print("Volume: ");
    Serial.println(VOLUME_RADIO);
  }
  Enregistre2_CLK = Enregistre3_CLK;
}
void Audio(void) {/// repris de chat gpt
  int ADC_Gauche = analogRead(ADC_PIN_LEFT);
  int ADC_Droite = analogRead(ADC_PIN_RIGHT);

  int16_t audioGauche = (ADC_Gauche - 275) * 64;  // echantilloner sur 16 bits recentrée sur 0 puis amplifier 275 son de qualitée
  int16_t audioDroite = (ADC_Droite - 275) * 64;
  I2S.write(audioGauche);
  I2S.write(audioDroite);
}
void Initi_Ampli(void) {///librairie
  I2S.begin(I2S_PHILIPS_MODE, 44100, 16);  // Initialisation de l'I²S mode Philips, 44.1 kHz, 16 bits44100
}