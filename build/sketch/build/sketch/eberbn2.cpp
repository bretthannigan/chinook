#define _INT0_PIN_ 2
#include "eberbn2.h"
#include "pinIO.h"

pin_t<B, 5> test(input);
pin_t<B, 4> test2(input);

eberbn2::eberbn2(uint8_t pin_oGlowRelay, uint8_t pin_oFanRelay, uint8_t pin_oFuelRelay, uint8_t pin_iFlameSwitch, uint8_t pin_iOverheatSwitch) {
        
    // Set pins.
    _pin_oGlowRelay = pin_oGlowRelay;
    _pin_oFanRelay = pin_oFanRelay;
    _pin_oFuelRelay = pin_oFuelRelay;
    _pin_iFlameSwitch = pin_iFlameSwitch;
    _pin_iOverheatSwitch = pin_iOverheatSwitch;
    _fuelPumpPulses = 0;
    volatile uint8_t* test = &PORTD ;

    //gpio_conf(SINGLE_ARG(_port_oGlowRelay, _pin_oGlowRelay, _pin_oGlowRelay), OUTPUT, 0);
    // gpio_conf1(_port_oFanRelay, _pin_oFanRelay, OUTPUT, 0);
    // gpio_conf1(_port_oFuelRelay, _pin_oFuelRelay, OUTPUT, 0);
    // gpio_conf1(_port_iFlameSwitch, _pin_iFlameSwitch, INPUT, NOPULLUP);
    // gpio_conf1(_port_iOverheatSwitch, _pin_iOverheatSwitch, INPUT, NOPULLUP);

    // Set interrupt for fan pulses.
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC01);

    // Set PWM.

}

void eberbn2::set_glowRelay(bool isOn) {
    _set_port(_pin_oGlowRelay, isOn);
}

void eberbn2::set_fanRelay(bool isOn) {
    _set_port(_pin_oFanRelay, isOn);
}

void eberbn2::set_fuelRelay(bool isOn) {
    _set_port(_pin_oFuelRelay, isOn);
}

bool eberbn2::get_glowRelay() {
    return _get_port(_pin_oGlowRelay);
}

bool eberbn2::get_fanRelay() {
    return _get_port(_pin_oFanRelay);
}

bool eberbn2::get_fuelRelay() {
    return _get_port(_pin_oFuelRelay);
}

bool eberbn2::get_flameSwitch() {
    return _get_port(_pin_iFlameSwitch);
}

bool eberbn2::get_overheatSwitch() {
    return _get_port(_pin_iOverheatSwitch);
}

// Helper functions.

void eberbn2::_set_port(uint8_t pin, bool val) {

}

bool eberbn2::_get_port(uint8_t pin) {
    #define test D, 1, 1
    return gpio_rd(PORT, test);
}

double eberbn2::get_fuelConsumption() {
    return _fuelPumpPulses*_L_PER_PULSE;
}

void eberbn2::ISR_fuelPumpPulse() {
    _fuelPumpPulses++;
}