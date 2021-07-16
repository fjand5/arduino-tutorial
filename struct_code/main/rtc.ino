
// ============================== rtc.ino ==================================================
#include <Wire.h>
#include <RTC.h>
static DS1307 RTC;
void setupRTC() {
  RTC.begin();
  RTC.startClock();

}
String cvt2num(int num){
  return num<10?String("0")+num:String(num);
}
String getDays(){
  String day = cvt2num(RTC.getDay());
  String month = cvt2num(RTC.getMonth());
  String year = cvt2num(RTC.getYear());
  return String(day + "/" + month + "/" + year);
}
String getTimes(){  
  String hours = cvt2num(RTC.getHours());
  String minutes = cvt2num(RTC.getMinutes());
  String seconds = cvt2num(RTC.getSeconds());
  return String(hours + ":" + minutes + ":" + seconds);
}
void loopRTC() {
  // put your main code here, to run repeatedly:

}
