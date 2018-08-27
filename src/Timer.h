#ifndef Timer_Class
#define Timer_Class

class Timer {
  /* Find out if a timer has expired
    Can drift by 1 msec (use Timer::NoDrift for no drift)
    Can change interval at any time (or leave it)
    Can initialize, or set interval
    Can test & set interval in one call (convenience)
    Automatically restarts for next period (use Timer::OneShot for once)
    Or manually restart (with optional new interval)

    Several Usage Patterns (see examples)

    * SimplePeriodic if your loop is quick enough, or your period can drift
      and you just need to know when a timer has expired
    * ChangePeriodic changing the interval as it goes, based on a potentiometer
    * IntervalAtSetup: if you want to set the interval in setup()
    * ExplicitRestart: for statemachines, or timing from another event

  */

  public:
    // intervals in msec, limited to 65,536 seconds (use Timer::Long for longer)
    int interval; // you can change the interval

    // Set the initial interval at construct time, or later
    Timer() : interval(0),  timer_start(millis()) {}
    Timer(int interval) : interval(interval),  timer_start(millis()) {}

    // The next test will be expired (if interval doesn't change)
    void force_expired() {
      timer_start = millis() - interval;
    }

    // Restart with the current interval
    void restart() {
      timer_start = millis();
      }

    // restart with a new interval
    void restart(int interval) {
      this->interval = interval;
      restart();
    }

    // Has the timer expired?
    // auto-restarts, can drift
    boolean is_expired(); 

    // Has the timer expired against this interval?
    // like above, but interval can be set each time
    boolean is_expired(int interval) {
      this->interval = interval;
      return is_expired();
    }

  private:
    unsigned long timer_start;
};
#endif
