//  - - -  Variables  - - -


//  - - -  CLOCK related FUNCTIONS  - - -
void display_drawtime(strDateTime strDtTm=DateTime, uint16_t color=MainColor, int x=2, int y=56) {
    display_drawhour(strDtTm, color, x, y);
    display_text(String(':'), color, 4, x + 40, y);
    display_drawmin(strDtTm, color, x, y);
    //display_drawsec(strDtTm, color, x, y);
}


void display_updatetime(uint16_t color=MainColor, uint16_t bgcolor=BGColor, int x=2, int y=56) {
  //curDateTime();
  if (LastDateTime.hour != DateTime.hour) {
      display_drawhour(LastDateTime, bgcolor, x, y);
      display_drawhour(DateTime, color, x, y);
  }
  if (LastDateTime.minute != DateTime.minute) {
      display_drawmin(LastDateTime, bgcolor, x, y);
      display_drawmin(DateTime, color, x, y);
  }
  if (LastDateTime.second != DateTime.second) {
      if (DateTime.second%2 == 0 ) display_text(String(':'), color, 4, x + 40, y);
      else display_text(String(':'), bgcolor, 4, x + 40, y);
      /*
      display_drawsec(LastDateTime, bgcolor, x, y);
      display_drawsec(DateTime, color, x, y);
      */
  }
  //LastDateTime = DateTime;
}

void display_updatedate(uint16_t color=MainColor, uint16_t bgcolor=BGColor, int x=7, int y=105) {
      //curDateTime();  //Skipped as display_drawclock() function should run much more often than this one.
    if (LastDateTime.wday != DateTime.wday) {
        display_drawwday(LastDateTime, bgcolor, x, y);
        display_drawwday(DateTime, color, x, y);
    }
    if (LastDateTime.day != DateTime.day) {
        display_drawday(LastDateTime, bgcolor, x, y);
        display_drawday(DateTime, color, x, y);
    }
    if (LastDateTime.month != DateTime.month) {
        display_drawmonth(LastDateTime, bgcolor, x, y);
        display_drawmonth(DateTime, color, x, y);
    }
    /*
    if (LastDateTime.year != DateTime.year) {
        display_drawyear(LastDateTime, bgcolor, x, y);
        display_drawyear(DateTime, color, x, y);
    }
    */
    //LastDateTime = DateTime;
}


void display_updateclock() {
        curDateTime();
        display_updatetime();
        display_updatedate();
        LastDateTime = DateTime;
}


void loop_clock() {
   if(A_COUNT == 1 && !A_STATUS && (millis() - Last_A > Butt_Interval)) {
        MENU = (MENU + 1)%(sizeof(menu_main)/sizeof(*menu_main));
        //telnet_println("Menu: " + menu_main[MENU]);
        A_COUNT = 0;
    }
    if (((millis() - RefMillis)%1000) < 20) {
        display_updateclock();
        if (config.Alarm_State) alarm_ring();
    }
}
