#include <unity.h>
#include "ButtonHandler.h"
#include "mocks/ArduinoMock.h"

ButtonHandler buttons;

void setUp(void) {
    ArduinoMock::reset();
    buttons.begin();
}

void test_button_not_pressed_initially(void) {
    TEST_ASSERT_FALSE(buttons.isStartPressed());
    TEST_ASSERT_FALSE(buttons.isAeroPressed());
    TEST_ASSERT_FALSE(buttons.isStopPressed());
}

void test_start_button_single_press(void) {
    // Symulacja naciśnięcia przycisku (LOW dla pull-up)
    ArduinoMock::setPinState(Config::START_BUTTON, LOW);
    
    // Pierwszy odczyt powinien wykryć naciśnięcie
    TEST_ASSERT_TRUE(buttons.isStartPressed());
    
    // Kolejny odczyt nie powinien wykryć naciśnięcia (debouncing)
    TEST_ASSERT_FALSE(buttons.isStartPressed());
    
    // Zwolnienie przycisku
    ArduinoMock::setPinState(Config::START_BUTTON, HIGH);
    TEST_ASSERT_FALSE(buttons.isStartPressed());
}

void test_button_debouncing(void) {
    // Naciśnięcie przycisku
    ArduinoMock::setPinState(Config::START_BUTTON, LOW);
    TEST_ASSERT_TRUE(buttons.isStartPressed());
    
    // Próba odczytu przed upływem czasu debouncing
    ArduinoMock::advanceMillis(100); // mniej niż BUTTON_DEBOUNCE
    TEST_ASSERT_FALSE(buttons.isStartPressed());
    
    // Odczyt po upływie czasu debouncing
    ArduinoMock::advanceMillis(Config::Timings::BUTTON_DEBOUNCE);
    TEST_ASSERT_FALSE(buttons.isStartPressed()); // Nadal false bo przycisk nie został zwolniony
    
    // Zwolnienie i ponowne naciśnięcie
    ArduinoMock::setPinState(Config::START_BUTTON, HIGH);
    ArduinoMock::advanceMillis(Config::Timings::BUTTON_DEBOUNCE);
    ArduinoMock::setPinState(Config::START_BUTTON, LOW);
    TEST_ASSERT_TRUE(buttons.isStartPressed());
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    
    RUN_TEST(test_button_not_pressed_initially);
    RUN_TEST(test_start_button_single_press);
    RUN_TEST(test_button_debouncing);
    
    UNITY_END();
    return 0;
}