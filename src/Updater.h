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

class Updater {
public:
	Updater(ESP8266WebServer* webServer, char* URI, int port);
	virtual ~Updater();
	void update(Variator* vario, Instruction* instruction);
	void setServer(char* webServerURI);
	void setPort(int port);
	char* getURI();
	int getPort();
	ESP8266WebServer* getServer();
	void setServer(ESP8266WebServer* server);
private:
	char* URI;
	int port;
	ESP8266WebServer* webServer;
	StaticJsonBuffer<300> JSONBuffer;
	static bool updateSettings(JsonObject* parser, Variator* vario, Instruction* instruction);

};

#endif /* SRC_UPDATER_H_ */
