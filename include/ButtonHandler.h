#pragma once

#include "Constants.h"
#include <Arduino.h>

class ButtonHandler {
private:
    // Czasy ostatnich naciśnięć dla debouncingu
    unsigned long lastStartButtonTime = 0;
    unsigned long lastAeroButtonTime = 0;
    unsigned long lastStopButtonTime = 0;

    // Poprzednie stany przycisków
    bool lastStartButtonState = HIGH;
    bool lastAeroButtonState = HIGH;
    bool lastStopButtonState = HIGH;

public:
    ButtonHandler();
    
    // Inicjalizacja pinów
    void begin();
    
    // Sprawdzanie poszczególnych przycisków
    bool isStartPressed();
    bool isAeroPressed();
    bool isStopPressed();

    // Metoda do aktualizacji stanów przycisków
    void update();
};