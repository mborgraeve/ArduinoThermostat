//// Created by matth on 2023-01-02.
//

#include "configuration.h"

#ifdef HEATING_THERMOSTAT_ACTIVE
#include "AcHeatingThermostat.h"
#include <algorithm>

AcHeatingThermostat::AcHeatingThermostat(Timer *timer) {
    this->ac = new IRCoolixAC(HEATING_THERMOSTAT_CONTROL_PIN);
    this->ac->begin();
    this->smoothed = HEATING_INITIAL_VALUE;
    this->timer = timer;
    this->lastUpdate = 0;
    this->target = HEATING_DEFAULT_TARGET;
    this->isHeating = false;
    this->shouldUpdate = false;

}

AcHeatingThermostat::~AcHeatingThermostat() {
    delete this->ac;
    this->ac = nullptr;
    this->timer = nullptr;
}

void AcHeatingThermostat::loop(float value) {
    //update value
    if (this->lastUpdate + HEATING_UPDATE_DELAY < timer->n()) {
        if (this->smoothed != -1) {
            this->smoothed = HEATING_ALPHA * value + (1 - HEATING_ALPHA) * this->smoothed;
        } else {
            this->smoothed = value;
        }
        this->lastUpdate = timer->n();
    }
    LOG_IF_DEBUG_LN("Updated AcHeatingThermostat value to:")
    LOG_IF_DEBUG_LN(this->readValue())

    //update state
    if(this -> shouldUpdate){
        this->ac->setSensorTemp((uint8_t) target);
        this->ac->on();
        this->shouldUpdate = false;
    }
}

float AcHeatingThermostat::readValue() const {
    return this->smoothed;
}

float AcHeatingThermostat::readTarget() const {
    return this->target;
}

void AcHeatingThermostat::updateTargetTemperature(float temperature) {
    float previousTarget = this->target;
    this->target = MAX(temperature, HEATING_DEFAULT_TARGET);
    float newTarget = this->target;
    if(previousTarget != newTarget){this->shouldUpdate = true;}
}

#endif //HEATING_THERMOSTAT_ACTIVE