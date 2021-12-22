#ifndef PinAllocation_h
#define PinAllocation_h



//#define SET_ANALOG   1
//#define SET_DIGITAL  0

//#define SET_INPUT   1
//#define SET_OUTPUT  0

//#define PRESSED 0
//#define NOTPRESSED 1

//#define SET_TRUE 	1
//#define SET_FALSE 	0

#define OUTPUT_HIGH  0
#define OUTPUT_LOW   1

#define ON 1
#define OFF 0

#define LED1 0 	// GPIO 0 PIN No OF ESP8266

#define pswFactoryReset  14


#define SELECT_GPS_ON_UART	1
#define SELECT_RFID_ON_UART	2
#define SELECT_PC_ON_UART		3

/*#define LEDDEV1 12
#define LEDDEV2 13
#define LEDDEV3 14
#define LEDDEV4 16*/
#define url_version "http://neworss.s3.ap_south_.amazonaws.com/version.txt"
#define url_bin "http://neworss.s3.ap_south_.amazonaws.com/firmware.bin"

#define ConfigLED 13 //GPIO 13 pin connected with config led
#define InternetConLED 12 //GPIO 12 pin conneced with Internet connectivity Led





void LEDToggle();

#endif
