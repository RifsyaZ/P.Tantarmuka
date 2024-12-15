#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp;//Inialisasi Pemanggilan Nama bmp
float Suhu, Tekanan, Ketinggian;

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  oled.init();
  oled.clearDisplay();
  while (!bmp.begin(0x76)) {
    Serial.println("Belum Terhubung ke Sensor, Coba Cek Rangkaian");
    oled.setTextXY(0, 0);
    oled.putString("BMP-280 Tidak Terhubung!!!");
    delay(1000);
  }
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     // Mode
                  Adafruit_BMP280::SAMPLING_X16,  // Pengambilan suhu
                  Adafruit_BMP280::SAMPLING_X16,  // Pengambilan tekanan
                  Adafruit_BMP280::FILTER_X16,    // Filter
                  Adafruit_BMP280::STANDBY_MS_500); // Waktu standby

  Serial.println("Sensor BMP-280 Terhubung");
  oled.setTextXY(0, 0);
  oled.putString("BMP-280 Terhubung!!!");
}

void loop()
{
  BacaSensor();
  Monitor();
  Display();
}
void BacaSensor() {
  Suhu = bmp.readTemperature();
  Tekanan = bmp.readPressure() / 100.0F;
  Ketinggian = bmp.readAltitude(1013.25);
  delay(1000);
}
void Monitor() {
  Serial.print("Suhu = ");
  Serial.print(Suhu);
  Serial.println(" *C");
  Serial.print("Tekanan = ");
  Serial.print(Tekanan); // Konversi dari Pa ke hPa
  Serial.println(" hPa");
  Serial.print("Approx altitude = ");
  Serial.print(Ketinggian); // Estimasi ketinggian
  Serial.println(" m");
  Serial.println();
}
void Display() {
  oled.clearDisplay();
  oled.setTextXY(0, 1);
  oled.putString("Suhu = ");
  oled.setTextXY(0, 7);
  oled.putString(String(Suhu));
  oled.setTextXY(2, 1);
  oled.putString("Tekanan = ");
  oled.setTextXY(2, 10);
  oled.putString(String(Tekanan));
  oled.setTextXY(5, 1);
  oled.putString("Ketinggian = ");
  oled.setTextXY(5, 10);
  oled.putString(String(Ketinggian));
}
