/////////////////////////////////////////////////////////
//Created by Stephan K for the ChemE Car Team Fall 2016//
/////////////////////////////////////////////////////////

/*/////// \\\\\\\\\ 
|||||Variables|||||
\\\\\\\\\ ///////*/
/* Variables used in the program. */
#include "pins.h"
#include "settings.h"
#include "debug.h"

//Other Variables\\
/* These are variables which should not be changed. These are required for the program to opporated. */

int loops = 0;
int checked_loops = 0;
int state = 0;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
unsigned long flickering_button_previousMillis = 0;
unsigned long flickering_button_timeout_previousMillis = 0;
int flickering_button_state = 0;
int flickering_button_loops = 0;
bool smart_control = true;
bool allow_button = true;
unsigned long buttonMilli = 0;
bool dec_bBuffer = false;
long bBuffer = 0;

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

  //Lights led since the board should be ready and is now looping.
  if(debug_board_ready){
    digitalWrite(board_ready, HIGH);
  }

  if(smart_control) {
    for (int i = 0; i < 10; i++) {
      delay(100);
      digitalWrite(board_ready, LOW);
      delay(100);
      digitalWrite(board_ready, HIGH);
    }
  }
}

void loop() {
  //Gets the current milliseconds time.
  currentMillis = millis();
  
  //Gets the state of the sensor pin (HIGH(1)/LOW(0))
  state = !digitalRead(digitalSensor);

  //Gets the current state of the decrease buffer switch.
  /*
  if (digitalRead(decrease_buffer_switch) == HIGH) {
    bBuffer = decreasedButtonBuffer;
  } else {
    bBuffer = buttonBuffer;
  }
  */

  //DEBUG\\
  
  if(!debug_state){
    Serial.print("Sensor state: ");
    Serial.println(state);
  }
  if(!debug_on){
    Serial.print("Motor: ");
    Serial.println(on);
  }
  
  //END DEBUG\\
  
  if(smart_control){
    smartfn();
  }else{
    if(state == check){
      on = true;
    }else{
      on = false;
    }
    if(on){
      digitalWrite(motor, HIGH);
    }
  }
  //If the variable on is false, trun the motor off. (!false = true)
  if(!on){
    digitalWrite(motor, LOW);
  }
}
