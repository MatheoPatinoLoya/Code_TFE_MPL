#include "Peripherique.h"
 #include <Adafruit_ILI9341.h>
 #include <Adafruit_GFX.h>
#define TFT_CS 10
#define TFT_RST 6
#define TFT_DC 12
void setup() {
  Serial.begin(9600);
  Pin_Mode();

  if (!initi_radio(true, false)) {// le 2 pour mute
    while (1)
      ;
  }

  if (!I2S.begin(I2S_PHILIPS_MODE, 44100, 16))  // Initialisation de l'I²S mode Philips, 44.1 kHz, 16 bits44100
  {
    while (1)
      ;
  }
  Lire_CLK();

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
     //pinMode(PWM, INPUT);
  //  analogWrite(PWM, 255);

  Serial.begin(9600);
  tft.begin();         // Initialise l'écran
  tft.setRotation(1);  // Définissez l'orientation de l'écran

  // Efface l'écran avec une couleur de fond
  tft.fillScreen(ILI9341_BLACK);

  // Afficher du texte
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.println("Hello,World!");

  // Dessinez quelques formes
  tft.fillRect(10, 30, 100, 50, ILI9341_RED);      // Rectangle rouge
  tft.drawCircle(150, 60, 30, ILI9341_ORANGE);     // Cercle bleu
  tft.drawLine(10, 100, 200, 100, ILI9341_GREEN);  // Ligne verte
}

void loop() {
  Volume();
  Station();
  Audio();
}