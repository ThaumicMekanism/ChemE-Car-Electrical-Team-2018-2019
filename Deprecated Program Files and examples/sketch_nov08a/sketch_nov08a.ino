#include <Adafruit_INA219.h>

// Modified Moving Average for PWM Curerent or PWM Voltage
// by James Lewis
// www.baldengineer.com/mma
//
// Connect a wire between pin 5 (pwmPin) and analog 0 (analogPin)
// Open the serial monitor. Send the + and - characters to change
// the speed. (you can type in multiples like '+++' to change quickly)
//
// The "average" voltage valued display is the PWM average
// uses 244 bytes of RAM versus 442 bytes of RAM for 100 averages
// calcultes in about 56us versus 1068us

// Pins
const byte pwmPin = 9;
const byte analogPin = A0;
 
// Let's compare an average of 100
const byte averageCount = 100;
 
// So we can change the PWM value
int PWMvalue = 128; //~50% Duty
 
// Variables for the Modified Moving Average
float movingAverage;
float movingAverageSum;
 
// Timer variables
unsigned long previousMillis = 0;
unsigned int printInterval = 500;
unsigned long startTime = 0;
unsigned long stopTime = 0;
Adafruit_INA219 ina219;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ina219.begin();
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  //ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  ina219.setCalibration_16V_400mA();
  pinMode(analogPin, INPUT); // not necessary, for FYI
  pinMode(pwmPin, OUTPUT); // not neceessary, for FYI
   
  // Start the PWM waveform
  analogWrite(pwmPin, PWMvalue); // ~50% Duty Cycle
 
  // Pre-load MMA
  for (int x=0; x < averageCount; x++){
      float shuntvoltage = ina219.getShuntVoltage_mV();
      float busvoltage = ina219.getBusVoltage_V();
      float current_mA = ina219.getCurrent_mA();
      float loadvoltage = busvoltage + (shuntvoltage / 1000);
      float currentValue = loadvoltage;
    
    movingAverageSum = movingAverageSum + current_mA;
  }
     
   // Calculate inital average
   movingAverage = movingAverageSum / averageCount;
}
 
void loop() {
  // check for serial control
  handleSerial();
 
   
  // each interation of loop, update moving average
  // Get a new sample
  //unsigned int currentValue = analogRead(analogPin);
  float shuntvoltage = ina219.getShuntVoltage_mV();
  float busvoltage = ina219.getBusVoltage_V();
  float current_mA = ina219.getCurrent_mA();
  float loadvoltage = busvoltage + (shuntvoltage / 1000);
  float currentValue = loadvoltage;
 
  startTime = micros();
  // Remove previous movingAverage from the sum
  movingAverageSum = movingAverageSum - movingAverage;
  // Replace it with the current sample
  movingAverageSum = movingAverageSum + current_mA;
  // Recalculate movingAverage
  movingAverage = movingAverageSum / averageCount;
  stopTime = micros();
 
  if (millis() - previousMillis >= printInterval) {
    Serial.print(F("currentValue: "));
    Serial.println(currentValue);
    Serial.print(F("iValue: "));
    Serial.println(current_mA);
    Serial.print(F("PWM Value: "));
    Serial.println(PWMvalue);
    Serial.print(F("Moving Average: "));
    Serial.println(movingAverage);
    Serial.print("Calculation time: ");
    Serial.print(stopTime - startTime);
    Serial.println(" us");
    Serial.println();
    Serial.flush();
 
    // reset the millis clock
    previousMillis = millis();
     
  }
 
}
 
void handleSerial() {
  // we only care about two characters to change the pwm
  if (Serial.available() > 0) {
    switch (Serial.read()) {
      case '+':
        PWMvalue = PWMvalue + 32;
        if (PWMvalue >= 255)
          PWMvalue = 255;
      break;
      case '-':
        PWMvalue = PWMvalue - 32;
        if (PWMvalue <= 0)
          PWMvalue = 0;
      break;
    }
    analogWrite(pwmPin, PWMvalue);
  }
}
