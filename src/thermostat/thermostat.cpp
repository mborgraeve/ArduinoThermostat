#include "../configuration.h"

#ifdef THERMOSTAT_ACTIVE
#include "thermostat.h"

StateThermostat state;

void setupThermostat(){
    pinMode(THERMOSTAT_CONTROL_PIN, OUTPUT);
    state = {false};
}

void loopThermostat(){
    digitalWrite(THERMOSTAT_CONTROL_PIN, state.currentState ? HIGH : LOW );
    state = {!state.currentState};
}

#endif //THERMOSTAT_ACTIVE