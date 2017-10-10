#include <math.h>

#define DRV_IN 2
#define V_IN 3
#define ONBOARD_LED 13
#define DRV_OUT 8

#define delay 60000

long time=0;
bool state = false;



void setup() {
  Serial.begin(115200);
pinMode(DRV_IN,INPUT);
pinMode(V_IN,INPUT);
pinMode(ONBOARD_LED,OUTPUT);
pinMode(DRV_OUT,OUTPUT);
time = millis();
digitalWrite(ONBOARD_LED,HIGH);
digitalWrite(DRV_OUT,HIGH);
}

void loop() {
  
  if((millis()-time)>delay ){
    time = millis();
    if(state){
      state = false;
      digitalWrite(ONBOARD_LED,LOW);
      digitalWrite(DRV_OUT,LOW);
    }else{
      state = true;
      digitalWrite(ONBOARD_LED,HIGH);
      digitalWrite(DRV_OUT,HIGH);
    }
  }
  int drv = analogRead(DRV_IN);
  int vin = analogRead(V_IN);
  
  
  Serial.write( 0xff );
  Serial.write( (drv >> 8) & 0xff );
  Serial.write( drv & 0xff );
  
  Serial.write( (vin >> 8) & 0xff );
  Serial.write( vin & 0xff );
  //delay(10);
  
  //delay(10);
  }
