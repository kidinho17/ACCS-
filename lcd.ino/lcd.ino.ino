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
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(40,38,41,39,37,35);
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
    Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  initLCD();
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
    lcd.print("Control System");
    lcd.setCursor(0, 1);
}
