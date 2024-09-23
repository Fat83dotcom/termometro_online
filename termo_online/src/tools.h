#ifndef TOOLS
#define TOOLS

#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128 // Oled display width(largura), in pixels
#define SCREEN_HEIGHT 64 // Oled display height(altura), in pixels
#define Oled_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, Oled_RESET);

void visor(double value);
double getTemp(int sensor);
class HandlingData;

void visor(double value) {
  display.invertDisplay(0);
  display.setTextSize(3);
  display.setTextColor(WHITE);

  display.setCursor(30, 5);
  display.println("TEMP");
  
  display.setCursor(1, 37);
  display.print(value);
  display.println(" C");

  
  display.display();
  display.clearDisplay();
}

double getTemp(int sensor) {
  int RawADC = analogRead(sensor);
  long Resistance;
  double Temp;
  Resistance=((10240000/RawADC) - 10000);
  Temp = log(Resistance);
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;  // Convert Kelvin to Celsius
  return Temp;  
}

class HandlingData {
  private:
  double _sum;
  int _meanCount;

  public:
  HandlingData(int meanCount) {
    _meanCount = meanCount;
  }

  void engine(double value) {
    static double mean;
    static int count = 0;
    if (count == this->_meanCount) {
      mean = (this->_sum / this->_meanCount);
      visor(mean);
      count = 0;
      mean = 0;
      this->_sum = 0;
    }
    else {
      this->_sum += value;
      count++;
    }
  }
};

#endif