/////////////////////////////////////////////////////////
//Created by Stephan K for the ChemE Car Team 2017-2018//
/////////////////////////////////////////////////////////
/*/////// \\\\\\\\\ 
|||||Includes||||||
\\\\\\\\\ ///////*/
#include <EEPROM.h> //This includes the functions which eeprom uses so that we can store data even when the board looses power.
#include "BlinkLed.h"
#include "Logger.h"

/*/////// \\\\\\\\\ 
|||||Variables|||||
\\\\\\\\\ ///////*/
/* Variables used in the program. */
#include "pins.h"
#include "settings.h"
#include "debug.h"

//Other Variables\\
/* These are variables which should not be changed. These are required for the program to run. */

int loops = 0;
int checked_loops = 0;
int state = 0;
unsigned long previousMillis = 0;
unsigned long currentTime = 0;
bool smart_control = true;
bool allow_button = true;
bool prevResetState = false;
bool smart_switch = false;
bool smart_switch_prev = false;
unsigned long button_timeout = 0;
BlinkLed* blinkled;
Logger* logger;

//END Other Variables

/*///////// \\\\\\\\\\\
|||||END Variables|||||
\\\\\\\\\\\ /////////*/

void setup() {
  //PinMode Setup\\

  //pinMode(motor_speed_pin, OUTPUT);
  pinMode(digitalSensor, INPUT);
  pinMode(analogSensor, INPUT);
  pinMode(motor, OUTPUT);
  pinMode(reset, INPUT);
  pinMode(board_ready, OUTPUT);
  pinMode(smart_control_switch, INPUT);
  //pinMode(decrease_buffer_switch, INPUT);
  pinMode(adLightSwitch, INPUT);


  //END PinMode Setup\\

  //Turns the motor on if the variable on is true.
  if(on == true){
    digitalWrite(motor, HIGH);
  }

  

  //Switches to change settings
  if(allow_switches == true){
    smart_control = digitalRead(smart_control_switch);
  }

  //Controls the motors speed.
  motor_speed = (abs(motor_speed) / 100) * 255;
  if(motor_speed > 255){
    motor_speed = 255;
  }
  //analogWrite(motor_speed_pin, motor_speed);
  
  //Debug Channel Init (Initiates regardless of if it is called or not later.)
  Serial.begin(9600);

  blinkled = new BlinkLed();
  logger = new Logger();

  //Lights led since the board should be ready and is now looping.
  if(debug_board_ready){
    digitalWrite(board_ready, HIGH);
  }

  //Writes to the console the results of the previous time it was measuring.
  //writeTimer();
  parserinit();
  
  //Causes the ready light to flicker if smart control is on.
  if(smart_control) {
    blinkled->add(board_ready, 100, 10, 0);
  } else {
    timerInit();
  }
  
}

void loop() {
  parser();
  
  //Gets the current milliseconds time.
  currentTime = millis();

  blinkled->tick(currentTime);
  
  //Gets the state of the sensor pin (HIGH(1)/LOW(0))
  state = lightSensor(true);
  
  smart_switch_prev = smart_switch;
  smart_switch = digitalRead(smart_control_switch);

  //DEBUG\\
  
  if(debug_state){
    Serial.print("Sensor state: ");
    Serial.println(state);
  }
  if(debug_on){
    Serial.print("Motor: ");
    Serial.println(on);
  }
  
  //END DEBUG\\
  
  if(smart_control){
    smartfn();
  }else{
    if (smart_switch_prev != smart_switch) {
      if (smart_switch) {
        blinkled->add(board_ready, 250, -1, 0);
      } else {
        blinkled->rem(board_ready, HIGH);
      }
    }
    if(state == check){
      on = true;
    }else{
      on = false;
    }
    checkTimer();
    if(on){
      digitalWrite(motor, HIGH);
    }
  }
  //If the variable on is false, trun the motor off. (!false = true)
  if(!on){
    digitalWrite(motor, LOW);
  }
}

bool readBtn(int pin, bool prev) {
  if (currentTime - button_timeout > 100) {
    button_timeout = currentTime;
    return digitalRead(reset);
  } else {
    return prev;
  }
}

