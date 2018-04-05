extern "C++"{
  #include "statemachine.h"
}

state_t cur_state;
instance_data_t cur_data;

void setup() {
  pinMode(13, OUTPUT);

  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = 15624;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= ((1 << CS10) | (1 << CS12));
  TIMSK1 |= (1 << OCIE1A);
  sei();

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