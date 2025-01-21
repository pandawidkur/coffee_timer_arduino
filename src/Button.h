#ifndef BUTTON_H
#define BUTTON_H

class Button {
  private:
    int pin;
    bool lastState;
    unsigned long lastDebounceTime;
    static const unsigned long DEBOUNCE_DELAY = 50;
    bool currentState;

  public:
    Button(int pin);
    void update();
    bool isPressed();
    bool wasPressed();
};

#endif 