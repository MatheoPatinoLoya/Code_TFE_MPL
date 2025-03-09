#include <I2S.h>
#include <Arduino.h>
#include <Wire.h>
#include <radio.h>
#include <RDA5807M.h>
// ----- Configuration des broches -----
#define CLK 13  // Encodeur lineaire G
#define DT 11
#define CLK1 A3  // Encodeur lineaire D
#define DT1 A4
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
#define MAX_VOLUME 25           // fixer un volume max
#define MIN_STATION 8930        // fixer une station min
#define MAX_STATION 10500       // fixer une station max
#define STATION_INITIALE 9300   // fixer une station initiale

RDA5807M radio;
int dernierEtatCLK, dernierEtatCLK1;
int stationActuelle = STATION_INITIALE;
int volume = 12;

void Volume() {
  int etatComparateur = digitalRead(CLK);   //etat initial de clk enregistré(variable)
  if (etatComparateur != dernierEtatCLK) {  //verifie le sens horaire,anti grace a dt
    if (digitalRead(DT) != etatComparateur) {
      if (volume < MAX_VOLUME) volume++;  //grace au sens de rotation on ajuste le volume
    } else {
      if (volume > 0) volume--;
    }

    radio.setVolume(volume);  //  le volume est appliquer a la radio

    Serial.print("Voulume actuelle: ");
    Serial.println(volume);
  }
  dernierEtatCLK = etatComparateur;  // mise a jour
}

void Station() {
  int etatComparateur1 = digitalRead(CLK1);

  if (etatComparateur1 != dernierEtatCLK1) {
    if (digitalRead(DT1) != etatComparateur1) {
      if (stationActuelle < MAX_STATION) stationActuelle += 10;  //augmente de station tant que elle ne depasse pas le max
      else stationActuelle = MIN_STATION;                        // si elle depase elle reveint a la station min
    } else {
      if (stationActuelle > MIN_STATION) stationActuelle -= 10;  // memme chose diminue jusqu'a station min
      else stationActuelle = MAX_STATION;                        // memme chose si elle depase la sation min et reviens a station max
    }

    radio.setBandFrequency(RADIO_BAND_FM, stationActuelle);

    Serial.print("Nouvelle station: ");
    Serial.println(stationActuelle / 100.0, 1);
  }
  dernierEtatCLK1 = etatComparateur1;
}

void Audio() {

  int16_t audioSampleLeft = (analogRead(ADC_PIN_LEFT) - 512) * 64;
  int16_t audioSampleRight = (analogRead(ADC_PIN_RIGHT) - 512) * 64;

  I2S.write(audioSampleLeft);   // Envoi du canal gauche
  I2S.write(audioSampleRight);  // Envoi du canal droit
                                                            
  delayMicroseconds(22);  // respecter le débit d'échantillonnage 44.1 kHz (1/44100 = ~22 µs)

}

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

  if (!I2S.begin(I2S_PHILIPS_MODE, 44100, 16)) {                   // Initialisation de l'I²S mode Philips, 44.1 kHz, 16 bits44100
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