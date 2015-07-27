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
 */

// include the library code:
#include <LiquidCrystal.h>
#include <DHT.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define DHTPIN 8     //DHT Sensor Input pin
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
   Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  //Start DHTSensor
  dht.begin();
  // Print a message to the LCD.
  initLCD();
  delay(5000); //delay 5 seconds then clear lcd
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  if(stringComplete){
    if(inputString == "clear" || inputString == "Clear" ||
    inputString == "CLEAR" || inputString == "clr"){
      initLCD();
    }
    else{
      initLCD();
      lcd.print(inputString);
      inputString = "";
      stringComplete = false;
    }
  }
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
    displayTemp(t,h);
  }
  delay(1000);
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

///////////////////////////////////////////////////////////////////////
void initLCD(){
    lcd.clear();
    lcd.print("Control Panel");
    lcd.setCursor(0, 1);
}
void displayTemp(int temp, int hud){
  initLCD();
  lcd.print("T:");
  lcd.print(temp);
  lcd.print("*C H:");
  lcd.print(hud);
  lcd.print("%");
}
