#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <ESP32Servo.h>
// Syarif Hidayat_D400220086
#define WIFI_SSID "RS"
#define WIFI_PASSWORD "123456789"
#define API_KEY "AIzaSyAqOZ-rJLM3cEXkKGamXJbbn_LJLtnQWBY"
#define DATABASE_URL "https://antarmuka-15e98-default-rtdb.firebaseio.com/"
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
// Syarif Hidayat_D400220086
Servo servoMotor;
// Syarif Hidayat_D400220086
const int PIN_L_E_D = 32;
const int PIN_D_H_T = 36;
int Sudut_Servo = 0;
// Syarif Hidayat_D400220086
int Sudut_60 = 60;
int Sudut_80 = 80;
int Sudut_6080 = 140;
// Syarif Hidayat_D400220086
void setup() {
  bool signupOK = false;
  Serial.begin(115200);
  pinMode(PIN_L_E_D, OUTPUT);
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
  }// Syarif Hidayat_D400220086
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
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
    }// Syarif Hidayat_D400220086
    else if (ledState == Sudut_80) {
      servoMotor.write(Sudut_80);
      dacWrite(25, 255);
      Serial.print("Value_Servo:");
      Serial.println(Sudut_80);
    }// Syarif Hidayat_D400220086
    else if (ledState == Sudut_6080) {
      servoMotor.write(Sudut_6080);
      dacWrite(25, 0);
      Serial.print("Value_Servo:");
      Serial.println(Sudut_6080);
    }// Syarif Hidayat_D400220086
  } else {
    Serial.println("Failed to read from Firebase");
    Serial.println("Error: " + fbdo.errorReason());
  }// Syarif Hidayat_D400220086
  int Value_DHT = analogRead(PIN_D_H_T);
  Serial.println("LDR value: " + String(Value_DHT));
  if (Firebase.RTDB.setInt(&fbdo, "/DHT/PLER", Value_DHT)) {
    Serial.println("LDR value sent to Firebase");
  } else {// Syarif Hidayat_D400220086
    Serial.println("Failed to send LDR value to Firebase");
    Serial.println("Error: " + fbdo.errorReason());
  }// Syarif Hidayat_D400220086
}
