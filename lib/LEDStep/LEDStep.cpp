#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "LEDStep.h"
byte ledStep::maxBrightness;
int ledStep::nextLED;
ledStep::ledStep(uint16_t n, uint16_t pin, neoPixelType type){
    //Adafruit_NeoPixel pixel(n, pin, type);
    pixels = new Adafruit_NeoPixel(n, pin, type);
}
ledStep::ledStep(){};
ledStep::ledStep(int position, int ledNumber){
    firstLED = position;
    count = ledNumber;

}
void ledStep::setMaxBrightness(byte setbright){
     maxBrightness = setbright;
}
void ledStep::setStep(byte brightness, unsigned int Color){

    uint32_t color = pixels.ColorHSV(Color , 255, brightness * float(maxBrightness / 255));
    pixels.fill(pixels.gamma32(color), firstLED, count);
    
    curBrightness = brightness;
    curColor = Color;
}
byte ledStep::currentBrightness(){
    return curBrightness;
}
unsigned int ledStep::currentColor(){
    return curColor;
}
void ledStep::show(){
    pixels.show();
}
void ledStep::clear(){
    pixels.clear();
}
void ledStep::begin(){
    pixels.begin();
}