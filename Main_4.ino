#include <Arduino.h>
#include <ESP8266httpUpdate.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include <PubSubClient.h>
#include "WifiTesting.h"
#include "PinAllocation.h"
#include "LEDToggle.h"
/******* RTC Liberaries *************/
#include <Wire.h>                   // for I2C communication
#include <RTClib.h> 
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "time.h"
#include <TimeLib.h>


/*********ALEXA LIBRARIES*************/
#define ESPALEXA DEBUG
#include <Espalexa.h>

extern String esid;
extern String epass;
extern int i;
extern int j;

extern unsigned char ConfigFlag;

// EEPROM function 
String gsReceivedData;



// Declaration of EEPROM Variables 

char Device_1_arr[100];

long Device_1_integer_Data[100];




/*void printLocalTime()
{
  struct tm timeinfo;
  //if(!getLocalTime(&timeinfo)){
   // Serial.println("Failed to obtain time");
   // return;
//  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
   RTC_RD();
}*/




void setup() 
{
    S_EEPROM_RTC_Beg();
    DEV_CURNT_STA();
   // pinMode(LED1,OUTPUT);
    //Serial.begin(9600); //Initialising if(DEBUG)Serial Monitor
    pinMode(pswFactoryReset,INPUT);
   // pinMode(12, OUTPUT);
   // pinMode(13, OUTPUT);
    //EEPROM.begin(512); //Initialasing EEPROM
    delay(10);
    pinMode(LED_BUILTIN, OUTPUT);
    HRD_FACT_RESET();
    
    if(ConfigFlag == 1)
    {
      RD_SSID_PWD_EEPROM_WiFi_AUTO_CON();    //FUNCTION FOR CONNECTING THE ESP WITH WIFI 
    }
    else
    {
       WiFi_AUTO_CON_NO_CONFIG();
    }
    
    WiFi_RSSI_STR();
   // time_t getNtpTime();
    //void digitalClockDisplay();
    //fnNTP_Format_GMT_Time();
   // void printDigits(int digits);
    //void sendNTPpacket(IPAddress &address);
    
     //RTC_NTP_FETCH_GMT_T();
    
    
    Serial.println("Going to the Loop");
     MQTT_CON_Dev_Top();
    EEPROM_RD();

    RTC_NTP_FETCH_GMT_T();
    
    
    
    Serial.println("My Version is 1V1");


    // Initialize a NTPClient to get time
    NTP_CLNT_BEG();
    ESP_ALEXA();
  }



 


  //init and get the time
 


   


int t=0;
time_t prevDisplay = 0; 
void loop() 
{

    //ApsisMQTTClient.loop();
       // Function for MQTT and LED Toggle After Connect
   // fnMQTTSerialPrintLEDToggle();
	    // Code for RTC and MQTT connection

     //RTC.read();
     
    MQTT_LOOP();  
    //fnRTC_NTP_LOOP();
    STR_NF_T_2DARRAY();
	  t++;
	  delay(2);
	  if(t>=1000)
	  {
	    RTC_RD();
	    t=0;


      WiFi_RSSI_SIG_LOOP();
  
  
  	  }

     ESP_ALEXA_Loop();
     delay(10); 

    //delay(2);
  
    
	  if (Serial.available()) 
	  {
	    char input = Serial.read();
	    if (input == 'u')   // update RTC time
	    {
         UPD_RTC();  // update RTC time
        
      }

      
    
     else if (input == '*')
      {
        //*W<T40FEVQNJYQS6WV4>213&422&133&433&544&122&433& for writing
        //*R<DY20OO1OKG1V0Q49>1369048>1>  for reading.
        THINK_SPEAK_RD_WRT();  
         
      }
      else if(input == 't')
      {
          
          //time_t getNtpTime();
          RTC_NTP_FETCH_GMT_T();   // for fetching GMT timing
          /*timeClient.update();
          unsigned long epochTime = timeClient.getEpochTime();
          Serial.print("Epoch Time: ");
          Serial.println(epochTime);
          
          String formattedTime = timeClient.getFormattedTime();
          Serial.print("Formatted Time: ");
          Serial.println(formattedTime); 

          int currentHour = timeClient.getHours();
          Serial.print("Hour: ");
          Serial.println(currentHour);  
        
          int currentMinute = timeClient.getMinutes();
          Serial.print("Minutes: ");
          Serial.println(currentMinute); 
           
          int currentSecond = timeClient.getSeconds();
          Serial.print("Seconds: ");
          Serial.println(currentSecond);  
        
          String weekDay = weekDays[timeClient.getDay()];
          Serial.print("Week Day: ");
          Serial.println(weekDay);    
        
          //Get a time structure
          struct tm *ptm = gmtime ((time_t *)&epochTime); 
        
          int monthDay = ptm->tm_mday;
          Serial.print("Month day: ");
          Serial.println(monthDay);
        
          int currentMonth = ptm->tm_mon+1;
          Serial.print("Month: ");
          Serial.println(currentMonth);
        
          String currentMonthName = months[currentMonth-1];
          Serial.print("Month name: ");
          Serial.println(currentMonthName);
        
          int currentYear = ptm->tm_year+1900;
          Serial.print("Year: ");
          Serial.println(currentYear);
        
          //Print complete date:
          String currentDate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);
          Serial.print("Current date: ");
          Serial.println(currentDate);
        
          Serial.println("");
        
          delay(2000);*/
        }
                    
            
        //fnRTCReadandUpdate();                          //UPDATE AND PRINT RTC DATA WHEN 'u' IS PRESSED ON TERMINAL   
	  }
}
