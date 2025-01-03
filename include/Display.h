#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Constants.h"

class Display {
private:
    Adafruit_SSD1306 display;

    // Metody pomocnicze do formatowania czasu
    void formatTime(unsigned long seconds, char* buffer);
    void clearAndSetCursor();

public:
    Display();
    
    // Inicjalizacja wyświetlacza
    bool begin();
    
    // Metody wyświetlania różnych ekranów
    void showIdle();
    void showTimer(unsigned long remainingTime);
    void showBlooming(unsigned long remainingTime);
    void showBrewing(unsigned long remainingTime);
    void showPressing(unsigned long remainingTime);
    void showCoolingDownPrompt();
    void showCoolingDown(unsigned long remainingTime);
    void showComplete();
    
    // Metoda do czyszczenia ekranu
    void clear();
};