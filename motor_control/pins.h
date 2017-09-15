/*These are the pins which the arduino uses. */

int sensor = 5; //Sensor Digital Pin (INPUT) 
int motor = 10; //Motor Digital Pin (OUTPUT)
int motor_speed_pin = 3; //Pin to set the PWM signal to control the speed of the motor. (OUTPUT)
int reset = 12; //Reset Digital Pin (INPUT)
int board_ready = 2; //Activates when the board is ready. (OUTPUT) (Meant for a LED)
//int check_state_switch = 9; //Determins whether to check for high or low state On/Off. (INPUT) (ONLY CHECKED WHEN: board first starts up)
int decrease_buffer_switch = 9; //Switch TBD (INPUT) (ONLY CHECKED WHEN: board first starts up)
int smart_control_switch = 7; //Gets switch input to use or don't use the smart control On/Off. (INPUT) (ONLY CHECKED WHEN: board first starts up)
//NOTE for smart_control_switch: This is only checked when the board is turned on!!!
//This allows the optimized checking if the motor should be on or off. 
//This makes the reset and other checking if false not work. 
//The motor will be ON or OFF based off of the state of the sensor which we are checking for.

// TEST! from jack