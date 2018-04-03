#ifndef statemachine_h
#define statemachine_h

#include "Arduino.h"

typedef enum { STATE_INITIAL, STATE_WARMUP, STATE_START, STATE_RUN, STATE_COOLDOWN, STATE_ERROR, NUM_STATES } state_t;
typedef struct instance_data {} instance_data_t;
typedef state_t state_func_t(instance_data_t* data);
typedef void transition_func_t(instance_data_t* data);
//state_t cur_state;
//instance_data_t cur_data;

state_t onStateInitial(instance_data_t* data);
state_t onStateWarmup(instance_data_t *data);
state_t onStateStart(instance_data_t* data);
state_t onStateRun(instance_data_t* data);
state_t onStateCooldown(instance_data_t* data);
state_t onStateError(instance_data_t* data);
state_t run_state(state_t state, instance_data_t* data);
void onTransitionInitial(instance_data_t* data);
void onTransitionWarmup(instance_data_t* data);
void onTransitionStart(instance_data_t* data);
void onTransitionRun(instance_data_t* data);
void onTransitionCooldown(instance_data_t* data);
void onTransitionError(instance_data_t* data);

state_func_t* const state_table[NUM_STATES] = {
  do_state_initial, do_state_warmup, do_state_start, do_state_run, do_state_cooldown, do_state_error
};

transition_func_t* const transition_table[NUM_STATES][NUM_STATES] = {
  // TO:
  //  STATE_INITIAL   STATE_WARMUP          STATE_START         STATE_RUN         STATE_COOLDOWN        STATE_ERROR
  {   NULL,           onTransitionWarmup,   NULL,               NULL,             NULL,                 onTransitionError },
  {   NULL,           NULL,                 onTransitionStart   NULL,             NULL,                 onTransitionError },
  {   NULL,           NULL,                 NULL,               onTransitionRun,  NULL,                 onTransitionError },
  {   NULL,           NULL,                 NULL,               NULL,             onTransitionCooldown, onTransitionError },
  {   NULL,           NULL,                 NULL,               NULL,             NULL,                 onTransitionError },
  {   NULL,           NULL,                 NULL,               NULL,             NULL,                 NULL              }
}

#endif
