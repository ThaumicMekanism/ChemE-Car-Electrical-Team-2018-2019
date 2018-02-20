int motor = 6;
void setup() {
  // put your setup code here, to run once:
  
  pinMode(motor, OUTPUT);
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
    Serial.println("Ramping up motor..");
    for (int i = 0; i < 256; i++) {
      analogWrite(motor, i);
      delay(5);
    }
    Serial.println("Digital on");
    digitalWrite(motor, HIGH);
    delay(2000);
    Serial.println("Analog 255");
    analogWrite(motor, 255);
    delay(2000);
    Serial.println("Analog 128");
    analogWrite(motor, 128);
    delay(2000);
    Serial.println("Analog 0");
    analogWrite(motor, 0);
    delay(2000);
    Serial.println("Analog 50");
    analogWrite(motor, 50);
    delay(3000);
    Serial.println("Digital off");
    digitalWrite(motor, LOW);
    delay(2000);
  }
}
