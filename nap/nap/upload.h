/*
  To upload through terminal you can use: curl -F "image=@firmware.bin" esp8266-webupdate.local/update
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "programer.h"
#ifndef STASSID
#define STASSID "Vong Cat-Hide"
#define STAPSK  "78787878"
#endif
ESP8266WebServer server(80);
const char* serverIndex1 = "<form method='POST' action='/update1' enctype='multipart/form-data'><input type='file' name='update1'><input type='submit' value='Update1'></form>";
const char* serverIndex2 = "<form method='POST' action='/update2' enctype='multipart/form-data'><input type='file' name='update2'><input type='submit' value='Update2'></form>";

File reciveFile;
void uploadHanlder(int pin){
     HTTPUpload& upload = server.upload();
      if (upload.status == UPLOAD_FILE_START) {
        avrprog.setSPI(pin, &SPI);
        reciveFile = LittleFS.open( upload.filename, "w");
      } else if (upload.status == UPLOAD_FILE_WRITE) {
        reciveFile.write(upload.buf, upload.currentSize);
      } else if (upload.status == UPLOAD_FILE_END) {
        reciveFile.close();
        uploadProg(upload.filename);
        LittleFS.remove(upload.filename);
      }
      yield();
}
void setupUpload(void) {
  Serial.println("Booting Sketch...");
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(STASSID, STAPSK);
  if (WiFi.waitForConnectResult() == WL_CONNECTED) {
    server.on("/chip1", HTTP_GET, []() {
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", serverIndex1);
    });
      server.on("/chip2", HTTP_GET, []() {
      server.sendHeader("Connection", "close");
      server.send(200, "text/html", serverIndex2);
    });
    server.on("/update1", HTTP_POST, []() {
      server.sendHeader("Connection", "close");
      server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    }, []() {
        uploadHanlder(D1);
    });
       server.on("/update2", HTTP_POST, []() {
      server.sendHeader("Connection", "close");
      server.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    }, []() {
        uploadHanlder(D2);
    });
    server.begin();
  } else {
    Serial.println("WiFi Failed");
  }
   Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());   
}

void loopUpload(void) {
  server.handleClient();
}
