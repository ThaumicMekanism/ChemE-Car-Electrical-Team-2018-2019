#include <SD.h>
#include <SPI.h>

void setup() {
  // put your setup code here, to run once:
  SD.begin(10);
  Serial.begin(115200);
  String fn = "tesasdff.txt";
  File f = SD.open(fn, FILE_WRITE);
  Serial.println(f);
  f.close();
  Serial.println(SD.exists(fn));
}

void loop() {
  // put your main code here, to run repeatedly:

}
