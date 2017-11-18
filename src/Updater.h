/*
 * Updater.h
 *
 *  Created on: 5 nov. 2017
 *      Author: Matthieu
 */

#ifndef SRC_UPDATER_H_
#define SRC_UPDATER_H_

#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include "Variator.h"
#include "Instruction.h"
#include "Timer.h"

class Updater {
public:
	Updater(ESP8266WebServer* webServer, const char* URI, Timer* timer,
			int port, time_t updateDelay);
	virtual ~Updater();
	int forceUpdate(Variator* vario, Instruction* instruction);
	int update(Variator* vario, Instruction* instruction);
	void setServer(char* webServerURI);
	void setPort(int port);
	const char* getURI();
	int getPort();
	ESP8266WebServer* getServer();
	void setServer(ESP8266WebServer* server);
	void setUpdateDelay(time_t delay);
	time_t getUpdateDelay();
	static const int RETURN_CODE_OK=0;
	static const int RETURN_CODE_OK_NOT_UPDATED=1;
	static const int RETURN_CODE_PARSING_FAILED =10;
	static const int RETURN_CODE_UPDATE_FAILED =11;
	static const int RETURN_CODE_OTHER_FAILURE = 12;
private:
	time_t updateDelay;
	time_t lastUpdate;
	const char* URI;
	int port;
	ESP8266WebServer* webServer;
	StaticJsonBuffer<300> JSONBuffer;
	Timer* timer;
	bool updateSettings(JsonObject* parser, Variator* vario,
			Instruction* instruction);

};

#endif /* SRC_UPDATER_H_ */
