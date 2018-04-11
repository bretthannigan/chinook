#ifndef pins_h
#define pins_h

// Relay outputs.
#define _PIN_O_FAN_RELAY_ 5 // PWM
#define _PIN_O_GLOW_RELAY_ 8
#define _PIN_O_FUEL_RELAY_ 9 // PWM

// LED outputs.
#define _PIN_O_LED_RUN_ A3 // Analog pin used as digital output.
#define _PIN_O_LED_ERROR_ 4

// Safety switch inputs.
#define _PIN_I_SW_FLAME_ 7
#define _PIN_I_SW_OVERHEAT_ 6

// Control inputs.
#define _PIN_I_V_SENSE_ 2 // Analog
#define _PIN_I_FAN_PULSE_ 2 // INT 
#define _PIN_I_EN_ 3

// Potentiometer inputs.
#define _PIN_I_POT_0_ 0 // Analog
#define _PIN_I_POT_1_ 1 // Analog

#endif