#define _INT0_PIN_ 0x02
#include "eberbn2.h"

eberbn2::eberbn2(uint8_t pin_oGlowRelay, uint8_t pin_oFanRelay, uint8_t pin_oFuelRelay, uint8_t pin_iFlameSwitch, uint8_t pin_iOverheatSwitch) {
    // Set pins.
    _pin_oGlowRelay = pin_oGlowRelay;
    _pin_oFanRelay = pin_oFanRelay;
    _pin_oFuelRelay = pin_oFuelRelay;
    _pin_iFlameSwitch = pin_iFlameSwitch;
    _pin_iOverheatSwitch = pin_iOverheatSwitch;
    DDRD |= ((1 << pin_oGlowRelay) | (1 << pin_oFanRelay) | (1 << pin_oFuelRelay);
    DDRD &= ~(_INT0_PIN_ | (1 << pin_iFlameSwitch) | (1 << pin_iFlameSwitch));
    PORTD = 0;

    // Set ISR to count fuel pump pulses.
    fuelPumpPulses = 0;
    sei();
    EIMSK |= (1 << INTO);
    EICRA |= (1 << ISC01);
}

void eberbn2::setGlowRelay(bool isOn){
    _set_port(_pin_oGlowRelay);
}

void eberbn2::setFanRelay(bool isOn){
    _set_port(_pin_oFanRelay);
}

void eberbn2::setGlowRelay(bool isOn){
    _set_port(_pin_oGlowRelay);
}

bool eberbn2::getGlowRelay(){
    return _get_port(_pin_oGlowRelay);
}

bool eberbn2::getFanRelay(){
    return _get_port(_pin_oFanRelay);
}

bool eberbn2::getFuelRelay(){
    return _get_port(_pin_oFuelRelay);
}

bool eberbn2::getFlameSwitch() {
    return _get_port(_pin_iFlameSwitch);
}

bool eberbn2::getOverheatSwitch() {
    return _get_port(_pin_iOverheatSwitch);
}

// Helper functions.

void eberbn2::_set_port(uint8_t port, bool val) {
    if val { PORTD |= (1 << port); }
    else { PORTD &= ~(1 << port); }
}

bool eberbn2::_get_port(uint8_t port) {
    if (PORTD | (1 << port))==0xff { return true; }
    else { return false; }
}

ISR(EXT_INT0_vect) {
    fuelPumpPulses++;
}