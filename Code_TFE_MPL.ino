#include "Peripherique.h"


void setup() {
  Serial.begin(9600);
  Pin_Mode();
  Initi_Radio();
  Initi_I2S();
  Lire_CLK();

  tft.begin();
  tft.setRotation(1); 
  tft.fillScreen(ILI9341_BLACK);  

 
}

void loop() {
  Volume();
  Station();
  Audio();

}