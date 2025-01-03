#include "Display.h"

Display::Display() 
    : display(Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT, &Wire, Config::OLED_RESET) {
}

bool Display::begin() {
    // Inicjalizacja wyświetlacza
    if(!display.begin(SSD1306_SWITCHCAPVCC, Config::OLED_ADDRESS)) {
        return false;
    }
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    return true;
}

void Display::formatTime(unsigned long milliseconds, char* buffer) {
    unsigned long seconds = milliseconds / 1000;
    unsigned long minutes = seconds / 60;
    seconds = seconds % 60;
    
    // Format: MM:SS
    sprintf(buffer, "%02lu:%02lu", minutes, seconds);
}

void Display::clearAndSetCursor() {
    display.clearDisplay();
    display.setCursor(0, 0);
}

void Display::showIdle() {
    clearAndSetCursor();
    display.println("Minutnik");
    display.println("");
    display.println("Minutnik czy AeroPress");

}

void Display::showTimer(unsigned long remainingTime) {
    clearAndSetCursor();
    display.println("Minutnik");
    
    char timeBuffer[6];
    formatTime(remainingTime, timeBuffer);
    
    display.setTextSize(2);
    display.setCursor(30, 16);
    display.print(timeBuffer);
    display.setTextSize(1);
    display.display();
}

void Display::showBlooming(unsigned long remainingTime) {
    clearAndSetCursor();
    display.println("AeroPress - Blooming");
    
    char timeBuffer[6];
    formatTime(remainingTime, timeBuffer);
    
    display.setTextSize(2);
    display.setCursor(30, 16);
    display.print(timeBuffer);
    display.setTextSize(1);
    display.display();
}

void Display::showBrewing(unsigned long remainingTime) {
    clearAndSetCursor();
    display.println("AeroPress - Brewing");
    
    char timeBuffer[6];
    formatTime(remainingTime, timeBuffer);
    
    display.setTextSize(2);
    display.setCursor(30, 16);
    display.print(timeBuffer);
    display.setTextSize(1);
    display.display();
}

void Display::showPressing(unsigned long remainingTime) {
    clearAndSetCursor();
    display.println("AeroPress - Pressing");
    
    char timeBuffer[6];
    formatTime(remainingTime, timeBuffer);
    
    display.setTextSize(2);
    display.setCursor(30, 16);
    display.print(timeBuffer);
    display.setTextSize(1);
    display.display();
}

void Display::showCoolingDownPrompt() {
    clearAndSetCursor();
    display.println("Chcesz wytudzić kawę?");
    display.println("");
    display.println("Tak/Nie");
    display.display();
}

void Display::showCoolingDown(unsigned long remainingTime) {
    clearAndSetCursor();
    display.println("Stygnięcie");
    
    char timeBuffer[6];
    formatTime(remainingTime, timeBuffer);
    
    display.setTextSize(2);
    display.setCursor(30, 16);
    display.print(timeBuffer);
    display.setTextSize(1);
    display.display();
}

void Display::showComplete() {
    clearAndSetCursor();
    display.println("GOTOWE");
    display.println("");
    display.println("Smacznej kawusi!");
    display.display();
}

void Display::clear() {
    display.clearDisplay();
    display.display();
}