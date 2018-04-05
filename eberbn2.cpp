#define _INT0_PIN_ 2
#include "eberbn2.h"

eberbn2::eberbn2(uint8_t pin_oGlowRelay, uint8_t pin_oFanRelay, uint8_t pin_oFuelRelay, uint8_t pin_iFlameSwitch, uint8_t pin_iOverheatSwitch) {
    // Set pins.
    _pin_oGlowRelay = pin_oGlowRelay;
    _pin_oFanRelay = pin_oFanRelay;
    _pin_oFuelRelay = pin_oFuelRelay;
    _pin_iFlameSwitch = pin_iFlameSwitch;
    _pin_iOverheatSwitch = pin_iOverheatSwitch;
    DDRD = 0;
    DDRD |= (1 << pin_oGlowRelay) | (1 << pin_oFanRelay) | (1 << pin_oFuelRelay);
    DDRD &= ~((1 << _INT0_PIN_) | (1 << pin_iFlameSwitch) | (1 << pin_iFlameSwitch));
    PORTD = 0;

    // // Set ISR to count fuel pump pulses.
    // fuelPumpPulses = 0;
    // sei();
    // EIMSK |= (1 << INT0);
    // EICRA |= (1 << ISC01);
}

void eberbn2::set_glowRelay(bool isOn){
    _set_port(_pin_oGlowRelay, isOn);
}

void eberbn2::set_fanRelay(bool isOn){
    _set_port(_pin_oFanRelay, isOn);
}

void eberbn2::set_fuelRelay(bool isOn){
    _set_port(_pin_oFuelRelay, isOn);
}

bool eberbn2::get_glowRelay(){
    return _get_port(_pin_oGlowRelay);
}

bool eberbn2::get_fanRelay(){
    return _get_port(_pin_oFanRelay);
}

bool eberbn2::get_fuelRelay(){
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
    if (val) { PORTD |= (1 << pin); }
    else { PORTD &= ~(1 << pin); }
}

bool eberbn2::_get_port(uint8_t pin) {
    if (PIND & (1 << pin)) { return true; }
    else { return false; }
}

// ISR(EXT_INT0_vect) {
//     fuelPumpPulses++;
// }