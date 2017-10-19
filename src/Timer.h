/*
 * Timer.h
 *
 *  Created on: 13 oct. 2017
 *      Author: Matthieu
 */

#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_

#include <NTPClient.h>
#include <WiFiUdp.h>
#include <TimeLib.h>
#include <Arduino.h>

class Timer {
public:
	static void init(const char* server, int timeZone, int interval);

	/*============================================================================*/
	/*  time and date functions   */
	int hour();            // the hour now
	int hour(time_t t);    // the hour for the given time
	int hourFormat12();    // the hour now in 12 hour format
	int hourFormat12(time_t t); // the hour for the given time in 12 hour format
	uint8_t isAM();            // returns true if time now is AM
	uint8_t isAM(time_t t);    // returns true the given time is AM
	uint8_t isPM();            // returns true if time now is PM
	uint8_t isPM(time_t t);    // returns true the given time is PM
	int minute();          // the minute now
	int minute(time_t t);  // the minute for the given time
	int second();          // the second now
	int second(time_t t);  // the second for the given time
	int day();             // the day now
	int day(time_t t);     // the day for the given time
	int weekday();         // the weekday now (Sunday is day 1)
	int weekday(time_t t); // the weekday for the given time
	int month();           // the month now  (Jan is month 1)
	int month(time_t t);   // the month for the given time
	int year();            // the full four digit year: (2009, 2010 etc)
	int year(time_t t);    // the year for the given time

	time_t now();         // return the current time as seconds since Jan 1 1970

	char* monthStr(uint8_t month);
	char* dayStr(uint8_t day);
	char* monthShortStr(uint8_t month);
	char* dayShortStr(uint8_t day);
private:
	// NTP Servers:
	//static const char ntpServerName[] = "us.pool.ntp.org";
	//static const char ntpServerName[] = "time.nist.gov";
	//static const char ntpServerName[] = "time-a.timefreq.bldrdoc.gov";
	//static const char ntpServerName[] = "time-b.timefreq.bldrdoc.gov";
	//static const char ntpServerName[] = "time-c.timefreq.bldrdoc.gov";
	//static const char* ntpServerName  = "ca.pool.ntp.org";

	//const int timeZone = 1;     // Central European Time
	//const int timeZone = -5;  // Eastern Standard Time (USA)
	//const int timeZone = -4;  // Eastern Daylight Time (USA)
	//const int timeZone = -8;  // Pacific Standard Time (USA)
	//const int timeZone = -7;  // Pacific Daylight Time (USA)

	static const char* server;
	static int timeZone;
	static int interval;

	static WiFiUDP ntp;
	static NTPClient timeClient;

	static long syncProvider();

};

#endif /* SRC_TIMER_H_ */