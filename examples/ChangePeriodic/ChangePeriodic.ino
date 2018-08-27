// ChangePeriodic
// Use the pot to set the period every time

#include <Timer.h>
Timer OneSecondTic(1000); // initialize interval

const int POT = A0; // wire a pot to A0 as usual

void setup() {
  Serial.begin(9600); 
  // nothing needed for timer
  OneSecondTic.force_expired(); // optional: first test will be expired immediately
}

void loop() {
  // ... quick stuff ... // each msec this takes may cause that much drift

  int pot_value = analogRead(POT); // 0..1024

  // Does not wait for previous interval, uses what you say now
  if ( OneSecondTic.is_expired( pot_value ) ) { // immediately use changing interval
    Serial.print("Expire "); 
    Serial.println(millis()); // watch for drift
    // automatically restarts OneSecondTic for the next interval
  } 
}
