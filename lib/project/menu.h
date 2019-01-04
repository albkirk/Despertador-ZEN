
//  - - -  Constants
static const String menu[] = {"Clock", "Alarm", "Sounds", "Lights", "Shades", "System"};


//  - - -  Variables  - - -
byte MENU = 0;
byte Last_MENU = (sizeof(menu)/sizeof(*menu));
unsigned long MENU_LastTime = 0;              // Last MENU selection time stamp
unsigned int Backto_MENU = 120;               // Timeout to return to Main (clock) Menu
bool Menu_Next = false;                       // Aux flag to jumo to next menu
bool Menu_1stRun = false;                     // Aux flag to run a pice of code just once
int delta = 0;                                // Aux var with the value to be added. Used on functions: set_alarm(),...

//  - - - AUX libraries
#include <menu_alarm.h>

//  - - -  Functions  - - -
void loop_icons() {
  //  -- WiFI Icon --
    if ( WIFI_state != Last_WIFI_state ) {
        if ( WIFI_state == WL_CONNECTED ) tft.drawBitmap(20, 0, wifi_icon, 20, 15, ST7735_WHITE);
        else tft.drawBitmap(20, 0, wifi_icon, 20, 15, BGColor);
        Last_WIFI_state = WIFI_state;
    };

  // -- ALARM Icon --
    if ( config.Alarm_State != Last_Alarm_State ) {
        if (config.Alarm_State) tft.drawBitmap(0,0,bell,16,16,MainColor);
        else tft.drawBitmap(0,0,bell,16,16,BGColor);
        Last_Alarm_State = config.Alarm_State;
    };

  // battery Icon
  //tft.drawBitmap(109,0,battery_icon, 20, 15, ST7735_GREEN);
}

void loop_clock() {
   if(A_COUNT == 1 && !A_STATUS && (millis() - last_A > 6 * interval)) {
        MENU = (MENU + 1)%(sizeof(menu)/sizeof(*menu));
        //telnet_println("Menu: " + menu[MENU]);
        A_COUNT = 0;
    }
    if (((millis() - RefMillis)%1000) < 20) {
        tft_updateclock();
        if (config.Alarm_State) alarm_ring();
    }
}




void loop_sounds() {
}

void loop_lights() {
}

void loop_shades() {
}

void loop_system() {
}


void menu_setup() {
  Last_Alarm_State = !config.Alarm_State;             // To force the bell icon update
}

void menu_loop() {

    // MENU handling
    if (Last_MENU != MENU) {
        switch(Last_MENU) {
            case 0:
                tft_drawtime(LastDateTime, BGColor);  // Clear clock
                tft_drawdate(LastDateTime, BGColor);  // Clear date
                break;
            case 1:
                tft_drawalarm(config.AlarmDateTime, BGColor);
                break;
        }
        switch(MENU) {
            case 0:
                curDateTime();
                tft_drawtime(DateTime, MainColor);
                tft_drawdate(DateTime, MainColor);
                LastDateTime = DateTime;
                break;
            case 1:
                tft_drawalarm(config.AlarmDateTime, MainColor);
                break;
        }
        //telnet_print("Last Menu: " + menu[Last_MENU]);
        //telnet_println("\tCurrent Menu: " + menu[MENU]);
        tft_text(menu[Last_MENU], BGColor, 1, Last_MENU * 18, 18);  // Clear Menu
        tft_text(menu[MENU], MainColor, 1, MENU * 18, 18);          // write Menu
        Last_MENU = MENU;
        MENU_LastTime = millis();
    }
    // Timeout to clear sub-menu flags and return to Main (clock) Menu
    if ( millis() - MENU_LastTime > (Backto_MENU * 1000)) {
        Alarm_Set = false;
        MENU = 0;
    }

    switch(MENU) {
        case 0:
                loop_clock();
                break;
        case 1:
                loop_alarm();
                break;
        /*
        case 2:
                loop_sounds();
                break;
        case 3:
                loop_lights();
                break;
        case 4:
                loop_shades();
                break;
        case 5:
                loop_system();
                break;
        */
        default :
                if(A_COUNT == 1 && !A_STATUS && (millis() - last_A > 6 * interval)) {
                    MENU = (MENU + 1)%(sizeof(menu)/sizeof(*menu));
                    telnet_println("Menu: " + menu[MENU]);
                    A_COUNT = 0;
            }
    }

    // ICONs handling
    loop_icons();
}
