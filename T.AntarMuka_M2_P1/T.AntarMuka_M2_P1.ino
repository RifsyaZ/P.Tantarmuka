#include <Wire.h>
void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  Serial.println();
  Serial.println("Mendeteksi I2C");
  Serial.println("Memulai proses scan...");
  Serial.println();
  byte count = 0;
  Wire.begin();
  //Syarif Hidayat _ D400220086
  for (byte i = 8; i < 120; i++) {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0) {
      Serial.print("Alamat interface I2C = ");
      Serial.print(i, DEC);
      Serial.print(" (0x");
      Serial.print(i, HEX);
      Serial.println(")");
      count++;
      delay(1);
    }
  }
  Serial.println();
  Serial.print("Ditemukan ");
  Serial.print(count, DEC);
  Serial.println("Perangkat ");
}
void loop() {
  //Syarif Hidayat _ D400220086
}
