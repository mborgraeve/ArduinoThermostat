#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <PString.h>
#include <DHT.h>


#define DHT11_PIN 2
#define DHTTYPE DHT11
//DHT dht(DHT11_PIN, DHTTYPE,11);
const char* ssid = "BandelBorgraeveBGN"; // remplacer par le SSID de votre WiFi
const char* password = "coucoucnous"; // remplacer par le mot de passe de votre WiFi
ESP8266WebServer server(80); // on instancie un serveur ecoutant sur le port 80
float t, h;
//const int average_loop = 300;
char answerBuffer[5000];

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
    Serial.print("hello !");
  });
  pinMode(2, OUTPUT);
  server.on("/2/on", [](){
    digitalWrite(2,HIGH);
    server.send(200, "text/plain", "LED 2 turned on !");
    Serial.print("LED 2 turned on !");
  });
  server.on("/2/off", [](){
    digitalWrite(2,LOW);
    server.send(200, "text/plain", "LED 2 turned off !");
    Serial.print("LED 2 turned off !");
  });
  //server.on("/2/read", [](){
  //  PString answer(answerBuffer, sizeof(answerBuffer));
  //  average=0;
  //  answer.print("Read:");
  //  for(int i = 0; i<average_loop;i++){
  //    int chk = DHT.read11(DHT11_PIN);
  //    answer.print("T:");answer.print(DHT.temperature);
  //    answer.print(",H:");answer.print(DHT.humidity);
  //    answer.print(";");
  //    average = average + DHT.temperature;
  //  }
  //  answer.print("\n");
   // average = average / average_loop;
   // answer.print("Average:");
  //  answer.print(average);
  //  Serial.print(answerBuffer);
  //  server.send(200, "text/plain", answerBuffer);
  //});
  // on commence a ecouter les requetes venant de l'exterieur
  //server.on("/all", [](){
  //  PString answer(answerBuffer, sizeof(answerBuffer));
  //  h = dht.readHumidity();          // Read humidity (percent)
  //  t = dht.readTemperature(false);     // Read temperature
  //  answer.print("T:");
  //  answer.print(t);
  //  answer.print(",H:");
  //  answer.print(h);
  //  answer.print("\n");
  //  server.send(200, "text/plain", answerBuffer);
  //});
  server.begin();
}
void loop(void){
  // a chaque iteration, on appelle handleClient pour que les requetes soient traitees
  server.handleClient();
  delay(1000);
}
