
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <Arduino.h>
#include <Wire.h>
#include <radio.h>
#include <RDA5807M.h>
#include <I2S.h>

#define CLK 13
#define DT 11
#define CLK1 A3
#define DT1 A4
#define ADC_PIN_LEFT A0
#define ADC_PIN_RIGHT A1
#define I2S_BCLK_PIN 1
#define I2S_LRC_PIN 0
#define I2S_DIN_PIN 9

 #define TFT_CS 10
 #define TFT_RST 6
 #define TFT_DC 12

extern Adafruit_ILI9341 tft;


#define FIX_BAND RADIO_BAND_FM
#define MAX_VOLUME 25
#define MIN_STATION 8930
#define MAX_STATION 10500
#define STATION_INITIALE 9300

void Volume(void);   //chatgpt et reflexion de ma part
void Station(void);  //chatgpt et reflexion de ma part
void Audio(void);    //chatgpt et reflexion de ma part
////////////////////////////////
void afficherVolume(int vol);  //Fait part moi
int afficherStation(void);     // Fait part moi
void Initi_Radio(void);            // chatgpt et reflexion de ma part
void Pin_Mode(void);           // Fait part moi
void Lire_CLK(void);           //Fait part moi
////////////////////////////////
void Initi_I2S(void);
