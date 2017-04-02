// Include library found at 
// https://docs.google.com/file/d/0Bwrp4uluZCpNdE9oWTY0M3BncTA/edit 
#include "SevSeg.h"

#include <math.h>
#define ANALOG_IN 0
#define DRIVER_OUT 2
#define TEMP_IN 5
#define ALPHA 0.0001
#define INTERVAL 5000


//Create an instance of the object.
SevSeg sevseg;
double temperature=0.;
double smoothx = 0;
unsigned long last_time = millis();
unsigned long current_time = 0;
unsigned int count =0;


void setup() {
  //Serial.begin(9600);
  Serial.begin(115200);
pinMode(DRIVER_OUT,OUTPUT);
    // Set up pins
  // Arguments : 
  // First 0 is for common cathode
  // Following 0 to 11 numbers are for Arduino pins
  // connected to display in the following order
  // 1,2,3,4,A,B,C,D,E,F,G,DP
  //byte digitPins[] ={2,3,4,5};
  //byte segmentPins[]={13,11,7,8,10,12,6,9};
  //sevseg.begin(COMMON_ANODE,4,digitPins,segmentPins);
  //sevseg.setBrightness(10);
}

void thermistor(int RawADC) {
  double Temp;
  Temp = log(10000.0 * ((1024.0 / RawADC - 1)));
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp )) * Temp );
  Temp = Temp - 273.15;            // Convert Kelvin to Celcius
  //Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
  temperature= Temp;
  //temperature = temperature*(1-ALPHA)+Temp*10.*ALPHA;
}
void loop() {
current_time=millis();
  /*if(current_time-last_time > INTERVAL){
    count++;
    last_time = current_time;
    if(count%2){
      digitalWrite(DRIVER_OUT, HIGH);
    }else{digitalWrite(DRIVER_OUT, LOW);}
  }*/
  
  //thermistor(analogRead(ANALOG_IN));
  //int tint = (int) temperature;
  //int tint = (int) analogRead(ANALOG_IN);
  //int tint = analogRead(ANALOG_IN);
  int tint = analogRead(ANALOG_IN);
  thermistor(tint);
    //Serial.write( 0xff );
  //Serial.write( (tint >> 8) & 0xff );
  //Serial.write( tint & 0xff );
  Serial.print("\n");
  Serial.print(tint);
  //Serial.print("t:");
  //Serial.print(temperature);


  // Prepare number to display, and dot position 
  // (0 to 3, other number means no dot)  
  //sevseg.setNumber(tint);
  // Display number 
  //sevseg.refreshDisplay();
  //delay(500);
  // To maintain display with this wiring, 
  // we are forced to loop over those commands rapidly
  //delay(500);

  //sevseg.refreshDisplay(); // Must run repeatedly
  /*int val = analogRead(ANALOG_IN);
  Serial.write( 0xff );
  Serial.write( (val >> 8) & 0xff );
  Serial.write( val & 0xff );*/
  //delay(1000);
}
