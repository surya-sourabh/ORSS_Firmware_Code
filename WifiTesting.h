#include <TimeLib.h>

#ifndef WifiTesting_h
#define WifiTesting_h

 


//WiFiClient ApsisClient;

//ESP8266WebServer  server(80);



//#define NTP_PACKET_SIZE 48
void fnMQTTSerialPrintLEDToggle(void);
void fnMQTTConnectWithDeviceTopic(void);
void MQTTConnect();
void callback(char *topic, byte *payload, unsigned int length);
void MQTTCon(void);
void MQTTPrint(void);
void repeatedCall();  
bool testWifi(void);
void launchWeb(void);
void setupAP(void);
void createWebServer();
void fnHardFactoryReset(void);
void fnDetectWifiAndConnect(void);
void fnReadSSID_PWD_FromEEPROM_WiFiAutoConnect(void); 
void fnMQTTLoop(void);
//void RTCRead(void);
//void RTCWrite(void);
void fnupdateRTC();
void fnRTC_Read();
void fnSerailEEPROMRtcBegin(void);
void fnRTCReadandUpdate(void);
int fnEEPROMTimeToInteger(unsigned char uchLocation);
void fnEEPROMRead(void);
void fnThingSpeakWrite(void);
void fnThingSpeakReadWrite2(void);
void fnRTC_EPORCH_fetch_Time(void);
void  fnNTPClientbegin(void);
void FirmwareUpdate(void);
void EspAlexa(void);
void fnWiFi_RSSIStrength(void);
void fnWiFi_RSSI_SignalLoop(void);
void EspAlexaLoop(void);
void fnStoreOnOffTimeFrom2DArray(void);
void fnRTC_NTP_LOOP(void);
void sendNTPpacket(IPAddress &address);
//time_t getNtpTime();
void fnNTP_Format_GMT_Time(void);
void fnRTC_NTP_fetchGMT_Time(void);
void digitalClockDisplay(void);
void fnWifiAutoConnectNOoConfig(void);
void fnDeviceCurrentStatus(void);

//***************************************NEW_FUNCTION_NAME***************************************************************************//

void MQTT_CON_Dev_Top(void);
void MQTT_SPrnt_LED_Tog(void);
void MQTT_CON();
int EEPROM_T_INT(unsigned char uchLocation);
void S_EEPROM_RTC_Beg(void);
void callback(char *topic, byte *payload, unsigned int length);
void MQTT_LOOP(void);
bool TEST_WiFi(void);
void WiFi_RSSI_STR(void);
void WiFi_RSSI_SIG_LOOP();
void HRD_FACT_RESET(void);
void LAUNCH_WEB();
void SETUP_AP(void);
void CRT_WEB_SERVER();
void DTCT_WiFi_CON(void);
void WiFi_AUTO_CON_NO_CONFIG(void);
void RD_SSID_PWD_EEPROM_WiFi_AUTO_CON(void);
void EEPROM_RD(void);
void STR_NF_T_2DARRAY(void);
void UPD_RTC();
void RTC_RD();
void  NTP_CLNT_BEG();
void RTC_NTP_FETCH_GMT_T(void);
void DEV_CURNT_STA(void);
void THINK_SPEAK_RD_WRT(void);
void ESP_ALEXA(void);
void ESP_ALEXA_Loop(void);
void FRMWR_UPD(void);


#endif
