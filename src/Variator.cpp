///*
// * Variator.cpp
// *
// *  Created on: 4 nov. 2017
// *      Author: Matthieu
// */
//
//#include "Variator.h"
//
//Variator::Variator() {
//}
//Variator::Variator(int ratio, time_t cycleDuration, uint8_t pin) {
//	this->cycleDuration = cycleDuration;
//	this->targetRatio = ratio;
//	this->pin = pin;
//	pinMode(pin, OUTPUT);
//}
//
//Variator::~Variator() {
//}
//
//void Variator::setRatio(int ratio) {
//	this->targetRatio = ratio;
//}
//
//void Variator::setCycleDuration(time_t cycleDuration) {
//	if (cycleDuration > 0) {
//		this->cycleDuration = cycleDuration;
//	}
//
//}
//void Variator::update() {
//	int heater = this->cycleDuration / this->targetRatio;
//	int s = millis() / 1000;
//	//first check if new cycle
//	if (s > this->cycleStart + this->cycleDuration) {
//		this->cycleStart = s;
//	}
//	//then see where we are in current cycle and update pin only if needed
//	if (((s - this->cycleStart) * Instruction::FULL_POWER
//			< this->targetRatio * this->cycleDuration) && (!this->heating)) {
//		digitalWrite(this->pin, HIGH);
//		this->heating = true;
//	} else if (((s - this->cycleStart) * Instruction::FULL_POWER
//			>= this->targetRatio * this->cycleDuration) && this->heating) { //no heat
//		digitalWrite(this->pin, LOW);
//		this->heating = false;
//	}
//}
//
//bool Variator::isHeating() {
//	return heating;
//}
