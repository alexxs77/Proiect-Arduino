#include <LiquidCrystal.h>
#include <Stepper.h>
#include <DHT.h>
#include <Wire.h>

LiquidCrystal lcd(7, 8, 9, 10, 6, 12);
const int stepsPerRevolution = 500;
Stepper myStepper(stepsPerRevolution, 13, A1, A0, A2);

#define DHT11PIN 2
#define DHTTYPE DHT22
DHT dht(DHT11PIN, DHTTYPE);

unsigned long timpDisplay = 0;
int h, x = 24;
#define ENABLE 5
#define DIRA 3
#define DIRB 4
double kp = 40.0;

void afisaretemperatura() {
  float citireH = dht.readHumidity();
  float citireT = dht.readTemperature();

  if (!isnan(citireH)) {
    h = (int)citireH; 
    Wire.beginTransmission(9);
    Wire.write(h);
    Wire.endTransmission();
  }

  lcd.setCursor(0, 0);
  lcd.print("Temperatura este");
  
  if (!isnan(citireT)) {
    lcd.setCursor(4, 1);
    lcd.print(citireT, 2); 
  }
  
  lcd.setCursor(9, 1);
  lcd.print("*C");                          
}

void porniremotor(int viteza) {
  analogWrite(ENABLE, viteza); 
  PORTD |= (1 << PD3);   
  PORTD &= ~(1 << PD4);  
}

void opriremotor() {
  analogWrite(ENABLE, 0); 
  PORTD &= ~(1 << PD3);  
  PORTD &= ~(1 << PD4);  
}

void verificaretemperatura() { 
  float citireT = dht.readTemperature();
  
  if (!isnan(citireT)) {
    double eroare = citireT - (float)x; 
    if (eroare > 0) {
      double output = 100 + (kp * eroare);
      int vitezaPWM = (int)output;
      if (vitezaPWM > 255) vitezaPWM = 255; 
      porniremotor(vitezaPWM); 
    } else {
      opriremotor();
    }
  } 
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  // Configurare pini motor DC
  DDRD |= (1 << DDD5) | (1 << DDD3) | (1 << DDD4);
  myStepper.setSpeed(30);
  
  lcd.begin(16, 2);
  Wire.begin(); 
}

void loop() {
  if (millis() - timpDisplay >= 2000) {
    afisaretemperatura();
    timpDisplay = millis();
  }
  
  
  verificaretemperatura(); 
  
  delay(10);
}