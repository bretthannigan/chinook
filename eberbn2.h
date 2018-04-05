#ifndef eberbn2_h
#define eberbn2_h

#include <avr/io.h>
#include <avr/interrupt.h>

volatile static uint32_t fuelPumpPulses;

class eberbn2 {
    public:
        eberbn2(uint8_t pin_oGlowRelay, uint8_t pin_oFanRelay, uint8_t pin_oFuelRelay, uint8_t pin_iFlameSwitch, uint8_t pin_iOverheatSwitch);
        void set_glowRelay(bool isOn);
        void set_fanRelay(bool isOn);
        void set_fuelRelay(bool isOn);
        bool get_glowRelay();
        bool get_fanRelay();
        bool get_fuelRelay();
        bool get_flameSwitch();
        bool get_overheatSwitch();

    private:
        // Helper functions.
        void _set_port(uint8_t port, bool val);
        bool _get_port(uint8_t port);
        uint8_t _pin_oGlowRelay, _pin_oFanRelay, _pin_oFuelRelay;
        uint8_t _pin_iFlameSwitch, _pin_iOverheatSwitch;
};

#endif