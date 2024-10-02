const int led  = 13;
String code;
void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}
void loop() {
  if (Serial.available()) {
    code = Serial.readStringUntil('\n');
    code.trim();
  } if (code == "hidup") {
    digitalWrite(led, HIGH);
    Serial.println("LED HIDUP");
    code = "";
  }
  else if (code == "mati") {
    digitalWrite(led, LOW);
    Serial.println("LED MATI");
    code = "";
  }
  else if (code == "kedip") {
    Serial.println("LED BERKEDIP");
    while (true) {
      digitalWrite(led, HIGH);
      delay(1000);
      digitalWrite(led, LOW);
      delay(1000);
      if (Serial.available()) {
        code = Serial.readStringUntil('\n');
        code.trim();
        break;
      }
    }
  }
  delay(100);
}
