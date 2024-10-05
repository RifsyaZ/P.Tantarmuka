#include <SoftwareSerial.h>
const int PuterMemet = A0;
int SV_memet;
SoftwareSerial Txserial(9, 8);

void setup() {
  pinMode(PuterMemet, INPUT);
  Txserial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  Baca();
  delay(150);
}

void Baca() {
  SV_memet = analogRead(PuterMemet);
  Txserial.print(SV_memet);
  Txserial.print("\n");  
  Serial.print("SV_memet = ");
  Serial.println(SV_memet);
}
