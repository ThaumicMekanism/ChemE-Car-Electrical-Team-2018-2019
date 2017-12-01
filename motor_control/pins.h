/*These are the pins which the arduino uses. */

#define digitalSensor 5 //Sensor Digital Pin (INPUT)
#define analogSensor A0 //Sensor Analog Pin (INPUT)
#define motor 6 //Motor Digital Pin (OUTPUT)
//#define motor_speed_pin 3 //Pin to set the PWM signal to control the speed of the motor. (OUTPUT)
#define reset 2 //Reset Digital Pin (INPUT)
#define board_ready 7 //Activates when the board is ready. (OUTPUT) (Meant for a LED)
//int check_state_switch = 9; //Determins whether to check for high or low state On/Off. (INPUT) (ONLY CHECKED WHEN: board first starts up)
//#define decrease_buffer_switch 9 //Switch TBD (INPUT) (ONLY CHECKED WHEN: board first starts up)
#define adLightSwitch 3 //Changes which light sensor is read (aka. digital (on) or analog (off)) (INPUT)
#define smart_control_switch 4 //Gets switch input to use or don't use the smart control On/Off. (INPUT) (ONLY CHECKED WHEN: board first starts up)
//NOTE for smart_control_switch: This is only checked when the board is turned on!!!
//This allows the optimized checking if the motor should be on or off. 
//This makes the reset and other checking if false not work. 
//The motor will be ON or OFF based off of the state of the sensor which we are checking for.
#define chipselect 10
