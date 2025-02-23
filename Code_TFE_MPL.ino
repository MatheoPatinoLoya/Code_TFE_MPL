#include "RTClib.h"  //librairie du rtc
RTC_PCF8523 rtc;

#include <Adafruit_GFX.h>  //Bilboiteque pour l'ecran
#include <Adafruit_ILI9341.h>

#include <Arduino.h>
#include <Wire.h>
#include <radio.h>
#include <RDA5807M.h>
#include <I2S.h>  // Bibliothèque pour l'I²S

// ----- Configuration des broches -----

#define CLK 13  // Encodeur lineaire G
#define DT 11

#define CLK A3  // Encodeur lineaire D
#define DT A4

#define TFT_CS 10  //broche de l'ecran
#define TFT_RST 6
#define TFT_DC 12



#define ADC_PIN_LEFT A0   // Broche pour l'entrée analogique gauche (RLOUD du RDA5807M)
#define ADC_PIN_RIGHT A1  // Broche pour l'entrée analogique droite (GLOUD du RDA5807M)
#define I2S_BCLK_PIN 1    // Broche BCLK de l'I²S tx
#define I2S_LRC_PIN 0     // Broche LRC de l'I²S rx
#define I2S_DIN_PIN 9     // Broche DIN de l'I²S

// ----- Configuration fixe du RDA5807M -----
#define FIX_BAND RADIO_BAND_FM  ///< Bande FM
#define FIX_STATION 9290        ///< Station à 89.30 MHz
#define FIX_VOLUME 10           ///< Niveau de volume

RDA5807M radio;  // Instance pour gérer le RDA5807M

void setup() {
  // Initialisation série pour le débogage
  Serial.begin(9600);

  if (!rtc.initialized() || rtc.lostPower()) {
    Serial.println("RTC non initialisé, réglage de l'heure...");
    rtc.adjust(DateTime(2025, 2, 23, 18, 30, 0));  // Régle l'horloge à 23 février 2025,18h30
  }

  // Initialisation du module RDA5807M
  if (!radio.initWire(Wire)) {
    Serial.println("Erreur : module radio non détecté !");
    while (1)
      ;
  }

  // Configuration de la radio
  radio.setup(RADIO_FMSPACING, RADIO_FMSPACING_100);   // Espacement pour l'Europe
  radio.setup(RADIO_DEEMPHASIS, RADIO_DEEMPHASIS_50);  // Déaccentuation pour l'Europe
  radio.setBandFrequency(FIX_BAND, FIX_STATION);       // Fixer la station
  radio.setVolume(FIX_VOLUME);
  radio.setMono(false);
  radio.setMute(false);

  Serial.println("RDA5807M configuré.");

  // Initialisation de l'I²S
  if (!I2S.begin(I2S_PHILIPS_MODE, 44100, 16)) {  // Mode Philips, 44.1 kHz, 16 bits44100
    Serial.println("Erreur : impossible d'initialiser l'I²S.");
    while (1)
      ;
  }

  Serial.println("I²S initialisé.");
}

void loop() {
  
  DateTime now = rtc.now();

    Serial.print("Date: ");
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" - Heure: ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.println(now.second(), DEC);

    delay(1000); 
  
  
  
  // Lecture du signal analogique sur les broches ADC_PIN_LEFT (RLOUD) et ADC_PIN_RIGHT (GLOUD)
  int adcValueLeft = analogRead(ADC_PIN_LEFT);
  int adcValueRight = analogRead(ADC_PIN_RIGHT);

  // Normalisation des valeurs ADC pour correspondre au format audio 16 bits
  int16_t audioSampleLeft = (adcValueLeft - 512) * 64;    // Ajustement de l'amplitude pour le canal gauche 64
  int16_t audioSampleRight = (adcValueRight - 512) * 64;  // Ajustement de l'amplitude pour le canal droit

  // Envoi des deux canaux au MAX98357 via I²S
  I2S.write(audioSampleLeft);   // Envoi du canal gauche
  I2S.write(audioSampleRight);  // Envoi du canal droit

  // Optionnel : ajout d'une pause pour respecter le débit d'échantillonnage
  delayMicroseconds(22);  // Correspond à 44.1 kHz (1/44100 = ~22 µs)

  // Débogage périodique (toutes les 3 secondes)
  static unsigned long lastDebug = 0;
  if (millis() - lastDebug > 3000) {
    char freq[12];
    radio.formatFrequency(freq, sizeof(freq));
    Serial.print("Station: ");
    Serial.println(freq);

    Serial.print("Radio Info: ");
    radio.debugRadioInfo();

    Serial.print("Audio Info: ");
    radio.debugAudioInfo();

    Serial.print("Left Channel ADC: ");
    Serial.println(adcValueLeft);

    Serial.print("Right Channel ADC: ");
    Serial.println(adcValueRight);

    lastDebug = millis();
  }
}
