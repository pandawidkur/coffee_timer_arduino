#include "Timer.h"

Timer::Timer()
    : currentState(Config::State::IDLE),
      startTime(0),
      remainingTime(0),
      isRunning(false),
      coolingDownReady(false) {
}

Config::State Timer::getState() const {
    return currentState;
}

unsigned long Timer::getRemainingTime() const {
    return remainingTime;
}

bool Timer::isComplete() const {
    if (!isRunning) return false;
    
    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - startTime;
    return elapsedTime >= remainingTime;
}

void Timer::startTimer() {
    currentState = Config::State::TIMER;
    startTime = millis();
    remainingTime = Config::Timings::TIMER_STEP; // 30 sekund
    isRunning = true;
}

void Timer::incrementTimer() {
    if (currentState == Config::State::TIMER) {
        remainingTime += Config::Timings::TIMER_STEP;
        startTime = millis(); // Reset czasu startu przy każdej zmianie
    }
}

void Timer::decrementTimer() {
    if (currentState == Config::State::TIMER && remainingTime > Config::Timings::TIMER_STEP) {
        remainingTime -= Config::Timings::TIMER_STEP;
        startTime = millis(); // Reset czasu startu przy każdej zmianie
    }
}

void Timer::startAeroPress() {
    currentState = Config::State::AERO_BLOOMING;
    startTime = millis();
    remainingTime = Config::Timings::BLOOMING_TIME;
    isRunning = true;
    coolingDownReady = false;
}

void Timer::confirmCoolingDown() {
    if (currentState == Config::State::AERO_WAIT_COOLING_DOWN) {
        currentState = Config::State::AERO_COOLING_DOWN;
        startTime = millis();
        remainingTime = Config::Timings::COOLING_TIME;
        coolingDownReady = true;
    }
}

void Timer::stop() {
    currentState = Config::State::IDLE;
    isRunning = false;
    coolingDownReady = false;
}

bool Timer::shouldTransitionToNextState() const {
    if (!isRunning) return false;

    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - startTime;
    
    switch (currentState) {
        case Config::State::TIMER:
            return elapsedTime >= remainingTime;
            
        case Config::State::AERO_BLOOMING:
            return elapsedTime >= Config::Timings::BLOOMING_TIME;
            
        case Config::State::AERO_BREWING:
            return elapsedTime >= Config::Timings::BREWING_TIME;
            
        case Config::State::AERO_PRESSING:
            return elapsedTime >= Config::Timings::PRESSING_TIME;
            
        case Config::State::AERO_COOLING_DOWN:
            return elapsedTime >= Config::Timings::COOLING_TIME;
            
        default:
            return false;
    }
}

void Timer::transitionToNextState() {
    switch (currentState) {
        case Config::State::AERO_BLOOMING:
            currentState = Config::State::AERO_BREWING;
            startTime = millis();
            remainingTime = Config::Timings::BREWING_TIME;
            break;
            
        case Config::State::AERO_BREWING:
            currentState = Config::State::AERO_PRESSING;
            startTime = millis();
            remainingTime = Config::Timings::PRESSING_TIME;
            break;
            
        case Config::State::AERO_PRESSING:
            currentState = Config::State::AERO_WAIT_COOLING_DOWN;
            coolingDownReady = false;
            break;
            
        case Config::State::AERO_COOLING_DOWN:
        case Config::State::TIMER:
            stop();
            break;
            
        default:
            break;
    }
}

void Timer::update() {
    if (currentState == Config::State::IDLE || currentState == Config::State::AERO_WAIT_COOLING_DOWN) {
        return;
    }

    if (shouldTransitionToNextState()) {
        transitionToNextState();
    } else if (isRunning) {
        unsigned long currentTime = millis();
        unsigned long elapsedTime = currentTime - startTime;
        remainingTime = getRemainingTime() - elapsedTime;
    }
}