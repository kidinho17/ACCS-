// Date and time functions using a DS1307 RTC connected via I2C and Wire lib

#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  #ifdef AVR
  Wire.begin();
#else
  Wire1.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
#endif
  rtc.begin();
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(getTime());
  delay(1000);
}

String getTime(){
  DateTime now = rtc.now();
  String strYear = String(now.year());
  String strMonth = String(now.month());
  String strDay = String(now.day());
  String strHour = String(now.hour());
  String strMinutes = String(now.minute());
  String strSeconds = String(now.second());

  return strYear + ("/") + strMonth+ ("/") + strDay+ (" ") + strHour+ (":") + strMinutes+ (":") + strSeconds;
}
