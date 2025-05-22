#include "Peripherique.h"

RDA5807M radio;
RTC_PCF8523 rtc;
//*******************Variable Globale*******************************
//// librairie + moi + chat gpt
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
int dernierEtatCLK = 0;
int dernierEtatCLK1 = 0;
int stationActuelle = STATION_INITIALE;
int volume = 10;
////
char JourDeSemaine[7][12] = {///////// chat gpt
  "Dimanche", "Lundi", "Mardi", "Mercredi",
  "Jeudi", "Vendredi", "Samedi"
};
//////////chat gpt + librairie + moi

void Volume(void) {  ////////////chatgpt et reflexion de ma part
  int etatComparateur = digitalRead(CLK);
  if (etatComparateur != dernierEtatCLK) 
  {
    if (digitalRead(DT) != etatComparateur) 
    {
      if (volume < MAX_VOLUME) volume++;
    } else {
      if (volume > 0) volume--;
    }
    radio.setVolume(volume);
    ////////////////////////////////chatgpt et reflexion de ma part
    /////////////////////////////////////////////////¨Parametre pour gere l'affichage sur l'ecran (position ,taille ,etc)

    // tft.fillRect(0, 0, 240, 20, ILI9341_BLACK);
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
void Station(void) {/////////chatgpt et reflexion de ma part
  int etatComparateur1 = digitalRead(CLK1);
  if (etatComparateur1 != dernierEtatCLK1) 
  {
    if (digitalRead(DT1) != etatComparateur1) 
    {
      if (stationActuelle < MAX_STATION)
      {
        stationActuelle = stationActuelle + 10;  //simplification de l'operateur ternaire ? fait par chat g^t en m'inspirant du volume
      }
       else 
      {
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
    tft.fillRect(120, 200, 80, 16, ILI9341_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    tft.setCursor(10, 200);
    tft.print("Station :   ");
    tft.setCursor(120, 200);
    tft.print(stationActuelle / 100.0, 1);
    ////////////////////////////////////////////////

    dernierEtatCLK1 = etatComparateur1;
  }
}/////chatgpt 
  int ADC_Gauche = analogRead(ADC_PIN_LEFT);
  int ADC_Droite = analogRead(ADC_PIN_RIGHT);

  int16_t audioGauche = (ADC_Gauche - 275) * 64;  // echantilloner sur 16 bits recentrée sur 0 puis amplifier 275 son de qualitée
  int16_t audioDroite = (ADC_Droite - 275) * 64;

  I2S.write(audioGauche);
  I2S.write(audioDroite);
}
////////////////////////////////////////////////////////////////chatgpt et reflexion de ma part
void Initi_Radio(void) //////////libraire
{
  radio.initWire(Wire);
  radio.setup(RADIO_FMSPACING, RADIO_FMSPACING_100);   // Espacement pour l'Europe
  radio.setup(RADIO_DEEMPHASIS, RADIO_DEEMPHASIS_50);  // Déaccentuation pour l'Europe
  radio.setBandFrequency(FIX_BAND, STATION_INITIALE);  // Fixer la station
  radio.setVolume(volume);
  radio.setMono(true);
  radio.setMute(true);
}
void Pin_Mode(void) 
{
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(CLK1, INPUT);
  pinMode(DT1, INPUT);
}
void Lire_CLK(void) 
{
  dernierEtatCLK = digitalRead(CLK);
  dernierEtatCLK1 = digitalRead(CLK1);
}

///////////////////////////////////////////////////////////////librairie
void Initi_I2S(void) {
  I2S.begin(I2S_PHILIPS_MODE, 44100, 16);  // Initialisation de l'I²S mode Philips, 44.1 kHz, 16 bits44100
}
void Initi_SPI(void) 
{
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
}
void Initi_RTC(void) // moi
{  
  if (!rtc.begin()) 
  {
    tft.setCursor(10, 40);
    tft.setTextColor(ILI9341_RED);
    tft.println("Erreur RTC !");
  }
  if (!rtc.initialized() || rtc.lostPower()) {
    rtc.adjust(DateTime(2025, 5, 15, 11, 31, 0));
  }
}
////////////////////////////////////////////////////////libraire




/////////////////////////////////////////:chat gpt
bool affichageActif = false;  // Affiche l'ecran deja eteint
bool ancienEtatBP = HIGH;    //   l'etat de bouton 

void Date_Heure_Jour(void) 
{
  static int ancienneSeconde = -1;///////// enregistrement des valeur 
  static int ancienneMinute = -1;
  static int ancienneHeure   = -1;
  static int ancienJour      = -1;
  static int ancienMois      = -1;
  static int ancienneAnnee   = -1;
  static int ancienJourSemaine = -1;

  bool etatBP = digitalRead(BP);  // Lis l'etat du Bp
///////////////////quand j'appuie le bp affiche l'heure la date etc il demute la radio 
//une second fois n'affiche plus les jour heure ,etc sur l'ecran , il mute la radio 
  
  if (ancienEtatBP == HIGH) //  verfication de l'etat
  {                   
    if (etatBP == LOW) 
    {                   
      if (affichageActif == false) 
      {    
        affichageActif = true;
        radio.setMute(true);
      } else {
        affichageActif = false;
        radio.setMute(false);

        tft.fillRect(0, 0, 320, 80, ILI9341_BLACK);
        ancienneSeconde = -1;
        ancienneMinute = -1;
        ancienneHeure = -1;
        ancienJour = -1;
        ancienMois = -1;
        ancienneAnnee = -1;
        ancienJourSemaine = -1;
      }
    }
  }
  ancienEtatBP = etatBP; //enregistre l'ancien etat du Bp et renouvelle 

  if (affichageActif == true) 
  {
    DateTime now = rtc.now();
    tft.setTextSize(2);

    // Jour de la semaine
    if (now.dayOfTheWeek() < ancienJourSemaine) 
    {
     
    } else 
    {
      if (now.dayOfTheWeek() > ancienJourSemaine) {
        tft.setTextColor(ILI9341_BLACK);
        tft.setCursor(10, 10);
        tft.print("Jour : ");
        if (ancienJourSemaine >= 0) {
          tft.print(JourDeSemaine[ancienJourSemaine]);
        }
        tft.setTextColor(ILI9341_CYAN);
        tft.setCursor(10, 10);
        tft.print("Jour : ");
        tft.print(JourDeSemaine[now.dayOfTheWeek()]);
        ancienJourSemaine = now.dayOfTheWeek();
      }
    }

    // Date
    if (now.day() < ancienJour) {
      
    } else 
    {
      if (now.day() > ancienJour) 
      {
        tft.setTextColor(ILI9341_BLACK);
        tft.setCursor(10, 30);
        tft.print("Date : ");
        if (ancienJour >= 0) {
          tft.print(ancienJour);
          tft.print("/");
          tft.print(ancienMois);
          tft.print("/");
          tft.print(ancienneAnnee);
        }
        tft.setTextColor(ILI9341_YELLOW);
        tft.setCursor(10, 30);
        tft.print("Date : ");
        tft.print(now.day());
        tft.print("/");
        tft.print(now.month());
        tft.print("/");
        tft.print(now.year());

        ancienJour = now.day();
        ancienMois = now.month();
        ancienneAnnee = now.year();
      }
    }

    // Heure
    if (now.second() < ancienneSeconde) {
    
    } else {
      if (now.second() > ancienneSeconde) {
        tft.setTextColor(ILI9341_BLACK);
        tft.setCursor(10, 50);
        tft.print("Heure : ");
        if (ancienneHeure >= 0) {
          if (ancienneHeure < 10) tft.print("0");
          tft.print(ancienneHeure);
          tft.print(":");
          if (ancienneMinute < 10) tft.print("0");
          tft.print(ancienneMinute);
          tft.print(":");
          if (ancienneSeconde < 10) tft.print("0");
          tft.print(ancienneSeconde);
        }
        tft.setTextColor(ILI9341_GREEN);
        tft.setCursor(10, 50);
        tft.print("Heure : ");
        if (now.hour() < 10) tft.print("0");
        tft.print(now.hour());
        tft.print(":");
        if (now.minute() < 10) tft.print("0");
        tft.print(now.minute());
        tft.print(":");
        if (now.second() < 10) tft.print("0");
        tft.print(now.second());

        ancienneHeure = now.hour();
        ancienneMinute = now.minute();
        ancienneSeconde = now.second();
      }
    }
  }
}
///////////////////////////////////////////////////////////////////////////chat gpt 