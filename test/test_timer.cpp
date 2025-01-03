#include <unity.h>
#include "Timer.h"
#include "mocks/ArduinoMock.h"

Timer timer;

void setUp(void) {
    ArduinoMock::reset();
    timer = Timer(); // Reset timera przed każdym testem
}

void test_initial_state(void) {
    TEST_ASSERT_EQUAL(Config::State::IDLE, timer.getState());
    TEST_ASSERT_EQUAL(0, timer.getRemainingTime());
    TEST_ASSERT_FALSE(timer.isComplete());
}

// Testy dla trybu Timer
void test_timer_mode(void) {
    // Start timera
    timer.startTimer();
    TEST_ASSERT_EQUAL(Config::State::TIMER, timer.getState());
    TEST_ASSERT_EQUAL(Config::Timings::TIMER_STEP, timer.getRemainingTime());
    
    // Zwiększenie czasu
    timer.incrementTimer();
    TEST_ASSERT_EQUAL(Config::Timings::TIMER_STEP * 2, timer.getRemainingTime());
    
    // Zmniejszenie czasu
    timer.decrementTimer();
    TEST_ASSERT_EQUAL(Config::Timings::TIMER_STEP, timer.getRemainingTime());
    
    // Test zakończenia odliczania
    ArduinoMock::advanceMillis(Config::Timings::TIMER_STEP + 100);
    timer.update();
    TEST_ASSERT_TRUE(timer.isComplete());
}

// Testy dla trybu AeroPress
void test_aeropress_mode(void) {
    // Start AeroPress
    timer.startAeroPress();
    TEST_ASSERT_EQUAL(Config::State::AERO_BLOOMING, timer.getState());
    TEST_ASSERT_EQUAL(Config::Timings::BLOOMING_TIME, timer.getRemainingTime());
    
    // Przejście do fazy parzenia
    ArduinoMock::advanceMillis(Config::Timings::BLOOMING_TIME + 100);
    timer.update();
    TEST_ASSERT_EQUAL(Config::State::AERO_BREWING, timer.getState());
    TEST_ASSERT_EQUAL(Config::Timings::BREWING_TIME, timer.getRemainingTime());
    
    // Przejście do fazy wyciskania
    ArduinoMock::advanceMillis(Config::Timings::BREWING_TIME + 100);
    timer.update();
    TEST_ASSERT_EQUAL(Config::State::AERO_PRESSING, timer.getState());
    
    // Przejście do pytania o chłodzenie
    ArduinoMock::advanceMillis(Config::Timings::PRESSING_TIME + 100);
    timer.update();
    TEST_ASSERT_EQUAL(Config::State::AERO_WAIT_COOLING_DOWN, timer.getState());
}

void test_cooling_down_confirmation(void) {
    // Ustawienie stanu oczekiwania na chłodzenie
    timer.startAeroPress();
    ArduinoMock::advanceMillis(Config::Timings::BLOOMING_TIME + 100);
    timer.update();
    ArduinoMock::advanceMillis(Config::Timings::BREWING_TIME + 100);
    timer.update();
    ArduinoMock::advanceMillis(Config::Timings::PRESSING_TIME + 100);
    timer.update();
    
    // Potwierdzenie chłodzenia
    timer.confirmCoolingDown();
    TEST_ASSERT_EQUAL(Config::State::AERO_COOLING_DOWN, timer.getState());
    TEST_ASSERT_EQUAL(Config::Timings::COOLING_TIME, timer.getRemainingTime());
    
    // Zakończenie chłodzenia
    ArduinoMock::advanceMillis(Config::Timings::COOLING_TIME + 100);
    timer.update();
    TEST_ASSERT_EQUAL(Config::State::IDLE, timer.getState());
}

void test_stop_function(void) {
    // Test zatrzymania w różnych stanach
    timer.startTimer();
    timer.stop();
    TEST_ASSERT_EQUAL(Config::State::IDLE, timer.getState());
    
    timer.startAeroPress();
    timer.stop();
    TEST_ASSERT_EQUAL(Config::State::IDLE, timer.getState());
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    
    RUN_TEST(test_initial_state);
    RUN_TEST(test_timer_mode);
    RUN_TEST(test_aeropress_mode);
    RUN_TEST(test_cooling_down_confirmation);
    RUN_TEST(test_stop_function);
    
    UNITY_END();
    return 0;
}