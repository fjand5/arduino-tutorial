//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h>
#include <RTC.h>

static DS1307 RTC;

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 02); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  RTC.begin();
  lcd.init();                      // initialize the lcd
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hello, world!");
  RTC.startClock();
}


void loop()
{
  String day = String(RTC.getDay());
  String month = String(RTC.getMonth());
  String year = String(RTC.getYear());
  String hours = String(RTC.getHours());
  String minutes = String(RTC.getMinutes());
  String seconds = String(RTC.getSeconds());

  String days = String(day + ":" + month + ":" + year);
  String times = String(hours + ":" + minutes + ":" + seconds);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(days);
  lcd.setCursor(0, 1);
  lcd.print(times);
  delay(1000);

}
