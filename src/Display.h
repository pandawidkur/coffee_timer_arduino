#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_SSD1306.h>

class Display {
  private:
    Adafruit_SSD1306* oled;
    static const int SCREEN_WIDTH = 128;
    static const int SCREEN_HEIGHT = 32;
    static const int OLED_RESET = -1;
    static const int BATTERY_PIN = A0;

  public:
    Display();
    bool begin();
    void showMainMenu(bool isTimerSelected);
    void showBigTimer(int seconds);
    void showAeroStatus(const char* status, int seconds);
    void showMessage(const char* message);
    void showBatteryStatus();
    void clearDisplay() { oled->clearDisplay(); oled->display(); }
    void setTextSize(int size) { oled->setTextSize(size); }
    void setTextColor(int color = SSD1306_WHITE) { oled->setTextColor(color); }
    void setCursor(int x, int y) { oled->setCursor(x, y); }
    void println(const char* text) { oled->println(text); }
    void print(const char* text) { oled->print(text); }
    void print(int number) { oled->print(number); }
    void display() { oled->display(); }
};

#endif 