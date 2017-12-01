#ifndef settings_h
#define settings_h
/* These variables are dependent on your board layout and preference. */

#define allow_switches true //Allows for the switches below to actually be registered
float motor_speed = 100; //Percent as int which should be from 0 to 100, 100 being max speed.
#define interval 1000 //Number of milliseconds for confirm shutoff (1000 milliseconds = 1 second).
bool on = false; //Default state of the motors. (true = on, false = off)
#define check HIGH //The value of which we compare to the output of the sensor. Put HIGH if you want to have the motor on when there is light, put LOW if you want to have the motor on when it is dark.
#define whichSensor true //This change which sensor input is being used. True = analogue; False = Digital.
#define logVoltage true //This will log the voltage and current to the file if true.
#define logSensor true //This will log the Sensors value if true.




#endif
