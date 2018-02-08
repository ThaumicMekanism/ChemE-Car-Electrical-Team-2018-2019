#include <Wire.h>
#include <Adafruit_INA219.h>

Adafruit_INA219 ina219;

int m = 6;
// Pins
const byte pwmPin = 6;
 
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
void setup() {
  // put your setup code here, to run once:
  pinMode(m, OUTPUT);
  Serial.begin(115200);

  uint32_t currentFrequency;
    
  Serial.println("Hello!");
  
  // Initialize the INA219.
  // By default the initialization will use the largest range (32V, 2A).  However
  // you can call a setCalibration function to change this range (see comments).
  ina219.begin();
  // To use a slightly lower 32V, 1A range (higher precision on amps):
  //ina219.setCalibration_32V_1A();
  // Or to use a lower 16V, 400mA range (higher precision on volts and amps):
  //ina219.setCalibration_16V_400mA();

  // Start the PWM waveform
  analogWrite(pwmPin, PWMvalue); // ~50% Duty Cycle
 
  // Pre-load MMA
  for (int x=0; x < averageCount; x++)
    movingAverageSum = movingAverageSum + voltage();
     
   // Calculate inital average
   movingAverage = movingAverageSum / averageCount;
}
bool r = false;
void loop() {

 
  // check for serial control
  handleSerial();
 
   
  // each interation of loop, update moving average
  // Get a new sample
  unsigned int currentValue = voltage();
 
  startTime = micros();
  // Remove previous movingAverage from the sum
  movingAverageSum = movingAverageSum - movingAverage;
  // Replace it with the current sample
  movingAverageSum = movingAverageSum + currentValue;
  // Recalculate movingAverage
  movingAverage = movingAverageSum / averageCount;
  stopTime = micros();
 
  if (millis() - previousMillis >= printInterval) {
    Serial.print(F("currentValue: "));
    Serial.println(currentValue);
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
      case 's':
          Serial.println("Toggling!");
          r = !r;
        break;
    }
    if(r) {
      analogWrite(pwmPin, PWMvalue);
    } else {
      analogWrite(pwmPin, 0);
    }
  }
}
float voltage() {
  float shuntvoltage = 0;
  float busvoltage = 0;
  float loadvoltage = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  return busvoltage + (shuntvoltage / 1000);
}

