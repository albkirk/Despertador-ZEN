/*
 * * Main File to trigger all C code using "arduino" style.
 * * It contains all necessary function calls on setup and loop functions
 * * HOW TO USE THIS TEMPLATE:
 * * -- Adjust the parameter below to your project.
 * *    Parameters on struct "config" will be store on memory.
 * *    Don't forget to customize the Mem read and write actions on "lib/project/custostore.h"
 * * -- Use the "// **** Normal code ..." zones to add you own definition, functions, setup and loop code
 * * -- You can also add you own MQTT actions on "lib/project/customqtt.h"
 * * -- Suggest to use "lib/project/" to add your own h files
 */
#include <Arduino.h>
#include <rom/rtc.h>
#include <WiFi.h>

// HARWARE & SOFTWARE Version
#define BRANDName "AlBros_Team"                         // Hardware brand name
#define MODELName "ZENDesperta"                         // Hardware model name
#define SWVer "01.05"                                   // Major.Minor Software version (use String 01.00 - 99.99 format !)

// Battery & ESP Voltage
#define BattPowered true                                // Is the device battery powered?
#define LDO_Corr float(-0.05)                           // Battery Voltage [volt] corrective Factor due to LDO/Diode voltage drop
#define Batt_L_Thrs 10                                  // Battery level threshold [0%-100%] (before slepping forever).

// GPIO to Function Assignment
#define Using_ADC false                                 // will this device use the ADC? (if not it will measure the interval voltage)
#define LED_esp 22                                      // ESP Led is connected to GPIO x. -1 means NOT used!
#define DHTPIN -1                                       // GPIO Connected to DHT22 Data PIN. -1 means NO DHT used!
#define BUZZER -1                                       // (Active) Buzzer pin. Suggest to use pin 0.  -1 means NOT used!

# define custo_strDateTime true
struct strDateTime {
    byte hour;
    byte minute;
    byte second;
    int year;
    byte month;
    byte day;
    byte wday;
    bool alarm;
    byte sound;
};

struct __attribute__((__packed__)) strConfig {
  char DeviceName[16];
  char Location[16];
  char ClientID[8];
  byte ONTime;
  byte SLEEPTime;
  boolean DEEPSLEEP;
  boolean LED;
  boolean TELNET;
  boolean OTA;
  boolean WEB;
  boolean Remote_Allow;
  boolean STAMode;
  char ssid[32];
  char WiFiKey[32];
  boolean dhcp;
  byte IP[4];
  byte Netmask[4];
  byte Gateway[4];
  char NTPServerName[128];
  long TimeZone;
  long Update_Time_Via_NTP_Every;
  boolean isDayLightSaving;
  char MQTT_Server[128];
  long MQTT_Port;
  char MQTT_User[16];
  char MQTT_Password[16];
  char UPDATE_Server[128];
  long UPDATE_Port;
  char UPDATE_User[16];
  char UPDATE_Password[16];
  long Temp_Corr;
  char InitColor[10];
  byte Volume;
  bool Alarm_State;
  strDateTime AlarmDateTime;
} config;


void config_defaults() {
    Serial.println("Setting config Default values");

    strcpy(config.DeviceName, "ZENDesperta");            // Device Name
    strcpy(config.Location, "Suite");                    // Device Location
    strcpy(config.ClientID, "001001");                   // Client ID (used on MQTT)
    config.ONTime = 60;                                   // 0-255 seconds (Byte range)
    config.SLEEPTime = 0;                                 // 0-255 minutes (Byte range)
    config.DEEPSLEEP = false;                             // 0 - Disabled, 1 - Enabled
    config.LED = false;                                   // 0 - OFF, 1 - ON
    config.TELNET = false;                                // 0 - Disabled, 1 - Enabled
    config.OTA = true;                                    // 0 - Disabled, 1 - Enabled
    config.WEB = false;                                   // 0 - Disabled, 1 - Enabled
    config.Remote_Allow = true;                           // 0 - Not Allow, 1 - Allow remote operation
    config.STAMode = true;                                // 0 - AP or AP+STA Mode, 1 - Station only Mode
    //config.ssid = String("ALU_MEO_IPTV");                 // Wireless LAN SSID (STA mode)
    //config.WiFiKey = String("ALUME0IPTV");                  // Wireless LAN Key (STA mode)
    strcpy(config.ssid, "ThomsonCasaN");                 // Wireless LAN SSID (STA mode)
    strcpy(config.WiFiKey, "12345678");                  // Wireless LAN Key (STA mode)
    config.dhcp = true;                                   // 0 - Static IP, 1 - DHCP
    config.IP[0] = 192; config.IP[1] = 168; config.IP[2] = 1; config.IP[3] = 10;
    config.Netmask[0] = 255; config.Netmask[1] = 255; config.Netmask[2] = 255; config.Netmask[3] = 0;
    config.Gateway[0] = 192; config.Gateway[1] = 168; config.Gateway[2] = 1; config.Gateway[3] = 254;
    strcpy(config.NTPServerName, "pt.pool.ntp.org");         // NTP Server
    config.Update_Time_Via_NTP_Every = 1200;              // Time in minutes to re-sync the clock
    config.TimeZone = 0;                                  // -12 to 13. See Page_NTPSettings.h why using -120 to 130 on the code.
    config.isDayLightSaving = 1;                          // 0 - Disabled, 1 - Enabled
    strcpy(config.MQTT_Server, "iothubna.hopto.org");    // MQTT Broker Server (URL or IP)
    config.MQTT_Port = 1883;                              // MQTT Broker TCP port
    strcpy(config.MQTT_User, "admin");                   // MQTT Broker username
    strcpy(config.MQTT_Password, "admin");               // MQTT Broker password
    strcpy(config.UPDATE_Server, "iothubna.hopto.org");  // UPDATE Server (URL or IP)
    config.UPDATE_Port = 1880;                            // UPDATE Server TCP port
    strcpy(config.UPDATE_User, "user");                  // UPDATE Server username
    strcpy(config.UPDATE_Password, "1q2w3e4r");          // UPDATE Server password
    config.Temp_Corr = 0;     // Sensor Temperature Correction Factor, typically due to electronic self heat.
    strcpy(config.InitColor, "#EEEEEEFF");                // RGB Initial color (when powering ON)
    config.Volume = 100;      // Speaker volume [0-100%].
    config.Alarm_State = false;                           // Alarm state (true -> Ring / False -> Not Ring)
    config.AlarmDateTime = {0, 1, 0, 0, 0, 0, 7, true, 1};// Alarm DateTime structure
}

