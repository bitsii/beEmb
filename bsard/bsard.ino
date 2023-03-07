#include <ESP8266WiFi.h>
#include <ESP8266httpUpdate.h>

//WiFiServer* server;

void setup() {
  Serial.begin(115200);   
  //ESP.wdtDisable();
  //ESP.wdtFeed();
  //yield();
  //delay(beva_millis->bevi_int);
  //Serial.println("AP Started");


  /*boolean result = WiFi.softAP("yo_bs", "finn4321");
  if(result == true)
  {
    Serial.println("AP Started");
    String lip = WiFi.softAPIP().toString();
    Serial.println(lip);
  }
  else
  {
    Serial.println("AP Start Failed!");
  }*/

  WiFi.begin("your-ssid", "your-password");
  int count = 0;
  while (WiFi.status() != WL_CONNECTED && count < 40) {
    delay(500);
    Serial.print(".");
    count++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("no luck connecting to wifi");
  }

  //server = new WiFiServer(5308);
  //server->begin();

}

void loop() {
  //run app loop
  WiFiClient client;
  //t_httpUpdate_return ret = ESPhttpUpdate.update(client, "http://hpprodev.bitsii.org:14587/sw1x73p16e85.bin");
  t_httpUpdate_return ret = ESPhttpUpdate.update(client, "http://hpprodev.bitsii.org:14587/sw1x92athpg03v2.bin.gz");


  /*
  unsigned long currentTime = millis();
  unsigned long previousTime = 0;
  long timeoutTime = 2000;

  WiFiClient client = server->available();
  if (client) {
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) {
      previousTime = currentTime;
      currentTime = millis();
      if (client.available()) {
        String response = client.readString();
        Serial.println(response);
      }
    }
  }
  */

}
