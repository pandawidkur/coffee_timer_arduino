#ifndef TIMER_H
#define TIMER_H

class Timer {
  private:
    unsigned long startTime;
    unsigned long duration;
    bool isRunning;

  public:
    Timer();
    void start(unsigned long seconds);
    void stop();
    void addTime(unsigned long seconds);
    bool isFinished();
    unsigned long getRemainingSeconds();
};

#endif 