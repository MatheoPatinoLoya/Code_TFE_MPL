#include "Peripherique.h"

RDA5807M radio;


RTC_PCF8523 rtc;
//*******************Variable Globale*******************************

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);


void Pin_Mode(void) {

  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  
}

void Initi_Radio(void) {

  radio.initWire(Wire);
  radio.setup(RADIO_FMSPACING, RADIO_FMSPACING_100);
  radio.setup(RADIO_DEEMPHASIS, RADIO_DEEMPHASIS_50);

  radio.setBandFrequency(BANDE_RADIO, FREQUENCE_RADIO); /// parametre pas fixe
  radio.setVolume(VOLUME_RADIO);//  parametre pas fixe
  radio.setMute(false);
  radio.setMono(false);


 
}

void Station(void) {
 



 
}
