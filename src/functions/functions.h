#ifndef HEADER_J
#define HEADER_J

#include "main.h"

void setStep(int step, byte color[], int Brightness);

byte getBrightness(int step);

bool readPin(int pin);

void updateStep();

void updateCount();

#endif