#pragma once
#include "dist.h"
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
ESP8266WebServer server(80);

typedef void (*Response)();

void addApi(String path, Response response){
  if(path.indexOf("/")>=0)
    path = path.substring(1);
  server.on(String("/") + path, response);
  
  }

void handleIndex() {
  server.sendHeader("Content-Encoding", "gzip");
  server.send(200, "text/html", index_html, index_html_length);
}
void setupWebserver(){
    server.addHook([](const String & method, const String & url, WiFiClient * client, ESP8266WebServer::ContentTypeFunction contentType) {
    (void)method;      // GET, PUT, ...
    (void)url;         // example: /root/myfile.html
    (void)client;      // the webserver tcp client connection
    (void)contentType; // contentType(".html") => "text/html"
    server.sendHeader("Access-Control-Allow-Origin", "*");
    return ESP8266WebServer::CLIENT_REQUEST_CAN_CONTINUE;
  });
  server.on("/", handleIndex);
  server.on("/js/app.js", [](){
      server.sendHeader("Content-Encoding", "gzip");
      server.send(200, "application/javascript", app_js, app_js_length);

  });
  server.begin();
}
void loopWebserver(){
  server.handleClient();

}