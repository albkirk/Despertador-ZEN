#include <EEPROM.h>
#define EEPROMZize 2048

String STOR_FLAG = "ABC";

//
//  Create data Struct that will be store on RTC memmory
//
struct {
  unsigned long lastUTCTime = 0;
  unsigned int LastWiFiChannel = 1;
} rtcData;


//
//  AUXILIAR functions to handle EEPROM
//

void storage_print() {

  Serial.println("Printing Config");
  Serial.printf("Device Name: %s and Location: %s\n", config.DeviceName.c_str(), config.Location.c_str());
  Serial.printf("ON time[sec]: %d  SLEEP Time[min]: %d  DEEPSLEEP enabled: %d\n", config.ONTime, config.SLEEPTime, config.DEEPSLEEP);
  Serial.printf("LED enabled: %d - TELNET enabled: %d - OTA enabled: %d - WEB enabled: %d\n", config.LED, config.TELNET, config.OTA, config.WEB);
  Serial.printf("WiFi STA Mode: %d\n", config.STAMode);
  Serial.printf("WiFi SSID: %s\n", config.ssid.c_str());
  Serial.printf("WiFi Key: %s\n", config.WiFiKey.c_str());

  Serial.printf("DHCP enabled: %d\n", config.dhcp);
  if(!config.dhcp) {
      Serial.printf("IP: %d.%d.%d.%d\n", config.IP[0],config.IP[1],config.IP[2],config.IP[3]);
      Serial.printf("Mask: %d.%d.%d.%d\n", config.Netmask[0],config.Netmask[1],config.Netmask[2],config.Netmask[3]);
      Serial.printf("Gateway: %d.%d.%d.%d\n", config.Gateway[0],config.Gateway[1],config.Gateway[2],config.Gateway[3]);
  }
  Serial.printf("NTP Server Name: %s\n", config.NTPServerName.c_str());
  Serial.printf("NTP update every %ld minutes.\n", config.Update_Time_Via_NTP_Every);
  Serial.printf("Timezone: %ld  -  DayLight: %d\n", config.TimeZone, config.isDayLightSaving);
}


boolean storage_read() {
    Serial.println("Reading Configuration");
    EEPROM.get(0, STOR_FLAG);
    if (STOR_FLAG == "CFG") {
        Serial.println("Configurarion Found!");
        EEPROM.get(16, config);
        return true;
    }
    else {
        Serial.println("Configurarion NOT FOUND!!!!");
        Serial.println("Storage FLAG: " + STOR_FLAG);
        return false;
    }
}


void storage_write() {
  Serial.println("Writing Config");
  STOR_FLAG = "CFG";
  EEPROM.put(0, STOR_FLAG);
  EEPROM.put(16, config);
  EEPROM.commit();
}


void storage_reset() {

  Serial.println("Reseting Config");
  STOR_FLAG = "RST";
  EEPROM.put(0, STOR_FLAG);
  EEPROM.commit();
}

void storage_setup() {
    bool CFG_saved = false;
    EEPROM.begin(EEPROMZize);     // define an EEPROM space of 2048 Bytes to store data
    //storage_reset();            // Hack to reset storage during boot
    config_defaults();
    CFG_saved = storage_read();   //When a configuration exists, it uses stored values
    if (!CFG_saved) {             // If NOT, it Set DEFAULT VALUES to "config" struct
        config_defaults();
        storage_write();
    }
    storage_print();
}
