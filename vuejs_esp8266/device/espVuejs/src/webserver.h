#include "dist.h"
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
ESP8266WebServer server(80);


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

void handleIndex() {
  server.sendHeader("Content-Encoding", "gzip");
  server.send(200, "text/html", index_html, index_html_length);
}
void setupWebserver(){
  server.on("/", handleIndex);
  server.on("/scanWifi", scanWifi);
  server.on("/js/app.js", [](){
      server.sendHeader("Content-Encoding", "gzip");
      server.send(200, "application/javascript", app_js, app_js_length);

  });
  server.begin();
}
void loopWebserver(){
  server.handleClient();

}