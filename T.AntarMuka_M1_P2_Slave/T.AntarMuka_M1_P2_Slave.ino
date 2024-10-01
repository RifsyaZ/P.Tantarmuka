#include <SoftwareSerial.h>
#include "var.h"
void setup() {
  Rxserial.begin(9600);
  pinMode(13, OUTPUT);
}
void loop() {
  if (Rxserial.available() > 0) {
    val = Rxserial.read();
  }
  if (val == '1') {
    Serial.println(val);
    digitalWrite(led, HIGH);
  }
  else if (val == '0') {
    Serial.println(val);
    digitalWrite(led, LOW);
  }
}
