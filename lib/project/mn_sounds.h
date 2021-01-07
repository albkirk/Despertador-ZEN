//  - - -  Variables  - - -
//bool Sound_State = false;                   // Defined on config structure Sound state (true -> Ring / False -> Not Ring)
bool Last_Sound_State = false;                // Last Sound state
bool Sound_Set = false;                       // set Sound time menu
byte Sound_Set_index = 9;                     // Sound item index to set (hour, min, wday, alarm, sound,...)

//  - - -  ALARM related FUNCTIONS  - - -
void loop_sounds() {
    if(A_COUNT == 1 && !A_STATUS && (millis() - Last_A > Butt_Interval)) {   // Next Menu
            MENU = (MENU + 1)%(sizeof(menu_main)/sizeof(*menu_main));
            telnet_println("Menu: " + menu_main[MENU]);
            A_COUNT = 0;
    }
    if(A_COUNT == 2 && !A_STATUS && (millis() - Last_A > Butt_Interval)) {   // Back to Menu 0
            MENU = 0;
            A_COUNT = 0;
    }
    if(B_COUNT == 1 && !B_STATUS && (millis() - Last_B > Butt_Interval)) {   // Next sound
        tft_drawnext(SetColor);
        tft_drawsound(SOUNDs, BGColor);
        SOUNDs = (SOUNDs + 1) % (sizeof(sounds)/sizeof(*sounds));
        tft_drawsound(SOUNDs, MainColor);
        delay(100);
        tft_drawnext(MainColor);
        B_COUNT = 0;
    }
    if(B_COUNT == 1 && B_STATUS && (millis() - Last_B > Butt_Interval)) {    // Play sound
        tft_drawplay(0, BGColor);
        tft_drawplay(2, EditColor);
        player_play(SOUNDs);
        MENU_LastTime = millis();
        B_COUNT = 0;
    }
    if(B_COUNT == 2 && !B_STATUS && (millis() - Last_B > Butt_Interval)) {   // Previous sound
        tft_drawprevious(SetColor);
        tft_drawsound(SOUNDs, BGColor);
        if (SOUNDs == 0) SOUNDs = (sizeof(sounds)/sizeof(*sounds)) - 1;
        else SOUNDs = (SOUNDs - 1) % (sizeof(sounds)/sizeof(*sounds));
        tft_drawsound(SOUNDs, MainColor);
        delay(100);
        tft_drawprevious(MainColor);
        B_COUNT = 0;
    }
    if(C_COUNT == 1 && !C_STATUS && (millis() - Last_C > Butt_Interval)) {   // Volume UP
            tft_drawvolume(config.Volume, BGColor);
            config.Volume = config.Volume + 10;
            if (config.Volume > 100) config.Volume = 0;
            tft_drawvolume(config.Volume, MainColor);
            C_COUNT = 0;
    }
    if(C_COUNT == 1 && C_STATUS && (millis() - Last_C > Butt_Interval)) {    // Store Volume
            player_beep(1);
            storage_write();
            C_COUNT = 0;
    }
    if(C_COUNT == 2 && !C_STATUS && (millis() - Last_C > Butt_Interval)) {   // Volume DOWN
            tft_drawvolume(config.Volume, BGColor);
            if (config.Volume == 0) config.Volume = 100;
            else if (config.Volume <= 10) config.Volume = 0;
            else config.Volume = config.Volume - 10;
            tft_drawvolume(config.Volume, MainColor);
            C_COUNT = 0;
    }
    if (play_status == 1) {
            tft_drawplay(2, BGColor);
            tft_drawplay(0, MainColor);
            play_status = 0;
    }
}
