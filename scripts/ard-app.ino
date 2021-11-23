#include "BEH_4_Base.hpp"

void setup() {
  Serial.begin(115200); 
  //ESP.wdtDisable();  
  char* args[] = {(char*)""};
  bems_relocMain(1, args);
  //run app setup          
  be::BEC_2_8_3_EmbeddedApp::bece_BEC_2_8_3_EmbeddedApp_bevs_inst->bem_startLoop_0();
}

void loop() {
  //run app loop
  be::BEC_2_8_3_EmbeddedApp::bece_BEC_2_8_3_EmbeddedApp_bevs_inst->bem_handleLoop_0();
}
