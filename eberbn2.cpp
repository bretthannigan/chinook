#define _INT0_PIN_ 2
#include "eberbn2.h"

eberbn2::eberbn2() {
        
/*     // Set pins.
    _pin_oGlowRelay = pin_oGlowRelay;
    _pin_oFanRelay = pin_oFanRelay;
    _pin_oFuelRelay = pin_oFuelRelay;
    _pin_iFlameSwitch = pin_iFlameSwitch;
    _pin_iOverheatSwitch = pin_iOverheatSwitch;
    _fuelPumpPulses = 0; */

    // Set interrupt for fan pulses.
    EIMSK |= (1 << INT0); // Port D pin 2 (Uno pin 2).
    EICRA |= (1 << ISC01);

}

void eberbn2::set_glowRelay(bool isOn) {
    _pin_oGlowRelay = isOn;
}

void eberbn2::set_fanRelay(bool isOn) {
    _pin_oFanRelay = isOn;
}

void eberbn2::set_fuelRelay(bool isOn) {
    _pin_oFuelRelay = isOn;
}

bool eberbn2::get_flameSwitch() {
    return (bool) _pin_iFlameSwitch;
}

bool eberbn2::get_overheatSwitch() {
    return (bool) _pin_iOverheatSwitch;
}

double eberbn2::get_fuelConsumption() {
    return _fuelPumpPulses*_L_PER_PULSE;
}

void eberbn2::ISR_fuelPumpPulse() {
    _fuelPumpPulses++;
}