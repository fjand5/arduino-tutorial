
#define CMD_ON_LED_1 1
#define CMD_OFF_LED_1 2
#define CMD_ON_LED_2 3
#define CMD_OFF_LED_2 4

void setup() {
  Serial.begin(115200);
  setupNRF();
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  setOnReciveData([](uint8_t cmd) {
    Serial.println(cmd);
    if (cmd == CMD_ON_LED_1) {
      digitalWrite(3, LOW);
    }else if(cmd == CMD_OFF_LED_1) {
      digitalWrite(3, HIGH);
    }else if(cmd == CMD_ON_LED_2) {
      digitalWrite(4, LOW);
    }else if(cmd == CMD_OFF_LED_2) {
      digitalWrite(4, HIGH);
    }
  });
}

void loop() {
  loopNRF();
}
