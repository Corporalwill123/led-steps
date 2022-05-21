#include "functions.h"

void setStep(int step, byte color[], int Brightness) {
  pixels.fill(pixels.Color( (color[0] * bright *Brightness) / 255 / 255, (color[1] * bright * Brightness) / 255 / 255, (color[2] * bright * Brightness) / 255 / 255), ledStepStart[step], ledStepSize[step]);
  ledStepBrightness[step] = Brightness;
}

byte getBrightness(int step) {
  return ledStepBrightness[step];
}

bool readPin(int pin) {
  long unsigned timeOut = micros();
  while(digitalRead(pin) == HIGH){
    yield();
    if (micros() - timeOut > 255 * 2 * 150){
      return LOW;
    }
  }
  while(digitalRead(pin) == LOW){
    yield();
    if (micros() - timeOut > 255 * 2 * 150){
      return LOW;
    }
  }
  long unsigned startTime = micros();
  while(digitalRead(pin) == HIGH){
    yield();
    if (micros() - timeOut > 255 * 2 * 150){
      return LOW;
    }
  }
  int distance = (int)(micros() - startTime)/147;
  if(distance < 38)
  return HIGH;
  else
  return LOW;
}

void updateStep(){
  for (int i = 0; i < stepNumber; i++) {
    setStep(i, rgb, ledStepBrightness[i]);
  }
  pixels.show();
}

void updateCount() {
  //code for bottom sensors
  yield();
  if (!manualButton && !offButton){
    if (bottomSensor && readPin(firstSensor) == LOW){
      bottomSensor = false;
    }
    if (topSensor && readPin(fourthSensor) == LOW){
      topSensor = false;
    }
    if (!bottomSensor && readPin(firstSensor) == HIGH){
      bottomSensor = true;
      resetTimer.reset();
      goUp++;
    }
    if (!topSensor && readPin(fourthSensor) == HIGH){
      topSensor = true;
      resetTimer.reset();
      goDown++;
    }
  }
}

