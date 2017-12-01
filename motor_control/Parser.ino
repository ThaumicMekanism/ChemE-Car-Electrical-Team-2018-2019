void parserinit() {
  Serial.println("Here are a list of commands you can use:\n");
  Serial.println("T - Will print out all the timing data.");
  Serial.println("C - Will clear the Timing data.");
}
void parser() {
  if (Serial.available() > 0 && false) {
    char c = toupper(Serial.read());
    if (c == 'T') {
      //writeTimer();
    } else if(c == 'C') {
      //clearTimer();
    }
  }
}

