/*
  The circuit:
 * LCD RS pin to digital pin 12 -- 40
 * LCD Enable pin to digital pin 11 -- 38
 * LCD D4 pin to digital pin 5 -- 41
 * LCD D5 pin to digital pin 4 -- 39
 * LCD D6 pin to digital pin 3 -- 37
 * LCD D7 pin to digital pin 2 -- 35
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3 -- 37)
 Date and time functions using a DS1307 RTC connected via I2C and Wire lib
 */
/*================================= include the library code ============================*/
#include <LiquidCrystal.h>
#include <DHT.h>
#include <Wire.h>
#include "RTClib.h"
#include <String.h>
#include <Adafruit_CC3000.h>
#include <ccspi.h>
#include <SPI.h>
#include "utility/debug.h"

/*================================= RT Clock  ===========================================*/
RTC_DS1307 rtc;

/*================================= Liquid Crystal =======================================*/
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(40, 38, 41, 39, 37, 35);

/*================================= DHT Sensor ==========================================*/
#define DHTPIN 34     //DHT Sensor Input pin
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);

/*================================= Wi-Fi Shield ========================================*/
// These are the interrupt and control pins
#define ADAFRUIT_CC3000_IRQ   3  // MUST be an interrupt pin!
// These can be any two pins
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10
// Use hardware SPI for the remaining pins
// On an UNO, SCK = 13, MISO = 12, and MOSI = 11
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT, SPI_CLOCK_DIVIDER); // you can change this clock speed
                                         
#define WLAN_SSID       "Pussy Killers House"           // cannot be longer than 32 characters!
#define WLAN_PASS       "DavidFerreiraPambo!"          // Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2

#define WLAN_SECURITY   WLAN_SEC_WPA2

#define IDLE_TIMEOUT_MS  3000      // Amount of time to wait (in milliseconds) with no data received before closing the connection. If you know the server you're accessing is quick to respond, you can reduce this value

// What page to grab!
#define WEBSITE      "10.0.0.4"

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

unsigned long int intTime = 0, old_intTime = 0;
int counter = 0;

void setup() {
   Serial.begin(9600);
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
   //set up the LCD's number of columns and rows:
   lcd.begin(16, 2);
  //Start DHTSensor
    dht.begin();
  // Clear the LCD.
    lcd.clear();
  
  //Setup the Wi-Fi STARTS =================================================
  lcd.print("Initializing");
  lcd.setCursor(0, 1);
  lcd.print("Wi-Fi Module");
  if (!cc3000.begin())
  {
    lcd.clear(); lcd.print(F("Couldn't begin()!"));
    while(1);
  }
  
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    lcd.clear(); lcd.println("Failed!");
    while(1);
  }
   
  lcd.clear(); lcd.print("Connected to:"); lcd.setCursor(0, 1); lcd.print(WLAN_SSID);
 
  while (!cc3000.checkDHCP()) /* Wait for DHCP to complete lcd.print("Request DHCP"); */
  {
    delay(100); // ToDo: Insert a DHCP timeout!
  }  
  //Setup the Wi-Fi ENDS =================================================
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
    displayTemp(t,h, getTime());
  }
  delay(1000);

  //time to upload data //1 min interval
  intTime = millis();
  int interval = intTime-old_intTime;
  if (interval > 30000)    
  {
    counter++;
    old_intTime = intTime;
  }
  if(counter == 2){
    counter = 0;
    String d = "/ACCS_Web/add.php?t=" + String("1") + "&h=" + String("1") + "&l=" + String("1") + "&fs=" + String("1") + "&date=" + getDate() + "&time="+ getTime1();
    uploadData(d, d.length());
  }

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
  lcd.print("% L:");
  lcd.print("0");
}

String getTime() {
  DateTime now = rtc.now();
  String strYear = String(now.year());
  String strMonth = String(now.month());
  String strDay = String(now.day());
  String strHour = String(now.hour());
  String strMinutes = String(now.minute());
  String strSeconds = String(now.second());
  
  return strDay + ("-") + strMonth + ("-") + strYear.substring(2,4) + (" ") + strHour+ (":") + strMinutes+ (":") + strSeconds;
}
String getDate() {
  DateTime now = rtc.now();
  String strYear = String(now.year());
  String strMonth = String(now.month());
  String strDay = String(now.day());
 
  return strYear + ("-") + strMonth + ("-") + strDay;
}
String getTime1() {
  DateTime now = rtc.now();
  String strHour = String(now.hour());
  String strMinutes = String(now.minute());
  String strSeconds = String(now.second());
 
  return strHour + (":") + strMinutes+ (":") + strSeconds;
}
/*================================= Updload data ============================*/
void uploadData(String d, int l){
  
   char data[100] = {};
   d.toCharArray(data, l);  
  
  uint32_t address = 167772164; //Server ip address 
  Adafruit_CC3000_Client www = cc3000.connectTCP(address, 80);
  if (www.connected()) {
    www.fastrprint(F("GET "));
    www.fastrprint(data);
    www.fastrprint(F(" HTTP/1.1\r\n"));
    www.fastrprint(F("Host: http:10.0.0.4")); 
    www.fastrprint(F("\r\n"));
    www.fastrprint(F("\r\n"));
    www.println();
  } else {
    lcd.clear();
    lcd.print("Connection to"); 
    lcd.setCursor(0,1);
    lcd.print("server failed");
    delay(10000);    
    return;
  }
  
  /* Read data until either the connection is closed, or the idle timeout is reached. */ 
  unsigned long lastRead = millis();
  while (www.connected() && (millis() - lastRead < IDLE_TIMEOUT_MS)) {
    while (www.available()) {
      char c = www.read();
      //Serial.print(c);
      lastRead = millis();
    }
  }
  www.close();  
  cc3000.disconnect();
}
