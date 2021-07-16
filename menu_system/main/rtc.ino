
// ================== file rtc.ino ============================

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
int getDay(){  
  return RTC.getDay();
}
int getMonth(){  
  return RTC.getMonth();
}
int getYear(){  
  return RTC.getYear();
}
int getHours(){  
  return RTC.getHours();
}
int getMinutes(){  
  return RTC.getMinutes();
}
int getSeconds(){  
  return RTC.getSeconds();
}

void setDay(int val){  
  return RTC.setDay(val);
}
void setMonth(int val){  
  return RTC.setMonth(val);
}
void setYear(int val){  
  return RTC.setYear(val);
}
void setHours(int val){  
  return RTC.setHours(val);
}
void setMinutes(int val){  
  return RTC.setMinutes(val);
}
void setSeconds(int val){  
  return RTC.setSeconds(val);
}
void loopRTC() {
  // put your main code here, to run repeatedly:

}
