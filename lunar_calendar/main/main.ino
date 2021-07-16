// ================== file main.ino ============================

#define runEvery(t) for (static uint16_t _lasttime;\
                         (uint16_t)((uint16_t)millis() - _lasttime) >= (t);\
                         _lasttime += (t))
volatile bool showTimeFlag = true;
volatile bool showLunarFlag = true;
void setup() {
  Serial.begin(115200);
  setupLCD();
  setupRTC();
  setupBUTTON();
  setupMENU();
}
void loop() {
  loopBUTTON();
  if (showTimeFlag)
    runEvery(1000) {
    if (showLunarFlag) {
      printCenterLCD(0, getLunarDays() + " A");
    }
    else {
      printCenterLCD(0, getDays() + " D");

    }
    printCenterLCD(1, getTimes());
  }
}
