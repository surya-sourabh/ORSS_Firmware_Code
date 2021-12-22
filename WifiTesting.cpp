#include <NTPClient.h>


#include <Arduino.h>
#include <ESP8266httpUpdate.h>
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
#include "PinAllocation.h"
#include "LEDToggle.h"
#include "WifiTesting.h"
#include <PubSubClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Wire.h>                   // for I2C communication
#include <RTClib.h> 
#include <Espalexa.h>
#include <TimeLib.h>
#include "Time.h"


Espalexa espalexa;
RTC_DS1307 rtc;
//**************************************************************MQTT TESTING******************************************//

int i = 0;
int j=0;
int k;
char arr1[200];

unsigned char ConfigFlag = 0;

char gchCharArrayBuf[384];
char gunchCharArrayBuf_2D[24][16];

unsigned int D1S1TimeToIntegerValueON;
unsigned int NonRepeatFlagD1S1On;
unsigned int D1S1TimeToIntegerValueOFF;
unsigned int NonRepeatFlagD1S1Off;
unsigned int D1S2TimeToIntegerValueON;
unsigned int NonRepeatFlagD1S2On;
unsigned int D1S2TimeToIntegerValueOFF;
unsigned int NonRepeatFlagD1S2Off;
unsigned int D1S3TimeToIntegerValueON;
unsigned int NonRepeatFlagD1S3On;
unsigned int D1S3TimeToIntegerValueOFF;
unsigned int NonRepeatFlagD1S3Off;

unsigned int D2S1TimeToIntegerValueON;
unsigned int NonRepeatFlagD2S1On;
unsigned int D2S1TimeToIntegerValueOFF;
unsigned int NonRepeatFlagD2S1Off;
unsigned int D2S2TimeToIntegerValueON;
unsigned int NonRepeatFlagD2S2On;
unsigned int D2S2TimeToIntegerValueOFF;
unsigned int NonRepeatFlagD2S2Off;
unsigned int D2S3TimeToIntegerValueON;
unsigned int NonRepeatFlagD2S3On;
unsigned int D2S3TimeToIntegerValueOFF;
unsigned int NonRepeatFlagD2S3Off;

unsigned int D3S1TimeToIntegerValueON;
unsigned int NonRepeatFlagD3S1On;
unsigned int D3S1TimeToIntegerValueOFF;
unsigned int NonRepeatFlagD3S1Off;
unsigned int D3S2TimeToIntegerValueON;
unsigned int NonRepeatFlagD3S2On;
unsigned int D3S2TimeToIntegerValueOFF;
unsigned int NonRepeatFlagD3S2Off;
unsigned int D3S3TimeToIntegerValueON;
unsigned int NonRepeatFlagD3S3On;
unsigned int D3S3TimeToIntegerValueOFF;
unsigned int NonRepeatFlagD3S3Off;

unsigned int D4S1TimeToIntegerValueON;
unsigned int NonRepeatFlagD4S1On;
unsigned int D4S1TimeToIntegerValueOFF;
unsigned int NonRepeatFlagD4S1Off;
unsigned int D4S2TimeToIntegerValueON;
unsigned int NonRepeatFlagD4S2On;
unsigned int D4S2TimeToIntegerValueOFF;
unsigned int NonRepeatFlagD4S2Off;
unsigned int D4S3TimeToIntegerValueON;
unsigned int NonRepeatFlagD4S3On;
unsigned int D4S3TimeToIntegerValueOFF;
unsigned int NonRepeatFlagD4S3Off;

// MQTT Broker Credentials
const char *mqtt_broker = "44.196.40.28";   //18.118.98.89
const char *mqtt_username = "admin";
const char *mqtt_password = "public";
const int mqtt_port = 1883;



int Device1_Status = 0;
char arr2[200];
char arr3[200];
char arr4[200];
char arr5[200];
char Buffer2[10];

char AlarmDecision = 0;
int DeviceOn[12];
int DeviceOff[12];

int Device2_Status = 0;
int Device3_Status = 0;
int Device4_Status = 0;
int Device5_Status = 0;
int Device6_Status = 0;
int Device7_Status = 0;
int Device8_Status = 0;
int Device9_Status = 0;
int Device10_Status = 0;
int Device11_Status = 0;
int Device12_Status = 0;

WiFiClient ApsisClient;
PubSubClient ApsisMQTTClient(ApsisClient);
String Devicemac = WiFi.macAddress();



// RTC function 
//void UPD_RTC();
//void RTC_RD();





String strDevice1_Topic = "apsis/migro/" + Devicemac + "/1";
String strDevice2_Topic = "apsis/migro/" + Devicemac + "/2";
String strDevice3_Topic = "apsis/migro/" + Devicemac + "/3";
String strDevice4_Topic = "apsis/migro/" + Devicemac + "/4";
String strDevice5_Topic = "apsis/migro/" + Devicemac + "/5";
String strDevice6_Topic = "apsis/migro/" + Devicemac + "/6";
String strDevice7_Topic = "apsis/migro/" + Devicemac + "/7";
String strDevice8_Topic = "apsis/migro/" + Devicemac + "/8";
String strDevice9_Topic = "apsis/migro/" + Devicemac + "/9";
String strDevice10_Topic = "apsis/migro/" + Devicemac + "/10";
String strDevice11_Topic = "apsis/migro/" + Devicemac + "/11";
String strDevice12_Topic = "apsis/migro/" + Devicemac + "/12";

String strDevice1TimeSchedule_Topic = "apsis/migro/" + Devicemac + "/Plug1";
String strDevice2TimeSchedule_Topic = "apsis/migro/" + Devicemac + "/Plug2";
String strDevice3TimeSchedule_Topic = "apsis/migro/" + Devicemac + "/Plug3";
String strDevice4TimeSchedule_Topic = "apsis/migro/" + Devicemac + "/Plug4";

String strDeviceSendStatus_Topic = "apsis/migro/" + Devicemac + "/SendStatus";
String strDeviceGetStatus_Topic = "apsis/migro/" + Devicemac + "/GetStatus";
String strDeviceUpdateStatus_Topic = "apsis/migro/" + Devicemac + "/UpdateStatus";
String strDeviceONOFFStatus_Topic = "apsis/migro/" + Devicemac + "/ONOFFStatus";
String strRTCUpdate_Topic = "apsis/migro/" + Devicemac + "/RTCUpdate";

String strDev1Set1On_Topic = "apsis/migro/" + Devicemac + "/Dev1Set1On"; 
String strDev1Set1Off_Topic = "apsis/migro/" + Devicemac + "/Dev1Set1Off"; 
String strDev1Set2On_Topic = "apsis/migro/" + Devicemac + "/Dev1Set2On";
String strDev1Set2Off_Topic = "apsis/migro/" + Devicemac + "/Dev1Set2Off"; 
String strDev1Set3On_Topic = "apsis/migro/" + Devicemac + "/Dev1Set3On";
String strDev1Set3Off_Topic = "apsis/migro/" + Devicemac + "/Dev1Set3Off"; 
String strAlarmOnOff_Topic    = "apsis/migro/" + Devicemac + "/AlarmOnOff"; 

const char *Device1_Topic = strDevice1_Topic.c_str();
const char *Device2_Topic = strDevice2_Topic.c_str();
const char *Device3_Topic = strDevice3_Topic.c_str();
const char *Device4_Topic = strDevice4_Topic.c_str();
const char *Device5_Topic = strDevice5_Topic.c_str();
const char *Device6_Topic = strDevice6_Topic.c_str();
const char *Device7_Topic = strDevice7_Topic.c_str();
const char *Device8_Topic = strDevice8_Topic.c_str();
const char *Device9_Topic = strDevice9_Topic.c_str();
const char *Device10_Topic = strDevice10_Topic.c_str();
const char *Device11_Topic = strDevice11_Topic.c_str();
const char *Device12_Topic = strDevice12_Topic.c_str();
const char *Device1TimeSchedule_Topic = strDevice1TimeSchedule_Topic.c_str();
const char *Device2TimeSchedule_Topic = strDevice2TimeSchedule_Topic.c_str();
const char *Device3TimeSchedule_Topic = strDevice3TimeSchedule_Topic.c_str();
const char *Device4TimeSchedule_Topic = strDevice4TimeSchedule_Topic.c_str();

const char *DeviceSendStatus_Topic = strDeviceSendStatus_Topic.c_str();
const char *DeviceGetStatus_Topic = strDeviceGetStatus_Topic.c_str();
const char *DeviceUpdateStatus_Topic = strDeviceUpdateStatus_Topic.c_str();
const char *DeviceONOFFStatus_Topic = strDeviceONOFFStatus_Topic.c_str();
const char *RTCUpdate_Topic = strRTCUpdate_Topic.c_str();

const char *Dev1Set1On_Topic = strDev1Set1On_Topic.c_str();
const char *Dev1Set1Off_Topic = strDev1Set1Off_Topic.c_str();
const char *Dev1Set2On_Topic = strDev1Set2On_Topic.c_str();
const char *Dev1Set2Off_Topic = strDev1Set2Off_Topic.c_str();
const char *Dev1Set3On_Topic = strDev1Set3On_Topic.c_str();
const char *Dev1Set3Off_Topic = strDev1Set3Off_Topic.c_str();
const char *AlarmOnOff_Topic = strAlarmOnOff_Topic.c_str();








 

// for GMT time fetching*********************************************************

WiFiUDP ntpUDP;
//static const char ntpServerName[] = "us.pool.ntp.org";
//const float timeZone = 1;
//unsigned int localPort = 8888;
NTPClient timeClient(ntpUDP, "pool.ntp.org");


String Read_GMT_Time;
String Read_Channel_ID;
String Read_Channel_Name;
int unGMT_HH = 0;
int unGMT_MM = 0;
int unGMT_Dir = 0;


//Week Days
String weekDays[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//Month names
String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};


//*****************************SERIAL EEPROM RTC BEGIN*********************************//
void S_EEPROM_RTC_Beg(void)
{
  EEPROM.begin(512);
  rtc.begin(); 
  Serial.begin(9600);
}


//**********************************************MQTT_Commect******************************************************************//
void MQTT_CON_Dev_Top(void)
{
if (WiFi.status() == WL_CONNECTED)
  {
    FRMWR_UPD();
    digitalWrite(ConfigLED, LOW);
    digitalWrite(InternetConLED, HIGH);
    MQTT_CON();
    
    ApsisMQTTClient.subscribe(Device1_Topic);
    ApsisMQTTClient.subscribe(Device2_Topic);
    ApsisMQTTClient.subscribe(Device3_Topic);
    ApsisMQTTClient.subscribe(Device4_Topic);
    ApsisMQTTClient.subscribe(Device5_Topic);
    ApsisMQTTClient.subscribe(Device6_Topic);
    ApsisMQTTClient.subscribe(Device7_Topic);
    ApsisMQTTClient.subscribe(Device8_Topic);
    ApsisMQTTClient.subscribe(Device9_Topic);
    ApsisMQTTClient.subscribe(Device10_Topic);
    ApsisMQTTClient.subscribe(Device11_Topic);
    ApsisMQTTClient.subscribe(Device12_Topic);
    ApsisMQTTClient.subscribe(Device1TimeSchedule_Topic);
    ApsisMQTTClient.subscribe(Device2TimeSchedule_Topic);
    ApsisMQTTClient.subscribe(Device3TimeSchedule_Topic);
    ApsisMQTTClient.subscribe(Device4TimeSchedule_Topic);
    ApsisMQTTClient.subscribe(DeviceGetStatus_Topic);
    ApsisMQTTClient.subscribe(DeviceUpdateStatus_Topic);
    ApsisMQTTClient.subscribe(DeviceONOFFStatus_Topic);
    ApsisMQTTClient.subscribe(RTCUpdate_Topic);
    ApsisMQTTClient.subscribe(Dev1Set1On_Topic);
    ApsisMQTTClient.subscribe(AlarmOnOff_Topic);

    Serial.println("Device topics are ");
    Serial.println(Device1_Topic);
    Serial.println(Device2_Topic);
    Serial.println(Device3_Topic);
    Serial.println(Device4_Topic);
    Serial.println(Device5_Topic);
    Serial.println(Device6_Topic);
    Serial.println(Device7_Topic);
    Serial.println(Device8_Topic);
    Serial.println(Device9_Topic);
    Serial.println(Device10_Topic);
    Serial.println(Device11_Topic);
    Serial.println(Device12_Topic);
    Serial.println(Device1TimeSchedule_Topic);
    Serial.println(Device2TimeSchedule_Topic);
    Serial.println(Device3TimeSchedule_Topic);
    Serial.println(Device4TimeSchedule_Topic);
    Serial.println(DeviceSendStatus_Topic);
    Serial.println(DeviceGetStatus_Topic);
    Serial.println(DeviceUpdateStatus_Topic);
    Serial.println(DeviceONOFFStatus_Topic);
    Serial.println(RTCUpdate_Topic);
    Serial.println(Dev1Set1On_Topic);
    Serial.println(AlarmOnOff_Topic);

    delay(100);
  }

}


void MQTT_SPrnt_LED_Tog(void)
{
ApsisMQTTClient.loop();
  delay(10); 
    // put your main code here, to run repeatedly:
    char chSerialData;
    if (Serial.available() > 0) 
    {
        // read the incoming byte:
        chSerialData = Serial.read();

        // say what you got:
        Serial.print("I received: ");
        Serial.println(chSerialData, DEC);
        Serial.print(" | 0x");
        Serial.println(chSerialData, HEX);
    }

   // LEDToggle();

}


 



void MQTT_CON()
{
  ApsisMQTTClient.setServer(mqtt_broker, mqtt_port);
  ApsisMQTTClient.setCallback(callback);

  while (!ApsisMQTTClient.connected())
  {
    Serial.println("Connecting to mqtt broker.....");
    if (ApsisMQTTClient.connect(Devicemac.c_str(), mqtt_username, mqtt_password ))
    {
      Serial.println("mqtt broker connected");
    }
    else
    {
      Serial.print("failed with state ");
      Serial.print(ApsisMQTTClient.state());
      delay(2000);
    }
  }
}


