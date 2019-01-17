#include "statemachine.h"

/* I/O Pins */

pin_t<C, 3> pin_oFanLED = pin_t<C, 3>(OUTPUT);
pin_t<C, 2> pin_oGlowLED = pin_t<C, 2>(OUTPUT);
pin_t<C, 1> pin_oErrorLED = pin_t<C, 1>(OUTPUT);

/* State Functions */

void onAllStates(instance_data_t *data) {
  //Serial.println("On all states");
  data->iState++;
}

state_t onStateInitial(instance_data_t *data) {
  //Serial.println("Initial state");
  data->iState = 0;
  data->heater = new eberbn2();
  // Initialize pins. Heater interface pins are taken care of by eberbn2 class.
  data->errorCode = ERROR_NONE;
  return STATE_STANDBY;
}

state_t onStateStandby(instance_data_t *data) {
  //Serial.println("Standby state");
  if (data->heater->get_overheatSwitch()) {
    data->errorCode = ERROR_OVERHEAT;
    return STATE_ERROR_COOLDOWN;
  } else if (data->heater->get_flameSwitch()) {
    data->errorCode = ERROR_FLAME;
    return STATE_ERROR_COOLDOWN;
  // } else if (isPowerOn) {
  //   return STATE_WARMUP;
  } else { 
    return STATE_STANDBY;
  }
}

state_t onStateWarmup(instance_data_t *data) {
  //Serial.println("Warmup state");
  if (data->iState*SAMPLE_TIME_MS > TIMEOUT_STATE_WARMUP_MS) {
    return STATE_START;
  } else {
    return STATE_WARMUP;
  }
}

state_t onStateStart(instance_data_t *data) {
  //Serial.println("Start state");
  if (data->heater->get_overheatSwitch()) {
    data->errorCode = ERROR_OVERHEAT;
    return STATE_ERROR_COOLDOWN;
  } else if (data->heater->get_flameSwitch()) {
    return STATE_RUN;
  } else if (data->iState*SAMPLE_TIME_MS > TIMEOUT_STATE_START_MS) {
    data->errorCode = ERROR_NOFLAME;
    return STATE_ERROR_COOLDOWN;
  } else {
    return STATE_START;
  }
}

state_t onStateRun(instance_data_t *data) {
  if (data->heater->get_overheatSwitch()) {
    data->errorCode = ERROR_OVERHEAT;
    return STATE_ERROR_COOLDOWN;
  } else if (~data->heater->get_flameSwitch()) {
    data->errorCode = ERROR_NOFLAME;
    return STATE_ERROR_COOLDOWN;
  // } else if (~isPowerOn) {
  //   return STATE_COOLDOWN;
  } else {
    return STATE_RUN;
  }
}

state_t onStateCooldown(instance_data_t *data) {
  if (data->heater->get_flameSwitch()) {
    data->errorCode = ERROR_NOFLAME;
    return STATE_ERROR_COOLDOWN;
  } else if (data->iState*SAMPLE_TIME_MS > TIMEOUT_STATE_COOLDOWN_MS) {
    if (data->heater->get_flameSwitch()) {
      data->errorCode = ERROR_FLAME;
      return STATE_ERROR_COOLDOWN;
    } else {
      return STATE_STANDBY;
    }
  } else {
    return STATE_COOLDOWN;
  }
}

state_t onStateErrorCooldown(instance_data_t *data) {
  flashErrorCode(data->errorCode);
  if (data->iState*SAMPLE_TIME_MS > TIMEOUT_STATE_COOLDOWN_MS) {
    return STATE_ERROR_COOLDOWN;
  } else {
    return STATE_ERROR;
  }
}

state_t onStateError(instance_data_t *data) {
  flashErrorCode(data->errorCode);
  return STATE_ERROR;
}

/* State Transition Functions */

void onAllTransitions(instance_data_t *data) {
  data->iState = 0;
}

void onTransitionStandby(instance_data_t *data) {
  data->heater->set_fuelRelay(0);
  data->heater->set_fanRelay(0);
  data->heater->set_glowRelay(0);
}

void onTransitionWarmup(instance_data_t *data) {
  data->heater->set_fuelRelay(0);
  data->heater->set_fanRelay(0);
  data->heater->set_glowRelay(1);
}

void onTransitionStart(instance_data_t *data) {
  data->heater->set_fuelRelay(1);
  data->heater->set_fanRelay(1);
  data->heater->set_glowRelay(1);
}

void onTransitionRun(instance_data_t *data) {
  data->heater->set_fuelRelay(1);
  data->heater->set_fanRelay(1);
  data->heater->set_glowRelay(0);
}

void onTransitionCooldown(instance_data_t *data) {
  data->heater->set_fuelRelay(0);
  data->heater->set_fanRelay(1);
  data->heater->set_glowRelay(0);
}

void onTransitionErrorCooldown(instance_data_t *data) {
  data->heater->set_fuelRelay(0);
  data->heater->set_fanRelay(1);
  data->heater->set_glowRelay(0);
}

void onTransitionError(instance_data_t *data) {
  data->heater->set_fuelRelay(0);
  data->heater->set_fanRelay(0);
  data->heater->set_glowRelay(0);
}

/* State Transition Mechanism */

state_t run_state(state_t current_state, instance_data_t *data) {
  onAllStates(data);
  state_t new_state = state_table[current_state][new_state](data);
  transition_func_t* transition = transition_table[current_state][new_state];
  if(transition) {
    onAllTransitions(data);
    transition(data);
  }
  return new_state;
}

/* Helper Functions */

void flashErrorCode(error_t err) {
  static uint16_t iFlash = 0;
  if (iFlash%(NUM_ERRORS << 1)<(err << 1)) {
    pin_oErrorLED = iFlash%2;
    //gpio_wr(PIN, _PIN_O_LED_ERROR_, iFlash%2);
  } else {
    pin_oErrorLED = false;
  }
  iFlash++;
}