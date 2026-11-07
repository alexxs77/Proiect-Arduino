#include <LiquidCrystal.h>
#include <DHT.h>
LiquidCrystal lcd(7, 8, 9, 10, 6, 12);
#define DHT11PIN 2
#define DHTTYPE DHT22
DHT dht(DHT11PIN, DHTTYPE);
unsigned long timpDisplay = 0;

void afisaretemperatura() {
  float citireT = dht.readTemperature();
  lcd.setCursor(0, 0);
  lcd.print("Temperatura este");
  if (!isnan(citireT)) {
    lcd.setCursor(4, 1);
    lcd.print(citireT, 2); 
  }
  lcd.setCursor(9, 1);
  lcd.print("*C");                          
}
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin();
}
void loop() {
  if (millis() - timpDisplay >= 2000) {
    afisaretemperatura();
    timpDisplay = millis();
  }
}