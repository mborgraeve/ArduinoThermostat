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
    this->state = false;

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
    if (state) { //already cooling
        if (value < this->target - COOLING_HYSTERESIS_DELTA) {
            // if we went over the hysteresis, turn it off
            this->state = false;
        } //else continue cooling
    } else {
        //if we went above hysteresis, start cooling
        if (value > this->target + COOLING_HYSTERESIS_DELTA) {
            this->state = true;
        } //else keep it off
    }
    //update the pin
    this->state ? this->ac->on() : this->ac->off();
    LOG_IF_DEBUG_LN("Updated CoolingThermostat value and pin to:")
    LOG_IF_DEBUG_LN(this->shouldCool())
}

float CoolingThermostat::readValue() const {
    return this->smoothed;
}

bool CoolingThermostat::shouldCool() const {
    return this->state;
}

void CoolingThermostat::updateTargetTemperature(float temperature) {
    this->target = MAX(temperature, COOLING_DEFAULT_TARGET);
}

#endif //COOLING_THERMOSTAT_ACTIVE