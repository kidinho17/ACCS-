/*
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 Date and time functions using a DS1307 RTC connected via I2C and Wire lib
 */

// include the library code:
#include <LiquidCrystal.h>
#include <DHT.h>
#include <Wire.h>
#include "RTClib.h"
#include <String.h>
RTC_DS1307 rtc;


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define DHTPIN 7     //DHT Sensor Input pin
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
   Serial.begin(9600);
   //set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
  //Start DHTSensor
    dht.begin();
  // Clear the LCD.
    lcd.clear();
   //Setup the clock STARTS =================================================
    #ifdef AVR
      Wire.begin();
    #else
      Wire1.begin(); // Shield I2C pins connect to alt I2C bus on Arduino Due
    #endif
  rtc.begin();
  if (! rtc.isrunning()) {
    lcd.print("Clock is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  //Setup the clock ENDS =================================================
  
  delay(5000); //delay 5 seconds then clear lcd
}

void loop() {
  // Read Humidity
  int h = dht.readHumidity();
  // Read temperature as Celsius
  int t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    lcd.print("Failed to read sensor!");
    return;
  }
  else{
    Serial.println(t, DEC);
     Serial.println(h, DEC);
    displayTemp(t,h, getTime());
  }
  delay(1000);
}
///////////////////////////////////////////////////////////////////////
void displayTemp(int temp, int hud, String tm){
  lcd.clear();
  lcd.print(tm);
  lcd.setCursor(0, 1);
  lcd.print("T:");
  lcd.print(temp);
  lcd.print("*C H:");
  lcd.print(hud);
  lcd.print("%");
}

String getTime() {
  DateTime now = rtc.now();
  String strYear = String(now.year());
  String strMonth = String(now.month());
  String strDay = String(now.day());
  String strHour = String(now.hour());
  String strMinutes = String(now.minute());
  String strSeconds = String(now.second());

  return strDay + ("/") + strMonth + ("/") + strYear.substring(2,4) + (" ") + strHour+ (":") + strMinutes+ (":") + strSeconds;
}
/*================================= Junk Code ===============================
  /*if(stringComplete){
    if(inputString == "clear" || inputString == "Clear" ||
    inputString == "CLEAR" || inputString == "clr"){
      lcd.clear();
    }
    else{
      lcd.clear();
      lcd.print(inputString);
      inputString = "";
      stringComplete = false;
    }
  }
  
  

void serialEvent() {
  while (Serial.available()) {
    char inChar = Serial.read(); 
    if(inChar == ';'){
      stringComplete = true;
    }
    else inputString += inChar;
  }
}

================================= Junk Code =============================== */
