#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "BandelBorgraeveBGN"; // remplacer par le SSID de votre WiFi
const char* password = "coucoucnous"; // remplacer par le mot de passe de votre WiFi
ESP8266WebServer server(80); // on instancie un serveur ecoutant sur le port 80

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
  // on definit ce qui doit etre fait lorsque la route /bonjour est appelee
  // ici on va juste repondre avec un "hello !"
  server.on("/bonjour", [](){
    server.send(200, "text/plain", "hello !");
    Serial.println("hello !");
  });
  pinMode(2, OUTPUT);
  server.on("/2/on", [](){
    digitalWrite(2,HIGH);
    server.send(200, "text/plain", "LED 2 turned on !");
    Serial.println("LED 2 turned on !");
  });
  server.on("/2/off", [](){
    digitalWrite(2,LOW);
    server.send(200, "text/plain", "LED 2 turned off !");
    Serial.println("LED 2 turned off !");
  });
  server.begin();
}
void loop(void){
  // a chaque iteration, on appelle handleClient pour que les requetes soient traitees
  server.handleClient();
  delay(1000);
}
