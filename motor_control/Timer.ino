/*
 * This file will help store timing data to the EEPROM on the arduino.
 * 
 * This file uses EEPROM ADDRESSES: 0-5
 * 0 -> Reserved for current EEPROM Start address.
 * 1 -> Reserved for number of EEPROM Long Values.
 * 2-5 -> Reserved for the first EEPROM Long Value.
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
  Serial.print("There are ");
  Serial.print(EEPROM.read(0));
  Serial.println(" entries.");
  //Will make it so it outputs multiple eeprom results (as many as addr 0 says).
  Serial.println(EEPROMReadlong(2));
  Serial.println("***End of timing results***");
  return true;
}

bool checkTimer() {
  bool resetState = digitalRead(reset);
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
  EEPROMWritelong(2, currentTime - startingMeasurement);
}


