// Syarif Hidayat_D400220086_Kelas A //
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
  // Syarif Hidayat_D400220086_Kelas A //
  delay(500);
}
