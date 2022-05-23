/*
 * DHTSmoother.h
 *
 *  Created on: 4 nov. 2017
 *      Author: Matthieu
 */

#ifndef SRC_DHTSMOOTHER_H_
#define SRC_DHTSMOOTHER_H_
#include "DHT.h"
#include "Timer.h"

class DHTSmoother {
private:
	DHT* dht;
	float smoothedTemperature;
	float smoothedHumidity;
	float alpha;
	Timer* timer;
	time_t lastUpdate;
	time_t updateDelay;
public:
	virtual ~DHTSmoother();
	DHTSmoother(DHT* dht, Timer* timer, float alpha, time_t updateDelay);
	DHTSmoother();
	void init(DHT* dht, Timer* timer, float alpha, time_t updateDelay);
	void update();
	float readTemperature();
	float readHumidity();
};

#endif /* SRC_DHTSMOOTHER_H_ */
