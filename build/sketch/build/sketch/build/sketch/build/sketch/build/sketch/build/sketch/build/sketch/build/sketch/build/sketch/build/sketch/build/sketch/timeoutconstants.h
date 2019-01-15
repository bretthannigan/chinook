#ifndef timeoutconstants_h
#define timeoutconstants_h

#include <stdint.h>

static const uint16_t SAMPLE_TIME_MS = 1000;

// State Transitions
static const uint32_t TIMEOUT_STATE_WARMUP_MS = 5000;
static const uint32_t TIMEOUT_STATE_START_MS = 240000; // http://www.veewee.net/Eber/eber_ucontrolled_eng.htm
static const uint32_t TIMEOUT_STATE_COOLDOWN_MS = 180000; // Eberspacher BN2 Manual: for 20 degrees C ambient temperature.

#endif