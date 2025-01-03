#include <unity.h>
#include "Display.h"
#include "mocks/DisplayMock.h"

Display display;

void setUp(void) {
    display = Display();
    display.begin();
}

void test_display_initialization(void) {
    TEST_ASSERT_TRUE(display.begin());
}

void test_show_idle(void) {
    display.showIdle();
    auto& commands = display.getLastCommands();
    
    // Sprawdź czy ekran został wyczyszczony
    TEST_ASSERT_EQUAL(Adafruit_SSD1306::DisplayCommand::CLEAR, commands[0].type);
    
    // Sprawdź czy wyświetlony został tekst powitalny
    bool foundTitle = false;
    bool foundStartPrompt = false;
    bool foundAeroPrompt = false;
    
    for(const auto& cmd : commands) {
        if(cmd.type == Adafruit_SSD1306::DisplayCommand::TEXT) {
            if(cmd.text.find("AeroPress Timer") != std::string::npos) foundTitle = true;
            if(cmd.text.find("START - Timer") != std::string::npos) foundStartPrompt = true;
            if(cmd.text.find("AERO  - AeroPress") != std::string::npos) foundAeroPrompt = true;
        }
    }
    
    TEST_ASSERT_TRUE(foundTitle);
    TEST_ASSERT_TRUE(foundStartPrompt);
    TEST_ASSERT_TRUE(foundAeroPrompt);
}

void test_show_timer(void) {
    display.showTimer(30000); // 30 sekund
    auto& commands = display.getLastCommands();
    
    bool foundTitle = false;
    bool foundTime = false;
    
    for(const auto& cmd : commands) {
        if(cmd.type == Adafruit_SSD1306::DisplayCommand::TEXT) {
            if(cmd.text.find("Timer") != std::string::npos) foundTitle = true;
            if(cmd.text.find("00:30") != std::string::npos) foundTime = true;
        }
    }
    
    TEST_ASSERT_TRUE(foundTitle);
    TEST_ASSERT_TRUE(foundTime);
}

void test_show_blooming(void) {
    display.showBlooming(30000);
    auto& commands = display.getLastCommands();
    
    bool foundTitle = false;
    bool foundTime = false;
    
    for(const auto& cmd : commands) {
        if(cmd.type == Adafruit_SSD1306::DisplayCommand::TEXT) {
            if(cmd.text.find("Blooming") != std::string::npos) foundTitle = true;
            if(cmd.text.find("00:30") != std::string::npos) foundTime = true;
        }
    }
    
    TEST_ASSERT_TRUE(foundTitle);
    TEST_ASSERT_TRUE(foundTime);
}

void test_time_formatting(void) {
    // Test różnych formatów czasu
    display.showTimer(65000); // 1:05
    auto& commands1 = display.getLastCommands();
    bool found65sec = false;
    for(const auto& cmd : commands1) {
        if(cmd.type == Adafruit_SSD1306::DisplayCommand::TEXT) {
            if(cmd.text.find("01:05") != std::string::npos) found65sec = true;
        }
    }
    TEST_ASSERT_TRUE(found65sec);
    
    display.showTimer(3600000); // 60:00
    auto& commands2 = display.getLastCommands();
    bool found60min = false;
    for(const auto& cmd : commands2) {
        if(cmd.type == Adafruit_SSD1306::DisplayCommand::TEXT) {
            if(cmd.text.find("60:00") != std::string::npos) found60min = true;
        }
    }
    TEST_ASSERT_TRUE(found60min);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    
    RUN_TEST(test_display_initialization);
    RUN_TEST(test_show_idle);
    RUN_TEST(test_show_timer);
    RUN_TEST(test_show_blooming);
    RUN_TEST(test_time_formatting);
    
    UNITY_END();
    return 0;
}