/////////////////////////////////////////////////////////
//Created by Stephan K for the ChemE Car Team Fall 2016//
/////////////////////////////////////////////////////////

/*/////// \\\\\\\\\ 
|||||Variables|||||
\\\\\\\\\ ///////*/
/* Variables used in the program. */

//Custom Variables\\
/* These variables are dependent on your board layout and preference. */
int sensor = 5; //Sensor Digital Pin (INPUT) 
int motor = 10; //Motor Digital Pin (OUTPUT)
int motor_speed_pin = 3; //Pin to set the PWM signal to control the speed of the motor. (OUTPUT)
int reset = 12; //Reset Digital Pin (INPUT)
int board_ready = 2; //Activates when the board is ready. (OUTPUT) (Meant for a LED)
bool allow_switches = true; //Allows for the switches below to actually be registered
//int check_state_switch = 9; //Determins whether to check for high or low state On/Off. (INPUT) (ONLY CHECKED WHEN: board first starts up)
int decrease_buffer_switch = 9; //Switch TBD (INPUT) (ONLY CHECKED WHEN: board first starts up)
int smart_control_switch = 7; //Gets switch input to use or don't use the smart control On/Off. (INPUT) (ONLY CHECKED WHEN: board first starts up)
//NOTE: This is only checked when the board is turned on!!!
//This allows the optimized checking if the motor should be on or off. 
//This makes the reset and other checking if false not work. 
//The motor will be ON or OFF based off of the state of the sensor which we are checking for.
float motor_speed = 100; //Percent as int which should be from 0 to 100, 100 being max speed.
long interval = 750; //Number of milliseconds for confirm shutoff (1000 milliseconds = 1 second)
long buttonBuffer = 25000; //Number of milliseconds to not check the state (1000 milliseconds = 1 second).
long decreasedButtonBuffer = 5000; //If the decreased_buffer_switch is on, the buffer value will be set to this value.
bool on = false; //Default state of the motors. (true = on, false = off)
int check = HIGH; //The value of which we compare to the output of the sensor. Put HIGH if you want to have the motor on when there is light, put LOW if you want to have the motor on when it is dark.
bool flickering_button_fix = true; //This variable (hopefully) fixes the button from continuously reactivating the motor. It will stop the button from reseting for flickering_button_fix_time if it detects constant on. (true = on, false = off)
int flickering_button_fix_timeout_time = 5000; //This will prevent the button from doing anything for this alloted time in milliseconds.
int flickering_button_fix_check_interval = 1000; //This is the check to see if should do flickering stuff.


//END Custom Variables\\

//Debug Variables\\
/* These variables are for debug purposes, for the command line outputs. */

//Prints the value of the 'state' variable.
bool debug_state = true;
//Prints the value of the 'on' variable
bool debug_on = true;
//Prints every time the board does a check;
bool debug_check = false;
//Allows the board_ready pin to activate (turn on the led)
bool debug_board_ready = true;
//Allows the board_error pin to activate (turn on the led)
bool debug_board_error = false;


//END Debug Variables\\

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

  pinMode(motor_speed_pin, OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(motor, OUTPUT);
  pinMode(reset, INPUT);
  pinMode(board_ready, OUTPUT);
  pinMode(smart_control_switch, INPUT);
  pinMode(decrease_buffer_switch, INPUT);

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
  analogWrite(motor_speed_pin, motor_speed);
  
  //Debug Channel Init (Initiates regardless of if it is called or not later.)
  Serial.begin(9600);

  //Lights led since the board should be ready and is now looping.
  if(debug_board_ready){
    digitalWrite(board_ready, HIGH);
  }
} 

void loop() {
  //Gets the current milliseconds time.
  currentMillis = millis();
  
  //Gets the state of the sensor pin (HIGH(1)/LOW(0))
  state = !digitalRead(sensor);

  //Gets the current state of the decrease buffer switch.
  if (digitalRead(decrease_buffer_switch) == HIGH) {
    bBuffer = decreasedButtonBuffer;
  } else {
    bBuffer = buttonBuffer;
  }

  //DEBUG\\
  
  if(!debug_state){
    Serial.print("Sensor state: ");
    Serial.println(state);
    //Serial.println(state);
  }
  if(!debug_on){
    Serial.print("Motor: ");
    Serial.println(on);
    //Serial.println(on);
  }
  
  //END DEBUG\\
  
  if(smart_control){
    //Resets light
    if(digitalRead(reset) == HIGH and allow_button == true){
      //Turns motor back on and resets 'on' back to true (running)
      digitalWrite(motor, HIGH);
      on = true;
      buttonMilli = currentMillis;
    }
  
    //Counts the number of loops
    loops++;
    //Counts the number of loops where the state is equal to the check.
    if(state != check){
      checked_loops++;
    }

    //Count if button is on or off.
    flickering_button_loops++;
    if (digitalRead(reset) == HIGH) {
      flickering_button_state++;
    }
    Serial.println(allow_button);
    //Checks to see if the button is spamming.
    if (abs(currentMillis - flickering_button_previousMillis) >= flickering_button_fix_check_interval) {
       if (flickering_button_fix == true and allow_button == true and flickering_button_state*2 > flickering_button_loops) {
          flickering_button_timeout_previousMillis = currentMillis;
          allow_button = false;
       }
       flickering_button_previousMillis = currentMillis;
       flickering_button_loops = 0;
       flickering_button_state = 0;
    }
    if (abs(currentMillis - flickering_button_timeout_previousMillis) >= flickering_button_fix_timeout_time and allow_button == false) {
      allow_button = true;
    }
  
    //Checks to see if the the loop has looped for number of loops specified.
    if(abs(currentMillis - previousMillis) >= interval){
      //Debug that prints everytime this loop is entered (whenever it compares the loops vs checked_loops values.
      if(debug_check){
        Serial.write("Checked!");
        Serial.println();
      }
      //If the number of times state is equal to check is greater than the number of loops, turn the motor off.
      if(checked_loops > loops/2 && abs(currentMillis - buttonMilli) >= bBuffer){
        on = false;
      }
      //Reset the loops checks plus updating the timing variables.
      previousMillis = currentMillis;
      loops = 0;
      checked_loops = 0;
    }
    Serial.println("Loops: ");
    Serial.println(loops);
    Serial.println("Checked Loops: ");
    Serial.println(checked_loops);
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
