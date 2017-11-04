/*
 * DHTSmoother.cpp
 *
 *  Created on: 4 nov. 2017
 *      Author: Matthieu
 */

#include <DHTSmoother.h>

float smoothedTemperature = -1;
float smoothedHumidity = -1;
float alpha = 0;
time_t lastUpdate;
time_t updateDelay;

DHTSmoother::DHTSmoother(DHT* dht, Timer* timer, float alpha,
		time_t updateDelay) {
	this->init(dht, timer, alpha, updateDelay);
}

DHTSmoother::DHTSmoother() {
}

DHTSmoother::~DHTSmoother() {
}
void DHTSmoother::init(DHT* dht, Timer* timer, float alpha,
		time_t updateDelay) {
	this->dht = dht;
	this->alpha = alpha;
	this->smoothedHumidity = -1;
	this->smoothedTemperature = -1;
	this->timer = timer;
	this->updateDelay = updateDelay;
	this->lastUpdate = 0;
}

/**
 * Supposed to be called in every loop to ensure a proper smoothing.
 */
void DHTSmoother::update() {
	if (this->lastUpdate + this->updateDelay < timer->n()) {
		if (this->smoothedHumidity != -1) {
			this->smoothedHumidity = alpha * dht->readHumidity()
					+ (1 - alpha) * this->smoothedHumidity;
		} else {
			this->smoothedHumidity = dht->readHumidity();
		}
		if (this->smoothedTemperature != -1) {
			this->smoothedTemperature = alpha * dht->readTemperature()
					+ (1 - alpha) * this->smoothedTemperature;

		} else {
			this->smoothedTemperature = dht->readTemperature();
		}
		this->lastUpdate = timer->n();
	}
}
float DHTSmoother::readTemperature() {
	return this->smoothedTemperature;
}
float DHTSmoother::readHumidity() {
	return this->smoothedHumidity;
}
