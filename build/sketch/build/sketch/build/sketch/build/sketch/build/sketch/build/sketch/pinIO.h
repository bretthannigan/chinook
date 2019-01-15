#ifndef _PINIO_H
#define _PINIO_H

#include <avr/io.h>
#include <stdint.h>

enum port { B = (const uint16_t) &PORTB, C = (const uint16_t) &PORTC, D = (const uint16_t) &PORTD };
enum ddr { input = 0, output = 1 };

template<port _port, uint8_t bit> class pin_t
{
    public:
        //static constexpr uint8_t _port = port;
        static constexpr uint8_t _ddr = _port - 1;
        static constexpr uint8_t _pin = _port - 2;
        enum { mask=1<<bit };
        pin_t(ddr direction) { 
            // Constructor (initialize bit).
            *(volatile uint8_t*)_ddr = *(volatile uint8_t*)_ddr & ~mask | (direction & mask);
        }
        constexpr void operator=(bool n) {
            // Assignment operator (write bit).
            *(volatile uint8_t*)_port = *(volatile uint8_t*)_port & ~mask | (n & mask);
        }
        constexpr bool operator==(bool n) {
            // Equal to operator (read bit).
            return this->read();
        }
        constexpr bool operator!() {
            // Logical negation operator (read bit).
            return ~this->read();
        }
        constexpr bool operator!=(bool n) {
            // Not equal to operator (read bit).
            return this->read() != n;
        }
        constexpr bool operator&&(bool n) {
            // Logical and operator.
            return this->read() && n;
        }      
        constexpr void operator||(bool n) {
            return this->read() || n;
        }
        explicit operator bool() const {
            // Allow interpretation as boolean (avoids having to overload for pin_t type).
            return this->read();
        }

    private:
        static constexpr bool read() { return *(volatile uint8_t*)_pin & mask; }
};

#endif