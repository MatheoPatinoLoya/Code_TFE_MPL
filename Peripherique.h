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

#define BP A5
#define BP1 5

#define BANDE_RADIO  RADIO_BAND_FM //variable pour changer les parametre non fixe

void Initi_Radio(void);
void Station(void);
void Pin_Mode(void);
void Lecture_CLK(void);
void Volume(void);

void Audio (void);
void Initi_Ampli(void);