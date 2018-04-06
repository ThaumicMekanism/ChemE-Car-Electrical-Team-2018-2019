#ifndef Logger_h
#define Logger_h
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <SD.h>
#include <SPI.h>
#include "pins.h"
#include "settings.h"

class Logger {
    public:
        void tick(unsigned long t);
        void measure();
        void checkTimer(unsigned long curT);
        void newFile();
        void nextName();
        String fileName();
        Logger(bool *_onState, bool *_isActiveState, bool *_resetState, int *_sensorState);
        unsigned long measureThreshold = 100; // In milliseconds
    private:
        bool *onState;
        bool *isActiveState;
        bool *resetState;
        int *sensorState;
        Adafruit_INA219 ina219;
        File currentFile;
        bool prevResetState = false;
        bool measuring = false;
        unsigned long startingMeasurement = 0;
        unsigned int basenameInt = 0;
        unsigned int curnameInt = 0;
        unsigned long prevT = 0;
};
Logger::Logger(bool *_onState, bool *_isActiveState, bool *_resetState, int *_sensorState) {
    onState = _onState;
    isActiveState = _isActiveState;
    resetState = _resetState;
    sensorState = _sensorState;
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
    checkTimer(t);
}

void Logger::measure(){
  if (logSensor) {
    currentFile.print(*sensorState);
    if (logVoltage) {
      currentFile.print(F(","));
    }
  }
  if (logVoltage) {
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
    currentFile.print(loadvoltage);
  }
  if (logVoltage || logSensor) {
    currentFile.println("");
  }
}

void Logger::checkTimer(unsigned long curT) {
  if (!*isActiveState) {
    if (measuring && curT - prevT > measureThreshold) {
      measure();
      prevT = curT;
    }
    if (*resetState && *resetState != prevResetState) {
      measuring = !measuring;
      if (!measuring) {
        //save timer
        currentFile.print("Total Time (in milliseconds): ");
        currentFile.println(curT - startingMeasurement);
      } else {
        startingMeasurement = curT;
      }
    }
    *onState = measuring;
  }
  prevResetState = resetState;
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
    s += ".csv";
    return s;
}
#endif
