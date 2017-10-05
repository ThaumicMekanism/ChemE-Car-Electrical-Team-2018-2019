/* These variables are dependent on your board layout and preference. */

bool allow_switches = true; //Allows for the switches below to actually be registered
float motor_speed = 100; //Percent as int which should be from 0 to 100, 100 being max speed.
long interval = 1000; //Number of milliseconds for confirm shutoff (1000 milliseconds = 1 second).
bool on = false; //Default state of the motors. (true = on, false = off)
int check = HIGH; //The value of which we compare to the output of the sensor. Put HIGH if you want to have the motor on when there is light, put LOW if you want to have the motor on when it is dark.