// **** Normal code definition here ...

// - - -  COLOR related variables  - - -
    char Color[10]     = "#00000000"; // RGB Color code. syntax: '#' + RED + GREEN + BLUE + Transparency
    char LastColor[10] = "#00000000"; // each param use 2 CHARs and range from 0 to FF (HEX format of 0-255).
                                      // Transparency is ignored. It's kept only for compatibility purposes.

//  - - -  NeoPixels  - - -
#define NEOPixelsPIN  18              // pin on the ESP32 to connected to the NeoPixels
#define NEOPixelsNUM  8               // Number of NeoPixels LEDs

//  - - -  Shades  - - -
    byte SHADES = 80;                 // Position of SHADES


#include <storage.h>
#include <esp32hw.h>
#include <mywifi.h>
#include <telnet.h>
#include <ntp.h>
//#include <web.h>
#include <ota.h>
#include <mqtt.h>
#include <SDReader.h>
#include <global.h>



// **** Normal code functions here ...
#include <sounds.h>
#include <images.h>
#define  TFTRotate 1
#include <color.h>
#include <tft.h>
#include <dacplayer.h>
#include <menu.h>



void setup() {
// Start Serial interface
  //Serial.begin(74880);                      //This odd baud speed will show ESP8266 boot diagnostics too.
  Serial.begin(115200);                   // For faster communication use 115200

  Serial.println(" ");
  Serial.println("Hello World!");
  Serial.println("My ID is " + ChipID + " and I'm running version " + SWVer);
  Serial.println("Reset reason: " + String(ESPWakeUpReason()));

  // Output GPIOs

  // Input GPIOs

  // Start Hardware services, like: ESP_LED. DHT, internal ADC,...
      hw_setup();

  // Start Storage service and read stored configuration
      storage_setup();

  // Start WiFi service (Station or/and as Access Point)
      wifi_setup();

  // Start NTP service
      ntp_setup();

  // Start TELNET service
      if (config.TELNET) telnet_setup();

  // Start OTA service
      if (config.OTA) ota_setup();

  // Start ESP Web Service
      //if (config.WEB) web_setup();

  // Start MQTT service
      mqtt_setup();

  // Start SD Card reader
      SDReader_setup();

  //  LOW Battery check (GLOBAL library)
      //LOW_Batt_check();               // Must be execute after mqtt_setup. If LOW Batt, it will DeepSleep forever!


  // **** Normal SETUP Sketch code here...
  // Start TFT device
      tft_setup();

  // Start Player device
      player_setup();

  // Color Managament Service
      color_setup();

  // Start MENU
      menu_setup();



  // Last bit of code before leave setup
      ONTime_Offset = millis()/1000 + 0.1;  //  100ms after finishing the SETUP function it starts the "ONTime" countdown.
                                            //  it should be good enough to receive the MQTT "ExtendONTime" msg
} // end of setup()


void loop() {
  // allow background process to run.
      yield();

  // Hardware handling, namely the ESP_LED
      hw_loop();

  // WiFi handling
      wifi_loop();

  // NTP handling
      ntp_loop();

  // TELNET handling
      if (config.TELNET) telnet_loop();

  // OTA request handling
      if (config.OTA) ota_loop();

  // ESP Web Server requests handling
      //if (config.WEB) web_loop();

  // MQTT handling
      mqtt_loop();

  // DeepSleep handling
      deepsleep_loop();


  // **** Normal LOOP Skecth code here ...

  // Player handling
      player_loop();

  // Color handling
      color_loop();

  // MENU handling
      menu_loop();


}  // end of loop()
