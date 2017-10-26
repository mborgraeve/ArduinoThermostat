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
	int h();            // the hour now
	int h(time_t t);    // the hour for the given time
	int h12();    // the hour now in 12 hour format
	int h12(time_t t); // the hour for the given time in 12 hour format
	uint8_t AM();            // returns true if time now is AM
	uint8_t AM(time_t t);    // returns true the given time is AM
	uint8_t PM();            // returns true if time now is PM
	uint8_t PM(time_t t);    // returns true the given time is PM
	int m();          // the minute now
	int m(time_t t);  // the minute for the given time
	int s();          // the second now
	int s(time_t t);  // the second for the given time
	int d();             // the day now
	int d(time_t t);     // the day for the given time
	int w();         // the weekday now (Sunday is day 1)
	int w(time_t t); // the weekday for the given time
	int mo();           // the month now  (Jan is month 1)
	int mo(time_t t);   // the month for the given time
	int y();            // the full four digit year: (2009, 2010 etc)
	int y(time_t t);    // the year for the given time

	time_t n();         // return the current time as seconds since Jan 1 1970

	char* moStr(uint8_t month);
	char* dStr(uint8_t day);
	char* moShortStr(uint8_t month);
	char* dShortStr(uint8_t day);
	static void update();
	static void forceUpdate();
	static const char ntpServerName[];
	//static const char ntpServerName[] = "time.nist.gov";
	//static const char ntpServerName[] = "time-a.timefreq.bldrdoc.gov";
	//static const char ntpServerName[] = "time-b.timefreq.bldrdoc.gov";
	//static const char ntpServerName[] = "time-c.timefreq.bldrdoc.gov";
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

	static WiFiUDP udp;
	static NTPClient timeClient;

	static time_t syncProvider();

};

#endif /* SRC_TIMER_H_ */
