/* ****************************************************/

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <images.h>

// TFT PINOUT
#define TFT_BACKLIGHT  7  // Display backlight pin (NOT CONFIRMED!!!)
#define TFT_CS        16
#define TFT_RST        9
#define TFT_DC        17
#define TFT_CLK       5   // set these to be whatever pins you like!
#define TFT_MOSI      23  // set these to be whatever pins you like!
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST);
//Adafruit_ST7735 tft = Adafruit_ST7735(16, 17, 23, 5, 9); // CS,A0,SDA,CLK,RESET

uint16_t MainColor=ST7735_WHITE;
uint16_t BGColor=ST7735_BLACK;
uint16_t SetColor=ST7735_YELLOW;
uint16_t EditColor=ST7735_ORANGE;

void testlines(uint16_t color) {
  tft.fillScreen(BGColor);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, 0, x, tft.height()-1, color);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, 0, tft.width()-1, y, color);
  }

  tft.fillScreen(BGColor);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, 0, x, tft.height()-1, color);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, 0, 0, y, color);
  }

  tft.fillScreen(BGColor);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(0, tft.height()-1, x, 0, color);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(0, tft.height()-1, tft.width()-1, y, color);
  }

  tft.fillScreen(BGColor);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, x, 0, color);
  }
  for (int16_t y=0; y < tft.height(); y+=6) {
    tft.drawLine(tft.width()-1, tft.height()-1, 0, y, color);
  }
}

void tft_text(String text, int color=ST7735_WHITE, uint8_t s=1, int x=0, int y=0, bool wraptext=true) {
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(s);
  tft.setTextWrap(wraptext);
  tft.print(text);
}

void tft_pixel(int x=0, int y=0, int color=ST7735_WHITE) {
    tft.drawPixel(tft.width()/2, tft.height()/2, ST7735_GREEN);  // function to be reviewed
}

void testfastlines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(BGColor);
  for (int16_t y=0; y < tft.height(); y+=5) {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x=0; x < tft.width(); x+=5) {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}

