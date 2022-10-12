#include "configuration.h"

#ifdef THERMOSTAT_ACTIVE

#if !defined(THERMOSTAT_CONTROL_PIN)
#error "Thermostat control pin should be set"
#endif

#ifndef ARDUINOTHERMOSTAT_THERMOSTAT_H
#define ARDUINOTHERMOSTAT_THERMOSTAT_H

struct StateThermostat {
    bool currentState;
    float humidity;
};

void setupThermostat();

void loopThermostat();

#endif //ARDUINOTHERMOSTAT_THERMOSTAT_H

#endif //THERMOSTAT_ACTIVE
