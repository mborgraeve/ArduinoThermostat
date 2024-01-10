//// Created by matth on 2023-01-02.
//

#include "configuration.h"

#ifdef COOLING_THERMOSTAT_ACTIVE
#include "AcThermostat.h"
#include <algorithm>

CoolingThermostat::CoolingThermostat(Timer *timer) {
    this->ac = new IRCoolixAC(COOLING_THERMOSTAT_CONTROL_PIN);
    this->ac->begin();
    this->smoothed = COOLING_INITIAL_VALUE;
    this->timer = timer;
    this->lastUpdate = 0;
    this->target = COOLING_DEFAULT_TARGET;
    this->isCooling = false;

}

CoolingThermostat::~CoolingThermostat() {
    delete this->timer;
    delete this->ac;
    this->ac = nullptr;
    this->timer = nullptr;
}

void CoolingThermostat::loop(float value) {
    //update value
    if (this->lastUpdate + COOLING_UPDATE_DELAY < timer->n()) {
        if (this->smoothed != -1) {
            this->smoothed = COOLING_ALPHA * value + (1 - COOLING_ALPHA) * this->smoothed;
        } else {
            this->smoothed = value;
        }
        this->lastUpdate = timer->n();
    }
    LOG_IF_DEBUG_LN("Updated CoolingThermostat value to:")
    LOG_IF_DEBUG_LN(this->readValue())
    //update state
    bool stateChanged = false;
    if (isCooling) { //already cooling
        if (this->readValue() < this->target - COOLING_HYSTERESIS_DELTA) {
            // if we went over the hysteresis, turn it off
            this->isCooling = false;
            stateChanged = true;
        } //else continue cooling
    } else {
        //if we went above hysteresis, start cooling
        if (this->readValue() > this->target + COOLING_HYSTERESIS_DELTA) {
            this->isCooling = true;
            stateChanged = true;
        } //else keep it off
    }
    //update the state
    if (stateChanged) {
        if (this->isCooling) {
            this->ac->setSensorTemp((uint8_t) target);
            this->ac->on();
        } else {
            this->ac->off();
        }
    }
    LOG_IF_DEBUG_LN("Updated CoolingThermostat value and pin to:")
    LOG_IF_DEBUG_LN(this->shouldCool())
}

float CoolingThermostat::readValue() const {
    return this->smoothed;
}

bool CoolingThermostat::shouldCool() const {
    return this->isCooling;
}

void CoolingThermostat::updateTargetTemperature(float temperature) {
    this->target = MIN(temperature, COOLING_DEFAULT_TARGET);
}

#endif //COOLING_THERMOSTAT_ACTIVE