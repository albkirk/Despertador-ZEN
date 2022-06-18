
//  - - -  Constants
//static const String menu_main[] = {"Clock", "Alarm", "ZEN", "Shades", "System"};
//static const String menu_main[] = {"Clock", "Alarm", "Sounds", "Lights", "Shades", "System"};
static const String menu_main[] = {"Clock", "Alarm", "Sounds", "Lights", "Ambient", "System"};
//static const String menu_main[] = {"Clock", "Ambient"};
static const String menu_zen[] =    {"Florest",     "Beach",    "Night",     "Raibow",    "Sunset"};
//static const String sounds[] = {"Birds",       "Ocean",    "Crickets",  "Xilophone", "Waterfall"};
static const String lights[] = {"LIGHT_GREEN", "SKY_BLUE", "DEEP_BLUE", "PURPLE",    "ORANGE"};

// static const String SYSmenu[] = {"Sounds", "Lights", "IoT"};


//  - - -  Variables  - - -
byte MENU = 0;
byte Last_MENU = (sizeof(menu_main)/sizeof(*menu_main));
uint32_t MENU_LastTime = 0;              // Last MENU selection time stamp
unsigned int Backto_MENU = 120;               // Timeout to return to Main (clock) Menu
bool Menu_Next = false;                       // Aux flag to jumo to next menu
bool Menu_1stRun = false;                     // Aux flag to run a pice of code just once
int delta = 0;                                // Aux var with the value to be added. Used on functions: set_alarm(),...

byte ZEN = 0;
byte SOUNDs = 0;
byte LIGHTs = 0;

//  - - - AUX libraries
#include <mn_alarm.h>
//#include <mn_zen.h>
#include <mn_sounds.h>
#include <mn_lights.h>
#include <mn_ambient.h>
#include <mn_shades.h>
#include <mn_clock.h>  /// this must be the last one as it calls functions from previous libs
//  - - -  Functions  - - -

void menu_setup() {
  Last_Alarm_State = !config.Alarm_State;             // To force the bell icon update
  batt_icon_update();                                 // To force the Battery icon update
}

void menu_loop() {
    // MENU handling
    if (Last_MENU != MENU) {
        switch(Last_MENU) {   // actions to execute before Leaving the current menu. typically, to clean the screen...
            case 0:     // Clock
                display_drawtime(LastDateTime, BGColor);  // Clear clock
                display_drawdate(LastDateTime, BGColor);  // Clear date
                break;
            case 1:     // Alarm
                display_drawalarm(config.AlarmDateTime, BGColor);
                break;
            case 2:     // Sounds
                display_drawprevious(BGColor);
                display_drawplay(0, BGColor);
                display_drawplay(1, BGColor);
                display_drawplay(2, BGColor);
                display_drawnext(BGColor);
                display_drawsound(SOUNDs, BGColor);
                display_drawvolume(config.Volume, BGColor);
                break;
            case 3:     // Lights
                display_drawEFX(EFX, BGColor);
                for (size_t i = 0; i < NEOPixelsNUM; i++) NEOcolor_set (BLACK, i);
                break;
            case 4:     // Ambient
                display_drawambient(Last_Temperature, Last_Humidity, Last_Tempe_MIN, Last_Tempe_MAX, BGColor);
            //case 4:     // Shades
                    //display_drawshades(SHADES, BGColor);
                    break;
        }
        switch(MENU) {  // actions to execute whenn moving to current menu. typically, draw the full image.
            case 0:     // Clock
                curDateTime();
                display_drawtime(DateTime, MainColor);
                display_drawdate(DateTime, MainColor);
                LastDateTime = DateTime;
                break;
            case 1:     // Alarm
                display_drawalarm(config.AlarmDateTime, MainColor);
                break;
            case 2:     // Sounds
                display_drawprevious(MainColor);
                if (play_status <= 1) display_drawplay(0, MainColor);
                if (play_status >= 2) display_drawplay(2, EditColor);
                display_drawnext(MainColor);
                display_drawsound(SOUNDs, MainColor);
                display_drawvolume(config.Volume, MainColor);
                break;
            case 3:     // Lights
                display_drawEFX(EFX, MainColor);
                for (size_t i = 0; i < NEOPixelsNUM; i++) NEOcolor_set (BLACK, i);
                break;
            case 4:     // Alarm
                refresh_ambient();
            //case 4:     // Shades
                //display_drawshades(SHADES, MainColor);
                break;
        }
        //telnet_print("Last Menu: " + menu_main[Last_MENU]);
        //telnet_println("\tCurrent Menu: " + menu_main[MENU]);
        display_text(menu_main[Last_MENU], BGColor, 1, Last_MENU * 18, 20);  // Clear Menu
        display_text(menu_main[MENU], MainColor, 1, MENU * 18, 20);          // write Menu
        Last_MENU = MENU;
        MENU_LastTime = millis();
    }

    // Timeout to clear sub-menu flags and return to Main (clock) Menu
    if ( millis() - MENU_LastTime > (Backto_MENU * 1000)) {
        Alarm_Set = false;
        MENU = 0;
        //MENU = (MENU + 1)%(sizeof(menu_main)/sizeof(*menu_main));  // jump through all menus

    }

    switch(MENU) {
        case 0:     // Clock
                loop_clock();
                break;
        case 1:     // alarm
                loop_alarm();
                break;

        case 2:
                loop_sounds();
                break;
        case 3:
                loop_lights();
                break;
        case 4:     // alarm
                loop_ambient();
        //case 4:
                //loop_shades();
                break;
        /*
        case 5:
                loop_system();
                break;
        */
        default :
                if(A_COUNT == 1 && !A_STATUS && (millis() - Last_A > Butt_Interval)) {
                    MENU = (MENU + 1)%(sizeof(menu_main)/sizeof(*menu_main));
                    telnet_println("Menu: " + menu_main[MENU]);
                    A_COUNT = 0;
                }
                if(A_COUNT == 2 && !A_STATUS && (millis() - Last_A > Butt_Interval)) {
                    MENU = 0;
                    A_COUNT = 0;
                }
    }

    // ICONs handling
    loop_icons();
}
