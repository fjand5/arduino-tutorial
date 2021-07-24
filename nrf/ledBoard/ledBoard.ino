#define CMD_TOGGLE 1
void setup() {
  Serial.begin(115200);
  setupNRF();
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  setOnReciveData([](uint8_t cmd) {
    if (cmd == CMD_TOGGLE) {
      digitalWrite(3, !digitalRead(3));
    }
  });
}

void loop() {
  loopNRF();
}
