bool lightSensor(bool analog) {
  if (analog) { //If we are reading the analog values do this.
    //Serial.println(analogRead(analogSensor));
    if (analogRead(analogSensor) > 0) {
      return true;
    }
    return false;
  } else { //Else it is digital.
    return !digitalRead(digitalSensor); // The negation is because the digital light sensor we have outputs the inverse.
  }
}

