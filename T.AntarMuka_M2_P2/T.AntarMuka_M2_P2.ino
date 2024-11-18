  #include <LiquidCrystal_I2C.h>
  #include <Wire.h>
  LiquidCrystal_I2C lcd(0x27, 16, 2);
  void setup() {
    lcd.init();
    lcd.backlight();
  }
  void loop() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PRAKT. ANTARMUKA");
    lcd.setCursor(0, 1);
    lcd.print("2024/2025");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Syarif Hidayat");
    lcd.setCursor(0, 1);
    lcd.print("D400220086");
    delay(2000);
  }
