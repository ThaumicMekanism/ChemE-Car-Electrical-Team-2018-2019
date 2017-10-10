/*
 * This class uses a voltage divider to measure the voltage of a circut.
 * BE CAREFUL! Make sure you use the correct resistors to divide voltage or you will burn out your arduino!!!
 *      -----------
 *      |         |
 * Ex.  |         R1   Analog in
 *      Vs        | ---- +  |=======|
 *      |         R2        |Arduino|
 *      |         | ---- -  |=======|
 *      -----------   Shared Ground
 * 
 */

#ifndef Voltmeter_h
#define Voltmeter_h
#include <Arduino.h>

class Voltmeter {
  public:
    Voltmeter(int _pin, float _R1, float _R2, float _fixedDefVolt);
    int readPin(int p) {
      return digitalRead(p);
    }
    float getVoltage(void) { //Return vin!
       // read the value at analog input
       int value = readPin(pin);
       vout = (value * fixedDefVolt) / 1024.0;
       vin = vout / (R2/(R1+R2)); 
       if (vin<0.09) {
         vin=0.0; //statement to quash undesired reading!
       }
       return vin;     
    }
    float getAmp(void) { //Theoretical working of this though unsure if it will work in practice.
      return getVoltage() / (R1 + R2);
    }
    int pin;
    float R1;
    float R2;
    float fixedDefVolt;
    float vin = 0.0;
    float vout = 0.0;
};

Voltmeter::Voltmeter(int _pin, float _R1, float _R2, float _fixedDefVolt) {
    pin = _pin;
    R1 = _R1;
    R2 = _R2;
    fixedDefVolt = _fixedDefVolt;
}

#endif
