#include "Display.h"
#include <Wire.h>

// Dodane definicje
#define SSD1306_WHITE 1
#define SSD1306_SWITCHCAPVCC 0x2

Display::Display() {
  oled = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
}

bool Display::begin() {
  if(!oled->begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    return false;
  }
  oled->clearDisplay();
  oled->display();
  return true;
}

void Display::showMainMenu(bool isTimerSelected) {
  oled->clearDisplay();
  oled->setTextSize(2);
  oled->setTextColor(SSD1306_WHITE);
  
  oled->setCursor(5, 0);
  oled->println("Timer");
  
  oled->setCursor(5, 16);
  oled->println("Aero");
  
  oled->setCursor(115, isTimerSelected ? 0 : 16);
  oled->print(">");
  
  showBatteryStatus();
  oled->display();
}

void Display::showBigTimer(int seconds) {
  oled->clearDisplay();
  oled->setTextSize(3);
  oled->setTextColor(SSD1306_WHITE);
  
  char timeStr[6];
  sprintf(timeStr, "%d", seconds);
  int16_t x1, y1;
  uint16_t w, h;
  oled->getTextBounds(timeStr, 0, 0, &x1, &y1, &w, &h);
  int x = (SCREEN_WIDTH - w) / 2;
  int y = (SCREEN_HEIGHT - h) / 2;
  
  oled->setCursor(x, y);
  oled->print(seconds);
  
  showBatteryStatus();
  oled->display();
}

void Display::showAeroStatus(const char* status, int seconds) {
  oled->clearDisplay();
  
  oled->setTextSize(1);
  oled->setTextColor(SSD1306_WHITE);
  oled->setCursor(0, 0);
  oled->println(status);
  
  oled->setTextSize(3);
  char timeStr[6];
  sprintf(timeStr, "%d", seconds);
  int16_t x1, y1;
  uint16_t w, h;
  oled->getTextBounds(timeStr, 0, 0, &x1, &y1, &w, &h);
  int x = (SCREEN_WIDTH - w) / 2;
  
  oled->setCursor(x, 12);
  oled->print(seconds);
  
  showBatteryStatus();
  oled->display();
}

void Display::showMessage(const char* message) {
  oled->clearDisplay();
  oled->setTextSize(1);
  oled->setTextColor(SSD1306_WHITE);
  oled->setCursor(0, 0);
  oled->println(message);
  oled->display();
}

void Display::showBatteryStatus() {
  int batteryLevel = analogRead(BATTERY_PIN);
  int percentage = map(batteryLevel, 0, 1023, 0, 100);
  
  oled->setTextSize(1);
  oled->setCursor(90, 0);
  oled->print(percentage);
  oled->print("%");
} 