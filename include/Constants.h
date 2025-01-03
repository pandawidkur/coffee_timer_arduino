#pragma once

namespace Config {
    // Pin definitions
    constexpr int START_BUTTON = 2;
    constexpr int AERO_BUTTON = 3;
    constexpr int STOP_BUTTON = 4;
    constexpr int BUZZER_PIN = 13;

    // Display configuration
    constexpr int SCREEN_WIDTH = 128;
    constexpr int SCREEN_HEIGHT = 32;
    constexpr int OLED_RESET = -1;
    constexpr uint8_t OLED_ADDRESS = 0x3C;

    // Timing constants (in milliseconds)
    namespace Timings {
        // Button configuration
        constexpr unsigned long BUTTON_DEBOUNCE = 200;
        
        // Timer steps duration
        constexpr unsigned long BLOOMING_TIME = 30000;    // 30 seconds
        constexpr unsigned long BREWING_TIME = 90000;     // 90 seconds
        constexpr unsigned long PRESSING_TIME = 20000;    // 20 seconds
        constexpr unsigned long COOLING_TIME = 180000;    // 3 minutes
        
        // Timer increment/decrement step
        constexpr unsigned long TIMER_STEP = 30000;       // 30 seconds
        
        // Display timings
        constexpr unsigned long MESSAGE_DISPLAY_TIME = 5000; // 5 seconds
        constexpr unsigned long FINAL_MESSAGE_TIME = 10000;  // 10 seconds
    }

    // Program states
    enum class State {
        IDLE,           // Urządzenie oczekuje na wybór programu
        TIMER,          // Zwykły timer
        AERO_BLOOMING,  // AeroPress - faza bloomingu
        AERO_BREWING,   // AeroPress - faza parzenia
        AERO_PRESSING,  // AeroPress - faza wyciskania kawy
        AERO_WAIT_COOLING_DOWN,  // AeroPress - oczekiwanie na decyzję o chłodzeniu
        AERO_COOLING_DOWN        // AeroPress - faza chłodzenia
    };
}