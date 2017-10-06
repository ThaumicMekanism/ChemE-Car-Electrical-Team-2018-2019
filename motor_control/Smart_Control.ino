void smartfn() {
  //Resets light
    if(readBtn(reset, LOW) == HIGH and allow_button == true){
      //Turns motor back on and resets 'on' back to true (running)
      digitalWrite(motor, HIGH);
      on = true;
    }
  
    //Counts the number of loops
    loops++;
    //Counts the number of loops where the state is equal to the check.
    if(state != check){
      checked_loops++;
    }

    //Checks to see if the the loop has looped for number of loops specified.
    if(abs(currentTime - previousMillis) >= interval){
      //Debug that prints everytime this loop is entered (whenever it compares the loops vs checked_loops values.
      if(debug_check){
        Serial.write("Checked!");
        Serial.println();
      }
      //If the number of times state is equal to check is greater than the number of loops, turn the motor off.
      if(checked_loops > loops/2){
        on = false;
      }
      //Reset the loops checks plus updating the timing variables.
      previousMillis = currentTime;
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

