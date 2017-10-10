#include <SoftwareSerial.h>
// On crée une communication série software pour l'ESP8266
SoftwareSerial espSerial(10, 11); // RX, TX
void setup() {
  // On ouvre une communication serie hardware pour les messages destines au moniteur série
  Serial.begin(115200);
  // On ouvre la communication serie software pour l'ESP8266
  espSerial.begin(115200);
  
  delay(1000);
  Serial.println("Pret.");
}
void loop() { 
  // si l'ESP8266 a quelque chose a nous dire, on ecrit son message sur le moniteur série
  if (espSerial.available()) {
    Serial.write(espSerial.read());
  }
  // si quelque chose a été saisi dans le moniteur série, on l'envoie à l'ESP8266
  if (Serial.available()) {
    espSerial.write(Serial.read());
  }
}