void callback(char *topic, byte *payload, unsigned int length)
{
  String RTCYY = "";
  String RTCMM = "";
  String RTCDD = "";
  String RTCHH = "";
  String RTCMIN = "";
  String RTCSS = "";

  
  Serial.print("NEW Message arrived from topic: ");
  Serial.println();
//  Serial.println(topic);
//  Serial.print("Message:");
//  Serial.println("Device 1 topic is ");
  Serial.println(Device1_Topic);
  for (int i = 0; i < length; i++)
  {
    Serial.print((char) payload[i]);
  }
  Serial.println();
  if (strcmp(topic, Device1_Topic) == 0)
  {
    Serial.println("data come from topic 1");
    if ((char) payload[0] == '1')
    {
      Serial.println("**11");
      Device1_Status = 1;
      pinMode(0, OUTPUT);
      digitalWrite(0,HIGH);
      delay(1000);
      
      ApsisMQTTClient.publish(DeviceSendStatus_Topic, "1:ON");
    }
    if ((char) payload[0] == '0')
    {
      Serial. println("**10");
      Device1_Status = 0;
      pinMode(2, OUTPUT);
      digitalWrite(2,HIGH);
      delay(1000);
      ApsisMQTTClient.publish(DeviceSendStatus_Topic, "1:OFF");
    }
  }
  else if (strcmp(topic, Device2_Topic) == 0)
  {
    if ((char) payload[0] == '1')
    {
      Serial.println("**21"); 
      Device2_Status = 1;

      ApsisMQTTClient.publish(DeviceSendStatus_Topic, "2:ON");
    }
    if ((char) payload[0] == '0')
    {
      Serial.println("**20");
      Device2_Status = 0;
      ApsisMQTTClient.publish(DeviceSendStatus_Topic, "2:OFF");
    }
  }
  else if (strcmp(topic, Device3_Topic) == 0)
  {
    if ((char) payload[0] == '1')
    {
      Serial.println("**31");
      Device3_Status = 1;
      ApsisMQTTClient.publish(DeviceSendStatus_Topic, "3:ON");
    }
    if ((char) payload[0] == '0')
    {
      Serial.println("**30");
      Device3_Status = 0;
      ApsisMQTTClient.publish(DeviceSendStatus_Topic, "3:OFF");
    }
  }
  else if (strcmp(topic, Device4_Topic) == 0)
  {
    if ((char)payload[0] == '1')
    {
      Serial.println("**41"); 
      Device4_Status = 1;
      ApsisMQTTClient.publish(DeviceSendStatus_Topic, "4:ON");
    }
    if ((char)payload[0] == '0')
    {
      Serial.println("**40");
      Device4_Status = 0;
      ApsisMQTTClient.publish(DeviceSendStatus_Topic, "4:OFF");
    }
  }
   else if (strcmp(topic, Device5_Topic) == 0)
  {
    if ((char)payload[0] == '1')
    {
      Serial.println("**51"); 
      Device5_Status = 1;
      ApsisMQTTClient.publish(DeviceSendStatus_Topic, "5:ON");
    }
    if ((char)payload[0] == '0')
    {
      Serial.println("**50");
      Device5_Status = 0;
      ApsisMQTTClient.publish(DeviceSendStatus_Topic, "5:OFF");
    }
  }
   else if (strcmp(topic, Device6_Topic) == 0)
  {
    if ((char)payload[0] == '1')
    {
      Serial.println("**61"); 
      Device6_Status = 1;
      ApsisMQTTClient.publish(DeviceSendStatus_Topic, "6:ON");
    }
    if ((char)payload[0] == '0')
    {
      Serial.println("**60");
      Device6_Status = 0;
      ApsisMQTTClient.publish(DeviceSendStatus_Topic, "6:OFF");
    }
  }
   else if (strcmp(topic, Device7_Topic) == 0)
  {
    if ((char)payload[0] == '1')
    {
      Serial.println("**71"); 
      Device7_Status = 1;
      ApsisMQTTClient.publish(DeviceSendStatus_Topic, "7:ON");
    }
    if ((char)payload[0] == '0')
    {
      Serial.println("**70");
      Device7_Status = 0;
      ApsisMQTTClient.publish(DeviceSendStatus_Topic, "7:OFF");
    }
  }
   else if (strcmp(topic, Device8_Topic) == 0)
  {
    if ((char)payload[0] == '1')
    {
      Serial.println("**81"); 
      Device8_Status = 1;
      ApsisMQTTClient.publish(DeviceSendStatus_Topic, "8:ON");
    }
    if ((char)payload[0] == '0')
    {
      Serial.println("**80");
      Device8_Status = 0;
      ApsisMQTTClient.publish(DeviceSendStatus_Topic, "8:OFF");
    }
  }
   else if (strcmp(topic, Device9_Topic) == 0)
  {
    if ((char)payload[0] == '1')
    {
      Serial.println("**91"); 
      Device9_Status = 1;
      ApsisMQTTClient.publish(DeviceSendStatus_Topic, "9:ON");
    }
    if ((char)payload[0] == '0')
    {
      Serial.println("**90");
      Device9_Status = 0;
      ApsisMQTTClient.publish(DeviceSendStatus_Topic, "9:OFF");
    }
  }
   else if (strcmp(topic, Device10_Topic) == 0)
  {
    if ((char)payload[0] == '1')
    {
      Serial.println("**A1"); 
      Device10_Status = 1;
      ApsisMQTTClient.publish(DeviceSendStatus_Topic, "10:ON");
    }
    if ((char)payload[0] == '0')
    {
      Serial.println("**A0");
      Device10_Status = 0;
      ApsisMQTTClient.publish(DeviceSendStatus_Topic, "10:OFF");
    }
  }
   else if (strcmp(topic, Device11_Topic) == 0)
  {
    if ((char)payload[0] == '1')
    {
      Serial.println("**B1"); 
      Device11_Status = 1;
      ApsisMQTTClient.publish(DeviceSendStatus_Topic, "11:ON");
    }
    if ((char)payload[0] == '0')
    {
      Serial.println("**B0");
      Device4_Status = 0;
      ApsisMQTTClient.publish(DeviceSendStatus_Topic, "11:OFF");
    }
  }
   else if (strcmp(topic, Device12_Topic) == 0)
  {
    if ((char)payload[0] == '1')
    {
      Serial.println("**C1"); 
      Device12_Status = 1;
      ApsisMQTTClient.publish(DeviceSendStatus_Topic, "12:ON");
    }
    if ((char)payload[0] == '0')
    {
      Serial.println("**C0");
      Device12_Status = 0;
      ApsisMQTTClient.publish(DeviceSendStatus_Topic, "12:OFF");
    }
  }

/********************************************************************************************************************************88 */
    else  if (strcmp(topic, Device1TimeSchedule_Topic) == 0)
  {
    for(int i = 0;i <length;i++)
    {
      arr1[i] = payload[i];
      Serial.print("arr1[i] ");
      Serial.println(arr1[i]);
      delay(10);
    }
    for(i=0;i<96;i++)
    {
      EEPROM.write(i+127,arr1[i]);
      EEPROM.commit();
    }
    String Device1_addr;
    for (int i = 127; i <223; ++i)
    {
    Device1_addr += char(EEPROM.read(i));
    }
  
    Serial.println();
    Serial.print("Device1_addr: ");
    Serial.println(Device1_addr);
    delay(10); 

    Device1_addr.toCharArray(gchCharArrayBuf,Device1_addr.length()+1);
    int i =0;
    for(j=0;j<6;j++)
    {
      for(k=0;k<16;k++)
      {
       gunchCharArrayBuf_2D[j][k]=gchCharArrayBuf[i++];
      }
    }
  
    for(j=0;j<24;j++)
    {
      for(k=0;k<16;k++)
      {
        Serial.print(gunchCharArrayBuf_2D[j][k]);
        Serial.print(" ");
      }
      Serial.println(" ");
    } 

    NonRepeatFlagD1S1On = 1;   //FLAG FOR NON REPEAT OPERATION FOR DEV1 SET1 ON
    NonRepeatFlagD1S1Off = 1;  //FLAG FOR NON REPEAT OPERATION FOR DEV1 SET1 OFF
    NonRepeatFlagD1S2On = 1; //FLAG FOR NON REPEAT OPERATION FOR DEV1 SET2 ON
    NonRepeatFlagD1S2Off = 1; //FLAG FOR NON REPEAT OPERATION FOR DEV1 SET2 OFF
    NonRepeatFlagD1S3On = 1;   //FLAG FOR NON REPEAT OPERATION FOR DEV1 SET1 ON
    NonRepeatFlagD1S3Off = 1;  //FLAG FOR NON REPEAT OPERATION FOR DEV1 SET1 OFF
    
    
   

   
    
  } 
    
    
    else  if (strcmp(topic, Device2TimeSchedule_Topic) == 0)
  {
    for(int i = 0;i <length;i++)
    {
      arr2[i] = payload[i];
      Serial.print("arr2[i] ");
      Serial.println(arr2[i]);
      delay(10);
    }
    for(i=0;i<96;i++)
    {
      EEPROM.write(i+223,arr2[i]);
      EEPROM.commit();
    }
    String Device2_addr;
    for (int i = 223; i <319; ++i)
    {
    Device2_addr += char(EEPROM.read(i));
    }
  
    Serial.println();
    Serial.print("Device2_addr: ");
    Serial.println(Device2_addr);
    delay(10); 


     Device2_addr.toCharArray(gchCharArrayBuf,Device2_addr.length()+1);
    int i =0;
    int j,k;
    for(j=6;j<12;j++)
    {
      for(k=0;k<16;k++)
      {
       gunchCharArrayBuf_2D[j][k]=gchCharArrayBuf[i++];
      }
    }
  
    for(j=0;j<24;j++)
    {
      for(k=0;k<16;k++)
      {
        Serial.print(gunchCharArrayBuf_2D[j][k]);
        Serial.print(" ");
      }
      Serial.println(" ");
    } 

    NonRepeatFlagD2S1On = 1; //FLAG FOR NON REPEAT OPERATION FOR DEV1 SET2 ON
    NonRepeatFlagD2S1Off = 1; //FLAG FOR NON REPEAT OPERATION FOR DEV1 SET2 OFF
    NonRepeatFlagD2S2On = 1; //FLAG FOR NON REPEAT OPERATION FOR DEV1 SET2 ON
    NonRepeatFlagD2S2Off = 1; //FLAG FOR NON REPEAT OPERATION FOR DEV1 SET2 OFF
    NonRepeatFlagD2S3On = 1; //FLAG FOR NON REPEAT OPERATION FOR DEV1 SET2 ON
    NonRepeatFlagD2S3Off = 1; //FLAG FOR NON REPEAT OPERATION FOR DEV1 SET2 OFF


 }

 
  else  if (strcmp(topic, Device3TimeSchedule_Topic) == 0)
  {
    for(int i = 0;i <length;i++)
    {
      arr3[i] = payload[i];
      Serial.print("arr3[i] ");
      Serial.println(arr3[i]);
      delay(10);
    } 
    for(i=0;i<96;i++)
    {
      EEPROM.write(i+319,arr3[i]);
      EEPROM.commit();
    }
    String Device3_addr;
    for (int i = 319; i <415; ++i)
    {
    Device3_addr += char(EEPROM.read(i));
    }
  
    Serial.println();
    Serial.print("Device3_addr: ");
    Serial.println(Device3_addr);
    delay(10); 

    Device3_addr.toCharArray(gchCharArrayBuf,Device3_addr.length()+1);
    int i =0;
    int j,k;
    for(j=12;j<18;j++)
    {
      for(k=0;k<16;k++)
      {
       gunchCharArrayBuf_2D[j][k]=gchCharArrayBuf[i++];
      }
    }
  
    for(j=0;j<24;j++)
    {
      for(k=0;k<16;k++)
      {
        Serial.print(gunchCharArrayBuf_2D[j][k]);
        Serial.print(" ");
      }
      Serial.println(" ");
    }   

    NonRepeatFlagD3S1On = 1; //FLAG FOR NON REPEAT OPERATION FOR DEV1 SET2 ON
    NonRepeatFlagD3S1Off = 1; //FLAG FOR NON REPEAT OPERATION FOR DEV1 SET2 OFF
    NonRepeatFlagD3S2On = 1; //FLAG FOR NON REPEAT OPERATION FOR DEV1 SET2 ON
    NonRepeatFlagD3S2Off = 1; //FLAG FOR NON REPEAT OPERATION FOR DEV1 SET2 OFF
    NonRepeatFlagD3S3On = 1; //FLAG FOR NON REPEAT OPERATION FOR DEV1 SET2 ON
    NonRepeatFlagD3S3Off = 1; //FLAG FOR NON REPEAT OPERATION FOR DEV1 SET2 OFF

    
 }
  else  if (strcmp(topic, Device4TimeSchedule_Topic) == 0)
  {
    for(int i = 0;i <length;i++)
    {
      arr4[i] = payload[i];Serial.print("arr4[i] ");Serial.println(arr4[i]);delay(10);
    } 
    for(i=0;i<96;i++)
    {
      EEPROM.write(i+415,arr4[i]);
      EEPROM.commit();
    }
    String Device4_addr;
    for (int i = 415; i <511; ++i)
    {
    Device4_addr += char(EEPROM.read(i));
    }
  
    Serial.println();
    Serial.print("Device4_addr: ");
    Serial.println(Device4_addr);
    delay(10); 

    Device4_addr.toCharArray(gchCharArrayBuf,Device4_addr.length()+1);
    int i =0;
    int j,k;
    for(j=18;j<24;j++)
    {
      for(k=0;k<16;k++)
      {
       gunchCharArrayBuf_2D[j][k]=gchCharArrayBuf[i++];
      }
    }
  
    for(j=0;j<24;j++)
    {
      for(k=0;k<16;k++)
      {
        Serial.print(gunchCharArrayBuf_2D[j][k]);
        Serial.print(" ");
      }
      Serial.println(" ");
    }   

    NonRepeatFlagD4S1On = 1; //FLAG FOR NON REPEAT OPERATION FOR DEV1 SET2 ON
    NonRepeatFlagD4S1Off = 1; //FLAG FOR NON REPEAT OPERATION FOR DEV1 SET2 OFF
    NonRepeatFlagD4S2On = 1; //FLAG FOR NON REPEAT OPERATION FOR DEV1 SET2 ON
    NonRepeatFlagD4S2Off = 1; //FLAG FOR NON REPEAT OPERATION FOR DEV1 SET2 OFF
    NonRepeatFlagD4S3On = 1; //FLAG FOR NON REPEAT OPERATION FOR DEV1 SET2 ON
    NonRepeatFlagD4S3Off = 1; //FLAG FOR NON REPEAT OPERATION FOR DEV1 SET2 OFF

    
  }
   
    else if(strcmp(topic, DeviceGetStatus_Topic) == 0)
    {
      char Buffer[200];
      sprintf(Buffer,"1:%d,2:%d,3:%d,4:%d,5:%d,6:%d,7:%d,8:%d,9:%d,10:%d,11:%d,12:%d",Device1_Status,Device2_Status,Device3_Status,Device4_Status,Device5_Status,Device6_Status,Device7_Status,Device8_Status,Device9_Status,Device10_Status,Device11_Status,Device12_Status);
      ApsisMQTTClient.publish(DeviceSendStatus_Topic, Buffer);
    }
    else if(strcmp(topic, RTCUpdate_Topic) == 0)
    {
      for(i=0;i<4;i++)
      {
        RTCYY = RTCYY + (char)payload[i];
      }
      for(i=4;i<6;i++)
      {
        RTCMM = RTCMM + (char)payload[i];
      }
      for(i=6;i<8;i++)
      {
        RTCDD = RTCDD + (char)payload[i];
      }
      for(i=8;i<10;i++)
      {
        RTCHH = RTCHH + (char)payload[i];
      }
      for(i=10;i<12;i++)
      {
        RTCMIN = RTCMIN + (char)payload[i];
      }
      for(i=12;i<14;i++)
      {
        RTCSS = RTCSS + (char)payload[i];
      }
      int IntYY = RTCYY.toInt();
      Serial.print("The year is: ");
      Serial.println(IntYY);
      int IntMM = RTCMM.toInt();
      Serial.print("The Month is: ");
      Serial.println(IntMM);
      int IntDD = RTCDD.toInt();
      Serial.print("The Day is: ");
      Serial.println(IntDD);
      int IntHH = RTCHH.toInt();
      Serial.print("The Hour is: ");
      Serial.println(IntHH);
      int IntMIN = RTCMIN.toInt();
      Serial.print("The Minute is: ");
      Serial.println(IntMIN);
      int IntSS = RTCSS.toInt();
      Serial.print("The Second is: ");
      Serial.println(IntSS);
      rtc.adjust(DateTime(IntYY,IntMM,IntDD,IntHH,IntMIN,IntSS));
      Serial.println("RTC Updated");
      
    }

    /* else if(strcmp(topic, Dev1Set1On_Topic) == 0)
  {
    String D1S1OnHM = "";
    String D1S1OffHM = "";
    Serial.println("Alarm for Device1 for Set1");
    for(i=0; i<4; i++)
    {
      D1S1OnHM = D1S1OnHM + (char)payload[i];
      
    }
    Serial.println("Device 1 Set 1 On time: ");
    
    int IntD1S1OnHM = D1S1OnHM.toInt();
    Serial.println(IntD1S1OnHM);
    DeviceOn[0] = IntD1S1OnHM; 
    
     for(i=4; i<8; i++)
    {
      D1S1OffHM = D1S1OffHM + (char)payload[i];
      
    }
    Serial.println("Device 1 Set 1 Off time: ");
    int IntD1S1OffHM = D1S1OffHM.toInt();
    Serial.println(IntD1S1OffHM);
    DeviceOff[0] = IntD1S1OffHM; 
  }

   else if (strcmp(topic, AlarmOnOff_Topic) == 0)
  {
     AlarmDecision = (char)payload[0];
    //intAlarmOnOff = (AlarmDecision).toInt();
    if(AlarmDecision == '1')
    {
      Serial.println("Alarm is On"); 
    }
    else if (AlarmDecision == '0')
    {
     Serial.println("Alarm is Off");   
    }
  }*/
  

   
  
}

void MQTT_LOOP(void)
{
  ApsisMQTTClient.loop();
  //MQTT_SPrnt_LED_Tog();
}



//****************************************************************MQTT TESTING FINISH********************************************************************//

//****************************************************************WIFI TESTING********************************************************************//
// Global variable Declaration
int incomingByte = 0; // for incoming serial data
char chSerialData = 0;
//const int pswFactoryReset = 14; 
int nIterationCount1 = 0;
int addr = 0;
String content;
String st;
int statusCode;

