#pragma once

/// hardware pin specification
typedef unsigned char Pin;

/// default/undefined pin state pin
#define PIN_UNDEFINED ((Pin)0xFF)

/// number of @ref watchedPins
#define WATCHED_PINS 16

/// see @ref jshPinWatch / @ref jshGetWatchedPinState
extern Pin watchedPins[WATCHED_PINS];
