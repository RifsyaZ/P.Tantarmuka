#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire,OLED_RESET);
void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
}
void loop() {// Syarif Hidayat _ D400220086
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(39, 20);
  display.print("Praktikum");
  display.setTextSize(1);
  display.setCursor(38, 30);
  display.setTextColor(WHITE);
  display.println("Antarmuka ");
  display.setTextSize(1);
  display.setCursor(44, 40);
  display.setTextColor(WHITE);
  display.print("Modul 2");
  display.display();
  delay(2000);// Syarif Hidayat _ D400220086
  display.clearDisplay();
  display.setTextSize(1.5);
  display.setTextColor(WHITE);
  display.setCursor(52, 13);
  display.print("Syarif Hidayat");
  display.setTextSize(1.5);
  display.setTextColor(WHITE);
  display.setCursor(36, 33);
  display.print("D400220086");
  display.display();
  delay(2000);
}