String esid     = "";
String epass    = "";


HTTPClient http;
ESP8266WebServer  server(80); //Establishing local server at port 80 whenever required.


ESP8266WiFiMulti WiFiMulti;

//WiFiClient ApsisClient;

//RTC_NTP




bool TEST_WiFi(void)
{
    int c = 0;
    Serial.println("Waiting for Wifi to connect");
    while (c < 20)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            return true;
        }
        delay(1000);
        
        Serial.print(".");
        digitalWrite(12, !digitalRead(12));
        c++;
    }
    // Serial.println("");
    // Serial.println("Connect timed out, opening AP");
    return false;
}

//*******************************************RSSI_Strength*******************************************************************************************************************************//

void WiFi_RSSI_STR(void)
{
  Serial.begin(9600);
//  initWiFi();
  Serial.print("RRSI: ");
  Serial.println(WiFi.RSSI());
}

void WiFi_RSSI_SIG_LOOP()
{
  long WiFi_Sig = WiFi.RSSI();

      if(WiFi_Sig < 0 && WiFi_Sig > -10)
      {
       Serial.println("High quality: 98% ");
       Serial.println(WiFi.RSSI());
      }
       else if(WiFi_Sig < -10 && WiFi_Sig > -39)
      {
       Serial.println("High quality: 95% ");
       Serial.println(WiFi.RSSI());
      }
        else if(WiFi_Sig < -40 && WiFi_Sig > -50)
       {
        Serial.println("High quality: 90% ");   // foe -55 db
        Serial.println(WiFi.RSSI());
       }
      else if (WiFi_Sig < -50 && WiFi_Sig > -60)
      {
        Serial.println ("Good quality: 75% ");         // for -75 db
        Serial.println(WiFi.RSSI());
      }
       else if (WiFi_Sig < -60 && WiFi_Sig > -70)
      {
        Serial.println ("Midium quality: 50% ");         // for -75 db
        Serial.println(WiFi.RSSI());
      }
      else if (WiFi_Sig < -70 && WiFi_Sig > -80)
      {
        Serial.println ("Midium quality: 40% ");         // for -75 db
        Serial.println(WiFi.RSSI());
      }
      else if (WiFi_Sig < -80 && WiFi_Sig > -90)
      {
        Serial.println ("Low quality: 30% ");         // for -75 db
        Serial.println(WiFi.RSSI());
      }
      else if (WiFi_Sig < -90 && WiFi_Sig > -96)
      {
        Serial.println ("Low quality: 10% ");         // for -75 db
        Serial.println(WiFi.RSSI());
      }
      else if (WiFi_Sig < -100)
      {
        Serial.println ("No Signal : 0% ");         // for -75 db
        Serial.println(WiFi.RSSI());
      }
      else
        Serial.print("WiFi is not Connected");
      delay(100);
}






//***********************************************************HardFactoryReset*************************************************************************************************************************//

void HRD_FACT_RESET(void)
{
    // Serial.println("Befor Hard Resetting mode..... "); 
    // //delay(5000);

  while(digitalRead(pswFactoryReset) == 1)
   {
    ConfigFlag = 1;
    delay(1000);
    nIterationCount1++;
    Serial.print("nIterationCount1 = "); 
    Serial.println(nIterationCount1); 

    if(nIterationCount1 >= 5)
    {     
       Serial.print("Activated HardFactoryReset"); 

       pinMode(pswFactoryReset, OUTPUT);
       digitalWrite(pswFactoryReset, LOW );
       delay(1000);

       EEPROM.begin(512); //Initialize EEPROM
        // write to EEPROM.
        while (addr < 512)
      {
        EEPROM.write(addr, '0');
        addr++; //Increment address
      }
       /* EEPROM.write(addr, '0');
        addr++; //Increment address
        EEPROM.write(addr, '0');
        addr++; //Increment address
        EEPROM.write(addr, '0');
        addr++; //Increment address
        EEPROM.write(addr, '0');
        addr++; //Increment address
        EEPROM.write(addr, '0');*/
        EEPROM.commit(); //Store data to EEPROM
        Serial.println("HARD RESET");
        
      
       //ESP.restart();            
     } 
   }
    pinMode(pswFactoryReset, INPUT);
}


void LAUNCH_WEB()
{
    // Serial.println("");
    if (WiFi.status() == WL_CONNECTED)
        Serial.println("WiFi connected");

    CRT_WEB_SERVER();
    server.sendHeader(F("Access-Control-Allow-Origin"), F("*"));
    server.sendHeader(F("Access-Control-Max-Age"), F("600"));
    server.sendHeader(F("Access-Control-Allow-Methods"), F("PUT,POST,GET,OPTIONS"));
    server.sendHeader(F("Access-Control-Allow-Headers"), F("*"));
      // Start the server
    server.begin();
}


void SETUP_AP(void)
{
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    delay(100);
    WiFi.softAP("MIGRO_SWITCH", "");
    // Serial.println("Initializing_softap_for_wifi credentials_modification");
    LAUNCH_WEB();
    // Serial.println("over");
}


void CRT_WEB_SERVER()
{
    {
        server.on("/", []() {
            IPAddress ip = WiFi.softAPIP();
            String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
            content = "<!DOCTYPE HTML>\r\n<html><title> Migro_Switch: ";
            content +=Devicemac; 
            content += " </title> ";
            content += "<p style='text-transform: uppercase;'><center> <h1> MacID: ";
            content +=Devicemac;
            content +=" Welcome to Wifi Credentials Update page </h1> </center></p>";
            content += "<center> <h2> Provided By APSIS Solutions </h2> </center>";
            content += "<style>  Body {font-family: Calibri, Helvetica, sans-serif;background-color: pink;}";
            content += " form {border: 3px solid #f1f1f1;}";
            content += " .container {padding: 25px;background-color: lightblue;}";
            content += "input[type=text], input[type=password] {width: 100%;margin: 8px 0;padding: 12px 20px;display: inline-block;border: 2px solid green;box-sizing: border-box;} ";
            //content += "<form action=\"/scan\" method=\"POST\"><input type=\"submit\" value=\"scan\"></form>";
            content += "button {background-color: #4CAF50;width: 100%;color: orange;padding: 15px;margin: 10px 0px;border: none;cursor: pointer;} ";
            content += "</style> <body>";
            //content += ipStr;
            content += "<p>";
            content += st;
            content += "<div class='container'> ";
            content += "</p><form method='get' action='/setting'><h3><label>SSID: </label><h3><input type='text' name='ssid' id='ssid' placeholder='Enter Username' length=32><br><h3><label>PASSWORD:<label></h3><input type='password' id='pass' name='pass' placeholder='Enter Password' length=64><br><h3><label>Channel ID: </label><h3><input type='text' name='ChannelID' id='ChannelID' placeholder='ChannelID' length=32><br><h3><label>Channel Name: </label><h3><input type='text' name='ChannelName' id='ChannelName' placeholder='Enter ChannelName' length=32><br> <h3><label>TimeZone: </label><h3><input type='text' name='TimeZone' id='TimeZone' placeholder='Enter TimeZone' length=32><br><h3><label>latitude: </label><h3><input type='text' name='latitude' id='latitude' placeholder='Enter latitude' length=32><br><h3><label>longitude: </label><h3><input type='text' name='longitude' id='longitude' placeholder='Enter longitude' length=32><br><h3><label>ALTITUDE: </label><h3><input type='text' name='naltitude' id='naltitude' placeholder='Enter altitude' length=32><br><label>interval: </label><h3><input type='text' name='interval' id='interval' placeholder='Enter interval' length=32><br><h3><label>DEVICE ID: </label><h3><input type='text' name='ndeviceid' id='ndeviceid' placeholder='Enter DEVICE ID' length=32><br><button><input id='connect' type='submit'></button></div></form>";
            //content += "</p><form method='get' action='/setting'><h3><label>SSID: </label><h3><input type='text' name='ssid' id='ssid' placeholder='Enter Username' length=32><br><h3><label>PASSWORD:<label></h3><input type='password' id='pass' name='pass' placeholder='Enter Password' length=64><br><button><input id='connect' type='submit'></button></div></form>";
            content += "</html>";
            server.send(200, "text/html", content);
        });
        server.on("/scan", []() {
            //SETUP_AP();
            IPAddress ip = WiFi.softAPIP();
            String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);

            content = "<!DOCTYPE HTML>\r\n<html>go back";
            server.send(200, "text/html", content);
        });
        server.on("/setting", HTTP_OPTIONS,[](){
          Serial.print("CORS");
          server.send(204);
          });
        server.on("/setting",HTTP_GET, []() {
            String qsid = server.arg("ssid");
            String qpass = server.arg("pass");          
            String ChannelID = server.arg("ChannelID");
            String ChannelName = server.arg("ChannelName");
            String TimeZone = server.arg("TimeZone"); // TimeZone
            String longitude = server.arg("longitude");
            String latitude = server.arg("latitude");
            String naltitude = server.arg("naltitude"); //altitude
            String interval = server.arg("interval");
           // String alert = server.arg("alert");
            String ndeviceid = server.arg("ndeviceid");

            if (qsid.length() > 0 && qpass.length() > 0)
            {
                
                Serial.println("clearing eeprom");
                for (int i = 0; i < 78; ++i)
                {
                    EEPROM.write(i, 0);
                }
                Serial.println(qsid);
                Serial.println("");
                Serial.println(qpass);
                Serial.println("");

                Serial.println("writing eeprom ssid:");
                for (int i = 0; i < qsid.length(); ++i)
                {
                    EEPROM.write(14 + i, qsid[i]);
                    Serial.print("Wrote: ");
                    Serial.println(qsid[i]);
                }
                Serial.println("writing eeprom pass:");
                for (int i = 0; i < qpass.length(); ++i)
                {
                    EEPROM.write(46 + i, qpass[i]);
                    Serial.print("Wrote: ");
                    Serial.println(qpass[i]);
                }
                
                Serial.println("writing eeprom Channel ID:");
                for (int i = 0; i < ChannelID.length(); ++i)
                {
                  EEPROM.write( 78 + i, ChannelID[i]);
                  Serial.print("Wrote: ");
                  Serial.println(ChannelID[i]);
                }
                Serial.println("writing eeprom Channel Name:");
                for (int i = 0; i < ChannelName.length(); ++i)
                {
                  EEPROM.write(86 + i, ChannelName[i]);
                  Serial.print("Wrote: ");
                  Serial.println(ChannelName[i]);
                }
                Serial.println("writing eeprom TimeZone:");
                for (int i = 0; i < TimeZone.length(); ++i) ///TimeZone 96 to 101 we have 3 bit extra
                {
                  EEPROM.write( 96 + i, TimeZone[i]);
                  Serial.print("Wrote: ");
                  Serial.println(TimeZone[i]);
                }
        
                Serial.println("writing eeprom latitide:");
                for (int i = 0; i < latitude.length(); ++i) ///latitide
                {
                  EEPROM.write( 104 + i, latitude[i]);
                  Serial.print("Wrote: ");
                  Serial.println(latitude[i]);
                }
        
                Serial.println("writing eeprom longitude:");
                for (int i = 0; i < longitude.length(); ++i) ///longitude
                {
                  EEPROM.write( 112 + i, longitude[i]);
                  Serial.print("Wrote: ");
                  Serial.println(longitude[i]);
                }
        
                Serial.println("writing eeprom altitude:");
                for (int i = 0; i < naltitude.length(); ++i) ///altitude
                {
                  EEPROM.write( 124 + i, naltitude[i]);
                  Serial.print("Wrote: ");
                  Serial.println(naltitude[i]);
                }
        
                Serial.println("writing eeprom interval:");
                for (int i = 0; i < interval.length(); ++i) ///interval
                {
                  EEPROM.write( 180 + i, interval[i]);
                  Serial.print("Wrote: ");
                  Serial.println(interval[i]);
                }
        
               // Serial.println("writing eeprom alert:");
               // for (int i = 0; i < alert.length(); ++i) ///alert
               // {
               //   EEPROM.write( 185 + i, alert[i]);
               //   Serial.print("Wrote: ");
               //   Serial.println(alert[i]);
               // }
               /* Serial.println("writing eeprom ndeviceid:");
                for (int i = 0; i < ndeviceid.length(); ++i) ///alert
                {
                  EEPROM.write( 190 + i, ndeviceid[i]);
                  Serial.print("Wrote: ");
                  Serial.println(ndeviceid[i]);
                }*/
                EEPROM.commit();
               /* unsigned int gunConnection_Status_Flag;
                 gunConnection_Status_Flag = 0;
                EEPROM.write(212, gunConnection_Status_Flag);
                Serial.print("gunConnection_Status_Flag is : ");
                Serial.println(gunConnection_Status_Flag);
                EEPROM.commit();*/

                IPAddress ip = WiFi.softAPIP();

                String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
                Serial.print("ipStr :");
                Serial.println(ipStr);
                content = "<!DOCTYPE HTML>\r\n<html>SUCESS";
                content += "</html>";
                server.send(200, "text/html", content);
                statusCode = 200;
                delay(2000);
                ESP.reset();
            }
            else
            {
                content = "{\"Error\":\"404 not found\"}";
                statusCode = 404;
                Serial.println("Sending 404");
            }
            server.sendHeader("Access-Control-Allow-Origin", "*");
            server.send(statusCode, "application/json", content);
        });
    }

}       


void DTCT_WiFi_CON(void)
{
  while ((WiFi.status() != WL_CONNECTED)) // Keep waiting till WiFi Connect and then Start Server
  {
      //digitalWrite(13, !digitalRead(13));
      //delay(100);
      server.handleClient();
  }
}

//***********************************************WiFiAutoConnectNOConfig*************************************************************************//  
   

void WiFi_AUTO_CON_NO_CONFIG(void)
{
  pinMode(ConfigLED, OUTPUT);
  digitalWrite(ConfigLED, HIGH);
  pinMode(InternetConLED, OUTPUT);
  digitalWrite(InternetConLED, LOW);
  //---------------------------------------- Read eeprom for ssid and pass
  //*------------------------ EEPROM STARTING LOCATION: 2, EEPROM LOC 0 AND 1 ARE SAVED FOR FLAGS---------------------//
  Serial.println("Reading EEPROM ssid");

  for (int i = 14; i < 46; ++i)

  {
    esid += char(EEPROM.read(i));
  }
  Serial.print("SSID: ");
  Serial.println(esid);
  Serial.println("Reading EEPROM pass");

  for (int i = 46; i < 78; ++i)
  {
    epass += char(EEPROM.read(i));
  }
  Serial.print("PASS: ");
  Serial.println(epass);

  WiFi.begin(esid.c_str(), epass.c_str());    //  WiFi.begin("D-Link_DIR-615", "\"#@t#w@y\"");
  
  i=0;
  while(i<=10)
  {
    if(WiFi.status() == WL_CONNECTED)
    {
      break;
     
    }
    else
    {
      Serial.println(".");
    }
    i++;
    delay(1000);
  }

  if(WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Configuration mode has to be enabled: Press Hard Factory Reset");
    pinMode(pswFactoryReset, INPUT);
    while(digitalRead(pswFactoryReset) != 1)
    {
      Serial.println("Press hard factory reset to configure: ");
      delay(1000);
    }
  }
  Serial.println("Succesfully Connected!!!");

}


//***********************************************WiFiAutoConnect*************************************************************************//  
   

void RD_SSID_PWD_EEPROM_WiFi_AUTO_CON(void)  
{
    pinMode(ConfigLED, OUTPUT);
    digitalWrite(ConfigLED, HIGH);
    pinMode(InternetConLED, OUTPUT);
    digitalWrite(InternetConLED, LOW);
    //---------------------------------------- Read eeprom for ssid and pass
    Serial.println("Reading EEPROM ssid");
    
    for (int i = 14; i < 46; ++i) 
    {
        esid += char(EEPROM.read(i));
    }
    
    Serial.print("SSID: ");
    Serial.println(esid);
    Serial.println("Reading EEPROM pass");
    
    for (int i = 46; i < 78; ++i)
    {
        epass += char(EEPROM.read(i));
    }
    Serial.print("PASS: ");
    Serial.println(epass);

    WiFi.begin(esid.c_str(), epass.c_str());    //  WiFi.begin("D-Link_DIR-615", "\"#@t#w@y\"");

     if (TEST_WiFi())
    {
       // digitalWrite(13,LOW);
       // digitalWrite(12,HIGH);
        WiFi.softAPdisconnect();
        Serial.println("Succesfully Connected!!!");
        //return;
    }
    else
    {
        Serial.println("Turning the HotSpot On");
        LAUNCH_WEB();
        SETUP_AP(); // Setup HotSpot
    }
    DTCT_WiFi_CON();
}


   
//RTC_DS1307 rtc; 


