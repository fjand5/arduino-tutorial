#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "dist.h"
#ifndef STASSID
#define STASSID "Vong Cat-Hide"
#define STAPSK  "78787878"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

void handleIndex() {
  server.sendHeader("Content-Encoding", "gzip");
  server.send(200, "text/html", index_html, index_html_length);
}
void setup(void) {
  Serial.begin(115200);
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

  server.on("/", handleIndex);
  server.on("/js/app.js", [](){
    server.sendHeader("Content-Encoding", "gzip");
    server.send(200, "application/javascript", app_js, app_js_length);

  });
  server.begin();
}

void loop(void) {
  server.handleClient();
}