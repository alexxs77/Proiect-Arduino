#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 6, 12);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Testare Ecran");
}
void loop() {
  delay(1000);
}