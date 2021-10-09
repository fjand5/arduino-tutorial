#include "programer.h"
#include <PubSubClient.h>
const char* mqtt_server = "ngoinhaiot.com";

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  if (String(topic) == "lastwillesp8266/chip1") {
    index_image = 0;
    avrprog.setSPI(D1, &SPI);
    for (int i = 0; i < length; i++) {
      byte p = payload[i];
      if(p == ' ')
        p='\n';
      copyImage(p);
    }
    uploadProg();
  }
    if (String(topic) == "lastwillesp8266/chip2") {
    index_image = 0;
    avrprog.setSPI(D2, &SPI);
    for (int i = 0; i < length; i++) {
      byte p = payload[i];
      if(p == ' ')
        p='\n';
      copyImage(p);
    }
    uploadProg();
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), "lastwillesp8266", "123456")) {
      Serial.println("connected");
      client.subscribe("lastwillesp8266/#");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setupMQTT() {
  client.setBufferSize(5000);
  client.setServer(mqtt_server, 1111);
  client.setCallback(callback);
}

void loopMQTT() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
