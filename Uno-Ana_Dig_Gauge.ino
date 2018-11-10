// This is an simple example to display a Analog Gauge
// and a Digital Gauge with the wonderfull Adafruit_GFX.h Library 
// you can chance the Values in Gauge Header
/*
enum
{
	GaugeCenterX = 70,
	GaugeCenterY = 70,
	GaugeBackgroundColor = ILI9341_BEIGE,

	GaugeCircleRadius = 50,
	GaugeCircleRadiusColor = ILI9341_GOLD,
	GaugePointerLowColor = ILI9341_DARKGREEN,

	GaugePointerMidColor = ILI9341_CRIMSON,
	GaugePointerHighColor = ILI9341_RED,
	GaugePointerHubColor = ILI9341_NAVY,
	GaugeFrameColor = ILI9341_LIGHTBLUE,
	GaugeFrameColorLowerLine = ILI9341_DARKBLUE,
	GaugeFrameSize = 52,
	GaugeFrameHeight = GaugeFrameSize + 12,

	DigiTextColor = ILI9341_BLUEVIOLET,

	DigiBkColor = ILI9341_YELLOWGREEN,

	DigiX = 5,
	DigiY = 100,
	DigiW = 130,
	DigiH = 25
};
*/

/*
With the enum Unit can you change the unit 
const char aUnit[7][3] = { "", "mA", "mV", "O", "kO", "MO", "kV" };
enum Unit {

	Without  = 0,
	millyAmp = 1,
    millyVolt = 2,
	Ohm       = 3,
	KiloOhm   = 4,
	MegaOhm   = 5,
	kV        = 6
};
*/


#include "Gauge.h"
#include "SPI.h"
#include <Adafruit_GFX.h> 
#include <MCUFRIEND_kbv.h>

#include <stdio.h>  // include the C++ standard IO library

MCUFRIEND_kbv tft;

GAUGEClass * _Gauge;

// https://stackoverflow.com/questions/2704521/generate-random-double-numbers-in-c
double doubleRand() {
	return double(rand()) / (double(RAND_MAX) + 1.0);
}


void setup()
{
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  Serial.print("TFT ID = 0x");
  Serial.println(ID, HEX);
  Serial.println("Calibrate for your Touch Panel");
  if (ID == 0xD3D3) ID = 0x9486; // write-only shield
  tft.begin(ID);
  tft.setRotation(1);            //Landscape
  tft.fillScreen( ILI9341_DARKGRAY );

  Serial.print("Serial Print Done");

  _Gauge = new(GAUGEClass);
  _Gauge->initAnalog(&tft, GaugeBackgroundColor);
  
     //InitValue();

  for (uint16_t i = 0; i < 195; i++) {
	  _Gauge->SetAnalogValue(i);
	  delay(10);
	} 
  _Gauge->initDigi(&tft, GaugeBackgroundColor, DigiTextColor, millyVolt);
 
}

void loop()
{
	char Puffer[10];
	int T;
	// The max Value is 195.00 so you have to adopt this for your purpose 
	float f = doubleRand() * 195; // Float Values by chance 
	dtostrf(f, 1, 4, Puffer);  // The Arduino way to convert Floats to a string
	_Gauge->SetAnalogValue(f); // the Analog Gauge
	_Gauge->SetDigiValue(f);   // the Digital Gauge

	delay(100);
}