void testdrawrects(uint16_t color) {
  tft.fillScreen(BGColor);
  for (int16_t x=0; x < tft.width(); x+=6) {
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2) {
  tft.fillScreen(BGColor);
  for (int16_t x=tft.width()-1; x > 6; x-=6) {
    tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=radius; x < tft.width(); x+=radius*2) {
    for (int16_t y=radius; y < tft.height(); y+=radius*2) {
      tft.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x=0; x < tft.width()+radius; x+=radius*2) {
    for (int16_t y=0; y < tft.height()+radius; y+=radius*2) {
      tft.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles() {
  tft.fillScreen(BGColor);
  int color = 0xF800;
  int t;
  int w = tft.width()/2;
  int x = tft.height()-1;
  int y = 0;
  int z = tft.width();
  for(t = 0 ; t <= 15; t++) {
    tft.drawTriangle(w, y, y, x, z, x, color);
    x-=4;
    y+=4;
    z-=4;
    color+=100;
  }
}

void testroundrects() {
  tft.fillScreen(BGColor);
  int color = 100;
  int i;
  int t;
  for(t = 0 ; t <= 4; t+=1) {
    int x = 0;
    int y = 0;
    int w = tft.width()-2;
    int h = tft.height()-2;
    for(i = 0 ; i <= 16; i+=1) {
      tft.drawRoundRect(x, y, w, h, 5, color);
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
  tft.fillScreen(BGColor);
  tft.fillRoundRect(25, 10, 78, 60, 8, ST7735_WHITE);
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_RED);
  delay(500);
  // pause
  tft.fillRoundRect(25, 90, 78, 60, 8, ST7735_WHITE);
  tft.fillRoundRect(39, 98, 20, 45, 5, ST7735_GREEN);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST7735_GREEN);
  delay(500);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_BLUE);
  delay(50);
  // pause color
  tft.fillRoundRect(39, 98, 20, 45, 5, ST7735_RED);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST7735_RED);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_GREEN);
}

void tft_drawhour(strDateTime strDtTm=DateTime, uint16_t color=MainColor, int x=2, int y=56) {
      String text="";
      if (strDtTm.hour <=9) text = String("0") + String(strDtTm.hour);
      else text = String(strDtTm.hour);
      tft_text(text,        color, 4, x,      y);
}

void tft_drawmin(strDateTime strDtTm=DateTime, uint16_t color=MainColor, int x=2, int y=56) {
      String text="";
      if (strDtTm.minute <=9) text = String("0") + String(strDtTm.minute);
      else text = String(strDtTm.minute);
      tft_text(text,      color, 4, x + 55, y);
}

void tft_drawsec(strDateTime strDtTm=DateTime, uint16_t color=MainColor, int x=2, int y=56) {
      String text="";
      if (strDtTm.second <=9) text = String("0") + String(strDtTm.second);
      else text = String(strDtTm.second);
      tft_text(text,      color, 2, x + 102, y);
}

void tft_drawyear(strDateTime strDtTm=DateTime, uint16_t color=MainColor, int x=7, int y=105) {
      String text="";
      if (strDtTm.year <=9) text = String("0") + String(strDtTm.year);
      else text = String(strDtTm.year);
      tft_text(text,        color, 2, x + 73, y);
}

void tft_drawmonth(strDateTime strDtTm=DateTime, uint16_t color=MainColor, int x=7, int y=105) {
      String text="";
      if (strDtTm.month <=9) text = String("0") + String(strDtTm.month);
      else text = String(strDtTm.month);
      tft_text(text,        color, 2, x + 86, y);
}

void tft_drawday(strDateTime strDtTm=DateTime, uint16_t color=MainColor, int x=7, int y=105) {
      String text="";
      if (strDtTm.day <=9) text = String("0") + String(strDtTm.day);
      else text = String(strDtTm.day);
      tft_text(text,        color, 2, x + 50, y);
}

void tft_drawwday(strDateTime strDtTm=DateTime, uint16_t color=MainColor, int x=7, int y=105) {
      String text="";
      text = WeekDays[strDtTm.wday];
      tft_text(text,        color, 2, x,      y);
}

void tft_drawsound(strDateTime strDtTm=DateTime, uint16_t color=MainColor, int x=7, int y=34) {
      String text="";
      text = sounds[strDtTm.sound];
      tft_text(text,        color, 2, x,      y);
}

void tft_drawbell(strDateTime strDtTm=DateTime, uint16_t color=MainColor, int x=2, int y=56) {
      tft.drawBitmap(x + 104, y, bell, 16, 16, color);
      if (!strDtTm.alarm) {
          tft.drawLine(x + 104, y, x + 104 + 16, y + 16, color);
          tft.drawLine(x + 104, y + 16, x + 104 + 16, y, color);
      };
}



void tft_drawtime(strDateTime strDtTm=DateTime, uint16_t color=MainColor, int x=2, int y=56) {
    tft_drawhour(strDtTm, color, x, y);
    tft_text(String(':'), color, 4, x + 40, y);
    tft_drawmin(strDtTm, color, x, y);
    tft_drawsec(strDtTm, color, x, y);
}

void tft_drawalarm(strDateTime strDtTm=DateTime, uint16_t color=MainColor, int x=2, int y=56) {
    tft_drawhour(strDtTm, color, x, y);
    tft_text(String(':'), color, 4, x + 40, y);
    tft_drawmin(strDtTm, color, x, y);
    tft_drawwday(strDtTm, color, 7, 105);
    tft_drawbell(strDtTm, color, x, y);
    tft_drawsound(strDtTm, color, 7, 34);
}

void tft_drawdate(strDateTime strDtTm=DateTime, uint16_t color=MainColor, int x=7, int y=105) {
    tft_drawwday(strDtTm, color, x, y);
    tft_text(String(','), color, 2, x + 35, y);
    tft_drawday(strDtTm, color, x, y);
    tft_text(String('/'), color, 2, x + 74, y);
    tft_drawmonth(strDtTm, color, x, y);
    //tft_text(String('/'), color, 2, x + 61, y);
    //tft_drawyear(strDtTm, color, x, y);
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
      tft_drawsec(LastDateTime, bgcolor, x, y);
      tft_drawsec(DateTime, color, x, y);
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


void tft_setup() {
    // Use this initializer if you're using a 1.8" TFT
    //tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

    // Use this initializer (uncomment) if you're using a 1.44" TFT
    tft.initR(INITR_144GREENTAB);   // initialize a ST7735S chip, black tab
    Serial.println("TFT Initialized");

    long deltatime = millis();
    tft.fillScreen(ST7735_BLACK);
    deltatime = millis() - deltatime;

    tft.setRotation(rotate);
    /*
    tft.setTextColor(ST7735_RED);
    tft.setTextSize(0);
    tft.println("time: " + String(deltatime));
    tft.println("F Rate: " + String(1000/deltatime));
    delay(5000);
    */
    //tft.drawBitmap(40,0,user_icon, 15, 15, ST7735_WHITE);

}

void tft_updateclock() {
        curDateTime();
        tft_updatetime();
        tft_updatedate();
        LastDateTime = DateTime;
}
