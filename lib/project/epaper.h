/* ****************************************************/

#include <GxEPD2_BW.h>

GxEPD2_BW<GxEPD2_213_B73, GxEPD2_213_B73::HEIGHT> display(GxEPD2_213_B73(CS_PIN, DC_PIN, RST_PIN, BUSY_PIN)); // GDEH0213B73
uint16_t MainColor=GxEPD_BLACK;
uint16_t BGColor=GxEPD_WHITE;
uint16_t SetColor=GxEPD_DARKGREY;
uint16_t EditColor=GxEPD_LIGHTGREY;

#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeSerif24pt7b.h>
#include <Fonts/FreeMonoOblique18pt7b.h>
#include <Fonts/FreeSans24pt7b.h>

void display_text(String text, uint16_t color=MainColor, uint8_t s=1, int x=0, int y=0, const GFXfont *font = NULL, bool wraptext=true) {
    display.setCursor(x, y);
    display.setTextColor(color);
    if(font != NULL) display.setFont(font);
    else display.setFont();
    display.setTextSize(s);
    display.setTextWrap(wraptext);
    display.firstPage();
    do {
        display.print(text);
    } while (display.nextPage());
}

void display_drawhour(strDateTime strDtTm=DateTime, uint16_t color=MainColor, int x=2, int y=56) {
      String text="";
      if (strDtTm.hour <=9) text = String("0") + String(strDtTm.hour);
      else text = String(strDtTm.hour);
      display_text(text,        color, 4, x,      y);
      //display_text(text,        color, 1, x,      y, &FreeSerif24pt7b);
}

void display_drawmin(strDateTime strDtTm=DateTime, uint16_t color=MainColor, int x=2, int y=56) {
      String text="";
      if (strDtTm.minute <=9) text = String("0") + String(strDtTm.minute);
      else text = String(strDtTm.minute);
      display_text(text,      color, 4, x + 55, y);
      //display_text(text,      color, 1, x + 55, y, &FreeSerif24pt7b);
}

void display_drawsec(strDateTime strDtTm=DateTime, uint16_t color=MainColor, int x=2, int y=56) {
      String text="";
      if (strDtTm.second <=9) text = String("0") + String(strDtTm.second);
      else text = String(strDtTm.second);
      display_text(text,      color, 2, x + 102, y);
}

void display_drawyear(strDateTime strDtTm=DateTime, uint16_t color=MainColor, int x=7, int y=105) {
      String text="";
      if (strDtTm.year <=9) text = String("0") + String(strDtTm.year);
      else text = String(strDtTm.year);
      display_text(text,        color, 2, x + 73, y);
}

void display_drawmonth(strDateTime strDtTm=DateTime, uint16_t color=MainColor, int x=7, int y=105) {
      String text="";
      if (strDtTm.month <=9) text = String("0") + String(strDtTm.month);
      else text = String(strDtTm.month);
      display_text(text,        color, 2, x + 86, y);
}

void display_drawday(strDateTime strDtTm=DateTime, uint16_t color=MainColor, int x=7, int y=105) {
      String text="";
      if (strDtTm.day <=9) text = String("0") + String(strDtTm.day);
      else text = String(strDtTm.day);
      display_text(text,        color, 2, x + 50, y);
}

void display_drawwday(strDateTime strDtTm=DateTime, uint16_t color=MainColor, int x=7, int y=105) {
      String text="";
      text = WeekDays[strDtTm.wday];
      display_text(text,        color, 2, x,      y);
}

void display_drawsound(byte strDtTm_sound = 0, uint16_t color=MainColor, int x=7, int y=34) {
      String text="";
      text = sounds[strDtTm_sound];
      display_text(text,        color, 2, x,      y);
}

void display_drawvolume(byte volbar = config.Volume, uint16_t color=MainColor, int x=12, int y=96) {
      display.drawRect(x, y, 104, 10, color);
      display.fillRect(x+2, y+2, volbar, 6, color);
}

