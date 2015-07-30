#include <Adafruit_CC3000.h>
#include <Adafruit_CC3000_Server.h>
#include <ccspi.h>
#include <SPI.h>
#include <string.h>
#include "utility/debug.h"


// Number of variables & functions
#define NUMBER_VARIABLES 2
#define NUMBER_FUNCTIONS 1

// Include required libraries

// Define CC3000 chip pins
#define ADAFRUIT_CC3000_IRQ   3
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10

// WiFi network (change with your settings !)
#define WLAN_SSID       "Pussy Killers House"
#define WLAN_PASS       "DavidFerreriraPambo!"
#define WLAN_SECURITY   WLAN_SEC_WPA2

Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, 
ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT, SPI_CLOCK_DIVIDER);
                                                      
void setup(void)
{ 
  
  // Start Serial
  Serial.begin(9600);
  Serial.println("Staring Module");
  // Initialise the CC3000 module
  if (!cc3000.begin())
  {
    Serial.println("Falied");
    while(1);
  }
  Serial.println("Falied");
  // Connect to  WiFi network
  cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY);
    
  // Check DHCP
  while (!cc3000.checkDHCP())
  {
    delay(100);
  }  
  displayConnectionDetails();
}

void loop(void)
{
  //
}

bool displayConnectionDetails(void)
{
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;
  
  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv))
  {
    return false;
  }
  else
  {
    Serial.println(F("\nIP Addr: ")); cc3000.printIPdotsRev(ipAddress);
    return true;
  }
}
