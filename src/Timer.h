#ifndef Timer_Class
#define Timer_Class

// "Every" class can take lambdas, has more variations

class Timer {
  /* Find out if a timer has expired
    Intervals in msec, up to 65,536 seconds (use Timer::Long for longer)
    Can drift by 1 msec (use Timer::NoDrift for no drift)
    Can change interval at any time (or leave it)
    Can initialize, or set interval
    Can test & set interval in one call (convenience)
    Automatically restarts for next period (use Timer::OneShot for once)
    Or manually restart (with optional new interval)

    To use this with > 32767 seconds, you have to include a 'U':
      SomeTimer.interval = 40000U;
    Or a variable of type "unsigned int"

    Several Usage Patterns (see examples)

    * SimplePeriodic if your loop is quick enough, or your period can drift
      and you just need to know when a timer has expired
    * ChangePeriodic changing the interval as it goes, based on a potentiometer
    * IntervalAtSetup: if you want to set the interval in setup()
    * ExplicitRestart: for statemachines, or timing from another event

  */

  public:
    // intervals in msec, limited to 65,536 seconds (use Timer::Long for longer)
    unsigned int interval; // you can change the interval

    // Set the initial interval at construct time, or later
    Timer() : interval(0),  timer_start(millis()) {}
    Timer(int interval) : interval(interval),  timer_start(millis()) {}

    // The next test will be expired (if interval doesn't change)
    virtual void force_expired() {
      timer_start = millis() - interval;
    }

    // Restart with the current interval
    virtual void restart() {
      timer_start = millis();
      }

    // restart with a new interval
    void restart(int interval) {
      // we rely on this order:
      restart();
      this->interval = interval;
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

  public:

    class NoDrift {
      // Use this if you want to maintain synchronization with something else that is clock-periodic.
      // Same as Timer, but the interval is from when we should have expired.
      // Even if we don't check exactly on the expiry msec.
      // So, we don't drift (though we can't gaurantee expiry on the exact msec).
      // If is_expired() isn't checked in _at least_ the interval, we can miss an expiration (or several)
      // Substitable for Timer

    // we need to adjust all updates of timer_start to reflect when it would have expired

    void force_expired() {
      // even if we've lost several intervals, stay on period
      while timer_start < millis + interval*2 // do this for all of these
        probably can do math to do this
        timer_start = timer_start - interval;
    }

    // Restart with the current interval
    void restart() {
      timer_start = timer_start + interval;
      }

    // void restart(int interval) // will work, because of internal order

    boolean is_expired();  rewrite

};
#endif
