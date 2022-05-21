#include "main.h"

#include "functions/functions.h"
#include "wifi/wifi.h"

// #include <i18n.h>
// #include <IRac.h>
// #include <IRrecv.h>
// #include <IRremoteESP8266.h>
// #include <IRsend.h>
// #include <IRutils.h>
// #include <IRtext.h>
// #include <IRtimer.h>
// #include <ir_NEC.h>

#include <ESP8266WiFi.h>
#include <EEPROM.h>


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

bool autoButton = true;
bool manualButton = false;
bool offButton = false;
int timerLen = 30.0;
float delayLen = 0.3;
char delayLenChar[8];
byte rgb[] = {255, 17, 0};
byte bright = 255;


const int ledNumber = 34 * 4 + 30 * 14;
int const dataPin = D3;
int const ledStepSize[] = {34, 34, 34, 34, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30};
const int stepNumber = sizeof(ledStepSize) / sizeof(ledStepSize[0]); // 17 / 34
int ledStepStart[stepNumber];
int ledStepBrightness[stepNumber];
//int const ledStepSize[] = {12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12};

// 0 = always off, 2 = always on, 1 = turns on/off
byte goUp = 0;
byte goDown = 0;
bool OnOff = false;

// int RECV_PIN = D1;
// IRrecv myReceiver(RECV_PIN, 1024, 15, true);
//decode_results results;
//String previousCode;

bool bottomSensor = false;
bool topSensor = false;

byte ledOnUp = 0;
byte ledOnDown = 0;

// Timer bottomTimer;
// Timer topTimer;
Timer onTimer;
// Timer receiveTimer;
Timer showTimer;
Timer logTimer;
Timer resetTimer;
Timer storeTimer;
bool settingChanged = false;
int lastButton = 0; // 0 for AUTO, 1 for Manual, 2 for OFF
Adafruit_NeoPixel pixels(ledNumber, dataPin, NEO_GRB + NEO_KHZ800);


void setup() {
  EEPROM.begin(9);
  rgb[0] = (byte)EEPROM.read(0);
  rgb[1] = (byte)EEPROM.read(1);
  rgb[2] = (byte)EEPROM.read(2);
  bright = (byte)EEPROM.read(3);
  delayLen = (float)((EEPROM.read(4) << 8) + EEPROM.read(5)) /1000;
  timerLen = ((int) EEPROM.read(6) << 8) + EEPROM.read(7);
  lastButton = (int)EEPROM.read(8);
  if (lastButton == 0){
    resetTimer.start();
    resetTimer.reset();
    goUp = 0;
    goDown = 0;
    autoButton = true;
  }else if (lastButton == 1){
    goUp++;
    goDown++;
    resetTimer.stop();
    resetTimer.reset();
    manualButton = true;
  }else if (lastButton == 2){
    goUp = 0;
    goDown = 0;
    offButton = true;
  }

  Serial.begin(115200); // start console
  wifiSetup();
  // myReceiver.setUnknownThreshold(12);
  // myReceiver.enableIRIn(); //start IR reciever
  pixels.begin(); //start light strip
  // set pins
  pinMode(dataPin, OUTPUT);
  pinMode(fourthSensor, INPUT);
  pinMode(thirdSensor, INPUT);
  pinMode(firstSensor, INPUT);
  pinMode(secondSensor, INPUT);
  pixels.clear(); //reset light strip
  pixels.show(); //update light strip
  // initialize stair steps
  int ledPosition = 0;
  for (int i = 0; i < stepNumber; i++) {
    ledStepStart[i] = ledPosition;
    setStep(i, rgb, 0);
    ledPosition += ledStepSize[i];
  }
  pixels.show();
  Serial.println(ledNumber);
}

void loop() {
  // put your main code here, to run repeatedly
  wifiLoop();
  updateCount();
/*    if (logTimer.update() > 50) {
    Serial.print(readPin(firstSensor));
    Serial.print(" ");
    Serial.print(readPin(fourthSensor));
    Serial.print(" ");
    Serial.print(goDown);
    Serial.print(" ");
    Serial.print(goUp);
    Serial.print(" ");
    Serial.println(resetTimer.update());
    logTimer.reset();
  } */


  // while (true){
  //   yield();
  //   Serial.println(readPin(fourthSensor));
  // }
  if (showTimer.update() > 10) {

    if (goDown == 0 && goUp == 0) {
      for (int i = 0; i < stepNumber; i++) {
        int fade = getBrightness(i);
        if (fade <= 1) {
          fade = 0;
        } else {
          fade -= 1;
        }
        setStep(i, rgb, fade);
      }
      showTimer.reset();
    }
    if (onTimer.update() > delayLen * 1000) {
      if (goUp > 0) {
        setStep(ledOnUp, rgb, 255);
        if (ledOnUp < stepNumber - 1)
          ledOnUp++;
      }
      if (goDown > 0) {
        setStep(stepNumber - 1 - ledOnDown, rgb, 255);
        if (ledOnDown < stepNumber - 1 )
          ledOnDown++;
      }
      onTimer.reset();
    }
    pixels.show();
  }
  if (goUp == 0) {
    ledOnUp = 0;
  }
  if (goDown == 0) {
    ledOnDown = 0;
  }
  if (!manualButton && !offButton) {
    if (!resetTimer.running() && (goUp > 0 || goDown > 0)){
      resetTimer.start();
      resetTimer.reset();
    }
    if (resetTimer.running() && (goUp == 0 && goDown == 0)){
      resetTimer.stop();
      resetTimer.reset();
    }
    if ((goUp > 0 || goDown > 0) && resetTimer.update() > timerLen * 1000) {
      goDown = 0;
      goUp = 0;
      resetTimer.stop();
      resetTimer.reset();
    }
  }
  
if (storeTimer.update() > 1 * 30 * 1000){
  if (settingChanged){
    EEPROM.write(0, rgb[0]);
    EEPROM.write(1, rgb[1]);
    EEPROM.write(2, rgb[2]);
    EEPROM.write(3, bright);
    EEPROM.write(4, (int)(delayLen * 1000) >> 8);
    EEPROM.write(5, (int)(delayLen * 1000) % 256);
    EEPROM.write(6, timerLen >> 8);
    EEPROM.write(7, timerLen % 256);
    EEPROM.write(8, lastButton);
    EEPROM.commit();
    settingChanged = false;
    Serial.println("Saved Settings");
  }
  storeTimer.reset();
}
  //  for(int i=0; i<ledNumber; i++){
  //    pixels.setPixelColor(i,pixels.gamma32(pixels.ColorHSV(Hue, 255, 255)));
  //    pixels.show();
  //    yield();
  //  }
  //  showTimer.reset();
  //  while(showTimer.update() < 3000){yield();}
  //  Hue += 15000;



  //  for (int i = 0; i < stepNumber; i++) {
  //    setStep(i, Hue, 255);
  //    pixels.show();
  //    showTimer.reset();
  //    while(showTimer.update() < 1000){ yield();}
  //  }
  //  showTimer.reset();
  //  while (showTimer.update() < 10000) {
  //    yield();
  //  }
  //  Hue += 15000;
}