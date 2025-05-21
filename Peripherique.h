//************************Librairies*********************************
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <Arduino.h>
#include <Wire.h>
#include <radio.h>
#include <RDA5807M.h>
#include <I2S.h>
#include "RTClib.h"
//****************DEFINITION DES CONSTANTE***************************
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

#define FIX_BAND RADIO_BAND_FM
#define MAX_VOLUME 15
#define MIN_STATION 8800
#define MAX_STATION 10800
#define STATION_INITIALE 9300

#define BP A5

void Volume(void);   //chatgpt et reflexion de ma part
void Station(void);  //chatgpt et reflexion de ma part
void Audio(void);    //chatgpt et reflexion de ma part
////////////////////////////////
//     // Fait part moi
void Initi_Radio(void);        // chatgpt et reflexion de ma part
void Pin_Mode(void);           // Fait part moi
void Lire_CLK(void);           //Fait part moi
////////////////////////////////
void Initi_I2S(void);
void Initi_SPI(void);
void Initi_RTC(void);
void Date_Heure_Jour(void);
