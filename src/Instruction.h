/*
 * Instruction.h
 *
 *  Created on: 28 oct. 2017
 *      Author: Matthieu
 */

#include "timer.h"
#include <DHT.h>

#ifndef SRC_INSTRUCTION_H_
#define SRC_INSTRUCTION_H_

class Instruction {
private:
	float defaultTemperature;
	float instructedTemperature;
	time_t limit;
	static Timer timer;
public:
	Instruction(Timer timer, float defaultTemperature,
			float instructedTemperature, time_t limit);
	static void setTimer(Timer timer);
	virtual ~Instruction();
	float getDefaultTemperature();
	float getInstructedTemperature();
	time_t getLimit();
	void setLimit(time_t limit_);
	void setInstructedTemperature(float instructedTemperature_);
	void setDefaultTemperature(float defaultTemperature_);
	float shouldHeat();
	bool parseInstruction(const char*);
	static const int NO_POWER = 0;
	static const int VERY_LOW_POWER = 1;
	static const int LOW_POWER = 2;
	static const int MEDIUM_POWER = 3;
	static const int HIGH_POWER = 4;
	static const int FULL_POWER = 5;
	static const float T_DIFF = 0.3;
};

#endif /* SRC_INSTRUCTION_H_ */
