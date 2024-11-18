#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <ESP32Servo.h>
#include <DHT.h> // Tambahkan library DHT

#define WIFI_SSID "REDMI K70E" // ganti
#define WIFI_PASSWORD "FuckShit" // ganti
#define API_KEY "AIzaSyAqOZ-rJLM3cEXkKGamXJbbn_LJLtnQWBY" // ganti
#define DATABASE_URL "https://antarmuka-15e98-default-rtdb.firebaseio.com/" // ganti
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

Servo servoMotor;
#define DHTPIN 26
#define DHTTYPE DHT11
const int ledPin = 32;

int Sudut_Servo = 0;

// Konfigurasi DHT
DHT dht(DHTPIN, DHTTYPE);
int Set_Value_1 = 60; // ganti
int Set_Value_2 = 80; // ganti
int Set_Value_3 = 140; // ganti

void setup() {
  bool signupOK = false;
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  
  // Inisialisasi DHT
  dht.begin();

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
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  
  Serial.println("---------------");
  config.token_status_callback = tokenStatusCallback;
  Firebase.reconnectWiFi(true);
  Firebase.begin(&config, &auth);
  
  servoMotor.attach(23);
  servoMotor.write(Sudut_Servo);
}

void loop() {
  if (Firebase.RTDB.getString(&fbdo, "/tugas5antarmuka/SERVO")) {
    String ledStateStr = fbdo.stringData();
    int ledState = ledStateStr.toInt();
    Sudut_Servo = ledState;
    Serial.print("Value_Servo:");
    Serial.println(Sudut_Servo);
    
    if (ledState == Set_Value_1) {
      servoMotor.write(Set_Value_1);
      dacWrite(25, 130);
      Serial.print("Value_Servo:");
      Serial.println(Set_Value_1);
    } else if (ledState == Set_Value_2) {
      servoMotor.write(Set_Value_2);
      dacWrite(25, 255);
      Serial.print("Value_Servo:");
      Serial.println(Set_Value_2);
    } else if (ledState == Set_Value_3) {
      servoMotor.write(Set_Value_3);
      dacWrite(25, 0);
      Serial.print("Value_Servo:");
      Serial.println(Set_Value_3);
    }
  } else {
    Serial.println("Failed to read from Firebase");
    Serial.println("Error: " + fbdo.errorReason());
  }

  // Membaca nilai dari sensor DHT
  float suhu = dht.readTemperature(); // Membaca suhu dalam Celsius

  // Cek apakah pembacaan suhu berhasil
  if (isnan(suhu)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Suhu: ");
    Serial.println(suhu);
    
    // Mengirim nilai suhu ke Firebase
    if (Firebase.RTDB.setFloat(&fbdo, "/SUHU/PLUH", suhu)) {
      Serial.println("Suhu value sent to Firebase");
    } else {
      Serial.println("Failed to send suhu value to Firebase");
      Serial.println("Error: " + fbdo.errorReason());
    }
  }
}
