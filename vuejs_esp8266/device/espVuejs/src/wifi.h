#include <ESP8266WiFi.h>
#include "webserver.h"
#include "store.h"

#include <ArduinoJson.h>
#ifndef STASSID
#define STASSID "Vong Cat-Hide"
#define STAPSK  "78787878"
#endif


const char* ssid = STASSID;
const char* password = STAPSK;

void scanWifi() {
  StaticJsonDocument<1024> doc;
  JsonArray array = doc.to<JsonArray>();
  String ssid;
  int32_t rssi;
  uint8_t encryptionType;
  uint8_t* bssid;
  int32_t channel;
  bool hidden;
  int scanResult;

  Serial.println(F("Starting WiFi scan..."));

  scanResult = WiFi.scanNetworks(/*async=*/false, /*hidden=*/true);

  if (scanResult == 0) {
    Serial.println(F("No networks found"));
  } else if (scanResult > 0) {
    Serial.printf(PSTR("%d networks found:\n"), scanResult);

    // Print unsorted scan results
    for (int8_t i = 0; i < scanResult; i++) {
      JsonObject nestedObj = array.createNestedObject();
      WiFi.getNetworkInfo(i, ssid, encryptionType, rssi, bssid, channel, hidden);
      nestedObj["ssid"] = ssid;
      nestedObj["rssi"] = rssi;
      nestedObj["hidden"] = hidden;

      Serial.printf(PSTR("  %02d: [CH %02d] [%02X:%02X:%02X:%02X:%02X:%02X] %ddBm %c %c %s\n"),
                    i,
                    channel,
                    bssid[0], bssid[1], bssid[2],
                    bssid[3], bssid[4], bssid[5],
                    rssi,
                    (encryptionType == ENC_TYPE_NONE) ? ' ' : '*',
                    hidden ? 'H' : 'V',
                    ssid.c_str());
      delay(0);
    }
  } else {
    Serial.printf(PSTR("WiFi scan error %d"), scanResult);
  }
  String ret;
  serializeJson(array, ret);
  server.send(200, "application/json", ret.c_str());

}

void setwifi(){
  DynamicJsonDocument doc(512);
  deserializeJson(doc, server.arg(0));

  setValue("_ssid",doc["_ssid"]);
  setValue("_sspw",doc["_sspw"]);
  
  Serial.println(getValue("_ssid"));
Serial.println(getValue("_sspw"));
  server.send(200);
}
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
  addApi("/scanwifi", scanWifi);
  addApi("/setwifi", setwifi);
  
}

void loopWifi(void) {
}