void display_drawshades(byte level = 50, uint16_t color=MainColor, uint16_t bgcolor=BGColor, int x=24, int y=40) {
    display.drawRect(x - 2, y - 2, 84, 54, color);
    display.fillRect(x, y, 80, level/2, color);
    display.fillRect(x, y + level/2, 80, 50 - level/2, bgcolor);
}

void display_drawEFX(byte EFXid = 0, uint16_t color=MainColor, int x=7, int y=34) {
      String text="";
      text = EFXName[EFXid];
      display_text(text,        color, 2, x,      y);
}

void display_drawambient(float display_temp, float display_humi, float display_TMin, float display_TMax, uint16_t color=MainColor, int x=7, int y=56) {
      String text="";
      text = String("T: " + String(display_temp, 1) + "C");
      display_text(text,        color, 2, x,      y);
      text = String("H: " + String(display_humi, 0) + "%");
      display_text(text,        color, 2, x, y + 20);
      text = String("Min/Max T: " + String(display_TMin, 1) + "/" + String(display_TMax, 1));
      display_text(text,        color, 1, x, y + 40);

}

void display_drawprevious(uint16_t color=MainColor, int x=10, int y=56) {
      display.drawBitmap(x     , y, previous_icon, 32, 32, color);
}

void display_drawplay(byte pps = 0, uint16_t color=MainColor, int x=10, int y=56) {
    switch (pps) {
        case 0:
            display.drawBitmap(x + 38, y, play_icon, 32, 32, color);
            break;
        case 1:
            display.drawBitmap(x + 38, y, pause_icon, 32, 32, color);
            break;
        case 2:
            display.drawBitmap(x + 38, y, stop_icon, 32, 32, color);
            break;
    }
}

void display_drawnext(uint16_t color=MainColor, int x=10, int y=56) {
      display.drawBitmap(x + 76, y, next_icon, 32, 32, color);
}

void display_drawbell(strDateTime strDtTm=DateTime, uint16_t color=MainColor, int x=2, int y=56) {
      display.drawBitmap(x + 104, y, bell_icon, 16, 16, color);
      if (!strDtTm.alarm) {
          //if (color != BGColor) color = color - 0x841;
          display.drawLine(x + 104, y, x + 104 + 16, y + 16, color);
          display.drawLine(x + 104, y + 16, x + 104 + 16, y, color);
      };
}

void display_drawalarm(strDateTime strDtTm=DateTime, uint16_t color=MainColor, int x=2, int y=56) {
    display_drawhour(strDtTm, color, x, y);
    display_text(String(':'), color, 4, x + 40, y);
    display_drawmin(strDtTm, color, x, y);
    display_drawwday(strDtTm, color, 7, 105);
    display_drawbell(strDtTm, color, x, y);
    display_drawsound(strDtTm.sound, color, 7, 34);
}

void display_drawdate(strDateTime strDtTm=DateTime, uint16_t color=MainColor, int x=7, int y=105) {
    display_drawwday(strDtTm, color, x, y);
    display_text(String(','), color, 2, x + 35, y);
    display_drawday(strDtTm, color, x, y);
    display_text(String('/'), color, 2, x + 74, y);
    display_drawmonth(strDtTm, color, x, y);
    //display_text(String('/'), color, 2, x + 61, y);
    //display_drawyear(strDtTm, color, x, y);
}

