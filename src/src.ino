#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <PString.h>
#include <DHT.h>
#include "Timer.h"

#define	NTP_SERVER_NAME  "us.pool.ntp.org"
#define	NTP_TIMEZONE -4*60*60
#define NTP_INTERVAL 10 * 1000    // In miliseconds
#define DHT11_PIN 2
#define DHTTYPE DHT11

const char* ssid = "BandelBorgraeveBGN"; // remplacer par le SSID de votre WiFi
const char* password = "coucoucnous"; // remplacer par le mot de passe de votre WiFi
Timer timer;
ESP8266WebServer server(80); // on instancie un serveur ecoutant sur le port 80
float t, h;
char answerBuffer[100];
DHT dht(DHT11_PIN, DHTTYPE, 11);

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
	timer = Timer();
	timer.init(Timer::ntpServerName, NTP_TIMEZONE, NTP_INTERVAL);
	delay(2000);
	timer.forceUpdate();

	server.on("/all", [](){
	  PString answer(answerBuffer, sizeof(answerBuffer));
	    h = dht.readHumidity();          // Read humidity (percent)
	    t = dht.readTemperature(false);     // Read temperature
	    answer.print("T:");
	    answer.print(t);
	    answer.print(",H:");
	    answer.print(h);
	    answer.print("-");
	    answer.print(timer.y());
	    answer.print("/");
	    answer.print(timer.mo());
	    answer.print("/");
	    answer.print(timer.d());
	    answer.print("T");
	    answer.print(timer.h());
	    answer.print(":");
	    answer.print(timer.m());
	    answer.print(":");
	    answer.println(timer.s());
	    server.send(200, "text/plain", answerBuffer);
	  });
	  server.begin();
}
void loop(void) {
	// a chaque iteration, on appelle handleClient pour que les requetes soient traitees
	//timer.dayStr(timer.day());
	delay(1000);
	server.handleClient();

}
