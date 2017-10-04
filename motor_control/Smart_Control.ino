void smartfn() {
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
    //Serial.println(allow_button);
    //Checks to see if the button is spamming.
    /*
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
    */
  
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
    if(debug_check) {
      Serial.println("Loops: ");
      Serial.println(loops);
      Serial.println("Checked Loops: ");
      Serial.println(checked_loops);
    }
}

