int m = 6;
void setup() {
  // put your setup code here, to run once:
  pinMode(m, OUTPUT);
  Serial.begin(115200);
}
bool r = false;
void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    // read the incoming byte:
    char incomingByte = Serial.read();
    if (incomingByte == 's') {
      Serial.println("Toggling!");
      r = !r;
    }
  }
  if(r) {
    analogWrite(m, 255);
  } else {
    analogWrite(m, 0);
  }
}
