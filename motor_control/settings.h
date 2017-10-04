/* These variables are dependent on your board layout and preference. */

bool allow_switches = true; //Allows for the switches below to actually be registered
float motor_speed = 100; //Percent as int which should be from 0 to 100, 100 being max speed.
long interval = 750; //Number of milliseconds for confirm shutoff (1000 milliseconds = 1 second)
long buttonBuffer = 25000; //Number of milliseconds to not check the state (1000 milliseconds = 1 second).
long decreasedButtonBuffer = 5000; //If the decreased_buffer_switch is on, the buffer value will be set to this value.
bool on = false; //Default state of the motors. (true = on, false = off)
int check = HIGH; //The value of which we compare to the output of the sensor. Put HIGH if you want to have the motor on when there is light, put LOW if you want to have the motor on when it is dark.
//bool flickering_button_fix = true; //This variable (hopefully) fixes the button from continuously reactivating the motor. It will stop the button from reseting for flickering_button_fix_time if it detects constant on. (true = on, false = off)
//int flickering_button_fix_timeout_time = 5000; //This will prevent the button from doing anything for this alloted time in milliseconds.
//int flickering_button_fix_check_interval = 1000; //This is the check to see if should do flickering stuff.
