//  - - -  Variables  - - -


//  - - -  CLOCK related FUNCTIONS  - - -
void tft_drawtime(strDateTime strDtTm=DateTime, uint16_t color=MainColor, int x=2, int y=56) {
    tft_drawhour(strDtTm, color, x, y);
    tft_text(String(':'), color, 4, x + 40, y);
    tft_drawmin(strDtTm, color, x, y);
    //tft_drawsec(strDtTm, color, x, y);
}


void tft_updatetime(uint16_t color=MainColor, uint16_t bgcolor=BGColor, int x=2, int y=56) {
  //curDateTime();
  if (LastDateTime.hour != DateTime.hour) {
      tft_drawhour(LastDateTime, bgcolor, x, y);
      tft_drawhour(DateTime, color, x, y);
  }
  if (LastDateTime.minute != DateTime.minute) {
      tft_drawmin(LastDateTime, bgcolor, x, y);
      tft_drawmin(DateTime, color, x, y);
  }
  if (LastDateTime.second != DateTime.second) {
      if (DateTime.second%2 == 0 ) tft_text(String(':'), color, 4, x + 40, y);
      else tft_text(String(':'), bgcolor, 4, x + 40, y);
      /*
      tft_drawsec(LastDateTime, bgcolor, x, y);
      tft_drawsec(DateTime, color, x, y);
      */
  }
  //LastDateTime = DateTime;
}

void tft_updatedate(uint16_t color=MainColor, uint16_t bgcolor=BGColor, int x=7, int y=105) {
      //curDateTime();  //Skipped as tft_drawclock() function should run much more often than this one.
    if (LastDateTime.wday != DateTime.wday) {
        tft_drawwday(LastDateTime, bgcolor, x, y);
        tft_drawwday(DateTime, color, x, y);
    }
    if (LastDateTime.day != DateTime.day) {
        tft_drawday(LastDateTime, bgcolor, x, y);
        tft_drawday(DateTime, color, x, y);
    }
    if (LastDateTime.month != DateTime.month) {
        tft_drawmonth(LastDateTime, bgcolor, x, y);
        tft_drawmonth(DateTime, color, x, y);
    }
    /*
    if (LastDateTime.year != DateTime.year) {
        tft_drawyear(LastDateTime, bgcolor, x, y);
        tft_drawyear(DateTime, color, x, y);
    }
    */
    //LastDateTime = DateTime;
}


void tft_updateclock() {
        curDateTime();
        tft_updatetime();
        tft_updatedate();
        LastDateTime = DateTime;
}


void loop_clock() {
   if(A_COUNT == 1 && !A_STATUS && (millis() - Last_A > Butt_Interval)) {
        MENU = (MENU + 1)%(sizeof(menu_main)/sizeof(*menu_main));
        //telnet_println("Menu: " + menu_main[MENU]);
        A_COUNT = 0;
    }
    if (((millis() - RefMillis)%1000) < 20) {
        tft_updateclock();
        if (config.Alarm_State) alarm_ring();
    }
}
