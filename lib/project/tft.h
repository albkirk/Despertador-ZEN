/* ****************************************************/
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
//#include <SPI.h>


Adafruit_ST7735 display = Adafruit_ST7735(CS_PIN, DC_PIN, MOSI_PIN, CLK_PIN, RST_PIN);
uint16_t MainColor=ST7735_WHITE;
uint16_t BGColor=ST7735_BLACK;
uint16_t SetColor=ST7735_YELLOW;
uint16_t EditColor=ST7735_ORANGE;


#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeSerif24pt7b.h>
#include <Fonts/FreeMonoOblique18pt7b.h>
#include <Fonts/FreeSans24pt7b.h>

/*
void testlines(uint16_t color) {
  display.fillScreen(BGColor);
  for (int16_t x=0; x < display.width(); x+=6) {
    display.drawLine(0, 0, x, display.height()-1, color);
  }
  for (int16_t y=0; y < display.height(); y+=6) {
    display.drawLine(0, 0, display.width()-1, y, color);
  }

  display.fillScreen(BGColor);
  for (int16_t x=0; x < display.width(); x+=6) {
    display.drawLine(display.width()-1, 0, x, display.height()-1, color);
  }
  for (int16_t y=0; y < display.height(); y+=6) {
    display.drawLine(display.width()-1, 0, 0, y, color);
  }

  display.fillScreen(BGColor);
  for (int16_t x=0; x < display.width(); x+=6) {
    display.drawLine(0, display.height()-1, x, 0, color);
  }
  for (int16_t y=0; y < display.height(); y+=6) {
    display.drawLine(0, display.height()-1, display.width()-1, y, color);
  }

  display.fillScreen(BGColor);
  for (int16_t x=0; x < display.width(); x+=6) {
    display.drawLine(display.width()-1, display.height()-1, x, 0, color);
  }
  for (int16_t y=0; y < display.height(); y+=6) {
    display.drawLine(display.width()-1, display.height()-1, 0, y, color);
  }
}

void display_pixel(int x=0, int y=0, int color=ST7735_WHITE) {
    display.drawPixel(display.width()/2, display.height()/2, ST7735_GREEN);  // function to be reviewed
}

void testfastlines(uint16_t color1, uint16_t color2) {
  display.fillScreen(BGColor);
  for (int16_t y=0; y < display.height(); y+=5) {
    display.drawFastHLine(0, y, display.width(), color1);
  }
  for (int16_t x=0; x < display.width(); x+=5) {
    display.drawFastVLine(x, 0, display.height(), color2);
  }
}

void testdrawrects(uint16_t color) {
  display.fillScreen(BGColor);
  for (int16_t x=0; x < display.width(); x+=6) {
    display.drawRect(display.width()/2 -x/2, display.height()/2 -x/2 , x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2) {
  display.fillScreen(BGColor);
  for (int16_t x=display.width()-1; x > 6; x-=6) {
    display.fillRect(display.width()/2 -x/2, display.height()/2 -x/2 , x, x, color1);
    display.drawRect(display.width()/2 -x/2, display.height()/2 -x/2 , x, x, color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=radius; x < display.width(); x+=radius*2) {
    for (int16_t y=radius; y < display.height(); y+=radius*2) {
      display.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < display.width()+radius; x+=radius*2) {
    for (int16_t y=0; y < display.height()+radius; y+=radius*2) {
      display.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles() {
  display.fillScreen(BGColor);
  int color = 0xF800;
  int t;
  int w = display.width()/2;
  int x = display.height()-1;
  int y = 0;
  int z = display.width();
  for(t = 0 ; t <= 15; t++) {
    display.drawTriangle(w, y, y, x, z, x, color);
    x-=4;
    y+=4;
    z-=4;
    color+=100;
  }
}

void testroundrects() {
  display.fillScreen(BGColor);
  int color = 100;
  int i;
  int t;
  for(t = 0 ; t <= 4; t+=1) {
    int x = 0;
    int y = 0;
    int w = display.width()-2;
    int h = display.height()-2;
    for(i = 0 ; i <= 16; i+=1) {
      display.drawRoundRect(x, y, w, h, 5, color);
      x+=2;
      y+=3;
      w-=4;
      h-=6;
      color+=1100;
    }
    color+=100;
  }
}

void mediabuttons() {
  // play
  display.fillScreen(BGColor);
  display.fillRoundRect(25, 10, 78, 60, 8, ST7735_WHITE);
  display.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_RED);
  delay(500);
  // pause
  display.fillRoundRect(25, 90, 78, 60, 8, ST7735_WHITE);
  display.fillRoundRect(39, 98, 20, 45, 5, ST7735_GREEN);
  display.fillRoundRect(69, 98, 20, 45, 5, ST7735_GREEN);
  delay(500);
  // play color
  display.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_BLUE);
  delay(50);
  // pause color
  display.fillRoundRect(39, 98, 20, 45, 5, ST7735_RED);
  display.fillRoundRect(69, 98, 20, 45, 5, ST7735_RED);
  // play color
  display.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_GREEN);
}
*/

void display_text(String text, int color=ST7735_WHITE, uint8_t s=1, int x=0, int y=0, const GFXfont *font = NULL, bool wraptext=true) {
  display.setCursor(x, y);
  display.setTextColor(color);
  if(font != NULL) display.setFont(font);
  else display.setFont();
  display.setTextSize(s);
  display.setTextWrap(wraptext);
  display.print(text);
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
    if (Batt_Level > 100)  {
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
}

void loop_icons() {
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
}



void display_setup() {

    // Use this initializer if you're using a 1.8" TFT
    //display.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

    // Use this initializer (uncomment) if you're using a 1.44" TFT
    display.initR(INITR_144GREENTAB);   // initialize a ST7735S chip, black tab
    Serial.println("TFT Initialized");

    long deltatime = millis();
    display.fillScreen(BGColor);
    deltatime = millis() - deltatime;

    display.setRotation(TFTRotate);
    /*
    display.setTextColor(MainColor);    // ST7735_RED
    display.setTextSize(0);
    display.println("time: " + String(deltatime));
    display.println("F Rate: " + String(1000/deltatime));
    delay(5000);
    */
}
