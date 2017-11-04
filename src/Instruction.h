/*
 * Instruction.h
 *
 *  Created on: 28 oct. 2017
 *      Author: Matthieu
 */

#ifndef SRC_INSTRUCTION_H_
#define SRC_INSTRUCTION_H_
#include "timer.h"
#include <DHT.h>

class Instruction {
private:
	float defaultTemperature;
	float instructedTemperature;
	time_t limit;
	static Timer* timer;
	static int compare(float instructed, float current);
public:
	Instruction(Timer* timer, float defaultTemperature,
			float instructedTemperature, time_t limit);
	Instruction();
	virtual ~Instruction();
	void init(Timer* timer, float defaultTemperature,
			float instructedTemperature, time_t limit);
	static void setTimer(Timer* timer);
	float getDefaultTemperature();
	float getInstructedTemperature();
	time_t getLimit();
	void setLimit(time_t limit_);
	void setInstructedTemperature(float instructedTemperature_);
	void setDefaultTemperature(float defaultTemperature_);
	int shouldHeat(DHT* dht);bool parseInstruction(const char*);
	static const int NO_POWER = 0;
	static const int VERY_LOW_POWER = 1;
	static const int LOW_POWER = 2;
	static const int MEDIUM_POWER = 3;
	static const int HIGH_POWER = 4;
	static const int FULL_POWER = 5;
	static const float T_DIFF;
};

#endif /* SRC_INSTRUCTION_H_ */
