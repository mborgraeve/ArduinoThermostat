#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <PString.h>
#include <DHT.h>


#define DHT11_PIN 2
#define DHTTYPE DHT11

DHT dht(DHT11_PIN, DHTTYPE,11);
const char* ssid = "BandelBorgraeveBGN"; // remplacer par le SSID de votre WiFi
const char* password = "coucoucnous"; // remplacer par le mot de passe de votre WiFi
ESP8266WebServer server(80); // on instancie un serveur ecoutant sur le port 80
float t, h;
//const int average_loop = 300;
//char answerBuffer[5000];

void setup(void){
  Serial.println("Initializing...");
  Serial.begin(115200);
  pinMode(DHT11_PIN, INPUT);
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
  Serial.print("Wait 2s for DHT initialization");
  for(int i = 0;i<4;i++){delay(500);Serial.print(".");i++;}
  Serial.println(" Done!");
  
   //on commence a ecouter les requetes venant de l'exterieur
  server.on("/all", [](){
  //PString answer(answerBuffer, sizeof(answerBuffer));
    h = dht.readHumidity();          // Read humidity (percent)
    t = dht.readTemperature(false);     // Read temperature
  //  answer.print("T:");
  //  answer.print(t);
  //  answer.print(",H:");
  //  answer.print(h);
  //  answer.print("\n");
  //  server.send(200, "text/plain", answerBuffer);
    server.send(200, "text/plain", "Data read sent to serial");
    Serial.print("T:");
    Serial.print(h);
    Serial.print(",H:");
    Serial.print(t);
    Serial.println(";");
  });
  server.begin();
}
void loop(void){
  // a chaque iteration, on appelle handleClient pour que les requetes soient traitees
  server.handleClient();
  delay(1000);
}
