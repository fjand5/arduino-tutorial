#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "Vong Cat-Hide"
#define STAPSK  "78787878"
#endif


const char* ssid = STASSID;
const char* password = STAPSK;
void setupWifi(void) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
}

void loopWifi(void) {
}