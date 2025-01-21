#include "Buzzer.h"
#include <Arduino.h>

Buzzer::Buzzer(int pin) : pin(pin) {
  pinMode(pin, OUTPUT);
}

void Buzzer::beep(int duration) {
  tone(pin, 2000, duration);
}

void Buzzer::beepState() {
  tone(pin, 2500, 150);
}

void Buzzer::beepWarning() {
  tone(pin, 3000, 50);
}

void Buzzer::playFinishMelody() {
  tone(pin, NOTE_C6, 150);
  delay(200);
  tone(pin, NOTE_E6, 150);
  delay(200);
  tone(pin, NOTE_G6, 150);
  delay(200);
  tone(pin, NOTE_C6, 300);
  delay(300);
}

void Buzzer::playWarningSound() {
  tone(pin, 3000, 50);
}

void Buzzer::playMarioFinish() {
  // Prosta melodia Mario
  tone(pin, NOTE_G6, 150);
  delay(150);
  tone(pin, NOTE_C6, 150);
  delay(150);
  tone(pin, NOTE_E6, 150);
  delay(150);
  tone(pin, NOTE_G6, 300);
  delay(300);
} 