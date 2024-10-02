// Syarif Hidayat_D400220086_Kelas A //
#include <SPI.h>
#define LED 7
#define ipbutton 2
int buttonvalue;
int x;
void setup(void) {
  Serial.begin(9600);
  pinMode(ipbutton, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  digitalWrite(SS, HIGH);
}

void loop(void) {
  byte Mastersend, Mastereceive;
  buttonvalue = digitalRead(ipbutton);

  if (buttonvalue == LOW)
  {
    x = 1;
  }
  else {
    x = 0;
  }
  digitalWrite(SS, LOW);
  Mastersend = x;
  Mastereceive = SPI.transfer(Mastersend);
  // Syarif Hidayat_D400220086_Kelas A //
  if (Mastereceive == 1)
  {
    digitalWrite(LED, HIGH);
    Serial.println("Master LED ON");
  }
  else {
    digitalWrite(LED, LOW);
    Serial.println("Master LED OFF");
  }
  delay(1000);
}
