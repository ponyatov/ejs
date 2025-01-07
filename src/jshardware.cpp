#include "espruino.hpp"

/// Whether a pin is being used for soft PWM or not
BITFIELD_DECL(jshPinSoftPWM, JSH_PIN_COUNT);

Pin watchedPins[WATCHED_PINS];

void jshInit() {
    for (int i = 0; i < WATCHED_PINS; i++) {  //
        watchedPins[i] = PIN_UNDEFINED;
    }
    BITFIELD_CLEAR(jshPinSoftPWM);
}
