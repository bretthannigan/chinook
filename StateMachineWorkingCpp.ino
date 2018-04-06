extern "C++"{
  #include "statemachine.h"
}
#include <avr/interrupt.h>

state_t cur_state;
instance_data_t cur_data;

void setup() {
  pinMode(13, OUTPUT);

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
  EIMSK |= (1 << INT0);
  EICRA |= (1 << ISC01);

  cur_state = STATE_INITIAL;
  Serial.begin(9600);
  Serial.println("test");
}

void loop() {
}

ISR(TIMER1_COMPA_vect)
{
  cur_state = run_state(cur_state, &cur_data);
}

ISR(INT0_vect) {
  Serial.println("Interrupted.");
  cur_data.heater->ISRtest();
  Serial.println(cur_data.heater->get_fuelConsumption(), DEC);
}