/*
 * This file will help store timing data to the EEPROM on the arduino.
 * 
 * This file uses EEPROM ADDRESSES: 0-5
 * 0 -> Reserved for number of EEPROM Long Values.
 * 1 -> Reserved for current EEPROM Start address. 
 * 2- -> Reserved for the first EEPROM Long Value.
 * 
 * IMPORTANT: We don't need to reinclude EEPROM since the main file already has that included.
 */
bool measuring = false;
unsigned long startingMeasurement = 0;

bool timerInit() {

  return true; 
}

bool writeTimer() {
  Serial.println("***Timing results from last time***");
  Serial.print("Number of entries: ");
  int eep0 = EEPROM.read(0);
  Serial.println(eep0);
  //Will make it so it outputs multiple eeprom results (as many as addr 0 says).
  for (int i = 0; i < eep0; i++) {
    Serial.print(i + 1);
    Serial.print(". ");
    Serial.print(EEPROMReadlong(2 + i * 4));
    Serial.println("ms");
  }
  Serial.println("***End of timing results***\n");
  return true;
}

bool clearTimer() {
  Serial.println("Clearing timer...");
  EEPROM.write(0, 0);
  EEPROM.write(1, 2);
  Serial.println("Cleared!\n");
}
bool resetState = false;
bool checkTimer() {
  resetState = readBtn(reset, resetState);
  bool returnval = false;
  if (digitalRead(smart_control_switch)) {
    if (resetState && resetState != prevResetState) {
      measuring = !measuring;
      if (!measuring) {
        returnval = saveTimer();
      } else {
        startingMeasurement = currentTime;
        returnval = true;
      }
    }
    on = measuring;
  }
  prevResetState = resetState;
  return returnval;
}

bool saveTimer() {
  //FUTURE IDEA: Make it so it can remember multiple values! Will be using address 0,1 to 
  int eep1 = EEPROM.read(1);
  EEPROMWritelong(eep1, currentTime - startingMeasurement);
  EEPROM.write(0, EEPROM.read(0) + 1);
  if (eep1 + 4 <= 1023) {
    EEPROM.write(1, eep1 + 4);
  }
}


