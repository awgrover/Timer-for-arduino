// SimplePeriodic
// if your loop is quick enough, or your period can drift
// and you just need to know when a timer has expired

#include <Timer.h>
Timer OneSecondTic; // initialize interval to 0, so better set it in setup()...

void setup() {
  Serial.begin(9600); 
  OneSecondTic.interval = random(200, 600); // some value available at run-time
  OneSecondTic.force_expired(); // optional: first test will be expired immediately
}

void loop() {
  // ... quick stuff ... // each msec this takes may cause that much drift

  if ( OneSecondTic.is_expired() ) {
    Serial.print("Expire "); 
    Serial.println(millis()); // watch for drift
    // automatically restarts OneSecondTic for the next interval
  } 
}
