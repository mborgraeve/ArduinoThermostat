#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <Timer.h>

#define	NTP_SERVER_NAME  "ca.pool.ntp.org"
#define	NTP_TIMEZONE -5
#define NTP_INTERVAL 60 * 1000    // In miliseconds


const char* ssid = "BandelBorgraeveBGN"; // remplacer par le SSID de votre WiFi
const char* password = "coucoucnous"; // remplacer par le mot de passe de votre WiFi
Timer timer = Timer();



String formattedTime ;
void setup(void){
  Serial.println("Initializing...");
  Serial.begin(115200);
  
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

  timer.init(NTP_SERVER_NAME, NTP_TIMEZONE, NTP_INTERVAL);

}
void loop(void){
  // a chaque iteration, on appelle handleClient pour que les requetes soient traitees
  timer.dayStr(timer.day());
  delay(10000);
  Serial.println(timer.dayStr(timer.day()));
}
