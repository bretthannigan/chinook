#ifndef statemachine_h
#define statemachine_h
#ifndef NULL
#define NULL 0
#endif

#define _MOVING_AVERAGE_SIZE_ 5

//#include <Arduino.h>
#include "eberbn2.h"
#include "pins.h"

typedef enum { STATE_INITIAL, STATE_STANDBY, STATE_WARMUP, STATE_START, STATE_RUN, STATE_COOLDOWN, STATE_ERROR_COOLDOWN, STATE_ERROR, NUM_STATES } state_t;
typedef enum { ERROR_NONE, ERROR_NOFLAME, ERROR_FLAME, ERROR_OVERHEAT, ERROR_VOLTAGE, NUM_ERRORS } error_t;
typedef struct instance_data {
  eberbn2* heater;
	error_t errorCode;
  uint32_t iState;
  uint16_t lastPulses[_MOVING_AVERAGE_SIZE_] = { 0 }; // Number of fuel pump pulses measured in the last _MOVING_AVERAGE_SIZE_ sample times.
} instance_data_t;
typedef state_t state_func_t(instance_data_t* data);
typedef void transition_func_t(instance_data_t* data);

void onAllStates(instance_data_t* data);
state_t onStateInitial(instance_data_t* data);
state_t onStateStandby(instance_data_t* data);
state_t onStateWarmup(instance_data_t *data);
state_t onStateStart(instance_data_t* data);
state_t onStateRun(instance_data_t* data);
state_t onStateCooldown(instance_data_t* data);
state_t onStateErrorCooldown(instance_data_t* data);
state_t onStateError(instance_data_t* data);
state_t run_state(state_t state, instance_data_t* data);
void onAllTransitions(instance_data_t* data);
void onTransitionStandby(instance_data_t* data);
void onTransitionWarmup(instance_data_t* data);
void onTransitionStart(instance_data_t* data);
void onTransitionRun(instance_data_t* data);
void onTransitionCooldown(instance_data_t* data);
void onTransitionErrorCooldown(instance_data_t* data);
void onTransitionError(instance_data_t* data);

void flashErrorCode(error_t err);

state_func_t* const state_table[NUM_STATES] = {
  onStateInitial, onStateStandby, onStateWarmup, onStateStart, onStateRun, onStateCooldown, onStateErrorCooldown, onStateError
};

transition_func_t* const transition_table[NUM_STATES][NUM_STATES] = {
  // TO:
  //  STATE_INITIAL   	STATE_STANDBY	        STATE_WARMUP       	STATE_START       	STATE_RUN         	STATE_COOLDOWN        STATE_ERROR_COOLDOWN        STATE_ERROR 			    FROM:
  {   NULL,           	onTransitionStandby,  NULL,				        NULL,             	NULL,             	NULL,					        NULL,                       NULL              },	// STATE_INITIAL
  {	  NULL,				      NULL,				          onTransitionWarmup, NULL, 				      NULL,				        NULL, 					      NULL,                       onTransitionError },	// STATE_STANDBY
  {   NULL,           	NULL,                 NULL,			   	      onTransitionStart,	NULL,               NULL, 					      onTransitionErrorCooldown,  NULL              },	// STATE_WARMUP
  {   NULL,           	NULL,                 NULL,               NULL,  				      onTransitionRun,    NULL, 					      onTransitionErrorCooldown,  NULL              },	// STATE_START
  {   NULL,           	NULL,                 NULL,               NULL,             	NULL, 				      onTransitionCooldown, onTransitionErrorCooldown,  NULL              },	// STATE_RUN
  {   NULL,           	onTransitionStandby,  NULL,               NULL,             	NULL,               NULL, 					      onTransitionErrorCooldown,  NULL              },	// STATE_COOLDOWN
  {   NULL,           	NULL,                 NULL,               NULL,             	NULL,               NULL,              		NULL,                       onTransitionError },  // STATE_ERROR_COOLDOWN
  {   NULL,             NULL,                 NULL,               NULL,               NULL,               NULL,                 NULL,                       NULL              }   // STATE_ERROR
};

#endif