/*********************************** Declaration of RTC variables***********************/

  unsigned char b[4][16];
  //char gchCharArrayBuf[224];
 
//  int k;
/*unsigned int D1S1TimeToIntegerValueON;
unsigned int NonRepeatFlagD1S1On;
unsigned int D1S1TimeToIntegerValueOFF;
unsigned int NonRepeatFlagD1S1Off;
unsigned int D1S2TimeToIntegerValueON;
unsigned int NonRepeatFlagD1S2On;
unsigned int D1S2TimeToIntegerValueOFF;
unsigned int NonRepeatFlagD1S2Off;
unsigned int D1S3TimeToIntegerValueON;
unsigned int NonRepeatFlagD1S3On;
unsigned int D1S3TimeToIntegerValueOFF;
unsigned int NonRepeatFlagD1S3Off;

unsigned int D2S1TimeToIntegerValueON;
unsigned int D2S1TimeToIntegerValueOFF;
unsigned int D2S2TimeToIntegerValueON;
unsigned int D2S2TimeToIntegerValueOFF;
unsigned int D2S3TimeToIntegerValueON;
unsigned int D2S3TimeToIntegerValueOFF;

unsigned int D3S1TimeToIntegerValueON;
unsigned int D3S1TimeToIntegerValueOFF;
unsigned int D3S2TimeToIntegerValueON;
unsigned int D3S2TimeToIntegerValueOFF;
unsigned int D3S3TimeToIntegerValueON;
unsigned int D3S3TimeToIntegerValueOFF;

unsigned int D4S1TimeToIntegerValueON;
unsigned int D4S1TimeToIntegerValueOFF;
unsigned int D4S2TimeToIntegerValueON;
unsigned int D4S2TimeToIntegerValueOFF;
unsigned int D4S3TimeToIntegerValueON;
unsigned int D4S3TimeToIntegerValueOFF;*/
  
  int gnRTCCurrentTime;
  int gnRTCWeekDay;
  //int gnUserWeekDay[7]={1,1,0,0,0,1,1};// 1->SMTWTFS
  int gnRTCActualWeekDay[7];
  
  int gnRTCCurrentTimeDump;
  unsigned int TimeToIntegerValueON;//sunitha (RTC)
  unsigned int TimeToIntegerValueOFF;
  //int t=0;




/****************************FUNCTION FOR READING THE EEPROM ADDRESS AND PRINT**************************************/

void EEPROM_RD(void)
{
   Serial.println(" EEPROM READING ");
   String addr;
  for (int i = 96; i <101; ++i)
  {
    Read_GMT_Time += char(EEPROM.read(i));
  }
  
  Serial.println();
  Serial.print("GMT TIME: ");
  Serial.println(Read_GMT_Time);

   //unGMT_Dir = Read_GMT_Time[0];
      if(Read_GMT_Time[0] == '+')
      {
        unGMT_Dir =1;
      }
      else if(Read_GMT_Time[0] == '-')
      {
         unGMT_Dir =2;
      }
      String Str_GMT_HH;
      String Str_GMT_MM;
      for(i=1; i<3; ++i)
      {
        Str_GMT_HH = Str_GMT_HH +  Read_GMT_Time[i] ;
      }
      for(i=3; i<5; ++i)
      {
        Str_GMT_MM = Str_GMT_MM +  Read_GMT_Time[i] ;
      }
      unGMT_HH = Str_GMT_HH.toInt();
      Serial.println(unGMT_HH);
      unGMT_MM = Str_GMT_MM.toInt();
      Serial.println(unGMT_MM);
      Serial.println(unGMT_Dir);
      delay(10);   
  

Serial.println(" EEPROM READING ");
   //String addr;
  for (int i = 78; i <86; ++i)
  {
    Read_Channel_ID += char(EEPROM.read(i));
  }
  
  Serial.println();
  Serial.print("Channel ID: ");
  Serial.println(Read_Channel_ID);
   delay(10);
  
Serial.println(" EEPROM READING ");
   //String addr;
  for (int i = 86; i <96; ++i)
  {
    Read_Channel_Name += char(EEPROM.read(i));
  }
  
  Serial.println();
  Serial.print("Channel Name: ");
  Serial.println(Read_Channel_Name);
  delay(10);

  
   

Serial.println(" EEPROM READING ");
   String EEPROM_addr;
  for (int i = 127; i <511; ++i)
  {
    EEPROM_addr += char(EEPROM.read(i));
  }
  
  Serial.println();
  Serial.print("EEPROM_addr: ");
  Serial.println(EEPROM_addr);
  delay(10); 

  EEPROM_addr.toCharArray(gchCharArrayBuf,EEPROM_addr.length()+1);
//  Serial.println("gchCharArrayBuf");
//  Serial.print(gchCharArrayBuf);

  for(j=0;j<24;j++)
  {
    for(k=0;k<16;k++)
    {
     gunchCharArrayBuf_2D[j][k]=gchCharArrayBuf[i++];
    }
  }

  for(j=0;j<24;j++)
  {
    for(k=0;k<16;k++)
    {
      Serial.print(gunchCharArrayBuf_2D[j][k]);
      Serial.print(" ");
    }
    Serial.println(" ");
  }
}

/****************************FUNCTION FOR CONVERTING EEPROM VALUES TO INTEGER; TIME COVERSION***********************/
   
    
    int EEPROM_T_INT(unsigned char uchLocation);
    int EEPROM_T_INT(unsigned char uchLocation)// time converstion
    {
  

      int nNumber=0;
      nNumber = gunchCharArrayBuf_2D[uchLocation][4]-'0';
      nNumber = nNumber*10 + gunchCharArrayBuf_2D[uchLocation][5]-'0';
      nNumber = nNumber*10 + gunchCharArrayBuf_2D[uchLocation][6]-'0';
      nNumber = nNumber*10 + gunchCharArrayBuf_2D[uchLocation][7]-'0';
      return nNumber;
    
    }

void STR_NF_T_2DARRAY(void)
{
  D1S1TimeToIntegerValueON= EEPROM_T_INT(0); // Device 1 Set 1 on
  //Serial.println("D1S1TimeToIntegerValueON");Serial.println(D1S1TimeToIntegerValueON);
  D1S1TimeToIntegerValueOFF= EEPROM_T_INT(1); // Device 1 set 1 off
  //Serial.println("D1S1TimeToIntegerValueOFF");Serial.println(D1S1TimeToIntegerValueOFF);
  D1S2TimeToIntegerValueON= EEPROM_T_INT(2); // Device 1 Set 2 on
  //Serial.println("D1S2TimeToIntegerValueON");Serial.println(D1S2TimeToIntegerValueON);
  D1S2TimeToIntegerValueOFF= EEPROM_T_INT(3); // Device 1 set 2 off
  //Serial.println("D1S2TimeToIntegerValueOFF");Serial.println(D1S2TimeToIntegerValueOFF);
  D1S3TimeToIntegerValueON= EEPROM_T_INT(4); // Device 1 Set 3 on
  //Serial.println("D1S3TimeToIntegerValueON");Serial.println(D1S3TimeToIntegerValueON);
  D1S3TimeToIntegerValueOFF= EEPROM_T_INT(5); // Device 1 set 3 off
  //Serial.println("D1S3TimeToIntegerValueOFF");Serial.println(D1S3TimeToIntegerValueOFF);

  D2S1TimeToIntegerValueON= EEPROM_T_INT(6); // Device 2 Set 1 on
  //Serial.println("D2S1TimeToIntegerValueON");Serial.println(D2S1TimeToIntegerValueON);
  D2S1TimeToIntegerValueOFF= EEPROM_T_INT(7); // Device 2 set 1 off
  //Serial.println("D2S1TimeToIntegerValueOFF");Serial.println(D2S1TimeToIntegerValueOFF);
  D2S2TimeToIntegerValueON= EEPROM_T_INT(8); // Device 2 Set 2 on
  //Serial.println("D2S2TimeToIntegerValueON");Serial.println(D2S2TimeToIntegerValueON);
  D2S2TimeToIntegerValueOFF= EEPROM_T_INT(9); // Device 2 set 2 off
  //Serial.println("D2S2TimeToIntegerValueOFF");Serial.println(D2S2TimeToIntegerValueOFF);
  D2S3TimeToIntegerValueON= EEPROM_T_INT(10); // Device 2 Set 3 on
  //Serial.println("D2S3TimeToIntegerValueON");Serial.println(D2S3TimeToIntegerValueON);
  D2S3TimeToIntegerValueOFF= EEPROM_T_INT(11); // Device 2 set 3 off
  //Serial.println("D2S3TimeToIntegerValueOFF");Serial.println(D2S3TimeToIntegerValueOFF);

  D3S1TimeToIntegerValueON= EEPROM_T_INT(12); // Device 3 Set 1 on
  //Serial.println("D3S1TimeToIntegerValueON");Serial.println(D3S1TimeToIntegerValueON);
  D3S1TimeToIntegerValueOFF= EEPROM_T_INT(13); // Device 3 set 1 off
  //Serial.println("D3S1TimeToIntegerValueOFF");Serial.println(D3S1TimeToIntegerValueOFF);
  D3S2TimeToIntegerValueON= EEPROM_T_INT(14); // Device 3 Set 2 on
  //Serial.println("D3S2TimeToIntegerValueON");Serial.println(D3S2TimeToIntegerValueON);
  D3S2TimeToIntegerValueOFF= EEPROM_T_INT(15); // Device 3 set 2 off
  //Serial.println("D3S2TimeToIntegerValueOFF");Serial.println(D3S2TimeToIntegerValueOFF);
  D3S3TimeToIntegerValueON= EEPROM_T_INT(16); // Device 3 Set 3 on
  //Serial.println("D3S3TimeToIntegerValueON");Serial.println(D3S3TimeToIntegerValueON);
  D3S3TimeToIntegerValueOFF= EEPROM_T_INT(17); // Device 3 set 3 off
  //Serial.println("D3S3TimeToIntegerValueOFF");Serial.println(D3S3TimeToIntegerValueOFF);

  D4S1TimeToIntegerValueON= EEPROM_T_INT(18); // Device 4 Set 1 on
  //Serial.println("D4S1TimeToIntegerValueON");Serial.println(D4S1TimeToIntegerValueON);
  D4S1TimeToIntegerValueOFF= EEPROM_T_INT(19); // Device 4 set 1 off
  //Serial.println("D4S1TimeToIntegerValueOFF");Serial.println(D4S1TimeToIntegerValueOFF);
  D4S2TimeToIntegerValueON= EEPROM_T_INT(20); // Device 4 Set 2 on
  //Serial.println("D4S2TimeToIntegerValueON");Serial.println(D4S2TimeToIntegerValueON);
  D4S2TimeToIntegerValueOFF= EEPROM_T_INT(21); // Device 4 set 2 off
  //Serial.println("D4S2TimeToIntegerValueOFF");Serial.println(D4S2TimeToIntegerValueOFF);
  D4S3TimeToIntegerValueON= EEPROM_T_INT(22); // Device 4 Set 3 on
  //Serial.println("D4S3TimeToIntegerValueON");Serial.println(D4S3TimeToIntegerValueON);
  D4S3TimeToIntegerValueOFF= EEPROM_T_INT(23); // Device 4 set 3 off
  //Serial.println("D4S3TimeToIntegerValueOFF");Serial.println(D4S3TimeToIntegerValueOFF);

}




//********************FUNCTION FOR RTC UPDATE****************************************************************************************//

void UPD_RTC()
{
  //delay(5000);
  Serial.println("Edit Mode..");
 
  const char txt[6][15] = { "year [4-digit]", "month [1~12]", "day [1~31]",
                            "hours [0~23]", "minutes [0~59]", "seconds [0~59]"};// ask user to enter new date and time
  String str = "";
  long newDate[6];
  while (Serial.available()) 
  {
    Serial.read();  // clear serial buffer
  }

  for (int i = 0; i < 6; i++) 
  {
    Serial.print("Enter ");
    Serial.print(txt[i]);
    Serial.print(": ");

   while (!Serial.available()) 
   {
      ; // wait for user input
   }

   str = Serial.readString();  // read user input
   newDate[i] = str.toInt();   // convert user input to number and save to array
   Serial.println(newDate[i]); // show user input
  }

  // update RTC
  rtc.adjust(DateTime(newDate[0], newDate[1], newDate[2], newDate[3], newDate[4], newDate[5]));
  Serial.println("RTC Updated!");




}


//********************FUNCTION FOR RTC READ*************************************************************//


