/*
 * Instruction.cpp
 *
 *  Created on: 28 oct. 2017
 *      Author: Matthieu
 */

#include <Instruction.h>

float defaultTemperature = 13.0;
float instructedTemperature = 16.0;
const float Instruction::T_DIFF = 0.1;
time_t blimit = 0;
Timer* Instruction::timer;

Instruction::Instruction(Timer* timer, float defaultTemperature,
		float instructedTemperature, time_t limit) {
	this->init(timer, defaultTemperature, instructedTemperature, limit);

}
Instruction::Instruction() {
}

Instruction::~Instruction() {
	// TODO Auto-generated destructor stub
}

void Instruction::init(Timer* timer, float defaultTemperature,
		float instructedTemperature, time_t limit) {
	this->setDefaultTemperature(defaultTemperature);
	Instruction::setTimer(timer);
	this->setInstructedTemperature(instructedTemperature);
	this->setLimit(limit);
}

void Instruction::setTimer(Timer* timer) {
	Instruction::timer = timer;
}

float Instruction::getDefaultTemperature() {
	return defaultTemperature;
}
float Instruction::getInstructedTemperature() {
	return instructedTemperature;
}
time_t Instruction::getLimit() {
	return limit;
}
void Instruction::setLimit(time_t limit_) {
	limit = limit_;
}

void Instruction::setInstructedTemperature(float instructedTemperature_) {
	instructedTemperature = instructedTemperature_;
}
void Instruction::setDefaultTemperature(float defaultTemperature_) {
	defaultTemperature = defaultTemperature_;
}

/*
 * Return a int between 0 and 5 included telling how much power we should give, in %, 5 being 100%, 0 being no heat needed.
 * see *_POWER static variables in Instruction class.
 */

int Instruction::getPower(DHTSmoother* dht) {
	//handle two kind of instructions : cold and hot ones
	//TODO let it run several minutes on COM port to check if no error.
	if (Instruction::timer->getEpochTime() <= getLimit()) {
		return Instruction::compare(instructedTemperature,
				dht->readTemperature());
	} else {
		return Instruction::compare(defaultTemperature, dht->readTemperature());
	}

}

int Instruction::compare(float instructed, float current) {
	if (current > instructed + Instruction::T_DIFF) {
		return Instruction::NO_POWER;
	} else if (current > instructed) {
		return Instruction::VERY_LOW_POWER;
	} else if (current > instructed - Instruction::T_DIFF) {
		return Instruction::LOW_POWER;
	} else if (current > instructed - Instruction::T_DIFF * 2) {
		return Instruction::MEDIUM_POWER;
	} else if (current > instructed - Instruction::T_DIFF * 3) {
		return Instruction::HIGH_POWER;
	} else {
		return Instruction::FULL_POWER;
	}
	//SHould not happen
	return Instruction::NO_POWER;
}
bool Instruction::parseInstruction(const char*) {
	//TODO
	return false;
}

