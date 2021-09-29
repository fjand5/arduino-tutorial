#include <Arduino.h>
#include "webserver.h"
#include "wifi.h"
#include "store.h"
void setup(void) {
  Serial.begin(115200);
  setupStore();
  setupWifi();
  setupWebserver();
  Serial.println(getValue("count"));
}

void loop(void) {
  loopWebserver();
  // delay(1000);
  // setValue("count", String(millis()), true);

  // Serial.println(getValue("count"));
}