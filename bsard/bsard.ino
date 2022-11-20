#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(115200);   
  //ESP.wdtDisable();
  //ESP.wdtFeed();
  //yield();
  //delay(beva_millis->bevi_int);
  //Serial.println("AP Started");
  boolean result = WiFi.softAP("yoit_bs", "finn4321");
  if(result == true)
  {
    Serial.println("AP Started");
    String lip = WiFi.softAPIP().toString();
    Serial.println(lip);
    //std::string lips = std::string(lip.c_str());
    //bevp_localIP = new BEC_2_4_6_TextString(lips);
    //bevp_up = BECS_Runtime::boolTrue;
  }
  else
  {
    Serial.println("AP Start Failed!");
    //bevp_up = BECS_Runtime::boolFalse;
  }
}

void loop() {
  //run app loop
}
