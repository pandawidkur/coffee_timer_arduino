#pragma once

// Mock dla funkcji Arduino
class ArduinoMock {
private:
    static unsigned long currentMillis;
    static int pinStates[20];  // Zakładamy max 20 pinów

public:
    static void reset() {
        currentMillis = 0;
        for(int i = 0; i < 20; i++) {
            pinStates[i] = HIGH;  // Domyślny stan dla pull-up
        }
    }

    static void setMillis(unsigned long millis) {
        currentMillis = millis;
    }

    static void advanceMillis(unsigned long delta) {
        currentMillis += delta;
    }

    static void setPinState(uint8_t pin, int state) {
        pinStates[pin] = state;
    }

    static int getPinState(uint8_t pin) {
        return pinStates[pin];
    }
};

// Implementacje funkcji Arduino
unsigned long millis() {
    return ArduinoMock::currentMillis;
}

void pinMode(uint8_t pin, uint8_t mode) {
    // Symulacja konfiguracji pinu
}

int digitalRead(uint8_t pin) {
    return ArduinoMock::getPinState(pin);
}

void digitalWrite(uint8_t pin, uint8_t val) {
    ArduinoMock::setPinState(pin, val);
}

void delay(unsigned long ms) {
    ArduinoMock::advanceMillis(ms);
}