// ExplicitRestart
// Start timing from some event

// Every second, read the pot, and start a timer from it's value

#include <Timer.h>
Timer OneSecondTic(1000); // initialize interval
Timer PotControlledTimer; // no-initialize (so it's 0)

const int POT = A0; // wire a pot to A0 as usual
int PotValue;

void setup() {
  Serial.begin(9600); 
  OneSecondTic.force_expired(); // we want to read pot on first loop
}

void loop() {

  // Every second...
  if ( OneSecondTic.is_expired() ) {
    // Read pot, start timer
    PotValue = analogRead(POT); // 0..1024
    Serial.print(millis());
    Serial.print(" Read "); 
    Serial.print( PotValue );
    Serial.println();

    PotControlledTimer.restart( PotValue ); // restart from "now", w/new value
  } 

  // could fire multiple times per second (for small potvalue, or never if pot > 1000)
  if ( PotControlledTimer.is_expired() ) { // interval only changes when we check above every second
    // timer auto restarts
    Serial.print(millis());
    Serial.print(" Pot "); 
    Serial.println();
  }
    
}
