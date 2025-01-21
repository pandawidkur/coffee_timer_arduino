#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Display.h"
#include "Buzzer.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Piny
const int GREEN_BTN_PIN = 2;
const int YELLOW_BTN_PIN = 3;
const int RED_BTN_PIN = 4;
const int BUZZER_PIN = 9;
const int LED_PIN = 13;

// Zmienne do debouncingu
unsigned long lastButtonPress = 0;
const unsigned long DEBOUNCE_DELAY = 250; // 250ms między wciśnięciami

// Stany programu
enum ProgramState {
  READY,
  REGULAR_PROGRAM,
  AERO_BLOOMING,
  AERO_BREWING,
  AERO_PRESSING
};

ProgramState currentState = READY;
unsigned long timerStart = 0;
int remainingSeconds = 0;

// Obiekty globalne
Display displayUI;
Buzzer buzzer(BUZZER_PIN);

void updateDisplay(const char* status, int seconds = -1) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println(status);
  
  if (seconds >= 0) {
    display.setCursor(0,16);
    display.print(seconds);
    display.println(" seconds");
  }
  
  display.display();
}

void setup() {
  Serial.begin(9600);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  display.clearDisplay();
  display.display();
  
  pinMode(GREEN_BTN_PIN, INPUT_PULLUP);
  pinMode(YELLOW_BTN_PIN, INPUT_PULLUP);
  pinMode(RED_BTN_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  
  updateDisplay("Ready to go");
  Serial.println("System gotowy");
}

void loop() {
  bool greenPressed = !digitalRead(GREEN_BTN_PIN);
  bool yellowPressed = !digitalRead(YELLOW_BTN_PIN);
  bool redPressed = !digitalRead(RED_BTN_PIN);

  unsigned long currentTime = millis();

  // Debugowanie
  if (greenPressed || yellowPressed || redPressed) {
    Serial.print("Buttons: G:");
    Serial.print(greenPressed);
    Serial.print(" Y:");
    Serial.print(yellowPressed);
    Serial.print(" R:");
    Serial.println(redPressed);
  }

  if ((currentTime - lastButtonPress) >= DEBOUNCE_DELAY) {
    if (greenPressed || yellowPressed || redPressed) {
      lastButtonPress = currentTime;
      
      switch (currentState) {
        case READY:
          if (greenPressed) {
            currentState = REGULAR_PROGRAM;
            remainingSeconds = 30;
            timerStart = currentTime;
            updateDisplay("Regular Program", remainingSeconds); // Używamy prostszej funkcji
            digitalWrite(LED_PIN, HIGH);
            buzzer.beep();
          }
          else if (yellowPressed) {
            currentState = AERO_BLOOMING;
            remainingSeconds = 30;
            timerStart = currentTime;
            updateDisplay("Aero Blooming", remainingSeconds); // Używamy prostszej funkcji
            digitalWrite(LED_PIN, HIGH);
            buzzer.beep();
          }
          break;
          
        case REGULAR_PROGRAM:
          if (greenPressed) {
            remainingSeconds += 30;
            updateDisplay("Regular Program", remainingSeconds);
            Serial.print("Dodano 30s. Pozostalo: ");
            Serial.println(remainingSeconds);
          }
          if (redPressed) {
            if (remainingSeconds > 30) {
              remainingSeconds -= 30;
              updateDisplay("Regular Program", remainingSeconds);
              Serial.print("Odjeto 30s. Pozostalo: ");
              Serial.println(remainingSeconds);
            } else {
              currentState = READY;
              digitalWrite(LED_PIN, LOW);
              updateDisplay("Tasty coffee");
              buzzer.playMarioFinish();
              delay(3000);
              displayUI.showMainMenu(true);
            }
          }
          break;

        case AERO_BLOOMING:
          if (redPressed || remainingSeconds <= 0) {
            currentState = AERO_BREWING;
            remainingSeconds = 90;
            timerStart = currentTime;
            updateDisplay("Aero Blooming", remainingSeconds);
            buzzer.beepState();
          }
          break;

        case AERO_BREWING:
          if (redPressed || remainingSeconds <= 0) {
            currentState = AERO_PRESSING;
            remainingSeconds = 20;
            timerStart = currentTime;
            updateDisplay("Aero Brewing", remainingSeconds);
            buzzer.beepState();
          }
          break;

        case AERO_PRESSING:
          if (redPressed || remainingSeconds <= 0) {
            currentState = READY;
            digitalWrite(LED_PIN, LOW);
            updateDisplay("Tasty coffee");
            buzzer.playMarioFinish();
            delay(3000);
            displayUI.showMainMenu(true);
          }
          break;
      }
    }
  }

  // Aktualizacja timera
  if (currentState != READY) {
    int elapsed = (currentTime - timerStart) / 1000;
    if (elapsed >= 1) {
      remainingSeconds--;
      timerStart = currentTime;
      
      if (remainingSeconds <= 3 && remainingSeconds > 0) {
        buzzer.beepWarning();
      }
      
      // Używamy prostszej funkcji wyświetlania
      switch (currentState) {
        case REGULAR_PROGRAM:
          updateDisplay("Regular Program", remainingSeconds);
          break;
        case AERO_BLOOMING:
          updateDisplay("Aero Blooming", remainingSeconds);
          break;
        case AERO_BREWING:
          updateDisplay("Aero Brewing", remainingSeconds);
          break;
        case AERO_PRESSING:
          updateDisplay("Aero Pressing", remainingSeconds);
          break;
      }
    }
  }

  delay(50);
}