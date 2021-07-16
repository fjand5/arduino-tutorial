
// ============================== main.ino ==================================================


void setup(){
  setupLCD();
  setupRTC();
}
void loop(){
  printCenterLCD(0,getDays());
  printCenterLCD(1,getTimes());
  delay(1000);
}
