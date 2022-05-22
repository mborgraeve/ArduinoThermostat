#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
//#include <ESP8266WebServer.h>
//#include <ESP8266mDNS.h>
//#include <PString.h>
//#include <DHT.h>
//#include "Timer.h"
//#include "Instruction.h"
//#include "DHTSmoother.h"
//#include "Variator.h"
//
//#define	NTP_SERVER_NAME  "us.pool.ntp.org"
//#define	NTP_TIMEZONE -4*60*60
//#define NTP_INTERVAL 10 * 1000    // In miliseconds
//#define DHT11_PIN 2
#define LED_PIN 2
//#define DHTTYPE DHT11
//#define VARIO_PIN 0

//const char* ssid = "BandelBorgraeveBGN"; // remplacer par le SSID de votre WiFi
//const char* password = "coucoucnous"; // remplacer par le mot de passe de votre WiFi
//Timer* timer;
//ESP8266WebServer server(80); // on instancie un serveur ecoutant sur le port 80
//char answerBuffer[100];
//
//DHT* dht;
//Instruction* instruction;
//DHTSmoother* smoother;
//Variator* vario;

void setup(void) {

	Serial.begin(115200);
	Serial.println("Initializing...");
	pinMode(LED_BUILTIN, OUTPUT);
}
void loop(void) {
	//timer.dayStr(timer.day());
	delay(1000);
    digitalWrite(LED_BUILTIN, HIGH);
	delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
}
