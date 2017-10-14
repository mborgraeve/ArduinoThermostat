/*
 * Timer.cpp
 *
 *  Created on: 13 oct. 2017
 *      Author: Matthieu
 */

#include <Timer.h>

WiFiUDP Timer::ntp = WiFiUDP();
NTPClient Timer::timeClient = NTPClient(ntp, server, timeZone, interval);
const char* Timer::server;
int Timer::timeZone;
int Timer::interval;


void Timer::init(const char* server, int timeZone, int interval){
	Timer::server = server;
	Timer::timeZone = timeZone;
	Timer::interval = interval;
	setSyncProvider(&Timer::syncProvider);
	setSyncInterval((long) Timer::interval);
	timeClient.begin();
}


long Timer::syncProvider() {
	return (long) timeClient.getEpochTime();
}

/*============================================================================*/
/*Encapsulating TimeLib.h functions*/
/*  time and date functions   */
int Timer::hour() {
	return hour();
}
;
// the hour now
int Timer::hour(time_t t) {
	return hour(t);
}
;
// the hour for the given time
int Timer::hourFormat12() {
	return hourFormat12();
}
;
// the hour now in 12 hour format
int Timer::hourFormat12(time_t t) {
	return hourFormat12(t);
}
;
// the hour for the given time in 12 hour format
uint8_t Timer::isAM() {
	return isAM();
}
;
// returns true if time now is AM
uint8_t Timer::isAM(time_t t) {
	return isAM(t);
}
;
// returns true the given time is AM
uint8_t Timer::isPM() {
	return isPM();
}
;
// returns true if time now is PM
uint8_t Timer::isPM(time_t t) {
	return isPM(t);
}
;
// returns true the given time is PM
int Timer::minute() {
	return minute();
}
;
// the minute now
int Timer::minute(time_t t) {
	return minute(t);
}
;
// the minute for the given time
int Timer::second() {
	return second();
}
;
// the second now
int Timer::second(time_t t) {
	return second(t);
}
;
// the second for the given time
int Timer::day() {
	return day();
}
;
// the day now
int Timer::day(time_t t) {
	return day(t);
}
;
// the day for the given time
int Timer::weekday() {
	return weekday();
}
;
// the weekday now (Sunday is day 1)
int Timer::weekday(time_t t) {
	return weekday(t);
}
;
// the weekday for the given time
int Timer::month() {
	return month();
}
;
// the month now  (Jan is month 1)
int Timer::month(time_t t) {
	return month(t);
}
;
// the month for the given time
int Timer::year() {
	return year();
}
;
// the full four digit year: (2009, 2010 etc)
int Timer::year(time_t t) {
	return year(t);
}
;
// the year for the given time

time_t Timer::now() {
	return now();
}
;
// return the current time as seconds since Jan 1 1970

char* Timer::monthStr(uint8_t month) {
	return monthStr(month);
}
;
char* Timer::dayStr(uint8_t day) {
	return dayStr(day);
}
;
char* Timer::monthShortStr(uint8_t month) {
	return monthShortStr(month);
}
;
char* Timer::dayShortStr(uint8_t day) {
	return dayShortStr(day);
}
;

