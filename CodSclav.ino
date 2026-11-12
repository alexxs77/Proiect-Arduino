#include <SevSeg.h>
#include <Wire.h>
SevSeg sevseg;
int x;

void setup() {
    byte numDigits = 4;  
    byte digitPins[] = {2, 3, 4, 5};
    byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
    sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, 0);
    sevseg.setBrightness(0);

    Wire.begin(9);
    Wire.onReceive(receiveEvent);
}

void receiveEvent(int bytes) {
  x = Wire.read();    
}

void loop() {
  sevseg.setNumber(x);     
  sevseg.refreshDisplay(); 
}