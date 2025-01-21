#ifndef BUZZER_H
#define BUZZER_H

class Buzzer {
  private:
    int pin;
    // Nuty z Mario
    static const int NOTE_C6 = 1047;
    static const int NOTE_E6 = 1319;
    static const int NOTE_E7 = 2637;
    static const int NOTE_C7 = 2093;
    static const int NOTE_G6 = 1568;
    static const int NOTE_G7 = 3136;

  public:
    Buzzer(int pin);
    void beep(int duration = 100);
    void beepState();
    void beepWarning();
    void playMarioFinish();
    void playFinishMelody();
    void playWarningSound();
};

#endif 