void RTC_RD()// Reading data of DS1307
{
        //delay(5000);
        const char dayInWords[8][4] = {"", "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"}; // 0=SUN,1-MON,2-TUE,3-WED,4-THR,5-FRI,6-SAT
        const char monthInWords[13][4] = {" ", "JAN", "FEB", "MAR", "APR", "MAY", "JUN", 
                                             "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"}; // 0-NO USE,1-JAN,2-FEB,3-MAR,4-APR,5-MAY,6-JUNE,7-JULY,8-AUG,9-SEP,10-OCT,11-NOV,12-DEC // get time and date from RTC and save in variables
        DateTime rtcTime = rtc.now();
      
        int ss = rtcTime.second();
        int mm = rtcTime.minute();
        //int hh = rtcTime.twelveHour();
        int hh = rtcTime.hour();
        int DD = rtcTime.dayOfTheWeek();
        int dd = rtcTime.day();
        int MM = rtcTime.month();
        int yyyy = rtcTime.year();
      
        Serial.println(" date details");
        Serial.println(" ");
        // print date in dd-MMM-yyyy format and day of week
        if (dd < 10)   // add preceeding '0' if number is less than 10
        Serial.print('0');
        Serial.print(dd); // Date
        Serial.print("-");
        Serial.print(monthInWords[MM]); // Mon
        Serial.print("-");
        Serial.print(yyyy); // year
        Serial.println(" ");
      
      //  Serial.println("Day in a week int value ");  
      //  Serial.print(DD);
      
      //  Serial.println("Day in a week");  
      //  Serial.print(dayInWords[DD]);
       // delay(2000);
        Serial.println("Time");
        // print time in 12H format
        if (hh < 10)
        Serial.print('0');
        Serial.print(hh);
        Serial.print(':');
        if (mm < 10) 
        Serial.print('0');
        Serial.print(mm);
        Serial.print(':');
      
        if (ss < 10)
        Serial.print('0'); 
        Serial.print(ss);
      
  if (DD == 0) 
  {
    gnRTCActualWeekDay[0] = 1; //sun
  } 
  else 
  {
    gnRTCActualWeekDay[0] = 0;
  }
  if (DD == 1) 
  {
    gnRTCActualWeekDay[1] = 1; //mon
  } else 
  {
    gnRTCActualWeekDay[1] = 0;
  }
  if (DD == 2) 
  {
    gnRTCActualWeekDay[2] = 1; //tue
  } 
  else 
  {
    gnRTCActualWeekDay[2] = 0;
  }
  if (DD == 3)
  {
    gnRTCActualWeekDay[3] = 1; //wed
  } else 
  {
    gnRTCActualWeekDay[3] = 0;
  }
  if (DD == 4) 
  {
    gnRTCActualWeekDay[4] = 1; //thr
  } else {
    gnRTCActualWeekDay[4] = 0;
  }
  if (DD == 5) 
  {
    gnRTCActualWeekDay[5] = 1; //fri
  } else 
  {
    gnRTCActualWeekDay[5] = 0;
  }
  if (DD == 6) 
  {
    gnRTCActualWeekDay[6] = 1; //sat
  } 
  else 
  {
    gnRTCActualWeekDay[6] = 0;
  }
      
      
      Serial.println(" After concverstion gnRTCActualWeekDay");
      
       for (i=0;i<7;i++)
      {
        Serial.print(gnRTCActualWeekDay[i]); // week days array
        
      }
      
      delay(1000);
      gnRTCCurrentTime=hh*100+mm; // rtc value into integers
      Serial.println("gnRTCCurrentTime");
      Serial.println(gnRTCCurrentTime);
      delay(10);
      Serial.println("D1S1TimeToIntegerValueON");
      Serial.println(D1S1TimeToIntegerValueON);
      Serial.println("D1S1TimeToIntegerValueOFF");
      Serial.println(D1S1TimeToIntegerValueOFF);
      Serial.println("D1S2TimeToIntegerValueON");
      Serial.println(D1S2TimeToIntegerValueON);
      Serial.println("D1S2TimeToIntegerValueOFF");
      Serial.println(D1S2TimeToIntegerValueOFF);
      Serial.println("D1S3TimeToIntegerValueON");
      Serial.println(D1S3TimeToIntegerValueON);
      Serial.println("D1S3TimeToIntegerValueOFF");
      Serial.println(D1S3TimeToIntegerValueOFF);
      
      Serial.println("D2S1TimeToIntegerValueOn");
      Serial.println(D2S1TimeToIntegerValueON);
      Serial.println("D2S1TimeToIntegerValueOFF");
      Serial.println(D2S1TimeToIntegerValueOFF);
      Serial.println("D2S2TimeToIntegerValueON");
      Serial.println(D2S2TimeToIntegerValueON);
      Serial.println("D2S2TimeToIntegerValueOFF");
      Serial.println(D2S2TimeToIntegerValueOFF);
      Serial.println("D2S3TimeToIntegerValueON");
      Serial.println(D2S3TimeToIntegerValueON);
      Serial.println("D2S3TimeToIntegerValueOFF");
      Serial.println(D2S3TimeToIntegerValueOFF);
      
      Serial.println("D3S1TimeToIntegerValueON");
      Serial.println(D3S1TimeToIntegerValueON);
      Serial.println("D3S1TimeToIntegerValueOFF");
      Serial.println(D3S1TimeToIntegerValueOFF);
      Serial.println("D3S2TimeToIntegerValueON");
      Serial.println(D3S2TimeToIntegerValueON);
      Serial.println("D3S2TimeToIntegerValueOFF");
      Serial.println(D3S2TimeToIntegerValueOFF);
      Serial.println("D3S3TimeToIntegerValueON");
      Serial.println(D3S3TimeToIntegerValueON);
      Serial.println("D3S3TimeToIntegerValueOFF");
      Serial.println(D3S3TimeToIntegerValueOFF);
      
      Serial.println("D4S1TimeToIntegerValueON");
      Serial.println(D4S1TimeToIntegerValueON);
      Serial.println("D4S1TimeToIntegerValueOFF");
      Serial.println(D4S1TimeToIntegerValueOFF);
      Serial.println("D4S2TimeToIntegerValueON");
      Serial.println(D4S2TimeToIntegerValueON);
      Serial.println("D4S2TimeToIntegerValueOFF");
      Serial.println(D4S2TimeToIntegerValueOFF);
      Serial.println("D4S3TimeToIntegerValueON");
      Serial.println(D4S3TimeToIntegerValueON);
      Serial.println("D4S3TimeToIntegerValueOFF");
      Serial.println(D4S3TimeToIntegerValueOFF);





 /*******************************************************DEVICE1 SET1 **********************************************************/ 
 
    if (gnRTCCurrentTime == D1S1TimeToIntegerValueON)
      {
        Serial.println("_________Device 1 set 1_________________________________________");
        Serial.println(" in the rtc loop");
        if((gunchCharArrayBuf_2D[0][1] == 'C') && (gunchCharArrayBuf_2D[0][2] == '1'))
        {
          Serial.println(" in the config loop");
          if(gunchCharArrayBuf_2D[0][3] == 'R')
          {
          Serial.println(" in the repeat loop");
          
            if ( (gnRTCActualWeekDay[0] && (gunchCharArrayBuf_2D[0][8]-'0')) ||(gnRTCActualWeekDay[1] && (gunchCharArrayBuf_2D[0][9]-'0'))||(gnRTCActualWeekDay[2] && (gunchCharArrayBuf_2D[0][10]-'0')) ||(gnRTCActualWeekDay[3] == (gunchCharArrayBuf_2D[0][11]-'0')) ||
              (gnRTCActualWeekDay[4] && (gunchCharArrayBuf_2D[0][12]-'0')) || (gnRTCActualWeekDay[5] && (gunchCharArrayBuf_2D[0][13]-'0'))||(gnRTCActualWeekDay[6] && (gunchCharArrayBuf_2D[0][14]-'0')))      
              {
                Serial.println(" led on repeat DEVICE 1 SET1 ");
                Serial.println("**11");
                Device1_Status = 1;
                
              }
          }
          
          else if(gunchCharArrayBuf_2D[0][3] == 'N')
          {
          if(NonRepeatFlagD1S1On == 1)
          {
            Serial.println(" in the notrepeat loop");       
            Serial.println(" led on notrepeat DEVICE 1 SET1 ");
            Serial.println("**11");
            Device1_Status = 1;
            NonRepeatFlagD1S1On =0;
            //EEPROM.write(gunchCharArrayBuf_2D[0][3],'S');// WRITING STOP TO GET LED GLOW ONLY 1 TIME                
           
         }
        }
         else
           {
            Serial.println(" led off ");
           }
          } 
         }
      
       if (gnRTCCurrentTime == D1S1TimeToIntegerValueOFF)
      {
        Serial.println("_________Device 1 set 1_________________________________________");
        Serial.println(" in the rtc loop");
        if((gunchCharArrayBuf_2D[1][1] == 'C') && (gunchCharArrayBuf_2D[1][2] == '0'))
        {
          Serial.println(" in the config loop");
          if(gunchCharArrayBuf_2D[1][3] == 'R')
          {
          Serial.println(" in the repeat loop");
            
            if ( (gnRTCActualWeekDay[0] && (gunchCharArrayBuf_2D[1][8]-'0')) ||(gnRTCActualWeekDay[1] && (gunchCharArrayBuf_2D[1][9]-'0'))||(gnRTCActualWeekDay[2] && (gunchCharArrayBuf_2D[1][10]-'0')) ||(gnRTCActualWeekDay[3] == (gunchCharArrayBuf_2D[1][11]-'0')) ||
              (gnRTCActualWeekDay[4] && (gunchCharArrayBuf_2D[1][12]-'0')) || (gnRTCActualWeekDay[5] && (gunchCharArrayBuf_2D[1][13]-'0'))||(gnRTCActualWeekDay[6] && (gunchCharArrayBuf_2D[1][14]-'0')))      
              {
                Serial.println(" led off repeat DEVICE 1 SET1 ");
                Serial.println("**10");
                Device1_Status =0;
              }
          }
          
          else if(gunchCharArrayBuf_2D[1][3] == 'N')
           {
            if(NonRepeatFlagD1S1Off == 1)
            {
            Serial.println(" in the notrepeat loop");
                 
            Serial.println(" led off notrepeat DEVICE 1 SET1 ");
            Serial.println("**10");
            Device1_Status = 0;
            //EEPROM.write(gunchCharArrayBuf_2D[0][3],'S');// WRITING STOP TO GET LED GLOW ONLY 1 TIME
            NonRepeatFlagD1S1Off = 0;                
              
            }
           }
           else
           {
            Serial.println(" led on ");
           }  
         }
         
       }

/***********************************************DEVICE1 SET2 ALARM********************************************************************/

       if (gnRTCCurrentTime == D1S2TimeToIntegerValueON) 
        {
        
          Serial.println("_________Device 1 set 2_________________________________________");
          Serial.println(" in the rtc loop");
          if((gunchCharArrayBuf_2D[2][1] == 'C') && (gunchCharArrayBuf_2D[2][2] == '1'))
          {
              Serial.println(" in the config loop");
            if(gunchCharArrayBuf_2D[2][3] == 'R')
            {
            Serial.println(" in the repeat loop");
              
              if ( (gnRTCActualWeekDay[0] && (gunchCharArrayBuf_2D[2][8]-'0')) ||(gnRTCActualWeekDay[1] && (gunchCharArrayBuf_2D[2][9]-'0'))||(gnRTCActualWeekDay[2] && (gunchCharArrayBuf_2D[2][10]-'0')) ||(gnRTCActualWeekDay[3] && (gunchCharArrayBuf_2D[2][11]-'0')) ||
                (gnRTCActualWeekDay[4] && (gunchCharArrayBuf_2D[2][12]-'0')) || (gnRTCActualWeekDay[5] && (gunchCharArrayBuf_2D[2][13]-'0'))||(gnRTCActualWeekDay[6] && (gunchCharArrayBuf_2D[2][14]-'0')))      
                {
                  Serial.println(" led on repeat DEVICE 1 SET2 ");
                  Serial.println("**11");
                  Device1_Status = 1;
                }
            }
            
            else if(gunchCharArrayBuf_2D[2][3] == 'N')
             {
              if(NonRepeatFlagD1S2On == 1)
              {
              Serial.println(" in the notrepeat loop");
                  
              Serial.println(" led on notrepeat DEVICE 1 SET2 ");
              Serial.println("**11");
              Device1_Status =  1;
              NonRepeatFlagD1S2On = 0;
              //EEPROM.write(gunchCharArrayBuf_2D[2][3],'S');// WRITING STOP TO GET LED GLOW ONLY 1 TIME                
                
              }
             }
              else
              {
                Serial.println(" led off ");
              }  
           }
      }
      if (gnRTCCurrentTime == D1S2TimeToIntegerValueOFF)
      {
        Serial.println("_________Device 1 set 2_________________________________________");
        Serial.println(" in the rtc loop");
        if((gunchCharArrayBuf_2D[3][1] == 'C') && (gunchCharArrayBuf_2D[3][2] == '0'))
        {
          Serial.println(" in the config loop");
          if(gunchCharArrayBuf_2D[3][3] == 'R')
          {
          Serial.println(" in the repeat loop");
            
            if ( (gnRTCActualWeekDay[0] && (gunchCharArrayBuf_2D[3][8]-'0')) ||(gnRTCActualWeekDay[1] && (gunchCharArrayBuf_2D[3][9]-'0'))||(gnRTCActualWeekDay[2] && (gunchCharArrayBuf_2D[3][10]-'0')) ||(gnRTCActualWeekDay[3] == (gunchCharArrayBuf_2D[3][11]-'0')) ||
              (gnRTCActualWeekDay[4] && (gunchCharArrayBuf_2D[3][12]-'0')) || (gnRTCActualWeekDay[5] && (gunchCharArrayBuf_2D[3][13]-'0'))||(gnRTCActualWeekDay[6] && (gunchCharArrayBuf_2D[3][14]-'0')))      
              {
                Serial.println(" led off repeat DEVICE 1 SET2 ");
                Serial.println("**10");
                Device1_Status = 0;
              }
          }
          
          else if(gunchCharArrayBuf_2D[3][3] == 'N')
           {
            if(NonRepeatFlagD1S2Off == 1)
            {
            Serial.println(" in the notrepeat loop");
                 
            Serial.println(" led off notrepeat DEVICE 1 SET2 ");
            Serial.println("**10");
            Device1_Status = 0;
            NonRepeatFlagD1S2Off = 0;
            //EEPROM.write(gunchCharArrayBuf_2D[0][3],'S');// WRITING STOP TO GET LED GLOW ONLY 1 TIME                
              
            }
           }
           else
           {
            Serial.println(" led on ");
           }  
         }            
      }
/******************************* DEVICE 1 SET 3 ****************************************************************/

 if (gnRTCCurrentTime == D1S3TimeToIntegerValueON)
{
  Serial.println("_________Device 1 set 3_________________________________________");
  Serial.println(" in the rtc loop");
  if((gunchCharArrayBuf_2D[4][1] == 'C') && (gunchCharArrayBuf_2D[4][2] == '1'))
  {
      Serial.println(" in the config loop");
    if(gunchCharArrayBuf_2D[4][3] == 'R')
    {
    Serial.println(" in the repeat loop");
      
      if ( (gnRTCActualWeekDay[0] && (gunchCharArrayBuf_2D[4][8]-'0')) ||(gnRTCActualWeekDay[1] && (gunchCharArrayBuf_2D[4][9]-'0'))||(gnRTCActualWeekDay[2] && (gunchCharArrayBuf_2D[4][10]-'0')) ||(gnRTCActualWeekDay[3] && (gunchCharArrayBuf_2D[4][11]-'0')) ||
        (gnRTCActualWeekDay[4] && (gunchCharArrayBuf_2D[4][12]-'0')) || (gnRTCActualWeekDay[5] && (gunchCharArrayBuf_2D[4][13]-'0'))||(gnRTCActualWeekDay[6] && (gunchCharArrayBuf_2D[4][14]-'0')))      
        {
          Serial.println(" led on repeat DEVICE 1 SET3 ");
          Serial.println("**11");
          Device1_Status =1;
        }
    }
    
     else if(gunchCharArrayBuf_2D[4][3] == 'N')
             {
              if(NonRepeatFlagD1S3On == 1)
              {
              Serial.println(" in the notrepeat loop");
                  
              Serial.println(" led on notrepeat DEVICE 1 SET3 ");
              Serial.println("**11");
              Device1_Status =  1;
              NonRepeatFlagD1S3On = 0;
              //EEPROM.write(gunchCharArrayBuf_2D[2][3],'S');// WRITING STOP TO GET LED GLOW ONLY 1 TIME                
                
              }                 
        }
      }
      
      else
      {
        Serial.println(" led off ");
      }  
    } 
    


  if(gnRTCCurrentTime == D1S3TimeToIntegerValueOFF)
      {
        Serial.println("_________Device 1 set 3_________________________________________");
        Serial.println(" in the rtc loop");
        if((gunchCharArrayBuf_2D[5][1] == 'C') && (gunchCharArrayBuf_2D[5][2] == '0'))
        {
          Serial.println(" in the config loop");
          if(gunchCharArrayBuf_2D[5][3] == 'R')
          {
          Serial.println(" in the repeat loop");
            
            if ( (gnRTCActualWeekDay[0] && (gunchCharArrayBuf_2D[3][8]-'0')) ||(gnRTCActualWeekDay[1] && (gunchCharArrayBuf_2D[3][9]-'0'))||(gnRTCActualWeekDay[2] && (gunchCharArrayBuf_2D[3][10]-'0')) ||(gnRTCActualWeekDay[3] == (gunchCharArrayBuf_2D[3][11]-'0')) ||
              (gnRTCActualWeekDay[4] && (gunchCharArrayBuf_2D[3][12]-'0')) || (gnRTCActualWeekDay[5] && (gunchCharArrayBuf_2D[3][13]-'0'))||(gnRTCActualWeekDay[6] && (gunchCharArrayBuf_2D[3][14]-'0')))      
              {
                Serial.println(" led off repeat DEVICE 1 SET3 ");
                Serial.println("**10");
                Device1_Status =0;
              }
          }
          
          else if(gunchCharArrayBuf_2D[5][3] == 'N')
           {
            if(NonRepeatFlagD1S3Off == 1)
            {
            Serial.println(" in the notrepeat loop");
                 
            Serial.println(" led off notrepeat DEVICE 1 SET3 ");
            Serial.println("**10");
            Device1_Status =0;
            NonRepeatFlagD1S3Off = 0;
            //EEPROM.write(gunchCharArrayBuf_2D[0][3],'S');// WRITING STOP TO GET LED GLOW ONLY 1 TIME                
              
            }
           }
           else
           {
            Serial.println(" led on ");
           }  
         }            
      }
 /**************************************DEVICE 2 SET 1************************************/


  if (gnRTCCurrentTime == D2S1TimeToIntegerValueON) 
    {
      Serial.println("_________Device 2 set 1_________________________________________");
      Serial.println(" in the rtc loop");
      if((gunchCharArrayBuf_2D[6][1] == 'C') && (gunchCharArrayBuf_2D[6][2] == '1'))
      {
          Serial.println(" in the config loop");
        if(gunchCharArrayBuf_2D[6][3] == 'R')
        {
        Serial.println(" in the repeat loop");
          
          if ( (gnRTCActualWeekDay[0] && (gunchCharArrayBuf_2D[6][8]-'0')) ||(gnRTCActualWeekDay[1] && (gunchCharArrayBuf_2D[6][9]-'0'))||(gnRTCActualWeekDay[2] && (gunchCharArrayBuf_2D[6][10]-'0')) ||(gnRTCActualWeekDay[3] && (gunchCharArrayBuf_2D[6][11]-'0')) ||
            (gnRTCActualWeekDay[4] && (gunchCharArrayBuf_2D[6][12]-'0')) || (gnRTCActualWeekDay[5] && (gunchCharArrayBuf_2D[6][13]-'0'))||(gnRTCActualWeekDay[6] && (gunchCharArrayBuf_2D[6][14]-'0')))      
            {
              Serial.println(" led on repeat DEVICE 2 SET1 ");
              Serial.println("**21");
              Device2_Status = 1;
            }
        }  
        else if(gunchCharArrayBuf_2D[6][3] == 'N')
         {
          if(NonRepeatFlagD2S1On == 1)
          {
            Serial.println(" in the notrepeat loop");
             
            Serial.println(" led on notrepeat DEVICE 2 SET1 ");
            Serial.println("**21");
            Device2_Status = 1;
            NonRepeatFlagD2S1On =0;
          
             //EEPROM.write(gunchCharArrayBuf_2D[6][3],'S');// WRITING STOP TO GET LED GLOW ONLY 1 TIME                
          }
         }
          else
          {
            Serial.println(" led off ");
          }
       } 
    }  

     if (gnRTCCurrentTime == D2S1TimeToIntegerValueOFF)
      {
        Serial.println("_________Device 2 set 1_________________________________________");
        Serial.println(" in the rtc loop");
        if((gunchCharArrayBuf_2D[7][1] == 'C') && (gunchCharArrayBuf_2D[7][2] == '0'))
        {
          Serial.println(" in the config loop");
          if(gunchCharArrayBuf_2D[7][3] == 'R')
          {
          Serial.println(" in the repeat loop");
            
            if ( (gnRTCActualWeekDay[0] && (gunchCharArrayBuf_2D[7][8]-'0')) ||(gnRTCActualWeekDay[1] && (gunchCharArrayBuf_2D[7][9]-'0'))||(gnRTCActualWeekDay[2] && (gunchCharArrayBuf_2D[7][10]-'0')) ||(gnRTCActualWeekDay[3] == (gunchCharArrayBuf_2D[7][11]-'0')) ||
              (gnRTCActualWeekDay[4] && (gunchCharArrayBuf_2D[7][12]-'0')) || (gnRTCActualWeekDay[5] && (gunchCharArrayBuf_2D[7][13]-'0'))||(gnRTCActualWeekDay[6] && (gunchCharArrayBuf_2D[7][14]-'0')))      
              {
                Serial.println(" led off repeat DEVICE 2 SET1 ");
                Serial.println("**20");
                Device2_Status = 0;
              }
          }
          
          else if(gunchCharArrayBuf_2D[7][3] == 'N')
           {
            if(NonRepeatFlagD2S1Off == 1)
            {
              Serial.println(" in the notrepeat loop");
        
              Serial.println(" led off notrepeat DEVICE 2 SET1 ");
              Serial.println("**20");
              Device2_Status = 0;
              NonRepeatFlagD2S1Off =0;
              //EEPROM.write(gunchCharArrayBuf_2D[0][3],'S');// WRITING STOP TO GET LED GLOW ONLY 1 TIME                
             }
            }
           else
           {
            Serial.println(" led on ");
           }  
         }            
      }
    

/************************************************************DEVICE 2 SET 2*****************************************************************************/
     if (gnRTCCurrentTime == D2S2TimeToIntegerValueON) 
      {
        Serial.println("_________Device 2 set 2_________________________________________");
        if((gunchCharArrayBuf_2D[8][1] == 'C') && (gunchCharArrayBuf_2D[8][2] == '1'))
        {
          if(gunchCharArrayBuf_2D[8][3] == 'R')
          {
          Serial.println(" in the repeat loop");
           
            if ( (gnRTCActualWeekDay[0] && (gunchCharArrayBuf_2D[8][8]-'0')) ||(gnRTCActualWeekDay[1] && (gunchCharArrayBuf_2D[8][9]-'0'))||(gnRTCActualWeekDay[2] && (gunchCharArrayBuf_2D[8][10]-'0')) ||(gnRTCActualWeekDay[3] && (gunchCharArrayBuf_2D[8][11]-'0')) ||
              (gnRTCActualWeekDay[4] && (gunchCharArrayBuf_2D[8][12]-'0')) || (gnRTCActualWeekDay[5] && (gunchCharArrayBuf_2D[8][13]-'0'))||(gnRTCActualWeekDay[6] && (gunchCharArrayBuf_2D[8][14]-'0')))      
              {
                Serial.println(" led on repeat DEVICE 2 SET2 ");
                Serial.println("**21");
                Device2_Status = 1;
              }
          }
          
          else if(gunchCharArrayBuf_2D[8][3] == 'N')
           {
            if(NonRepeatFlagD2S2On == 1)
            {
                Serial.println(" in the notrepeat loop");
                     
                Serial.println(" led on notrepeat DEVICE 2 SET2 ");
                Serial.println("**21");
                Device2_Status = 1;
                NonRepeatFlagD2S2On =0;
                //EEPROM.write(gunchCharArrayBuf_2D[8][3],'S');// WRITING STOP TO GET LED GLOW ONLY 1 TIME  
            }              
              
           }
            else
            {
              Serial.println(" led off ");
            }  
           }
           
        }  

      if (gnRTCCurrentTime == D2S2TimeToIntegerValueOFF)
      {
        Serial.println("_________Device 2 set 2_________________________________________");
        Serial.println(" in the rtc loop");
        if((gunchCharArrayBuf_2D[9][1] == 'C') && (gunchCharArrayBuf_2D[9][2] == '0'))
        {
          Serial.println(" in the config loop");
          if(gunchCharArrayBuf_2D[9][3] == 'R')
          {
          Serial.println(" in the repeat loop");
            
            if ( (gnRTCActualWeekDay[0] && (gunchCharArrayBuf_2D[9][8]-'0')) ||(gnRTCActualWeekDay[1] && (gunchCharArrayBuf_2D[9][9]-'0'))||(gnRTCActualWeekDay[2] && (gunchCharArrayBuf_2D[9][10]-'0')) ||(gnRTCActualWeekDay[3] == (gunchCharArrayBuf_2D[9][11]-'0')) ||
              (gnRTCActualWeekDay[4] && (gunchCharArrayBuf_2D[9][12]-'0')) || (gnRTCActualWeekDay[5] && (gunchCharArrayBuf_2D[9][13]-'0'))||(gnRTCActualWeekDay[6] && (gunchCharArrayBuf_2D[9][14]-'0')))      
              {
                Serial.println(" led off repeat DEVICE 2 SET2 ");
                Serial.println("**20");
                Device2_Status = 0;
                
              }
          }
          
          else if(gunchCharArrayBuf_2D[9][3] == 'N')
           {
            if(NonRepeatFlagD2S2Off == 1)
            {
              Serial.println(" in the notrepeat loop");
                    
              Serial.println(" led off notrepeat DEVICE 2 SET2 ");
              Serial.println("**20");
              Device2_Status = 0;
              NonRepeatFlagD2S2Off =0;
              //EEPROM.write(gunchCharArrayBuf_2D[0][3],'S');// WRITING STOP TO GET LED GLOW ONLY 1 TIME 
            }               
          
            }
           else
           {
            Serial.println(" led on ");
           }  
         }            
      }

/***********************DEVICE 2 SET 3*****************************************/

 if (gnRTCCurrentTime == D2S3TimeToIntegerValueON) 
{
  Serial.println("_________Device 2 set 3_________________________________________");
  if((gunchCharArrayBuf_2D[10][1] == 'C') && (gunchCharArrayBuf_2D[10][2] == '1'))
  {
    if(gunchCharArrayBuf_2D[10][3] == 'R')
    {
    Serial.println(" in the repeat loop");
     
      if ( (gnRTCActualWeekDay[0] && (gunchCharArrayBuf_2D[10][8]-'0')) ||(gnRTCActualWeekDay[1] && (gunchCharArrayBuf_2D[10][9]-'0'))||(gnRTCActualWeekDay[2] && (gunchCharArrayBuf_2D[10][10]-'0')) ||(gnRTCActualWeekDay[3] && (gunchCharArrayBuf_2D[10][11]-'0')) ||
        (gnRTCActualWeekDay[4] && (gunchCharArrayBuf_2D[10][12]-'0')) || (gnRTCActualWeekDay[5] && (gunchCharArrayBuf_2D[10][13]-'0'))||(gnRTCActualWeekDay[6] && (gunchCharArrayBuf_2D[10][14]-'0')))      
        {
          Serial.println(" led on repeat DEVICE 2 SET3 ");
          Serial.println("**21");
          Device2_Status = 1;
        }
    }
    
    else if(gunchCharArrayBuf_2D[10][3] == 'N')
     {
      Serial.println(" in the notrepeat loop");
      //if ( (gnRTCActualWeekDay[0] && (gunchCharArrayBuf_2D[10][8]-'0')) ||(gnRTCActualWeekDay[1] && (gunchCharArrayBuf_2D[10][9]-'0'))||(gnRTCActualWeekDay[2] && (gunchCharArrayBuf_2D[10][10]-'0')) ||(gnRTCActualWeekDay[3] && (gunchCharArrayBuf_2D[10][11]-'0')) ||
      //(gnRTCActualWeekDay[4] && (gunchCharArrayBuf_2D[10][12]-'0')) || (gnRTCActualWeekDay[5] && (gunchCharArrayBuf_2D[10][13]-'0'))||(gnRTCActualWeekDay[6] && (gunchCharArrayBuf_2D[10][14]-'0')))      
       {   if(NonRepeatFlagD2S3On == 1)
         {     
          Serial.println(" led on notrepeat DEVICE 2 SET3 ");
          Serial.println("**21");
          Device2_Status = 1;
          NonRepeatFlagD2S3On =0;
          //EEPROM.write(gunchCharArrayBuf_2D[10][3],'S');// WRITING STOP TO GET LED GLOW ONLY 1 TIME 
         }               
        }
      }
      else
      {
        Serial.println(" led off ");
      }  
    } 
  } 

    if (gnRTCCurrentTime == D2S3TimeToIntegerValueOFF)
      {
        Serial.println("_________Device 2 set 3_________________________________________");
        Serial.println(" in the rtc loop");
        if((gunchCharArrayBuf_2D[11][1] == 'C') && (gunchCharArrayBuf_2D[11][2] == '0'))
        {
          Serial.println(" in the config loop");
          if(gunchCharArrayBuf_2D[11][3] == 'R')
          {
          Serial.println(" in the repeat loop");
            
            if ( (gnRTCActualWeekDay[0] && (gunchCharArrayBuf_2D[9][8]-'0')) ||(gnRTCActualWeekDay[1] && (gunchCharArrayBuf_2D[9][9]-'0'))||(gnRTCActualWeekDay[2] && (gunchCharArrayBuf_2D[9][10]-'0')) ||(gnRTCActualWeekDay[3] == (gunchCharArrayBuf_2D[9][11]-'0')) ||
              (gnRTCActualWeekDay[4] && (gunchCharArrayBuf_2D[9][12]-'0')) || (gnRTCActualWeekDay[5] && (gunchCharArrayBuf_2D[9][13]-'0'))||(gnRTCActualWeekDay[6] && (gunchCharArrayBuf_2D[9][14]-'0')))      
              {
                Serial.println(" led off repeat DEVICE 2 SET3 ");
                Serial.println("**20");
                Device2_Status = 0;
              }
          }
          
          else if(gunchCharArrayBuf_2D[11][3] == 'N')
           {
            if(NonRepeatFlagD2S3Off == 1)
            {
              Serial.println(" in the notrepeat loop");
                    
              Serial.println(" led off notrepeat DEVICE 2 SET3 ");
              Serial.println("**20");
              Device2_Status = 0;
              NonRepeatFlagD2S3Off =0;
              //EEPROM.write(gunchCharArrayBuf_2D[0][3],'S');// WRITING STOP TO GET LED GLOW ONLY 1 TIME
            }                
            
            }
           else
           {
            Serial.println(" led on ");
           }  
         }            
      }
      
/**************************************DEVICE 3 SET 1**********************************************************/


  if (gnRTCCurrentTime == D3S1TimeToIntegerValueON)
{
  Serial.println("_________Device 3 set 1_________________________________________");
  if((gunchCharArrayBuf_2D[12][1] == 'C') && (gunchCharArrayBuf_2D[12][2] == '1'))
  {
    if(gunchCharArrayBuf_2D[12][3] == 'R')
    {
    Serial.println(" in the repeat loop");
     
      if ( (gnRTCActualWeekDay[0] && (gunchCharArrayBuf_2D[12][8]-'0')) ||(gnRTCActualWeekDay[1] && (gunchCharArrayBuf_2D[12][9]-'0'))||(gnRTCActualWeekDay[2] && (gunchCharArrayBuf_2D[12][10]-'0')) ||(gnRTCActualWeekDay[3] && (gunchCharArrayBuf_2D[12][11]-'0')) ||
        (gnRTCActualWeekDay[4] && (gunchCharArrayBuf_2D[12][12]-'0')) || (gnRTCActualWeekDay[5] && (gunchCharArrayBuf_2D[12][13]-'0'))||(gnRTCActualWeekDay[6] && (gunchCharArrayBuf_2D[12][14]-'0')))      
        {
          Serial.println(" led on repeat DEVICE 3 SET1 ");
          Serial.println("**31");
          Device3_Status = 1;
        }
    }
    
    else if(gunchCharArrayBuf_2D[12][3] == 'N')
     {
      if(NonRepeatFlagD3S1On == 1)
      {
        Serial.println(" in the notrepeat loop");
           
        Serial.println(" led on not repeat DEVICE 3 SET1 ");
        Serial.println("**31");
        Device3_Status = 1;
        NonRepeatFlagD3S1On =0;
        
       // EEPROM.write(gunchCharArrayBuf_2D[12][3],'S');// WRITING STOP TO GET LED GLOW ONLY 1 TIME  
      }              
        
      }
      else
      {
        Serial.println(" led off ");
      }  
    } 
 }

 if (gnRTCCurrentTime == D3S1TimeToIntegerValueOFF)
    {
      Serial.println("_________Device 3 set 1_________________________________________");
      Serial.println(" in the rtc loop");
      if((gunchCharArrayBuf_2D[13][1] == 'C') && (gunchCharArrayBuf_2D[13][2] == '0'))
      {
        Serial.println(" in the config loop");
        if(gunchCharArrayBuf_2D[13][3] == 'R')
        {
        Serial.println(" in the repeat loop");
          
          if ( (gnRTCActualWeekDay[0] && (gunchCharArrayBuf_2D[13][8]-'0')) ||(gnRTCActualWeekDay[1] && (gunchCharArrayBuf_2D[13][9]-'0'))||(gnRTCActualWeekDay[2] && (gunchCharArrayBuf_2D[13][10]-'0')) ||(gnRTCActualWeekDay[3] == (gunchCharArrayBuf_2D[13][11]-'0')) ||
            (gnRTCActualWeekDay[4] && (gunchCharArrayBuf_2D[13][12]-'0')) || (gnRTCActualWeekDay[5] && (gunchCharArrayBuf_2D[13][13]-'0'))||(gnRTCActualWeekDay[6] && (gunchCharArrayBuf_2D[13][14]-'0')))      
            {
              Serial.println(" led off repeat DEVICE 3 SET1 ");
              Serial.println("**30");
              Device3_Status = 0;
            }
        }
        
        else if(gunchCharArrayBuf_2D[13][3] == 'N')
         {
           if(NonRepeatFlagD3S1Off == 1)
           {
              Serial.println(" in the notrepeat loop");
                 
              Serial.println(" led off notrepeat DEVICE 3 SET1 ");
              Serial.println("**30");
              Device3_Status = 0;
              NonRepeatFlagD3S1Off =0;
              //EEPROM.write(gunchCharArrayBuf_2D[0][3],'S');// WRITING STOP TO GET LED GLOW ONLY 1 TIME  
           }              
            
          }
         else
         {
          Serial.println(" led on ");
         }  
       }            
    }


/********************************DEVICE 3 SET 2************************/

 if (gnRTCCurrentTime == D3S2TimeToIntegerValueON)
{
  Serial.println("_________Device 3 set 2_________________________________________");
  if((gunchCharArrayBuf_2D[14][1] == 'C') && (gunchCharArrayBuf_2D[14][2] == '1'))
  {
    if(gunchCharArrayBuf_2D[14][3] == 'R')
    {
    Serial.println(" in the repeat loop");
     
      if ( (gnRTCActualWeekDay[0] && (gunchCharArrayBuf_2D[14][8]-'0')) ||(gnRTCActualWeekDay[1] && (gunchCharArrayBuf_2D[14][9]-'0'))||(gnRTCActualWeekDay[2] && (gunchCharArrayBuf_2D[14][10]-'0')) ||(gnRTCActualWeekDay[3] && (gunchCharArrayBuf_2D[14][11]-'0')) ||
        (gnRTCActualWeekDay[4] && (gunchCharArrayBuf_2D[14][12]-'0')) || (gnRTCActualWeekDay[5] && (gunchCharArrayBuf_2D[14][13]-'0'))||(gnRTCActualWeekDay[6] && (gunchCharArrayBuf_2D[14][14]-'0')))      
        {
          Serial.println(" led on repeat DEVICE 3 SET2 ");
           Serial.println("**31");
           Device3_Status = 1;
        }
    }
    
    else if(gunchCharArrayBuf_2D[14][3] == 'N')
     {
       if(NonRepeatFlagD3S2On == 1)
       {
          Serial.println(" in the notrepeat loop");
             
          Serial.println(" led on notrepeat DEVICE 3 SET2 ");
           Serial.println("**31");
           Device3_Status = 1;
           NonRepeatFlagD3S2On =0;
          //EEPROM.write(gunchCharArrayBuf_2D[14][3],'S');// WRITING STOP TO GET LED GLOW ONLY 1 TIME  
       }              
    
      }
      else
      {
        Serial.println(" led off ");
      }  
     }     
  }
 if (gnRTCCurrentTime == D3S2TimeToIntegerValueOFF)
    {
      Serial.println("_________Device 3 set 2_________________________________________");
      Serial.println(" in the rtc loop");
      if((gunchCharArrayBuf_2D[15][1] == 'C') && (gunchCharArrayBuf_2D[15][2] == '0'))
      {
        Serial.println(" in the config loop");
        if(gunchCharArrayBuf_2D[15][3] == 'R')
        {
        Serial.println(" in the repeat loop");
          
          if ( (gnRTCActualWeekDay[0] && (gunchCharArrayBuf_2D[15][8]-'0')) ||(gnRTCActualWeekDay[1] && (gunchCharArrayBuf_2D[15][9]-'0'))||(gnRTCActualWeekDay[2] && (gunchCharArrayBuf_2D[15][10]-'0')) ||(gnRTCActualWeekDay[3] == (gunchCharArrayBuf_2D[15][11]-'0')) ||
            (gnRTCActualWeekDay[4] && (gunchCharArrayBuf_2D[15][12]-'0')) || (gnRTCActualWeekDay[5] && (gunchCharArrayBuf_2D[15][13]-'0'))||(gnRTCActualWeekDay[6] && (gunchCharArrayBuf_2D[15][14]-'0')))      
            {
              Serial.println(" led off repeat DEVICE 3 SET2 ");
              Serial.println("**30");
              Device3_Status = 0;
            }
        }
        
        else if(gunchCharArrayBuf_2D[15][3] == 'N')
         {
           if(NonRepeatFlagD3S2Off == 1)
           {
              Serial.println(" in the notrepeat loop");
               
              Serial.println(" led off notrepeat DEVICE 3 SET2 ");
              Serial.println("**30");
              Device3_Status = 0;
              NonRepeatFlagD3S2Off =0;
              //EEPROM.write(gunchCharArrayBuf_2D[0][3],'S');// WRITING STOP TO GET LED GLOW ONLY 1 TIME   
           }             
            
          }
         else
         {
          Serial.println(" led on ");
         }  
       }            
    }

/////////***********************************DEVICE 3 SET 3****************************************************************////
    if (gnRTCCurrentTime == D3S3TimeToIntegerValueON)
{
  Serial.println("_________Device 3 set 3_________________________________________");
  if((gunchCharArrayBuf_2D[16][1] == 'C') && (gunchCharArrayBuf_2D[16][2] == '1'))
  {
    if(gunchCharArrayBuf_2D[16][3] == 'R')
    {
    Serial.println(" in the repeat loop");
     
      if ( (gnRTCActualWeekDay[0] && (gunchCharArrayBuf_2D[14][8]-'0')) ||(gnRTCActualWeekDay[1] && (gunchCharArrayBuf_2D[14][9]-'0'))||(gnRTCActualWeekDay[2] && (gunchCharArrayBuf_2D[14][10]-'0')) ||(gnRTCActualWeekDay[3] && (gunchCharArrayBuf_2D[14][11]-'0')) ||
        (gnRTCActualWeekDay[4] && (gunchCharArrayBuf_2D[14][12]-'0')) || (gnRTCActualWeekDay[5] && (gunchCharArrayBuf_2D[14][13]-'0'))||(gnRTCActualWeekDay[6] && (gunchCharArrayBuf_2D[14][14]-'0')))      
        {
          Serial.println(" led on repeat DEVICE 3 SET3 ");
           Serial.println("**31");
           Device3_Status = 1;
        }
    }
    
    else if(gunchCharArrayBuf_2D[16][3] == 'N')
     {
       if(NonRepeatFlagD3S3On == 1)
       {
            Serial.println(" in the notrepeat loop");
               
            Serial.println(" led on notrepeat DEVICE 3 SET3 ");
             Serial.println("**31");
             Device3_Status = 1;
             NonRepeatFlagD3S3On =0;
            //EEPROM.write(gunchCharArrayBuf_2D[14][3],'S');// WRITING STOP TO GET LED GLOW ONLY 1 TIME
       }                
    
      }
      else
      {
        Serial.println(" led off ");
      }  
     }     
  }
 if (gnRTCCurrentTime == D3S3TimeToIntegerValueOFF)
    {
      Serial.println("_________Device 3 set 3_________________________________________");
      Serial.println(" in the rtc loop");
      if((gunchCharArrayBuf_2D[17][1] == 'C') && (gunchCharArrayBuf_2D[17][2] == '0'))
      {
        Serial.println(" in the config loop");
        if(gunchCharArrayBuf_2D[17][3] == 'R')
        {
        Serial.println(" in the repeat loop");
          
          if ( (gnRTCActualWeekDay[0] && (gunchCharArrayBuf_2D[15][8]-'0')) ||(gnRTCActualWeekDay[1] && (gunchCharArrayBuf_2D[15][9]-'0'))||(gnRTCActualWeekDay[2] && (gunchCharArrayBuf_2D[15][10]-'0')) ||(gnRTCActualWeekDay[3] == (gunchCharArrayBuf_2D[15][11]-'0')) ||
            (gnRTCActualWeekDay[4] && (gunchCharArrayBuf_2D[15][12]-'0')) || (gnRTCActualWeekDay[5] && (gunchCharArrayBuf_2D[15][13]-'0'))||(gnRTCActualWeekDay[6] && (gunchCharArrayBuf_2D[15][14]-'0')))      
            {
              Serial.println(" led off repeat DEVICE 3 SET3 ");
              Serial.println("**30");
              Device3_Status = 0;
            }
        }
        
        else if(gunchCharArrayBuf_2D[17][3] == 'N')
         {
           if(NonRepeatFlagD3S3Off == 1)
           {
              Serial.println(" in the notrepeat loop");
               
              Serial.println(" led off notrepeat DEVICE 3 SET3 ");
              Serial.println("**30");
              Device3_Status = 0;
              NonRepeatFlagD3S3Off =0;
              //EEPROM.write(gunchCharArrayBuf_2D[0][3],'S');// WRITING STOP TO GET LED GLOW ONLY 1 TIME      
           }          
            
          }
         else
         {
          Serial.println(" led on ");
         }  
       }            
    }

/***********************DEVICE 4 SET 1 *******************************************/

  if (gnRTCCurrentTime == D4S1TimeToIntegerValueON)
{
  Serial.println("_________Device 4 set 1_________________________________________");
  if((gunchCharArrayBuf_2D[18][1] == 'C') && (gunchCharArrayBuf_2D[18][2] == '1'))
  {
    if(gunchCharArrayBuf_2D[18][3] == 'R')
    {
    Serial.println(" in the repeat loop");
     
      if ( (gnRTCActualWeekDay[0] && (gunchCharArrayBuf_2D[18][8]-'0')) ||(gnRTCActualWeekDay[1] && (gunchCharArrayBuf_2D[18][9]-'0'))||(gnRTCActualWeekDay[2] && (gunchCharArrayBuf_2D[18][10]-'0')) ||(gnRTCActualWeekDay[3] && (gunchCharArrayBuf_2D[18][11]-'0')) ||
        (gnRTCActualWeekDay[4] && (gunchCharArrayBuf_2D[18][12]-'0')) || (gnRTCActualWeekDay[5] && (gunchCharArrayBuf_2D[18][13]-'0'))||(gnRTCActualWeekDay[6] && (gunchCharArrayBuf_2D[18][14]-'0')))      
        {
          Serial.println(" led on repeat DEVICE 4 SET1 ");
          Serial.println("**41");
          Device4_Status = 1;
        }
    }
    
    else if(gunchCharArrayBuf_2D[18][3] == 'N')
     {
       if(NonRepeatFlagD4S1On == 1)
       {
          Serial.println(" in the notrepeat loop");      
          Serial.println(" led on notrepeat DEVICE 4 SET1 ");
          Serial.println("**41");
          Device4_Status = 1;
          NonRepeatFlagD4S1On =0;
          //EEPROM.write(gunchCharArrayBuf_2D[18][3],'S');// WRITING STOP TO GET LED GLOW ONLY 1 TIME       
       }         
      }
      }
      else
      {
        Serial.println(" led off ");
      }  
    }
   
   if (gnRTCCurrentTime == D4S1TimeToIntegerValueOFF)
    {
      Serial.println("_________Device 4 set 1_________________________________________");
      Serial.println(" in the rtc loop");
      if((gunchCharArrayBuf_2D[19][1] == 'C') && (gunchCharArrayBuf_2D[19][2] == '0'))
      {
        Serial.println(" in the config loop");
        if(gunchCharArrayBuf_2D[19][3] == 'R')
        {
        Serial.println(" in the repeat loop");
          
          if ( (gnRTCActualWeekDay[0] && (gunchCharArrayBuf_2D[19][8]-'0')) ||(gnRTCActualWeekDay[1] && (gunchCharArrayBuf_2D[19][9]-'0'))||(gnRTCActualWeekDay[2] && (gunchCharArrayBuf_2D[19][10]-'0')) ||(gnRTCActualWeekDay[3] == (gunchCharArrayBuf_2D[19][11]-'0')) ||
            (gnRTCActualWeekDay[4] && (gunchCharArrayBuf_2D[19][12]-'0')) || (gnRTCActualWeekDay[5] && (gunchCharArrayBuf_2D[19][13]-'0'))||(gnRTCActualWeekDay[6] && (gunchCharArrayBuf_2D[19][14]-'0')))      
            {
              Serial.println(" led off repeat DEVICE 4 SET1 ");
              Serial.println("**40");
              Device4_Status = 0;

             
            }
        }
        
        else if(gunchCharArrayBuf_2D[19][3] == 'N')
         {
          if(NonRepeatFlagD4S1Off == 1)
          {
              Serial.println(" in the notrepeat loop");
                   
              Serial.println(" led off notrepeat DEVICE 4 SET1 ");
              Serial.println("**40");
              Device4_Status = 0;
               NonRepeatFlagD4S1Off =0;
              //EEPROM.write(gunchCharArrayBuf_2D[0][3],'S');// WRITING STOP TO GET LED GLOW ONLY 1 TIME       
          }         
        
          }
         else
         {
          Serial.println(" led on ");
         }  
       }            
    }

      

/*/******************************DEVICE 4 SET 2**********************************/

 if (gnRTCCurrentTime == D4S2TimeToIntegerValueON) 
{
  Serial.println("_________Device 4 set 2_________________________________________");
  if((gunchCharArrayBuf_2D[20][1] == 'C') && (gunchCharArrayBuf_2D[20][2] == '1'))
  {
    if(gunchCharArrayBuf_2D[20][3] == 'R')
    {
    Serial.println(" in the repeat loop");
     
      if ( (gnRTCActualWeekDay[0] && (gunchCharArrayBuf_2D[20][8]-'0')) ||(gnRTCActualWeekDay[1] && (gunchCharArrayBuf_2D[20][9]-'0'))||(gnRTCActualWeekDay[2] && (gunchCharArrayBuf_2D[20][10]-'0')) ||(gnRTCActualWeekDay[3] && (gunchCharArrayBuf_2D[20][11]-'0')) ||
        (gnRTCActualWeekDay[4] && (gunchCharArrayBuf_2D[20][12]-'0')) || (gnRTCActualWeekDay[5] && (gunchCharArrayBuf_2D[20][13]-'0'))||(gnRTCActualWeekDay[6] && (gunchCharArrayBuf_2D[20][14]-'0')))      
        {
          Serial.println(" led on repeat DEVICE 4 SET2 ");
          Serial.println("**41");
          Device4_Status = 1;
        }
    }
    
    else if(gunchCharArrayBuf_2D[20][3] == 'N')
     {
      if(NonRepeatFlagD4S2On == 1)
      {
          Serial.println(" in the notrepeat loop");
                  
          Serial.println(" led on notrepeat DEVICE 4 SET2 ");
          Serial.println("**41");
          Device4_Status = 1;
           NonRepeatFlagD4S2On =0;
          //EEPROM.write(gunchCharArrayBuf_2D[20][3],'S');// WRITING STOP TO GET LED GLOW ONLY 1 TIME    
      }            
        
     }
      else
      {
        Serial.println(" led off ");
      }
    } 
  } 

  if (gnRTCCurrentTime == D4S2TimeToIntegerValueOFF)
    {
      Serial.println("_________Device 4 set 2_________________________________________");
      Serial.println(" in the rtc loop");
      if((gunchCharArrayBuf_2D[21][1] == 'C') && (gunchCharArrayBuf_2D[21][2] == '0'))
      {
        Serial.println(" in the config loop");
        if(gunchCharArrayBuf_2D[21][3] == 'R')
        {
        Serial.println(" in the repeat loop");
          
          if ( (gnRTCActualWeekDay[0] && (gunchCharArrayBuf_2D[21][8]-'0')) ||(gnRTCActualWeekDay[1] && (gunchCharArrayBuf_2D[21][9]-'0'))||(gnRTCActualWeekDay[2] && (gunchCharArrayBuf_2D[21][10]-'0')) ||(gnRTCActualWeekDay[3] == (gunchCharArrayBuf_2D[21][11]-'0')) ||
            (gnRTCActualWeekDay[4] && (gunchCharArrayBuf_2D[21][12]-'0')) || (gnRTCActualWeekDay[5] && (gunchCharArrayBuf_2D[21][13]-'0'))||(gnRTCActualWeekDay[6] && (gunchCharArrayBuf_2D[21][14]-'0')))      
            {
              Serial.println(" led off repeat DEVICE 4 SET2 ");
              Serial.println("**40");
              Device4_Status = 0;
            }
        }
        
        else if(gunchCharArrayBuf_2D[21][3] == 'N')
         {
          if(NonRepeatFlagD4S2Off == 1)
          {
          Serial.println(" in the notrepeat loop");
             
          Serial.println(" led off notrepeat DEVICE 4 SET2 ");
          Serial.println("**40");
          Device4_Status = 0;
           NonRepeatFlagD4S2Off =0;
          //EEPROM.write(gunchCharArrayBuf_2D[0][3],'S');// WRITING STOP TO GET LED GLOW ONLY 1 TIME                
        
          }
         else
         {
          Serial.println(" led on ");
         }  
       }            
    }
  }
///*************************************DEVICE 4 SET 3***************************************************************************//

 if (gnRTCCurrentTime == D4S3TimeToIntegerValueON) 
{
  Serial.println("_________Device 4 set 3_________________________________________");
  if((gunchCharArrayBuf_2D[22][1] == 'C') && (gunchCharArrayBuf_2D[22][2] == '1'))
  {
    if(gunchCharArrayBuf_2D[22][3] == 'R')
    {
    Serial.println(" in the repeat loop");
     
      if ( (gnRTCActualWeekDay[0] && (gunchCharArrayBuf_2D[22][8]-'0')) ||(gnRTCActualWeekDay[1] && (gunchCharArrayBuf_2D[22][9]-'0'))||(gnRTCActualWeekDay[2] && (gunchCharArrayBuf_2D[22][10]-'0')) ||(gnRTCActualWeekDay[3] && (gunchCharArrayBuf_2D[22][11]-'0')) ||
        (gnRTCActualWeekDay[4] && (gunchCharArrayBuf_2D[22][12]-'0')) || (gnRTCActualWeekDay[5] && (gunchCharArrayBuf_2D[22][13]-'0'))||(gnRTCActualWeekDay[6] && (gunchCharArrayBuf_2D[22][14]-'0')))      
        {
          Serial.println(" led on repeat DEVICE 4 SET3 ");
          Serial.println("**41");
          Device4_Status = 1;
        }
    }
    
    else if(gunchCharArrayBuf_2D[22][3] == 'N')
     {
      if(NonRepeatFlagD4S3On == 1)
      {
          Serial.println(" in the notrepeat loop");
                  
          Serial.println(" led on notrepeat DEVICE 4 SET3 ");
          Serial.println("**41");
          Device4_Status = 1;
           NonRepeatFlagD4S3On =0;
          //EEPROM.write(gunchCharArrayBuf_2D[20][3],'S');// WRITING STOP TO GET LED GLOW ONLY 1 TIME    
      }            
        
      }
      else
      {
        Serial.println(" led off ");
      }
    } 
  } 

  if (gnRTCCurrentTime == D4S3TimeToIntegerValueOFF)
    {
      Serial.println("_________Device 4 set 3_________________________________________");
      Serial.println(" in the rtc loop");
      if((gunchCharArrayBuf_2D[23][1] == 'C') && (gunchCharArrayBuf_2D[23][2] == '0'))
      {
        Serial.println(" in the config loop");
        if(gunchCharArrayBuf_2D[23][3] == 'R')
        {
        Serial.println(" in the repeat loop");
          
          if ( (gnRTCActualWeekDay[0] && (gunchCharArrayBuf_2D[21][8]-'0')) ||(gnRTCActualWeekDay[1] && (gunchCharArrayBuf_2D[21][9]-'0'))||(gnRTCActualWeekDay[2] && (gunchCharArrayBuf_2D[21][10]-'0')) ||(gnRTCActualWeekDay[3] == (gunchCharArrayBuf_2D[21][11]-'0')) ||
            (gnRTCActualWeekDay[4] && (gunchCharArrayBuf_2D[21][12]-'0')) || (gnRTCActualWeekDay[5] && (gunchCharArrayBuf_2D[21][13]-'0'))||(gnRTCActualWeekDay[6] && (gunchCharArrayBuf_2D[21][14]-'0')))      
            {
              Serial.println(" led off repeat DEVICE 4 SET3 ");
              Serial.println("**40");
              Device4_Status = 0;
            }
        }
        
        else if(gunchCharArrayBuf_2D[23][3] == 'N')
         {
          if(NonRepeatFlagD4S3Off == 1)
          {
            Serial.println(" in the notrepeat loop");
               
            Serial.println(" led off notrepeat DEVICE 4 SET3 ");
            Serial.println("**40");
            Device4_Status = 0;
             NonRepeatFlagD4S3Off =0;
            //EEPROM.write(gunchCharArrayBuf_2D[0][3],'S');// WRITING STOP TO GET LED GLOW ONLY 1 TIME                
          }
         }
         else
         {
          Serial.println(" led on ");
         }  
       }            
    }

}



