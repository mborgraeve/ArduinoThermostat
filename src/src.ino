#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <PString.h>
#include <DHT.h>
#include "Timer.h"
#include "Instruction.h"
#include "DHTSmoother.h"
#include "Variator.h"
#include "Updater.h"

#define	NTP_SERVER_NAME  "us.pool.ntp.org"
#define	NTP_TIMEZONE -4*60*60
#define NTP_INTERVAL 10 * 1000    // In miliseconds
#define DHT11_PIN 2
#define DHTTYPE DHT11
#define VARIO_PIN 0
#define SETTINGS_SERVER_URI "192.168.0.184"
#define SETTINGS_SERVER_PORT 8080
#define SETTINGS_SERVER_UPDATE_DELAY 600

const char* ssid = "BandelBorgraeveBGN"; // remplacer par le SSID de votre WiFi
const char* password = "coucoucnous"; // remplacer par le mot de passe de votre WiFi
Timer* timer;
ESP8266WebServer* wServer; // on instancie un serveur ecoutant sur le port 80
char answerBuffer[250];
//char serverBuffer[250];

DHT* dht;
Instruction* instruction;
DHTSmoother* smoother;
Variator* vario;
Updater* updater;

void setup(void) {
	//TODO Create a webserver that will trigger a call to retrieve settings from settings server.
	//TODO create the settings server.
	Serial.begin(115200);
	Serial.println("Initializing...");
	//DHT pin
	pinMode(DHT11_PIN, INPUT);
	wServer = new ESP8266WebServer(80);
	//WIFI
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	// on affiche l'adresse IP qui nous a ete attribuee
	Serial.println("");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
	//init timer

	timer = new Timer(Timer::ntpServerName, NTP_TIMEZONE, NTP_INTERVAL);
	delay(1000);

	dht = new DHT(DHT11_PIN, DHTTYPE, 11);
	timer->forceUpdate();

	instruction = new Instruction(timer, 17.0, 18.0, (long) 1509812400);

	smoother = new DHTSmoother(dht, timer, 0.08, (long) 2);

	vario = new Variator(0, 60, VARIO_PIN);

	updater = new Updater(wServer, &SETTINGS_SERVER_URI[0], timer,
			SETTINGS_SERVER_PORT, SETTINGS_SERVER_UPDATE_DELAY);

	wServer->on("/all", []() {
		PString answer(answerBuffer, sizeof(answerBuffer));
		answer.print("{\"Temperature\":");
		answer.print(smoother->readTemperature());
		answer.print(",\"Humidity\":");
		answer.print(smoother->readHumidity());
		answer.print(",\"Instruction\":{\"InstrutedTemperature\":");
		answer.print(instruction->getInstructedTemperature());
		answer.print(",\"DefaultTemperature\":");
		answer.print(instruction->getDefaultTemperature());
		answer.print(",\"TimeLimit\":");
		answer.print(instruction->getLimit());
		answer.print("},\"Power\":");
		answer.print(instruction->getPower(smoother));
		answer.print(",\"Variator\":{\"VariatorCycle\":");
		answer.print(vario->getCycleDuration());
		answer.print(",\"VariatorRatio\":");
		answer.print(vario->getRatio());
		answer.print("},\"Time\":");
		answer.print(timer->n());
		answer.print(",\"UpdateDelay\":");
		answer.print(updater->getUpdateDelay());
		answer.print("}");
		wServer->send(200, "text/plain", answerBuffer);
	});
	wServer->on("/update", []() {

		wServer->send(200, "text/plain", String(updater->forceUpdate(vario, instruction)));
//TODO here call for update from local server.
		});
	wServer->begin();
}
void loop(void) {
	// a chaque iteration, on appelle handleClient pour que les requetes soient traitees
	//timer.dayStr(timer.day());
	delay(1000);
	wServer->handleClient();
	smoother->update();
	updater->update(vario, instruction);
	vario->setRatio(instruction->getPower(smoother));
	vario->update();

}
