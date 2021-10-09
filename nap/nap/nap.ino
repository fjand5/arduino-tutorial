#include "programer.h"
#include "upload.h"
#include "mqtt.h"

#ifndef STASSID
#define STASSID "Vong Cat-Hide"
#define STAPSK  "78787878"
#endif
void setup() {
  Serial.begin(115200); /* Initialize serial for status msgs */

  while (!Serial)
    ;
  delay(100);

  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi failed, retrying.");
    delay(100);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  setupProg();
  setupUpload();
  setupMQTT();
}

void loop(void) {
  loopUpload();
  loopMQTT();
}
