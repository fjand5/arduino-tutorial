/*
  To upload through terminal you can use: curl -F "image=@firmware.bin" esp8266-webupdate.local/update
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "programer.h"

ESP8266WebServer server(80);
const char* serverIndex1 = "<form method='POST' action='/update1' enctype='multipart/form-data'><input type='file' name='update1'><input type='submit' value='Update1'></form>";
const char* serverIndex2 = "<form method='POST' action='/update2' enctype='multipart/form-data'><input type='file' name='update2'><input type='submit' value='Update2'></form>";

File reciveFile;
void uploadHanlder(int pin) {
  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    avrprog.setSPI(pin, &SPI);
    index_image = 0;
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    for (int i = 0; i < upload.currentSize; i ++)
      copyImage(upload.buf[i]);
  } else if (upload.status == UPLOAD_FILE_END) {
    uploadProg();
  }
  yield();
}
void setupUpload(void) {
  Serial.println("Booting Sketch...");

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
}

void loopUpload(void) {
  server.handleClient();
}
