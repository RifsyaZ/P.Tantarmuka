#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial Rxserial(8, 9);
LiquidCrystal_I2C Memet(0x27, 16, 2);

int MemetDiterima;
float Convert_Memet;
const int LED = 6;

void setup() {
  Rxserial.begin(9600);
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  Memet.init();
  Memet.backlight();
  Memet.clear();
  Memet.setCursor(0, 0);
  Memet.print("-----DONE-----");
}
void loop() {
  Terima_memet();
  delay(300);
  if (Convert_Memet >= 1.6) {
    digitalWrite(LED, HIGH);
    Memet.clear();
    Memet.setCursor(0, 0);
    Memet.print("Con_Mmt = ");
    Memet.setCursor(10, 0);
    Memet.print(Convert_Memet);
    Memet.setCursor(2, 1);
    Memet.print("--- HIDUP ---");
  }
  else {
    digitalWrite(LED, LOW);
    Memet.clear();
    Memet.setCursor(0, 0);
    Memet.print("Con_Mmt = ");
    Memet.setCursor(10, 0);
    Memet.print(Convert_Memet);
    Memet.setCursor(2, 1);
    Memet.print("--- MATI ---");
  }
}
void Terima_memet() {
  if (Rxserial.available()) {
    String received = Rxserial.readStringUntil('\n');
    MemetDiterima = received.toInt();
    Serial.print("Data diterima: ");
    Serial.print(MemetDiterima);
    Serial.print("     Convert = ");
    Convert_Memet = MemetDiterima / 100.0;
    Serial.println(Convert_Memet);
  }
}
