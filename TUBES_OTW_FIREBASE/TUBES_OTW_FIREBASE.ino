#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp;//Inialisasi Pemanggilan Nama bmp
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#define WIFI_SSID "RS"
#define WIFI_PASSWORD "Rifsya160022"
#define API_KEY "AIzaSyALNMq3I-DUe0Jgc80vsdNsa60xO3gjz-E"
#define DATABASE_URL "https://tam-tubes-default-rtdb.asia-southeast1.firebasedatabase.app"
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

const int Kipas = 2;//Relay CH1
const int Peltier = 15;//Relay CH2
const int Dht = 1;//PIN DHT ( Pilih D1 - D19 )

float Suhu, Tekanan, Ketinggian, kelembapan;

void SetPin() {
  pinMode(Kipas, OUTPUT);
  pinMode(Peltier, OUTPUT);
  pinMode(Dht, INPUT);
}
void setup()
{
  Serial.begin(115200);
  Wire.begin();
  SetPin();
  SetFireBase();
  oled.init();
  oled.clearDisplay();
  while (!bmp.begin(0x76)) {
    Serial.println("Belum Terhubung ke Sensor, Coba Cek Rangkaian");
    oled.setTextXY(0, 0);
    oled.putString("BMP-280 Tidak Terhubung!!!");
    //    delay(1000);
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
  TesRelay();
  Sistem(25, 70);// ( Set Suhu , Set Kelembapan )

}
void TesRelay() {
  while (1) {
    digitalWrite(Kipas, HIGH);
    digitalWrite(Peltier, LOW);
    delay(100);
    digitalWrite(Peltier, HIGH);
    digitalWrite(Kipas, LOW);
    delay(100);
  }
}
void SetFireBase() {
  bool signupOK = false;
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.println("Connected to Wi-Fi");
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  Serial.println();
  Serial.println("---------------Sign up");
  Serial.print("Sign up new user... ");
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  Serial.println("---------------");
  config.token_status_callback = tokenStatusCallback;
  Firebase.reconnectWiFi(true);
  Firebase.begin(&config, &auth);
}

void BacaSensor() {
  Suhu = bmp.readTemperature();
  Tekanan = bmp.readPressure() / 100.0F;
  Ketinggian = bmp.readAltitude(1013.25);
  //  delay(1000);
}
void KirimKeFirebase() {
  Firebase.RTDB.setInt(&fbdo, "/Data/Suhu", Suhu);
  Firebase.RTDB.setInt(&fbdo, "/Data/Kelembapan", Ketinggian);
  Firebase.RTDB.setInt(&fbdo, "/Data/Tekanan", Tekanan);
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
void Sistem(int SetSuhu, int SetKelembapan) {
  oled.clearDisplay();
  BacaSensor();
  KirimKeFirebase();
  Monitor();
  Display();
  if (Suhu >= SetSuhu) {
    digitalWrite(Peltier, HIGH); //Relay Peltier ON
  }
  else if (Suhu < SetSuhu) {
    digitalWrite(Peltier, LOW); //Relay Peltier OFF
  }

  if (kelembapan >= SetKelembapan) {
    digitalWrite(Kipas, HIGH); //Relay Kipas ON
  }
  else if (kelembapan < SetKelembapan) {
    digitalWrite(Kipas, LOW); //Relay Kipas OFF
  }
}
