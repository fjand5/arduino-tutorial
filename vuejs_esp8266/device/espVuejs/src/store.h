#pragma once
#define STORE_FILE_NAME "store"
#include <ArduinoJson.h>
#include "FS.h"
#include <LittleFS.h>

#include <map>

std::map <String, String> Store;

bool loadConfig() {
  File configFile = LittleFS.open(STORE_FILE_NAME, "r");
  if (!configFile) {
    Serial.println("Failed to open config file");
    return false;
  }

  size_t size = configFile.size();

  // Allocate a buffer to store contents of the file.
  std::unique_ptr<char[]> buf(new char[size]);

  // We don't use String here because ArduinoJson library requires the input
  // buffer to be mutable. If you don't use ArduinoJson, you may as well
  // use configFile.readString instead.
  configFile.readBytes(buf.get(), size);

  DynamicJsonDocument doc(10000);
  auto error = deserializeJson(doc, buf.get());
  JsonObject objData;
  if (error) {
    objData = doc.to<JsonObject>();
    Serial.println("Failed to parse config file");
  }
  objData = doc.as<JsonObject>();
  for (JsonPair kv : objData) {
      Store[kv.key().c_str()] = kv.value().as<char*>();
  }
  return true;
}

bool saveConfig() {
  DynamicJsonDocument doc(10000);
  JsonObject objData = doc.to<JsonObject>();

  
  for (auto const& item : Store)
  {
    objData[item.first] = item.second;
  }

  File configFile = LittleFS.open(STORE_FILE_NAME, "w");
  if (!configFile) {
    Serial.println("Failed to open config file for writing");
    return false;
  }

  serializeJson(doc, configFile);
  return true;
}

void setValue(String key, String val, bool save = false){
  Store[key] = val;
  if(save)
    saveConfig();
}

String getValue(String key){
  return Store[key];
}
void setupStore() {
  Serial.println("");
  delay(1000);
  Serial.println("Mounting FS...");

  if (!LittleFS.begin()) {
    Serial.println("Failed to mount file system");
    return;
  }
  if (!loadConfig()) {
    Serial.println("Failed to load config");
  } else {
    Serial.println("Config loaded");
  }
}