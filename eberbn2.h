#ifndef eberbn2_h
#define eberbn2_h

#include <avr/io.h>
#include "pinIO.h"

extern "C" void INT0_vect() __attribute__ ((signal)); // Allow ISR access to class methods. Source: http://cosa-arduino.blogspot.ca/2013/03/object-oriented-interrupt-handling.html

class eberbn2 {
    public:
        eberbn2();
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
        uint32_t _fuelPumpPulses;
        constexpr static double _L_PER_PULSE = 0.00003125; // 6.25 cc per 200 strokes. Source: http://shoptalkforums.com/viewtopic.php?t=113760#top
        friend void INT0_vect(void);
        void ISR_fuelPumpPulse();
        // Input pins:
        pin_t<D, 7> _pin_iFlameSwitch = pin_t<D, 7>(INPUT);
        pin_t<B, 0> _pin_iOverheatSwitch = pin_t<B, 0>(INPUT);
        // Output pins:
        pin_t<D, 4> _pin_oGlowRelay = pin_t<D, 4>(OUTPUT);
        pin_t<D, 5> _pin_oFanRelay = pin_t<D, 5>(OUTPUT);
        pin_t<D, 6> _pin_oFuelRelay = pin_t<D, 6>(OUTPUT);
};

#endif