//*************************************************Initialize_NTPClient_to_get_time******************************************************************************************************/


void  NTP_CLNT_BEG()
{
    timeClient.begin();
    // Set offset time in seconds to adjust for your timezone, for example:
    // GMT +1 = 3600
     //GMT +8 = 28800
    // GMT -1 = -3600
    // GMT 0 = 0
    // GMT +5.30 = 19800
    timeClient.setTimeOffset(19800);

    

}







//*********************************************RTC_NTP_FETCH_GMT*****************************************************************************************************************/





void RTC_NTP_FETCH_GMT_T(void)
 {
        
          timeClient.update();
          unsigned long epochTime = timeClient.getEpochTime();
          if(epochTime < 1629910920)  // Epoch time for 25th August, 2021
          {
            Serial.print("Wrong Epoch time received");
          }
          else
          {
            Serial.print("Correct Epoch time received/n");
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
          
            delay(2000);
            rtc.adjust(DateTime(currentYear, currentMonth, monthDay, currentHour, currentMinute, currentSecond));
            Serial.println("RTC Updated!");

            DateTime rtcTime = rtc.now();

            Serial.println("Current Date & Time: ");
            Serial.print(rtcTime.year(), DEC);
            Serial.print('/');
            Serial.print(rtcTime.month(), DEC);
            Serial.print('/');
            Serial.print(rtcTime.day(), DEC);
//            Serial.print(" (");
//            Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
//            Serial.print(") ");
            Serial.print(rtcTime.hour(), DEC);
            Serial.print(':');
            Serial.print(rtcTime.minute(), DEC);
            Serial.print(':');
            Serial.print(rtcTime.second(), DEC);
            Serial.println();

            Serial.println("NTP Time Zone over");
            Serial.println(unGMT_Dir);
          
            if(unGMT_Dir == 1)
            {
                Serial.println("+ GMT region");
                DateTime future (rtcTime + TimeSpan(0,+unGMT_HH,+unGMT_MM,0));
                Serial.println("Indian Date & Time (Now + 5 hours & 30 mins): ");
                int unISTYYYY = future.year();
                Serial.print(future.year(), DEC);
                Serial.print('/');
                int unISTMM = future.month();
                Serial.print(future.month(), DEC);
                Serial.print('/');
                int unISTDD = future.day();
                Serial.print(future.day(), DEC);
                Serial.print(' ');
                int unISTHH = future.hour();
                Serial.print(future.hour(), DEC);
                Serial.print(':');
                int unISTMIN = future.minute();
                Serial.print(future.minute(), DEC);
                Serial.print(':');
                int unISTSS = future.second();
                Serial.print(future.second(), DEC);
                Serial.println();
    
                rtc.adjust(DateTime(unISTYYYY, unISTMM, unISTDD, unISTHH, unISTMIN, unISTSS));
                Serial.println("RTC Updated!");
                
              }

              if(unGMT_Dir == 2)
            {
                Serial.println("- GMT region");
                DateTime future (rtcTime + TimeSpan(0,-unGMT_HH,-unGMT_MM,0));
                Serial.println("Indian Date & Time (Now + 5 hours & 30 mins): ");
                int unISTYYYY = future.year();
                Serial.print(future.year(), DEC);
                Serial.print('/');
                int unISTMM = future.month();
                Serial.print(future.month(), DEC);
                Serial.print('/');
                int unISTDD = future.day();
                Serial.print(future.day(), DEC);
                Serial.print(' ');
                int unISTHH = future.hour();
                Serial.print(future.hour(), DEC);
                Serial.print(':');
                int unISTMIN = future.minute();
                Serial.print(future.minute(), DEC);
                Serial.print(':');
                int unISTSS = future.second();
                Serial.print(future.second(), DEC);
                Serial.println();
    
                rtc.adjust(DateTime(unISTYYYY, unISTMM, unISTDD, unISTHH, unISTMIN, unISTSS));
                Serial.println("RTC Updated!");
                
              }

              

        }
 }

