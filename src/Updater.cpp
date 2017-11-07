/*
 * Updater.cpp
 *
 *  Created on: 5 nov. 2017
 *      Author: Matthieu
 */

#include "Updater.h"
ESP8266WebServer* server;
char* URI;
StaticJsonBuffer<300> JSONBuffer;

Updater::Updater(ESP8266WebServer* server, char* URI, int port = 80) {
	this->URI = URI;
	this->port = port;
	this->server = server;
}

Updater::~Updater() {
	// TODO Auto-generated destructor stub
}

void Updater::update(Variator* vario, Instruction* instruction) {
	HTTPClient http;
	http.begin(this->URI, this->port);
	int httpCode = http.GET();
	if (httpCode > 0) {
		String payload = http.getString();
		JsonObject& parser = JSONBuffer.parseObject(payload);
		if (!parser.success()) {
			http.end();
			server->send(500);
			return;
		}
		if (!this->updateSettings( parser, Variator* vario, Instruction* instruction)) {
			http.end();
			server->send(500);
			return;
		}
		http.end();
		server->send(200);
		return;
	}
	http.end();
	server->send(500);
}

bool Updater::updateSettings(JsonObject* parser, Variator* vario, Instruction* instruction, ){
	vario->setCycleDuration(parser["CycleDuration"]);
	instruction->setDefaultTemperature(parser["DefaultTemperature"]);
	instruction->setInstructedTemperature(parser["InstructedTemperature"]);

	return true;

}

void Updater::setServer(char* server) {
	this->URI = server;
}
void Updater::setPort(int port) {
	this->port = port;
}
char* Updater::getURI() {
	return this->URI;
}
int Updater::getPort() {
	return this->port;
}

void Updater::setServer(ESP8266WebServer* server) {
	this->server = server;
}
ESP8266WebServer* Updater::getServer() {
	return this->server;
}

//TODO use ArduinoJson (https://github.com/bblanchon/ArduinoJson) to parse JSON.
//TODO create the functions that will parse a json answer containing all settings: variator cycle, pins used, instructed, default, next default update - https://techtutorialsx.com/2016/07/17/esp8266-http-get-requests/
