#include "Arduino.h"
#include "statemachine.h"
#include "timeoutconstants.h"

/* State Functions */

state_t onStateInitial(instance_data_t *data) {
  return STATE_WARMUP;
}

state_t onStateWarmup(instance_data_t *data) {
  return STATE_START;
}

state_t onStateStart(instance_data_t *data) {
  return STATE_RUN;
}

state_t onStateRun(instance_data_t *data) {
 return STATE_COOLDOWN;
}

state_t onStateCooldown(instance_data_t *data) {
 return STATE_ERROR;
}

state_t onStateError(instance_data_t *data) {
  return STATE_ERROR;
}

/* State Transition Functions */

void onTransitionInitial(instance_data_t *data) {

}

void onTransitionWarmup(instance_data_t *data) {

}

void onTransitionStart(instance_data_t *data) {

}

void onTransitionRun(instance_data_t *data) {

}

void onTransitionCooldown(instance_data_t *data) {

}

void onTransitionError(instance_data_t *data) {

}

/* State Transition Mechanism */

state_t run_state(state_t current_state, instance_data_t *data) {
  state_t new_state = state_table[current_state][new_state](data);
  transition_func_t *transition = transition_table[cur_state][new_state];
  if(transition) {
    transition(data);
  }
  return new_state;
}
