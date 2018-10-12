#ifndef _PINIO_H
#define _PINIO_H

#include <avr/io.h>
#include <stdint.h>

enum port { B = (const uint16_t) &PORTB, C = (const uint16_t) &PORTC, D = (const uint16_t) &PORTD };
enum ddr { input = 0, output = 1 }; // Comment out if Arduino.h is loaded.

template<port _port, uint8_t bit> class pin_t
{
    public:
        //static constexpr uint8_t _port = port;
        static constexpr uint8_t _ddr = _port - 1;
        static constexpr uint8_t _pin = _port - 2;
        enum { mask=1<<bit };
        pin_t(ddr direction) { 
            *(volatile uint8_t*)_ddr = *(volatile uint8_t*)_ddr & ~mask | (direction & mask);
        }
        constexpr void operator=(bool n) {
            *(volatile uint8_t*)_port = *(volatile uint8_t*)_port & ~mask | (n & mask);
        }
        static constexpr void toggle() { *(volatile uint8_t*)_port ^= mask; }
        static constexpr bool read() { *(volatile uint8_t*)_pin & mask; }
};

#endif