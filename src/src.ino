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

#define	NTP_SERVER_NAME  "us.pool.ntp.org"
#define	NTP_TIMEZONE -4*60*60
#define NTP_INTERVAL 10 * 1000    // In miliseconds
#define DHT11_PIN 2
#define DHTTYPE DHT11
#define VARIO_PIN 0

const char* ssid = "BandelBorgraeveBGN"; // remplacer par le SSID de votre WiFi
const char* password = "coucoucnous"; // remplacer par le mot de passe de votre WiFi
Timer* timer;
ESP8266WebServer server(80); // on instancie un serveur ecoutant sur le port 80
char answerBuffer[100];

DHT* dht;
Instruction* instruction;
DHTSmoother* smoother;
Variator* vario;

void setup(void) {
	Serial.begin(115200);
	Serial.println("Initializing...");
	//DHT pin
	pinMode(DHT11_PIN, INPUT);
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

	vario = new Variator(0,60,VARIO_PIN);

	server.on("/all", []() {
		PString answer(answerBuffer, sizeof(answerBuffer));
		answer.print("T:");
		answer.print(smoother->readTemperature());
		answer.print(",H:");
		answer.print(smoother->readHumidity());
		answer.print(",Inst:");
		answer.print(instruction->getInstructedTemperature());
		answer.print(",Def:");
		answer.print(instruction->getDefaultTemperature());
		answer.print(",Limit:");
		answer.print(instruction->getLimit());
		answer.print(",command:");
		answer.print(instruction->getPower(smoother));
		answer.print(",Time:");
		answer.print(timer->y());
		answer.print("/");
		answer.print(timer->mo());
		answer.print("/");
		answer.print(timer->d());
		answer.print("T");
		answer.print(timer->h());
		answer.print(":");
		answer.print(timer->m());
		answer.print(":");
		answer.print(timer->s());
		server.send(200, "text/plain", answerBuffer);
	});
	server.begin();
}
void loop(void) {
	// a chaque iteration, on appelle handleClient pour que les requetes soient traitees
	//timer.dayStr(timer.day());
	delay(1000);
	server.handleClient();
	smoother->update();
	vario->setRatio(instruction->getPower(smoother));
	vario->update();
}