//**********************************************************************************EEPROM_Status_Print************************************************//


int unD1Status;
int unD2Status;
int unD3Status;
int unD4Status;
int unD5Status;
int unD6Status;
int unD7Status;
int unD8Status;
int unD9Status;
int unD10Status;
int unD11Status;
int unD12Status;

void DEV_CURNT_STA(void)
{
  unD1Status = EEPROM.read(2);
  unD2Status = EEPROM.read(3);
  unD3Status = EEPROM.read(4);
  unD4Status = EEPROM.read(5);
  unD5Status = EEPROM.read(6);
  unD6Status = EEPROM.read(7);
  unD7Status = EEPROM.read(8);
  unD8Status = EEPROM.read(9);
  unD9Status = EEPROM.read(10);
  unD10Status = EEPROM.read(11);
  unD11Status = EEPROM.read(12);
  unD12Status = EEPROM.read(13);
  if (unD1Status == 1)
  {
    Serial.println("**11");
  }
  else
  {
    Serial.println("**10");
  }

  if (unD2Status == 1)
  {
    Serial.println("**21");
  }
  else
  {
    Serial.println("**20");
  }
  if (unD3Status == 1)
  {
    Serial.println("**31");
  }
  else
  {
    Serial.println("**30");
  }
  if (unD4Status == 1)
  {
    Serial.println("**41");
  }
  else
  {
    Serial.println("**40");
  }
}




