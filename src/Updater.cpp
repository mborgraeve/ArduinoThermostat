/*
 * Updater.cpp
 *
 *  Created on: 5 nov. 2017
 *      Author: Matthieu
 */

#include "Updater.h"
ESP8266WebServer* webServer;
char* URI;
DynamicJsonBuffer JSONBuffer;

Updater::Updater(ESP8266WebServer* webServer, const char* URI, Timer* timer,
		int port, time_t updateDelay) {
	this->URI = URI;
	this->port = port;
	this->webServer = webServer;
	this->updateDelay = updateDelay;
	this->timer = timer;
	this->lastUpdate = 0;
}

Updater::~Updater() {
	// TODO Auto-generated destructor stub
}

int Updater::update(Variator* vario, Instruction* instruction) {
	if (timer->n() > this->lastUpdate + this->updateDelay) {
		this->lastUpdate = timer->n();
		return this->forceUpdate(vario, instruction);
	}
	return Updater::RETURN_CODE_OK_NOT_UPDATED;

}
int Updater::forceUpdate(Variator* vario, Instruction* instruction) {
	HTTPClient http;
	http.begin(this->URI, this->port);
	int httpCode = http.GET();
//	Serial.println("HTTPCode:");
//	Serial.println(httpCode);
	if (httpCode > 0) {
		String payload = http.getString();
		JsonObject& parser = JSONBuffer.parseObject(payload);
		if (!parser.success()) {
			Serial.print(payload);
			Serial.println("ENDOFPAYLOAD");
			Serial.println("Parser failed");
			http.end();
			return Updater::RETURN_CODE_PARSING_FAILED;
		}
		if (!this->updateSettings(&parser, vario, instruction)) {
			Serial.println("Update failed");
			return Updater::RETURN_CODE_UPDATE_FAILED;
		}
		http.end();
		JSONBuffer.clear();
		return Updater::RETURN_CODE_OK;
	}
	http.end();
	webServer->send(500);
	return Updater::RETURN_CODE_OTHER_FAILURE;
}

bool Updater::updateSettings(JsonObject* parser, Variator* vario,
		Instruction* instruction) {
	if (parser->containsKey("CycleDuration")) {
		vario->setCycleDuration(parser->operator []("CycleDuration"));
	}
	if (parser->containsKey("TimeLimit")) {

		instruction->setLimit(parser->operator []("TimeLimit"));
	}
	if (parser->containsKey("DefaultTemperature")) {
		instruction->setDefaultTemperature(
				parser->operator []("DefaultTemperature"));
	}
	if (parser->containsKey("InstructedTemperature")) {
		instruction->setInstructedTemperature(
				parser->operator []("InstructedTemperature"));
	}
	if (parser->containsKey("UpdateDelay")) {
		this->setUpdateDelay(parser->operator []("updateDelay"));
	}
	return true;
}

void Updater::setUpdateDelay(time_t delay) {
	this->updateDelay = delay;
}
time_t Updater::getUpdateDelay() {
	return this->updateDelay;
}

void Updater::setServer(char* webServerURI) {
	this->URI = webServerURI;
}
void Updater::setPort(int port) {
	this->port = port;
}
const char* Updater::getURI() {
	return this->URI;
}
int Updater::getPort() {
	return this->port;
}

void Updater::setServer(ESP8266WebServer* webserver) {
	this->webServer = webserver;
}
ESP8266WebServer* Updater::getServer() {
	return this->webServer;
}
//TODO use ArduinoJson (https://github.com/bblanchon/ArduinoJson) to parse JSON.
//TODO create the functions that will parse a json answer containing all settings: variator cycle, pins used, instructed, default, next default update - https://techtutorialsx.com/2016/07/17/esp8266-http-get-requests/
