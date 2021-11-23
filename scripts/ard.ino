#define ONBOARD_LED  2
#include "BEH_4_Base.hpp"

void setup() {
  pinMode(ONBOARD_LED,OUTPUT);
  
  Serial.begin(115200);                  
  //Serial.print("Hello World"); 
}

void loop() {
  delay(1000);
  //Serial.print("Hi Loop"); 
  //digitalWrite(ONBOARD_LED,HIGH);
  //delay(500);
  //digitalWrite(ONBOARD_LED,LOW);
  char* args[] = {(char*)""};
  bems_relocMain(1, args);
  //delay(2000);
  //digitalWrite(ONBOARD_LED,HIGH);
  //delay(1000);
  //digitalWrite(ONBOARD_LED,LOW);
}
