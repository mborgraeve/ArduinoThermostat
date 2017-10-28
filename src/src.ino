#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include "Timer.h"

#define	NTP_SERVER_NAME  "us.pool.ntp.org"
#define	NTP_TIMEZONE -4*60*60
#define NTP_INTERVAL 10 * 1000    // In miliseconds

const char* ssid = "BandelBorgraeveBGN"; // remplacer par le SSID de votre WiFi
const char* password = "coucoucnous"; // remplacer par le mot de passe de votre WiFi
Timer timer;

String formattedTime;

void setup(void) {
	Serial.begin(115200);
	Serial.println("Initializing...");
	// on demande la connexion au WiFi
	WiFi.begin(ssid, password);
	Serial.println("");
	// on attend d'etre connecte au WiFi avant de continuer
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	// on affiche l'adresse IP qui nous a ete attribuee
	Serial.println("");
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());

	delay(1000);
	timer = Timer();
	timer.init(Timer::ntpServerName, NTP_TIMEZONE, NTP_INTERVAL);
	delay(2000);
	timer.forceUpdate();
}
void loop(void) {
	// a chaque iteration, on appelle handleClient pour que les requetes soient traitees
	//timer.dayStr(timer.day());
	delay(1000);
	Serial.print(timer.y());
	Serial.print("/");
	Serial.print(timer.mo());
	Serial.print("/");
	Serial.print(timer.d());
	Serial.print("T");
	Serial.print(timer.h());
	Serial.print(":");
	Serial.print(timer.m());
	Serial.print(":");
	Serial.println(timer.s());
}
