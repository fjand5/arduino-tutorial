void setup() {
  Serial.begin(115200);
  setupNRF();
  setupBUTTON();
}

void loop() {
  loopBUTTON();
  loopNRF();
}
