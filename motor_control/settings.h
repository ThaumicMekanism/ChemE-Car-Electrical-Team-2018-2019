#ifndef settings_h
#define settings_h
/* These variables are dependent on your board layout and preference. */

#define allow_switches true //Allows for the switches below to actually be registered
#define interval 1000 //Number of milliseconds for confirm shutoff (1000 milliseconds = 1 second).
bool on = false; //Default state of the motors. (true = on, false = off)
#define check HIGH //The value of which we compare to the output of the sensor. Put HIGH if you want to have the motor on when there is light, put LOW if you want to have the motor on when it is dark.
#define whichSensor true //This change which sensor input is being used. True = analogue; False = Digital.
#define logVoltage true //This will log the voltage and current to the file if true.
#define logSensor true //This will log the Sensors value if true.
#define useVoltageControl true //This will limit the battery output voltage to an average of the set voltage 'VCMax'. If the average battery voltage is less than that it will output max else it will PWM to set the average around this.
#define VCMax 7.0 //Set this to the max voltage you want. This should be a float!
#define VCTolerance 0.2 //This sets the plus/minus value of the voltage so that it is within this range.


#endif
