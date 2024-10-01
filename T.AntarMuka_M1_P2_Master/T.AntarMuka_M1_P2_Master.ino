//PRAKTIKUM ANTARMUKA 2023/2024
//MODUL 1
//PERCOBAAN 2
//SERIAL KOMUNIKASI SATU ARAH ARDUINO DENGAN ARDUINO
(Tx / MASTER)
#include <SoftwareSerial.h>
const int button = 7;
int code;
SoftwareSerial Txserial(11, 10);
void setup() {
  pinMode(7, INPUT_PULLUP);
  Txserial.begin(9600);
  Serial.begin(9600);
}
void loop() {
  code = digitalRead(button);
  if (code == LOW) {
    Txserial.write("1");
    Serial.println("LED HIDUP");
  } else if (code == HIGH) {
    Txserial.write("0");
    Serial.println("LED MATI");
  }
  delay(500);
}
