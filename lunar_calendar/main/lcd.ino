
// ================== file lcd.ino ============================

#define COLUMN 16
#define ROW 2
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, COLUMN, ROW); // set the LCD address to 0x27 for a 16 chars and 2 line display
void setupLCD() {
  lcd.init();   
  lcd.backlight();
  lcd.clear();

}
int getColumn(){
  return COLUMN;
}
void printLCD(int x, int y, String content){
  lcd.setCursor(x, y);
  lcd.print(content);
}
void printCenterLCD(int line, String content){
  // TODO
  // 1. lấy length content
  int len = content.length();
  // 2. lấy 1 nữa khoảng trắng 
  int len2 = (COLUMN-len)/2;
  // 3. ghép khoảng trắng
  String spaceString;
  for(int i =0; i< len2; i ++){
    spaceString+=" ";
  }
  String ret = spaceString + content + spaceString;
  lcd.setCursor(0, line);
  lcd.print(ret);
}
void clearLCD(){
  lcd.clear();
}
void loopLCD() {
  // put your main code here, to run repeatedly:

}
