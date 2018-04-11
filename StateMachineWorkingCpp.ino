extern "C++"{
  #include "statemachine.h"
}
#include <avr/interrupt.h>

state_t cur_state;
instance_data_t cur_data;

int main(void) {
  // Configure pin modes.
  

  cli();
  // Set timer interrupt for sampling rate.
  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = 15624;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= ((1 << CS10) | (1 << CS12));
  TIMSK1 |= (1 << OCIE1A);
  sei();
  // Set external interrupt to count fuel pump pulses.


  cur_state = STATE_INITIAL;

  while (1) {

  }
  return 0;
}

// Interrupt service routines.

ISR(TIMER1_COMPA_vect)
{
  cur_state = run_state(cur_state, &cur_data);
}

ISR(INT0_vect) {
  cur_data.heater->ISR_fuelPumpPulse();
  cur_data.lastPulses[cur_data.iState % _MOVING_AVERAGE_SIZE_]++;
}