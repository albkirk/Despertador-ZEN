//  - - -  Variables  - - -
//bool Alarm_State = false;                   // Defined on config structure Alarm state (true -> Ring / False -> Not Ring)
bool Last_Alarm_State = false;                // Last Alarm state
bool Alarm_Set = false;                       // set Alarm time menu
byte Alarm_Set_index = 0;                     // Alarm item index to set (hour, min, wday, alarm, sound,...)

//  - - -  ALARM related FUNCTIONS  - - -
void alarm_ring(strDateTime stralrDtTm=config.AlarmDateTime, strDateTime strDtTm=DateTime) {
  if (stralrDtTm.alarm == true && strDtTm.second <=1 && stralrDtTm.hour == strDtTm.hour && stralrDtTm.minute == strDtTm.minute) {
      if (stralrDtTm.wday == 8 || (stralrDtTm.wday == 9 && strDtTm.wday >= 2 && strDtTm.wday <= 6) || (stralrDtTm.wday == 0 && (strDtTm.wday ==1 || strDtTm.wday ==7)) || stralrDtTm.wday == strDtTm.wday) {
            player_play(stralrDtTm.sound);
        }
  }
}


void set_alarm() {
        if(A_COUNT == 1 && !A_STATUS && (millis() - Last_A > Butt_Interval)) {
            A_COUNT = 0;
        }
        if(B_COUNT == 1 && !B_STATUS && (millis() - Last_B > Butt_Interval)) {
            Menu_Next = true;
            B_COUNT = 0;
            MENU_LastTime = millis();
        }
        if(C_COUNT == 1 && !C_STATUS && (millis() - Last_C > Butt_Interval)) {
            delta = 1;
            C_COUNT = 0;
        }
        if(C_COUNT == 2 && !C_STATUS && (millis() - Last_C > Butt_Interval)) {
            delta = 10;
            C_COUNT = 0;
        }
        switch (Alarm_Set_index) {
            case 0:       // edit hour
                if (delta !=0) {
                    display_drawhour(config.AlarmDateTime, BGColor);
                    config.AlarmDateTime.hour = (config.AlarmDateTime.hour + delta)%24;
                    display_drawhour(config.AlarmDateTime, EditColor);
                    delta = 0;
                    break;
                }
                if (Menu_Next) {
                    display_drawhour(config.AlarmDateTime, SetColor);
                    Menu_Next = false;
                    Menu_1stRun = true;
                    Alarm_Set_index ++;
                    break;
                }
                if (Menu_1stRun) {
                    display_drawhour(config.AlarmDateTime, EditColor);
                    Menu_1stRun = false;
                }
                break;
            case 1:       // edit minute
                if (delta !=0) {
                    display_drawmin(config.AlarmDateTime, BGColor);
                    config.AlarmDateTime.minute = (config.AlarmDateTime.minute + delta)%60;
                    display_drawmin(config.AlarmDateTime, EditColor);
                    delta = 0;
                    break;
                }
                if (Menu_Next) {
                    display_drawmin(config.AlarmDateTime, SetColor);
                    Menu_Next = false;
                    Menu_1stRun = true;
                    Alarm_Set_index ++;
                    break;
                }
                if (Menu_1stRun) {
                    display_drawmin(config.AlarmDateTime, EditColor);
                    Menu_1stRun = false;
                }
                break;
            case 2:       // edit Alarm Enabled
                if (delta !=0) {
                    display_drawbell(config.AlarmDateTime, BGColor);
                    config.AlarmDateTime.alarm = !config.AlarmDateTime.alarm;
                    display_drawbell(config.AlarmDateTime, EditColor);
                    delta = 0;
                    break;
                }
                if (Menu_Next) {
                    display_drawbell(config.AlarmDateTime, SetColor);
                    Menu_Next = false;
                    Menu_1stRun = true;
                    Alarm_Set_index ++;
                    break;
                }
                if (Menu_1stRun) {
                    display_drawbell(config.AlarmDateTime, EditColor);
                    Menu_1stRun = false;
                }
                break;
            case 3:       // edit week day
                if (delta !=0) {
                    display_drawwday(config.AlarmDateTime, BGColor);
                    config.AlarmDateTime.wday = (config.AlarmDateTime.wday + delta)%10;
                    display_drawwday(config.AlarmDateTime, EditColor);
                    delta = 0;
                    break;
                }
                if (Menu_Next) {
                    display_drawwday(config.AlarmDateTime, SetColor);
                    Menu_Next = false;
                    Menu_1stRun = true;
                    Alarm_Set_index ++;
                    break;
                }
                if (Menu_1stRun) {
                    display_drawwday(config.AlarmDateTime, EditColor);
                    Menu_1stRun = false;
                }
                break;
            case 4:       // edit Sound
                if (delta !=0) {
                    display_drawsound(config.AlarmDateTime.sound, BGColor);
                    config.AlarmDateTime.sound = (config.AlarmDateTime.sound + delta)%(sizeof(sounds)/sizeof(*sounds));;
                    display_drawsound(config.AlarmDateTime.sound, EditColor);
                    delta = 0;
                    break;
                }
                if (Menu_Next) {
                    display_drawsound(config.AlarmDateTime.sound, SetColor);
                    Menu_Next = false;
                    Menu_1stRun = true;
                    Alarm_Set_index ++;
                    break;
                }
                if (Menu_1stRun) {
                    display_drawsound(config.AlarmDateTime.sound, EditColor);
                    Menu_1stRun = false;
                }
                break;
            default :
                player_beep();
                Menu_Next = false;
                Menu_1stRun = true;
                Alarm_Set_index = 0;
        }
}

void loop_alarm() {
    if(B_COUNT == 1 && B_STATUS && (millis() - Last_B > Butt_Interval)) {
        if (!Alarm_Set) {
            Alarm_Set = true;
            display_drawalarm(config.AlarmDateTime, SetColor);
            Menu_Next = false;
            Menu_1stRun = true;
            Alarm_Set_index = 0;
        }
        else {
            Alarm_Set = false;
            player_beep(1);
            storage_write();
            display_drawalarm(config.AlarmDateTime, MainColor);
        }
        B_COUNT = 0;
    }
    if (Alarm_Set) {
        set_alarm();
    }
    else{
        if(A_COUNT == 1 && !A_STATUS && (millis() - Last_A > Butt_Interval)) {
            MENU = (MENU + 1)%(sizeof(menu_main)/sizeof(*menu_main));
            telnet_println("Menu: " + menu_main[MENU]);
            A_COUNT = 0;
        }
        if(A_COUNT == 2 && !A_STATUS && (millis() - Last_A > Butt_Interval)) {
            MENU = 0;
            A_COUNT = 0;
        }
        if(C_COUNT == 1 && C_STATUS && (millis() - Last_C > Butt_Interval)) {
            config.Alarm_State = !config.Alarm_State;
            storage_write();
            C_COUNT = 0;
        }
    }
}
