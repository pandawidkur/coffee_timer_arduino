#include "Timer.h"
#include <Arduino.h>

Timer::Timer() : startTime(0), duration(0), isRunning(false) {}

void Timer::start(unsigned long seconds) {
  startTime = millis();
  duration = seconds * 1000;
  isRunning = true;
}

void Timer::stop() {
  isRunning = false;
}

void Timer::addTime(unsigned long seconds) {
  if (isRunning) {
    duration += seconds * 1000;
  }
}

bool Timer::isFinished() {
  if (!isRunning) return false;
  return (millis() - startTime) >= duration;
}

unsigned long Timer::getRemainingSeconds() {
  if (!isRunning) return 0;
  unsigned long elapsed = millis() - startTime;
  if (elapsed >= duration) return 0;
  return (duration - elapsed) / 1000;
} 