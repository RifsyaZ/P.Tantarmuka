#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <ESP32Servo.h>
#include <DHT.h> // Tambahkan library DHT
// Syarif Hidayat_D400220086
#define WIFI_SSID "RS"
#define WIFI_PASSWORD "16022"
#define API_KEY "AIzaSyAqOZ-rJLM3cEXkKGamXJbbn_LJLtnQWBY"
#define DATABASE_URL "https://antarmuka-15e98-default-rtdb.firebaseio.com/"
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
// Syarif Hidayat_D400220086
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
// Syarif Hidayat_D400220086
Servo servoMotor;
#define DHTPIN 26
#define DHTTYPE DHT11
const int ledPin = 32;
int Sudut_Servo = 0;
DHT dht(DHTPIN, DHTTYPE);
int Sudut_60 = 60; // ganti
int Sudut_80 = 80; // ganti
int Sudut_140 = 140; // ganti
float suhu;// Syarif Hidayat_D400220086
void setup() {
  bool signupOK = false;
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  dht.begin();// Syarif Hidayat_D400220086
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }// Syarif Hidayat_D400220086
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
  } else {// Syarif Hidayat_D400220086
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }// Syarif Hidayat_D400220086
  Serial.println("---------------");
  config.token_status_callback = tokenStatusCallback;
  Firebase.reconnectWiFi(true);
  Firebase.begin(&config, &auth);
  servoMotor.attach(23);
  servoMotor.write(Sudut_Servo);
}// Syarif Hidayat_D400220086
void loop() {
  if (Firebase.RTDB.getString(&fbdo, "/tugas5antarmuka/SERVO")) {
    String ledStateStr = fbdo.stringData();
    int ledState = ledStateStr.toInt();
    Sudut_Servo = ledState;
    Serial.print("Value_Servo:");
    Serial.println(Sudut_Servo);
    if (ledState == Sudut_60) {
      servoMotor.write(Sudut_60);
      dacWrite(25, 130);
      Serial.print("Value_Servo:");
      Serial.println(Sudut_60);
    } else if (ledState == Sudut_80) {
      servoMotor.write(Sudut_80);
      dacWrite(25, 255);
      Serial.print("Value_Servo:");
      Serial.println(Sudut_80);
    } else if (ledState == Sudut_140) {
      servoMotor.write(Sudut_140);
      dacWrite(25, 0);
      Serial.print("Value_Servo:");
      Serial.println(Sudut_140);
    }// Syarif Hidayat_D400220086
  } else {
    Serial.println("Failed to read from Firebase");
    Serial.println("Error: " + fbdo.errorReason());
  }// Syarif Hidayat_D400220086
  suhu = dht.readTemperature();
  if (isnan(suhu)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {// Syarif Hidayat_D400220086
    Serial.print("Suhu: ");
    Serial.println(suhu);
    if (Firebase.RTDB.setFloat(&fbdo, "/SUHU/PLUH", suhu)) {
      Serial.println("Suhu value sent to Firebase");
      if (suhu < 32) {
        dacWrite(25, 0);
      }// Syarif Hidayat_D400220086
      else if (suhu > 32 && suhu < 34) {
        dacWrite(25, 130);
      }// Syarif Hidayat_D400220086
      else if (suhu > 34 ) {
        dacWrite(25, 255);
      }// Syarif Hidayat_D400220086
    } else {
      Serial.println("Failed to send suhu value to Firebase");
      Serial.println("Error: " + fbdo.errorReason());
    }// Syarif Hidayat_D400220086
  }// Syarif Hidayat_D400220086
}
