/*
 * Timer.cpp
 *
 *  Created on: 13 oct. 2017
 *      Author: Matthieu
 */

#include "Timer.h"

WiFiUDP Timer::udp = WiFiUDP();
const char Timer::ntpServerName[] = "us.pool.ntp.org";
NTPClient Timer::timeClient = NTPClient(udp, ntpServerName, 0, 0);

void Timer::init(const char* server, int timeZone, int interval) {
	//Timer::ntpServerName = server;

	setSyncProvider(&Timer::syncProvider);
	setSyncInterval((long) interval);
	timeClient.setUpdateInterval(interval);
	timeClient.setTimeOffset(timeZone);
	timeClient.begin();
	delay(1000);
	timeClient.forceUpdate();
}

time_t Timer::getEpochTime() {
	return timeClient.getEpochTime();
}

time_t Timer::syncProvider() {
	return (time_t) timeClient.getEpochTime();

}

void Timer::update() {
	Timer::timeClient.update();
}
void Timer::forceUpdate() {
	Timer::timeClient.forceUpdate();
	setTime((time_t) Timer::timeClient.getEpochTime());
}

/*============================================================================*/
/*Encapsulating TimeLib.h functions*/
/*  time and date functions   */
int Timer::h() {
	return hour();
}
;
// the hour now
int Timer::h(time_t t) {
	return hour(t);
}
;
// the hour for the given time
int Timer::h12() {
	return hourFormat12();
}
;
// the hour now in 12 hour format
int Timer::h12(time_t t) {
	return hourFormat12(t);
}
;
// the hour for the given time in 12 hour format
uint8_t Timer::AM() {
	return isAM();
}
;
// returns true if time now is AM
uint8_t Timer::AM(time_t t) {
	return isAM(t);
}
;
// returns true the given time is AM
uint8_t Timer::PM() {
	return isPM();
}
;
// returns true if time now is PM
uint8_t Timer::PM(time_t t) {
	return isPM(t);
}
;
// returns true the given time is PM
int Timer::m() {
	return minute();
}
;
// the minute now
int Timer::m(time_t t) {
	return minute(t);
}
;
// the minute for the given time
int Timer::s() {
	return second();
}
;
// the second now
int Timer::s(time_t t) {
	return second(t);
}
;
// the second for the given time
int Timer::d() {
	return day();
}
;
// the day now
int Timer::d(time_t t) {
	return day(t);
}
;
// the day for the given time
int Timer::w() {
	return weekday();
}
;
// the weekday now (Sunday is day 1)
int Timer::w(time_t t) {
	return weekday(t);
}
;
// the weekday for the given time
int Timer::mo() {
	return month();
}
;
// the month now  (Jan is month 1)
int Timer::mo(time_t t) {
	return month(t);
}
;
// the month for the given time
int Timer::y() {
	return year();
}
;
// the full four digit year: (2009, 2010 etc)
int Timer::y(time_t t) {
	return year(t);
}
;
// the year for the given time

time_t Timer::n() {
	return now();
}
;
// return the current time as seconds since Jan 1 1970

char* Timer::moStr(uint8_t month) {
	return monthStr(month);
}
;
char* Timer::dStr(uint8_t day) {
	return dayStr(day);
}
;
char* Timer::moShortStr(uint8_t month) {
	return monthShortStr(month);
}
;
char* Timer::dShortStr(uint8_t day) {
	return dayShortStr(day);
}
;

