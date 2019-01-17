#ifndef pins_h
#define pins_h

// Relay outputs.
#define _PIN_O_FAN_RELAY_ D, 5, 5 // PWM
#define _PIN_O_GLOW_RELAY_ B, 0, 0
#define _PIN_O_FUEL_RELAY_ B, 1, 1 // PWM

// LED outputs.
#define _PIN_O_LED_RUN_ C, 3, 3 // Analog pin used as digital output.
#define _PIN_O_LED_ERROR_ D, 4, 4

// Safety switch inputs.
#define _PIN_I_SW_FLAME_ D, 7, 7
#define _PIN_I_SW_OVERHEAT_ D, 6, 6

// Control inputs.
#define _PIN_I_V_SENSE_ C, 2, 2 // Analog
#define _PIN_I_FAN_PULSE_ D, 2, 2 // INT 
#define _PIN_I_EN_ D, 3, 3

// Potentiometer inputs.
#define _PIN_I_POT_0_ C, 0, 0 // Analog
#define _PIN_I_POT_1_ C, 1, 1 // Analog

#endif