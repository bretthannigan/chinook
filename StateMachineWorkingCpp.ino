extern "C++"{
  #include "statemachine.h"
}

#if false
#include <Arduino.h>
#endif

//#include <Arduino.h>
#include <avr/interrupt.h>

state_t CurrentState;
instance_data_t CurrentData;
volatile uint8_t TimerTicks = 0;
volatile bool IsStateReady = 1;

int main(void) {
  uint8_t timerTicks;
  bool isStateReady;

  // Configure pin modes.
  //Serial.begin(115200);

  cli();
  // Set timer interrupt for sampling rate.
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;
  OCR2A = 60; // for a 256 Hz timer.
  TCCR2A |= (1 << WGM21);
  TCCR2B |= ((1 << CS20) | (1 << CS21) | (1 << CS22)); // 1/1024 pre-scaler.
  TIMSK2 |= (1 << OCIE2A);
  sei();
  // Set external interrupt to count fuel pump pulses.

  CurrentState = STATE_INITIAL;

  while (1) {
    cli();
    timerTicks = TimerTicks;
    isStateReady = IsStateReady;
    sei();
    if ((timerTicks==0) && isStateReady) {
      IsStateReady = false;
      CurrentState = run_state(CurrentState, &CurrentData);
    }
  }
  
  return 0;
}

// Interrupt service routines.

ISR(TIMER2_COMPA_vect)
{
  TimerTicks++;
  IsStateReady = true;
}

ISR(INT0_vect) {
  CurrentData.heater->ISR_fuelPumpPulse();
  CurrentData.lastPulses[CurrentData.iState % _MOVING_AVERAGE_SIZE_]++;
}