#ifndef Logger_h
#define Logger_h
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <SD.h>
#include <SPI.h>
#include "pins.h"

class Logger {
    public:
        void tick(unsigned long t);
        void measure();
        bool checkTimer(unsigned long curT, bool isactiveState, bool resetState, bool onState);
        void newFile();
        void nextName();
        String fileName();
        Logger();
        unsigned long measureThreshold = 100; // In milliseconds
    private:
        Adafruit_INA219 ina219;
        File currentFile;
        bool prevResetState = false;
        bool measuring = false;
        unsigned long startingMeasurement = 0;
        unsigned int basenameInt = 0;
        unsigned int curnameInt = 0;
        unsigned long prevT = 0;
};
Logger::Logger() {
    ina219.begin();
    SD.begin(chipselect);
    while (SD.exists(fileName())) {
        if (basenameInt + 1 < basenameInt) {
            exit(1);
        }
        basenameInt++;
    }
    newFile();
}
void Logger::tick(unsigned long t) {
    
}
void Logger::measure(){
    float shuntvoltage = ina219.getShuntVoltage_mV();
    float busvoltage = ina219.getBusVoltage_V();
    float current_mA = ina219.getCurrent_mA();
    float loadvoltage = busvoltage + (shuntvoltage / 1000);
    currentFile.print(shuntvoltage);
    currentFile.print(F(","));
    currentFile.print(busvoltage);
    currentFile.print(F(","));
    currentFile.print(current_mA);
    currentFile.print(F(","));
    currentFile.println(loadvoltage);
}

bool Logger::checkTimer(unsigned long curT, bool isactiveState, bool resetState, bool onState) {
  if (isactiveState) {
    if (measuring && curT - prevT > measureThreshold) {
      measure();
      prevT = curT;
    }
    if (resetState && resetState != prevResetState) {
      measuring = !measuring;
      if (!measuring) {
        //save timer
        currentFile.print("Total Time (in milliseconds): ");
        currentFile.println(curT - startingMeasurement);
      } else {
        startingMeasurement = curT;
      }
    }
    return measuring;
  }
  prevResetState = resetState;
  return onState;
}

void Logger::newFile() {
    if (currentFile) {
        currentFile.close();
    }
    nextName();
    currentFile = SD.open(fileName(), FILE_WRITE);
}

void Logger::nextName() {
    while (SD.exists(fileName())) {
        if (curnameInt + 1 < curnameInt) {
            exit(1);
        }
        curnameInt++;
    }
}

String Logger::fileName() {
    String s = "ChemEdata-" + basenameInt;
    s += "-";
    s += curnameInt;
    s += ".svg";
    return s;
}
#endif
