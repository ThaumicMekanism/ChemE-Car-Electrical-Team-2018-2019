/**
 * This file will be in control of detecting current voltage and altering motor speed based off of this.
 * 
 * NOTE: Set controlledVoltage to true if setting motors PWM from here so that it does not get reset during the motor state part of the function.
 */


unsigned int VCpwmVal = 255;
Adafruit_INA219 VCina219;


// Let's compare an average of 100
const byte averageCount = 100;
// Variables for the Modified Moving Average
float movingAverage;
float movingAverageSum;

void VCinit() {
  VCina219.begin();
  // Pre-load MMA
  for (int x=0; x < averageCount; x++)
    movingAverageSum = movingAverageSum + analogRead(analogPin);
     
   // Calculate inital average
   movingAverage = movingAverageSum / averageCount;
}

void VCsetMotorPWM() {
  if (useVoltageControl) {
    analogWrite(motor, VCpwmVal);
  }
}

void VCCheckVoltage() {
  unsigned int currentValue = ina219.getBusVoltage_V();
  // Remove previous movingAverage from the sum
  movingAverageSum = movingAverageSum - movingAverage;
  // Replace it with the current sample
  movingAverageSum = movingAverageSum + currentValue;
  // Recalculate movingAverage
  movingAverage = movingAverageSum / averageCount;

  if (movingAverage < volatgeminustolerance) {
    
  } else if (movingAverage > voltageplustolerance) {
    
  }
}