void batt_icon_update() {
    //display_text((String((int)Batt_Level)+"%"),BGColor, 1, 104, 16);
    //display_text((String(voltage, 2)+"v"),BGColor, 1, 98, 26);
    float Batt_Level = getBattLevel();
    //display_text((String((int)Batt_Level)+"%"),ST7735_WHITE, 1, 104, 16);
    //display_text((String(voltage, 2)+"v"),ST7735_WHITE, 1, 98, 26);
/*    if (Batt_Level > 100)  {
        BattPowered = false;
        display.drawBitmap(110, 4,battery_icon_1_4, 16, 8, ST7735_BLUE);
        display.fillRect(113, 6, 2, 4, ST7735_BLUE);
        display.fillRect(117, 6, 2, 4, ST7735_BLUE);
        display.fillRect(121, 6, 2, 4, ST7735_BLUE);
    }
    if (Batt_Level > 75 && Batt_Level <= 100)  {
        BattPowered = true;
        display.drawBitmap(110, 4,battery_icon_1_4, 16, 8, ST7735_WHITE);
        display.fillRect(113, 6, 2, 4, ST7735_WHITE);
        display.fillRect(117, 6, 2, 4, ST7735_WHITE);
        display.fillRect(121, 6, 2, 4, ST7735_WHITE);
    }
    else if (Batt_Level > 50 && Batt_Level <= 75) {
        BattPowered = true;
        display.drawBitmap(110, 4,battery_icon_1_4, 16, 8, ST7735_WHITE);
        display.fillRect(113, 6, 2, 4, ST7735_WHITE);
        display.fillRect(117, 6, 2, 4, ST7735_WHITE);
        display.fillRect(121, 6, 2, 4, BGColor);
    }
    else if (Batt_Level > 25 && Batt_Level <= 50) {
        BattPowered = true;
      display.drawBitmap(110, 4,battery_icon_1_4, 16, 8, ST7735_WHITE);
      display.fillRect(113, 6, 2, 4, ST7735_WHITE);
      display.fillRect(117, 6, 2, 4, BGColor);
      display.fillRect(121, 6, 2, 4, BGColor);
    }
    else if (Batt_Level <= 25)  {
        BattPowered = true;
        display.drawBitmap(110, 4,battery_icon_1_4, 16, 8, ST7735_RED);
        display.fillRect(113, 6, 2, 4, BGColor);
        display.fillRect(117, 6, 2, 4, BGColor);
        display.fillRect(121, 6, 2, 4, BGColor);
        player_beepdn(2);
    }
    //LOW_Batt_check();
*/
}

void loop_icons() {
/*
  //  -- WiFI Icon --
    if ( WIFI_state != Last_WIFI_state ) {
        if ( WIFI_state == WL_CONNECTED ) display.drawBitmap(20, 0, wifi_icon, 16, 16, ST7735_WHITE);
        else display.drawBitmap(20, 0, wifi_icon, 16, 16, BGColor);
        Last_WIFI_state = WIFI_state;
    };
    //display.drawBitmap(20, 0, wifi_OFF_icon, 16, 16, ST7735_GREEN);


  // -- ALARM Icon --
    if ( config.Alarm_State != Last_Alarm_State ) {
        if (config.Alarm_State) display.drawBitmap(0,0,bell_icon,16,16,MainColor);
        else display.drawBitmap(0,0,bell_icon,16,16,BGColor);
        Last_Alarm_State = config.Alarm_State;
    };

  // battery Icon
    if (((millis() - RefMillis)%30000) < 20) batt_icon_update();

  // Touch Button
    if (Last_TL_STATUS != TL_STATUS) {
        if (TL_STATUS == true) display_text(("Touched!"),ST7735_GREEN, 1, 40, 2);
        if (TL_STATUS == false) display_text(("Touched!"),BGColor, 1, 40, 2);
        Last_TL_STATUS = TL_STATUS;
    }
*/
}


void display_setup() {

    delay(100);
    display.init(115200);

    Serial.println("EPaper Initialized");
    if (display.epd2.hasFastPartialUpdate) Serial.println("FAST!! partial mode");
    else if (display.epd2.hasPartialUpdate) Serial.println("Slow partial mode");
    else Serial.println("NO partial mode");
 
    display.setRotation(EPaperRotate);

    long deltatime = millis();
    display.fillScreen(BGColor);
    deltatime = millis() - deltatime;

    display.setTextColor(EditColor);    // ST7735_RED
    display.setTextSize(3);
    //display_text("time: " + String(deltatime));
    display_text("Date / Time: " + curDateTime());
    //display.println("F Rate: " + String(1000/deltatime));
    delay(5000);
    display.powerOff();
}
