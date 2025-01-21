#include "Button.h"
#include <Arduino.h>

Button::Button(int pin) : pin(pin), lastState(false), lastDebounceTime(0), currentState(false) {
  pinMode(pin, INPUT_PULLUP);
}

void Button::update() {
  bool reading = !digitalRead(pin);  // Odwracamy wartość bo używamy INPUT_PULLUP
  
  if (reading != lastState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    if (reading != currentState) {
      currentState = reading;
    }
  }
  
  lastState = reading;
}

bool Button::isPressed() {
  return currentState;
}

bool Button::wasPressed() {
  static bool previousState = false;
  bool result = currentState && !previousState;
  previousState = currentState;
  return result;
}