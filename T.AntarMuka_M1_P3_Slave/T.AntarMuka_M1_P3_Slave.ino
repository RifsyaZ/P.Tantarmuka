#include <SPI.h>
#define LEDpin 7
#define buttonpin 2
volatile boolean received;
volatile byte Slavereceived, Slavesend;
int buttonvalue;
int x;
void setup() {
  Serial.begin(9600);
  pinMode(buttonpin, INPUT_PULLUP);
  pinMode(LEDpin, OUTPUT);
  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE);
  received = false;
  SPI.attachInterrupt();
}

ISR(SPI_STC_vect)
{
  Slavereceived = SPDR;
  received = true;
}

void loop() {
  if (received)
  {
    if (Slavereceived == 1) {
      digitalWrite(LEDpin, HIGH);
      Serial.println("Slave LED ON");
    } else {
      digitalWrite(LEDpin, LOW);
      Serial.println("Slave LED OFF");
    }
    buttonvalue = digitalRead(buttonpin);
    if (buttonvalue == LOW)
    {
      x = 1;
    } else {
      x = 0;
    }
    Slavesend = x;
    SPDR = Slavesend;
    delay(1000);
  }
}
