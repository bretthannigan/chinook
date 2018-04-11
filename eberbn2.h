#ifndef eberbn2_h
#define eberbn2_h

#include <avr/io.h>

extern "C" void INT0_vect() __attribute__ ((signal)); // Allow ISR access to class methods. Source: http://cosa-arduino.blogspot.ca/2013/03/object-oriented-interrupt-handling.html

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
        double get_fuelConsumption();

    private:
        // Helper functions.
        void _set_port(uint8_t port, bool val);
        bool _get_port(uint8_t port);
        uint8_t _pin_oGlowRelay, _pin_oFanRelay, _pin_oFuelRelay;
        uint8_t _pin_iFlameSwitch, _pin_iOverheatSwitch;
        uint32_t _fuelPumpPulses;
        constexpr static double _L_PER_PULSE = 0.00003125; // 6.25 cc per 200 strokes. Source: http://shoptalkforums.com/viewtopic.php?t=113760#top
        friend void INT0_vect(void);
        void ISR_fuelPumpPulse();
};

#endif