
/*
  BlinkLed.h - Library for blinking one or more led's.
  Created by Stephan Kaminsky, October 5, 2017.
  Released into the public domain.
*/
#ifndef BlinkLed_h
#define BlinkLed_h
#include "Led.h"

#include <Arduino.h>
int numLedsTot = 14;
class BlinkLed
{
  public:
    BlinkLed();
    void add(int _pin, unsigned long _duration, int _numBlinks, long _offset) {
      if (_pin < numLedsTot) {
        if (leds[_pin] == NULL) {
          numLeds++;
        }
        leds[_pin] = new Led(_pin, _duration, _numBlinks * 2, _offset);
      //Serial.print("Added led on pin: ");
      //Serial.println(_pin);
      }
      
    }
    void tick(unsigned long t) {
      for (int i = 0; i < numLedsTot && numLeds > 0; i++) {
        Led* l = leds[i];
        if (l != NULL) {
          if (l->numBlinks == -2 || l->numBlinks > 0) {
            if (t - l->prevTime > l->duration) {
              digitalWrite(l->pin, !digitalRead(l->pin));
              l->prevTime = t;
              if (l->numBlinks > 0) {
                l->numBlinks--;
              }
            }
          } else {
            numLeds--;
            leds[l->pin] = NULL;
          }
        }
      }
    }
    void rem(int pin, bool state) {
      if (pin < numLedsTot) {
        //Serial.print("Removed led on pin: ");
        //Serial.println(pin);
        if (leds[pin] != NULL) {
          numLeds--;
          leds[pin] = NULL;
          digitalWrite(pin, state);
          
        }
      }
    }
  private:
    Led* leds[14];
    int numLeds;
};
BlinkLed::BlinkLed() {
  for (int i = 0; i < numLedsTot; i++) {
    leds[i] = NULL;
  }
}




#endif