/*********************************THINKSPEAK BEGIN********************************************************/


void THINK_SPEAK_RD_WRT(void)
{
    String serverName = "http://api.thingspeak.com/update?";
    String apiKey;
    char SerialStarData;
    String ReadWriteData;
    String field1;
    String field2;
    String field3;
    String field4;
    String field5;
    String field6;
    String field7;
    String field8;
    
    String Channel;
    String field;
    String Outputdata;
    String payload;
    String MainData;
    String DataToMicrocon;
   // if (Serial.available())
    //{
     //SerialStarData = Serial.read();
     //if (SerialStarData == '*')
     //{
        ReadWriteData = Serial.readStringUntil('<');
        if(ReadWriteData == "W")
        {
          apiKey = Serial.readStringUntil('>');
          field1 = Serial.readStringUntil('&');
          field2 = Serial.readStringUntil('&');
          field3 = Serial.readStringUntil('&');
          field4 = Serial.readStringUntil('&');
          field5 = Serial.readStringUntil('&');
          field6 = Serial.readStringUntil('&');
          field7 = Serial.readStringUntil('&');
         // field8 = Serial.readStringUntil('\n');

           delay(100);

      //Check WiFi connection status
        if(WiFi.status()== WL_CONNECTED)
       {
        HTTPClient http; 
       
        // Data to send with HTTP POST
        String httpRequestData = serverName + "api_key=" + apiKey + + "&field1=" + field1 + "&field2=" + field2 + "&field3=" + field3 + "&field4=" + field4 + "&field5=" + field5 + "&field6=" + field6 +  "&field7=" + field7;          
        // Send HTTP POST request
         http.begin(httpRequestData);
        // Specify content-type header
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        Serial.println(httpRequestData);
        int httpResponseCode = http.GET();
   
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);

        payload = http.getString();
        Serial.print("payload is: ");
        Serial.println(payload);
       
        // Free resources
        http.end();
        }
     }
     else if(ReadWriteData == "R")
      {
         apiKey  = Serial.readStringUntil('>');
         Channel = Serial.readStringUntil('>');
         field   = Serial.readStringUntil('>');
         String httpRequestData = "http://api.thingspeak.com/channels/" + Channel + "/fields/" + field + "/last.json?api_key=" + apiKey + "&results=2";
         Serial.print("httpRequestData is ");
         Serial.println(httpRequestData);
           if(WiFi.status()== WL_CONNECTED)
             {
                HTTPClient http;        
                http.begin(httpRequestData);
            // Specify content-type header
                http.addHeader("Content-Type", "application/x-www-form-urlencoded");
                Serial.println(httpRequestData);
                int httpResponseCode = http.GET();
           
                Serial.print("HTTP Response code: ");
                Serial.println(httpResponseCode);
        
                payload = http.getString();
                Serial.print("payload is: ");
                Serial.println(payload);
               
                // Free resources
                http.end();
             }
             //*R<DY20OO1OKG1V0Q49>1369048>1>
         Outputdata = payload.substring(61,62);
         DataToMicrocon = payload.substring(61,64);
         Serial.print("*<");
         Serial.print(DataToMicrocon);
         Serial.print(">");
         MainData = Serial.readStringUntil('"');
         Serial.print(Outputdata);
         //Serial.print("MainData is : ");

       }
  
}

//**************************************Firmware_Update*****************************************************************************************************************************//

const float version= 1.00;
void FRMWR_UPD(void)
  {
    http.begin(url_version);               // for security, ssl certification is required. 
    delay(100);
    int httpCode = http.GET();            // Get the version info 
    delay(100);                                     
    String payload; // String
    if (httpCode == HTTP_CODE_OK)         // Check flag for  version received 
    {
      payload = http.getString();         // save received version
      Serial.println(payload);
    }
    else
    {
      Serial.print("error in downloading version file:");
      Serial.println(httpCode);
     }
    http.end();
    if (httpCode == HTTP_CODE_OK)        
    {
      if( version >= payload.toFloat()  )              // Check flag, this is where it compares the previous version and the current version if( payload.equals(version))
      {   
         Serial.println("Device on latest firmware version");    // if its equal do nothing 
      }
    else
    {
       Serial.println("New firmware detected");    // else Get the frimware 
       Serial.println(payload.toFloat());
       WiFiClient client;
  
       ESPhttpUpdate.setLedPin(LED_BUILTIN, LOW);   // This blinks untill the code gets uploaded #notRequired tho', useful to note that uploading has initiated when the led flickers
  
      //," ","5B:FB:D1:D4:49:D3:0F:A9:C6:40:03:34:BA:E0:24:05:AA:D2:E2:01"); 
     t_httpUpdate_return ret = ESPhttpUpdate.update(url_bin);      // returns the binary of the firmware 
      switch (ret) 
      {
        case HTTP_UPDATE_FAILED:
          Serial.printf("HTTP request failed (%d): %s\n", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str()); // error flag
          break;
      case HTTP_UPDATE_NO_UPDATES:
          Serial.println("No updates");
          break;
      case HTTP_UPDATE_OK:
          Serial.println("HTTP_UPDATE_OK");
          break;
      } 
     }
   }  
}


/************************************ALEXA BEGINS*************************************/

const long interval = 10000; 

//void firstLightChanged(uint8_t brightness);
//void secondLightChanged(uint8_t brightness);
//void thirdLightChanged(uint8_t brightness);
//void fourthLightChanged(uint8_t brightness);

String Device_1_Name = "Room one light";
String Device_2_Name = "Room two light";
String Device_3_Name = "Hall light";
String Device_4_Name = "Bedroom light";



void firstLightChanged(uint8_t brightness)
{
//Control the device
  if (brightness)
  {
    if (brightness == 255)// on 
    {
  
      Serial.println("**11");
     // Serial.println("Device1 ON");
    }
    //Serial.print("ON, brightness ");
    //Serial.println(brightness);
  }
  else
  {
    Serial.println("**10");
    //Serial.println("Device1 OFF");
  }
}

void secondLightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {
    if (brightness == 255)
    {
     
      Serial.println("**21");
      //Serial.println("Device2 ON");
    }
    //Serial.print("ON, brightness ");
    //Serial.println(brightness);
  }
  else
  {
    
    Serial.println("**20");
    //Serial.println("Device2 OFF");
  }
}

void thirdLightChanged(uint8_t brightness)
{

  //Control the device  
  if (brightness)
  {
    if (brightness == 255)
    {
     
      Serial.println("**31");
    //  Serial.println("Device3 ON");
    }
    //Serial.print("ON, brightness ");
    //Serial.println(brightness);
  }
  else
  {
    Serial.println("**30");
    //Serial.println("Device3 OFF");
  }
}

void fourthLightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {

    if (brightness == 255)
    {
     
      Serial.println("**41");
      //Serial.println("Device4 ON");
    }
    //Serial.print("ON, brightness ");
    //Serial.println(brightness);
  }
  else
  {
   
    Serial.println("**40");
    //Serial.println("Device4 OFF");6
  }
}


void ESP_ALEXA(void)
{
    espalexa.addDevice(Device_1_Name, firstLightChanged); //simplest definition, default state off
    espalexa.addDevice(Device_2_Name, secondLightChanged);
    espalexa.addDevice(Device_3_Name, thirdLightChanged);
    espalexa.addDevice(Device_4_Name, fourthLightChanged);
   // espalexa.addDevice(Device_5_Name, fifthLightChanged);
  //  espalexa.addDevice(Device_6_Name, fourthLightChanged);
    espalexa.begin();

}

void ESP_ALEXA_Loop(void)
{
  espalexa.loop(); 
}
/************************************ALEXA ENDING*************************************/

  
