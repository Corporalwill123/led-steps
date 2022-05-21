#ifndef HEADER_H
#define HEADER_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Timer.h>

//D1 Reciever
//D2 Sensor1 *Bottom Sensor
//D3 LEDS
//D5 Sensor2
//D6 Sensor3
//D7 Sensor4 *Top Sensor

#define firstSensor  D2 //Downstairs Sensor Pin
#define secondSensor D5 //above downSensor
#define thirdSensor D6 //below upSensor
#define fourthSensor  D7 //Upstairs Sensor Pin

extern bool autoButton;
extern bool manualButton;
extern bool offButton;
extern int timerLen;
extern float delayLen;
extern char delayLenChar[8];
extern byte rgb[];
extern byte bright;


extern const int ledNumber;
extern int const dataPin;
extern int const ledStepSize[];
extern const int stepNumber; // 17 / 34
extern int ledStepStart[];
extern int ledStepBrightness[];
//int const ledStepSize[] = {12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12};

// 0 = always off, 2 = always on, 1 = turns on/off
extern byte goUp;
extern byte goDown;
extern bool OnOff;

// int RECV_PIN = D1;
// IRrecv myReceiver(RECV_PIN, 1024, 15, true);
//decode_results results;
//String previousCode;

extern bool bottomSensor;
extern bool topSensor;

extern byte ledOnUp;
extern byte ledOnDown;

// Timer bottomTimer;
// Timer topTimer;
extern Timer onTimer;
// Timer receiveTimer;
extern Timer showTimer;
extern Timer logTimer;
extern Timer resetTimer;
extern Timer storeTimer;
extern bool settingChanged;
extern int lastButton; // 0 for AUTO, 1 for Manual, 2 for OFF
extern Adafruit_NeoPixel pixels;

#endif