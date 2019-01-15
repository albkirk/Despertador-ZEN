//  - - -  Variables  - - -

static const String location[] = {"Cozinha", "Escritorio", "Quarto", "SalaJantar","SalaEstar","Suite"};
byte Last_SHADES = 0;                          // Last position of SHADES
bool Last_Shades_State = false;                // Last Shades state
bool Shades_Set = false;                       // set Shades time menu
byte Shades_Set_index = 9;                     // Shades item index to set (hour, min, wday, alarm, shades,...)

//  - - -  ALARM related FUNCTIONS  - - -
void set_shades() {
        if(A_COUNT == 1 && !A_STATUS && (millis() - last_A > 6 * interval)) {
            A_COUNT = 0;
        }
        if(B_COUNT == 1 && !B_STATUS && (millis() - last_B > 6 * interval)) {
            Menu_Next = true;
            B_COUNT = 0;
            MENU_LastTime = millis();
        }
        if(C_COUNT == 1 && !C_STATUS && (millis() - last_C > 6 * interval)) {
            delta = 1;
            C_COUNT = 0;
        }
        if(C_COUNT == 2 && !C_STATUS && (millis() - last_C > 6 * interval)) {
            delta = 10;
            C_COUNT = 0;
        }
        switch (Shades_Set_index) {
            case 0:       // edit hour
                if (delta !=0) {
                    //tft_drawhour(config.AlarmDateTime, BGColor);
                    //config.AlarmDateTime.hour = (config.AlarmDateTime.hour + delta)%24;
                    //tft_drawhour(config.AlarmDateTime, EditColor);
                    delta = 0;
                    break;
                }
                if (Menu_Next) {
                    //tft_drawhour(config.AlarmDateTime, SetColor);
                    Menu_Next = false;
                    Menu_1stRun = true;
                    Shades_Set_index ++;
                    break;
                }
                if (Menu_1stRun) {
                    //tft_drawhour(config.AlarmDateTime, EditColor);
                    Menu_1stRun = false;
                }
                break;
            case 1:       // edit minute
                if (delta !=0) {
                    //tft_drawmin(config.AlarmDateTime, BGColor);
                    //config.AlarmDateTime.minute = (config.AlarmDateTime.minute + delta)%60;
                    //tft_drawmin(config.AlarmDateTime, EditColor);
                    delta = 0;
                    break;
                }
                if (Menu_Next) {
                    //tft_drawmin(config.AlarmDateTime, SetColor);
                    Menu_Next = false;
                    Menu_1stRun = true;
                    Shades_Set_index ++;
                    break;
                }
                if (Menu_1stRun) {
                    //tft_drawmin(config.AlarmDateTime, EditColor);
                    Menu_1stRun = false;
                }
                break;
            case 2:       // edit Shades Enabled
                if (delta !=0) {
                    //tft_drawbell(config.AlarmDateTime, BGColor);
                    //config.AlarmDateTime.alarm = !config.AlarmDateTime.alarm;
                    //tft_drawbell(config.AlarmDateTime, EditColor);
                    delta = 0;
                    break;
                }
                if (Menu_Next) {
                    //tft_drawbell(config.AlarmDateTime, SetColor);
                    Menu_Next = false;
                    Menu_1stRun = true;
                    Shades_Set_index ++;
                    break;
                }
                if (Menu_1stRun) {
                    //tft_drawbell(config.AlarmDateTime, EditColor);
                    Menu_1stRun = false;
                }
                break;
            case 3:       // edit week day
                if (delta !=0) {
                    //tft_drawwday(config.AlarmDateTime, BGColor);
                    //config.AlarmDateTime.wday = (config.AlarmDateTime.wday + delta)%10;
                    //tft_drawwday(config.AlarmDateTime, EditColor);
                    delta = 0;
                    break;
                }
                if (Menu_Next) {
                    //tft_drawwday(config.AlarmDateTime, SetColor);
                    Menu_Next = false;
                    Menu_1stRun = true;
                    Shades_Set_index ++;
                    break;
                }
                if (Menu_1stRun) {
                    //tft_drawwday(config.AlarmDateTime, EditColor);
                    Menu_1stRun = false;
                }
                break;
            case 4:       // edit Shades
                if (delta !=0) {
                    //tft_drawshades(config.AlarmDateTime, BGColor);
                    //config.AlarmDateTime.shades = (config.AlarmDateTime.shades + delta)%(sizeof(shades)/sizeof(*shades));;
                    //tft_drawshades(config.AlarmDateTime, EditColor);
                    delta = 0;
                    break;
                }
                if (Menu_Next) {
                    //tft_drawshades(config.AlarmDateTime, SetColor);
                    Menu_Next = false;
                    Menu_1stRun = true;
                    Shades_Set_index ++;
                    break;
                }
                if (Menu_1stRun) {
                    //tft_drawshades(config.AlarmDateTime, EditColor);
                    Menu_1stRun = false;
                }
                break;
            default :
                player_beep();
                Menu_Next = false;
                Menu_1stRun = true;
                Shades_Set_index = 0;
        }
}

void loop_shades() {
    if(A_COUNT == 1 && !A_STATUS && (millis() - last_A > 6 * interval)) {
            MENU = (MENU + 1)%(sizeof(menu_main)/sizeof(*menu_main));
            telnet_println("Menu: " + menu_main[MENU]);
            A_COUNT = 0;
    }
    if(A_COUNT == 2 && !A_STATUS && (millis() - last_A > 6 * interval)) {
            MENU = 0;
            A_COUNT = 0;
    }
    if(B_COUNT == 1 && !B_STATUS && (millis() - last_B > 6 * interval)) {
            if (SHADES > 100) SHADES = 100;
            else SHADES = SHADES + 10;
            B_COUNT = 0;
    }
    if(C_COUNT == 1 && !C_STATUS && (millis() - last_C > 6 * interval)) {
            if (SHADES <= 10) SHADES = 0;
            else SHADES = SHADES - 10;
            C_COUNT = 0;
    }
    if(C_COUNT == 1 && C_STATUS && (millis() - last_C > 6 * interval)) {
            player_beep(1);
            //storage_write();
            C_COUNT = 0;
    }
    if(C_COUNT == 2 && !C_STATUS && (millis() - last_C > 6 * interval)) {
              C_COUNT = 0;
    }
    if (Last_SHADES != SHADES) {
        tft_drawshades(SHADES, MainColor);
        Last_SHADES=SHADES;
    }
}