#include <Arduino.h>
#include "webserver.h"
#include "wifi.h"

void setup(void) {
  Serial.begin(115200);
  setupWifi();
  setupWebserver();
  
}

void loop(void) {
  loopWebserver();
}