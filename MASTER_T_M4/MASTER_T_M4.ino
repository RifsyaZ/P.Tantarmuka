#include <SoftwareSerial.h>
SoftwareSerial blueMaster(8, 9);
const int button = 7;
int value;
void setup() {
  blueMaster.begin(9600);
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
}
void loop() {
  value = digitalRead(button);
  if (value == 0) {
    blueMaster.write('1');
    Serial.println("1");
  } else {
    blueMaster.write('0');
    Serial.println("0");
  }
  //delay(100);
}
