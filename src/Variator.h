/*
 * Variator.h
 *
 *  Created on: 4 nov. 2017
 *      Author: Matthieu
 */

#ifndef SRC_VARIATOR_H_
#define SRC_VARIATOR_H_

#include "Timer.h"
#include "Instruction.h"

class Variator {
public:
	Variator();
	Variator(int ratio, time_t cycleDuration, uint8_t pin);
	virtual ~Variator();
	void setRatio(int ratio);
	void setCycleDuration(time_t cycleDuration);
	time_t getCycleDuration();
	time_t getRatio();
	void update();bool isHeating();
private:
	int targetRatio = Instruction::NO_POWER;
	time_t cycleDuration = 60;
	time_t cycleStart = 0;bool heating = false;
	uint8_t pin = 0;
};

#endif /* SRC_VARIATOR_H_ */
