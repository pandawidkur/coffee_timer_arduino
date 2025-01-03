#pragma once

#include "Constants.h"
#include <Arduino.h>

class Timer {
private:
    Config::State currentState;
    unsigned long startTime;
    unsigned long remainingTime;
    bool isRunning;
    bool coolingDownReady;

public:
    Timer();
    
    // Metody kontroli stanu
    Config::State getState() const;
    unsigned long getRemainingTime() const;
    bool isComplete() const;
    
    // Metody dla trybu Timer
    void startTimer();
    void incrementTimer();
    void decrementTimer();
    
    // Metody dla trybu AeroPress
    void startAeroPress();
    void confirmCoolingDown();
    
    // Metody ogólne
    void stop();
    void update();
    
    // Metody pomocnicze
    bool shouldTransitionToNextState() const;
    void transitionToNextState();
};