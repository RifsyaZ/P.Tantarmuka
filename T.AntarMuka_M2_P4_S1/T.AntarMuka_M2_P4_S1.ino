#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);
const unsigned char PROGMEM customBitmap[] = {
  0b00001000,
  0b00110000,
  0b01100000,
  0b11111110,
  0b00001100,
  0b00011000,
  0b00100000
};// Syarif Hidayat_D400220086
void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  // display.drawBitmap(x position, y position, bitmap data,
  //bitmap width, bitmap height, color)
  display.drawBitmap(0, 0, customBitmap, 8, 7, WHITE);
  display.display();
}// Syarif Hidayat_D400220086
void loop() { }
