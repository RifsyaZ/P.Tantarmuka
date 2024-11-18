#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
LiquidCrystal_I2C MEMED(0x27, 16, 2);
SoftwareSerial blueSlave(8, 9);
int Hasil_Tombol = 0;
int Hasil_Terakhir_Tombol = 0;
int Jumlah_Ditekan = 0;
void setup() {
  blueSlave.begin(9600);
  Serial.begin(9600);
  MEMED.begin();
  MEMED.backlight();
}// Syarif Hidayat _ D400220086
void loop() {
  if (blueSlave.available() > 0) {
    Hasil_Tombol = blueSlave.read();
  }// Syarif Hidayat _ D400220086
  if (Hasil_Terakhir_Tombol == '1' && Hasil_Tombol == '0') {
    Jumlah_Ditekan++;
    if (Jumlah_Ditekan > 4) {
      Jumlah_Ditekan = 1;
    }// Syarif Hidayat _ D400220086
    delay(500);
    switch (Jumlah_Ditekan) {
      case 1:
        MEMED.clear();
        MEMED.setCursor(0, 0);
        MEMED.print("PRAKT. ANTARMUKA");
        MEMED.setCursor(0, 1);
        MEMED.print("MODUL 4");
        break;// Syarif Hidayat _ D400220086
      case 2:
        MEMED.clear();
        MEMED.setCursor(0, 0);
        MEMED.print("SYARIF HIDAYAT");
        MEMED.setCursor(0, 1);
        MEMED.print("D400220087");
        break;// Syarif Hidayat _ D400220086
      case 3:  // Kondisi 3 (Anggota 2)
        MEMED.clear();
        MEMED.setCursor(0, 0);
        MEMED.print("MAHESA ARYA");
        MEMED.setCursor(0, 1);
        MEMED.print("D400220086");
        break;// Syarif Hidayat _ D400220086
      case 4:  // Kondisi 4 (Anggota 3)
        MEMED.clear();
        MEMED.setCursor(0, 0);
        MEMED.print("MIKAIL HEGEL");
        MEMED.setCursor(0, 1);
        MEMED.print("D400220100");
        break;// Syarif Hidayat _ D400220086
    }
  }
  Hasil_Terakhir_Tombol = Hasil_Tombol;
}
