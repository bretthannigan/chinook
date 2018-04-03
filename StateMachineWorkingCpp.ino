extern "C++"{
  #include "statemachine.h"
}



void setup() {
  state_t cur_state = STATE_INITIAL;
  instance_data_t cur_data;
}

void loop() {
  cur_state = run_state(cur_state, &cur_data);
}
