// Syarif Hidayat_D400220086_Kelas A //
#include <SoftwareSerial.h>
SoftwareSerial Rxserial(10, 11);
char val;
const int led = 13;
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
  // Syarif Hidayat_D400220086_Kelas A //
  else if (val == '0') {
    Serial.println(val);
    digitalWrite(led, LOW);
  }
}
