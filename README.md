# chinook
Controller for Eberspacher BN2 heater.

## Description
This repository contains code and PCB schematics for a digital controller for the Eberspacher BN2 gasoline forced-air heater (early model). The BN2 was used in '60s-'70s air-cooled Volkswagens and was controlled by relay logic. The system in this repository replaces the unreliable relay logic system.

### Current Functionality
* On/off control of fan, fuel pump, glow plug.
* Timing for startup, shutdown sequences.
* Safety checks using flame sensor and overheat protection switch.

### Future Functionality
* Continuous control of fan speed and fuel pump rate with thermostat feedback.
* CO detection in air stream.

## Resources
* [https://www.thesamba.com/vw/forum/viewtopic.php?t=673779](https://www.thesamba.com/vw/forum/viewtopic.php?t=673779)
