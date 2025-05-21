#include "Peripherique.h"

RDA5807M radio;
RTC_PCF8523 rtc;
//*******************Variable Globale*******************************
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
int dernierEtatCLK = 0;
int dernierEtatCLK1 = 0;
int stationActuelle = STATION_INITIALE;
int volume = 10;

char JourDeSemaine[7][12] = {
  "Dimanche", "Lundi", "Mardi", "Mercredi",
  "Jeudi", "Vendredi", "Samedi"
};


void Volume(void) {
  int etatComparateur = digitalRead(CLK);
  if (etatComparateur != dernierEtatCLK) {
    if (digitalRead(DT) != etatComparateur) {
      if (volume < MAX_VOLUME) volume++;
    } else {
      if (volume > 0) volume--;
    }
    radio.setVolume(volume);
    /////////////////////////////////////////////////¨Parametre pour gere l'affichage sur l'ecran (position ,taille ,etc)
    tft.fillRect(0, 0, 240, 20, ILI9341_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    tft.setCursor(10, 180);
    tft.print("Volume :  ");
    tft.fillRect(120, 180, 60, 16, ILI9341_BLACK);
    tft.setCursor(120, 180);
    tft.print(volume);
    ////////////////////////////////////////////
  }
  dernierEtatCLK = etatComparateur;
}
void Station(void) {
  int etatComparateur1 = digitalRead(CLK1);
  if (etatComparateur1 != dernierEtatCLK1) {
    if (digitalRead(DT1) != etatComparateur1) {
      if (stationActuelle < MAX_STATION) {
        stationActuelle = stationActuelle + 10;  //simplification de l'operateur ternaire ? fait par moi en m'inspirant du volume
      } else {
        stationActuelle = MIN_STATION;
      }

    } else {

      if (stationActuelle > MIN_STATION) {
        stationActuelle = stationActuelle - 10;
      } else {
        stationActuelle = MAX_STATION;
      }
    }
    radio.setBandFrequency(FIX_BAND, stationActuelle);

    ///////////////////////////////////////////////// parametre pour gere l'affichage sur l'ercan (position ,taille ,etc) exemple pris dans la biblioteque
    tft.fillRect(0, 40, 240, 20, ILI9341_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    tft.setCursor(10, 200);
    tft.print("Station :   ");
    tft.setCursor(120, 200);
    tft.print(stationActuelle / 100.0, 1);
    ////////////////////////////////////////////////

    dernierEtatCLK1 = etatComparateur1;
  }
}
void Audio(void) {
  int ADC_Gauche = analogRead(ADC_PIN_LEFT);
  int ADC_Droite = analogRead(ADC_PIN_RIGHT);

  int16_t audioGauche = (ADC_Gauche - 275) * 64;  // echantilloner sur 16 bits recentrée sur 0 puis amplifier 275 son de qualitée
  int16_t audioDroite = (ADC_Droite - 275) * 64;

  I2S.write(audioGauche);
  I2S.write(audioDroite);
}
////////////////////////////////////////////////////////////////
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
void Initi_SPI(void) {
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
}
void Initi_RTC(void) {  // moi
  if (!rtc.begin()) {
    tft.setCursor(10, 40);
    tft.setTextColor(ILI9341_RED);
    tft.println("Erreur RTC !");
  }
  if (!rtc.initialized() || rtc.lostPower()) {
    rtc.adjust(DateTime(2025, 5, 15, 11, 31, 0));
  }
}


////////////////////////////////////////////////////////////////////
void Date_Heure_Jour(void) {
  if (digitalRead(BP) == LOW) {
    DateTime now = rtc.now();

    tft.fillRect(0, 0, 320, 80, ILI9341_BLACK);

    tft.setTextSize(2);
    tft.setTextColor(ILI9341_CYAN);
    tft.setCursor(10, 10);
    tft.print("Jour : ");
    tft.println(JourDeSemaine[now.dayOfTheWeek()]);

    tft.setCursor(10, 30);
    tft.setTextColor(ILI9341_YELLOW);
    tft.print("Date : ");
    tft.print(now.day());
    tft.print("/");
    tft.print(now.month());
    tft.print("/");
    tft.println(now.year());

    tft.setCursor(10, 50);
    tft.setTextColor(ILI9341_GREEN);
    tft.print("Heure : ");
    if (now.hour() < 10) tft.print("0");
    tft.print(now.hour());
    tft.print(":");
    if (now.minute() < 10) tft.print("0");
    tft.print(now.minute());
    tft.print(":");
    if (now.second() < 10) tft.print("0");
    tft.println(now.second());

    delay(1000);///// enlever le delay
  }
}