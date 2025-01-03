#include <Arduino.h>
#include "ButtonHandler.h"
#include "Display.h"
#include "Timer.h"

// Utworzenie obiektów globalnych
ButtonHandler buttons;
Display display;
Timer timer;

void handleButtons() {
    // Obsługa przycisku Start
    if (buttons.isStartPressed()) {
        switch (timer.getState()) {
            case Config::State::IDLE:
                timer.startTimer();
                break;
            case Config::State::TIMER:
                timer.incrementTimer();
                break;
            case Config::State::AERO_WAIT_COOLING_DOWN:
                timer.confirmCoolingDown();
                break;
        }
    }

    // Obsługa przycisku AeroPress
    if (buttons.isAeroPressed()) {
        switch (timer.getState()) {
            case Config::State::IDLE:
                timer.startAeroPress();
                break;
            case Config::State::AERO_WAIT_COOLING_DOWN:
                timer.confirmCoolingDown();
                break;
        }
    }

    // Obsługa przycisku Stop
    if (buttons.isStopPressed()) {
        switch (timer.getState()) {
            case Config::State::TIMER:
                timer.decrementTimer();
                break;
            default:
                timer.stop();
                break;
        }
    }
}

void updateDisplay() {
    switch (timer.getState()) {
        case Config::State::IDLE:
            display.showIdle();
            break;
            
        case Config::State::TIMER:
            display.showTimer(timer.getRemainingTime());
            break;
            
        case Config::State::AERO_BLOOMING:
            display.showBlooming(timer.getRemainingTime());
            break;
            
        case Config::State::AERO_BREWING:
            display.showBrewing(timer.getRemainingTime());
            break;
            
        case Config::State::AERO_PRESSING:
            display.showPressing(timer.getRemainingTime());
            break;
            
        case Config::State::AERO_WAIT_COOLING_DOWN:
            display.showCoolingDownPrompt();
            break;
            
        case Config::State::AERO_COOLING_DOWN:
            display.showCoolingDown(timer.getRemainingTime());
            break;
    }
}

void setup() {
    // Inicjalizacja komponentów
    buttons.begin();
    
    if (!display.begin()) {
        // Jeśli inicjalizacja wyświetlacza się nie powiedzie,
        // zatrzymaj program
        while (true) { delay(1); }
    }

    // Pokaż ekran startowy
    display.showIdle();
}

void loop() {
    // Aktualizacja stanu przycisków
    buttons.update();
    
    // Obsługa przycisków
    handleButtons();
    
    // Aktualizacja timera
    timer.update();
    
    // Aktualizacja wyświetlacza
    updateDisplay();
    
    // Małe opóźnienie dla stabilności
    delay(10);
}