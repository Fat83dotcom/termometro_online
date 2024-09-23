#include <Arduino.h>
#include "tools.h"

int pin = 13;
int sensorK10 = A0;
HandlingData *run = new HandlingData(1000);

void setup() {
  pinMode(pin, OUTPUT);
  pinMode(sensorK10, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  display.clearDisplay();
}

void blink(){
  static unsigned long current = millis();
  if ((millis() - current) < 500) {
    digitalWrite(pin, 1);
  }
  else {
    digitalWrite(pin, 0);
  }
  if ((millis() - current) > 1000) {
    current = millis();
  }
}

void loop() {
  blink();
  run->engine(getTemp(sensorK10));
}
