#ifndef LED_STEP
#define LED_STEP

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"

class ledStep{
    private:
        static int nextLED;
        static byte maxBrightness;
        

        int firstLED, count;
        unsigned int curColor;
        byte curBrightness;
    public:
        ledStep();
        ledStep(int position, int ledNumber);
        void setStep(byte brightness, unsigned int Color);
        byte currentBrightness();
        unsigned int currentColor();

        static void setMaxBrightness( byte setbright);
        static void show();
        static void clear();
        static void begin();
};

#endif