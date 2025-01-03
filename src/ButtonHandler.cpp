#include "ButtonHandler.h"

ButtonHandler::ButtonHandler() {
    // Konstruktor - na razie pusty, inicjalizacja jest w begin()
}

void ButtonHandler::begin() {
    // Konfiguracja pinów jako wejścia z pull-up
    pinMode(Config::START_BUTTON, INPUT_PULLUP);
    pinMode(Config::AERO_BUTTON, INPUT_PULLUP);
    pinMode(Config::STOP_BUTTON, INPUT_PULLUP);
}

bool ButtonHandler::isStartPressed() {
    bool currentState = digitalRead(Config::START_BUTTON);
    unsigned long currentTime = millis();
    
    // Sprawdzamy czy: 
    // 1. Przycisk jest wciśnięty (LOW bo pull-up)
    // 2. Poprzedni stan był niewciśnięty
    // 3. Minął czas debouncing
    if (currentState == LOW && 
        lastStartButtonState == HIGH && 
        (currentTime - lastStartButtonTime) > Config::Timings::BUTTON_DEBOUNCE) {
        
        lastStartButtonTime = currentTime;
        lastStartButtonState = currentState;
        return true;
    }
    
    lastStartButtonState = currentState;
    return false;
}

bool ButtonHandler::isAeroPressed() {
    bool currentState = digitalRead(Config::AERO_BUTTON);
    unsigned long currentTime = millis();
    
    if (currentState == LOW && 
        lastAeroButtonState == HIGH && 
        (currentTime - lastAeroButtonTime) > Config::Timings::BUTTON_DEBOUNCE) {
        
        lastAeroButtonTime = currentTime;
        lastAeroButtonState = currentState;
        return true;
    }
    
    lastAeroButtonState = currentState;
    return false;
}

bool ButtonHandler::isStopPressed() {
    bool currentState = digitalRead(Config::STOP_BUTTON);
    unsigned long currentTime = millis();
    
    if (currentState == LOW && 
        lastStopButtonState == HIGH && 
        (currentTime - lastStopButtonTime) > Config::Timings::BUTTON_DEBOUNCE) {
        
        lastStopButtonTime = currentTime;
        lastStopButtonState = currentState;
        return true;
    }
    
    lastStopButtonState = currentState;
    return false;
}

void ButtonHandler::update() {
    // Aktualizacja stanu wszystkich przycisków
    isStartPressed();
    isAeroPressed();
    isStopPressed();
}