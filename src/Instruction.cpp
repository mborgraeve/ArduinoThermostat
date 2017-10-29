/*
 * Instruction.cpp
 *
 *  Created on: 28 oct. 2017
 *      Author: Matthieu
 */

#include <Instruction.h>

float defaultTemperature = 13.0;
float instructedTemperature = 16.0;
time_t limit = 0;
Timer Instruction::timer;

Instruction::Instruction(Timer timer, float defaultTemperature,
		float instructedTemperature, time_t limit) {
	this->setDefaultTemperature(defaultTemperature);
	Instruction::setTimer(timer);
	this->setInstructedTemperature(instructedTemperature);
	this->setLimit(limit);
}

Instruction::~Instruction() {
	// TODO Auto-generated destructor stub
}

float getDefaultTemperature() {
	return defaultTemperature;
}
float getInstructedTemperature() {
	return instructedTemperature;
}
time_t getLimit() {
	return limit;
}
void setLimit(time_t limit_) {
	limit = limit_;
}

void setInstructedTemperature(float instructedTemperature_) {
	instructedTemperature = instructedTemperature_;
}
void setDefaultTemperature(float defaultTemperature_) {
	defaultTemperature = defaultTemperature_;
}

/*
 * Return a int between 0 and 5 included telling how much power we should give, in %, 5 being 100%, 0 being no heat needed.
 * see *_POWER static variables in Instruction class.
 */

int shouldHeat(DHT dht) {
	//handle two kind of instructions : cold and hot ones
	//TODO the thinking is not done yet
	if (Instruction::timer.getEpochTime() > getLimit()) {
		switch (floor((dht.readTemperature() - instructedTemperature) * 2) / 2) {
		case -2:
			break;
		case -1:
			break;
		default:
			if (floor((dht.readTemperature() - instructedTemperature) * 2) / 2
					< 2) {
				//more than 2 C degrees difference, full thrust
				return Instruction::FULL_POWER;
			} else if (floor(
					(dht.readTemperature() - instructedTemperature) * 2) / 2
					>= 0) {
				//current is higher than instructed, full stop.
				return Instruction::NO_POWER;
			}
			break;
		}
	else {}

}

bool parseInstruction(const char*) {}

