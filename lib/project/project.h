//  - - -  Display  - - -
#define TFTRotate 1
#define EPaperRotate 3

//  - - -  NeoPixels  - - -
#define NEOPixelsPIN  18 //21         // pin on the ESP32 to connected to the NeoPixels
#define NEOPixelsNUM  8               // Number of NeoPixels LEDs

//bool Alarm_State = false;                   // Defined on config structure Alarm state (true -> Ring / False -> Not Ring)
bool Last_Alarm_State = false;                // Last Alarm state


// **** Project code definition here ...
#include <buttons.h>
#include <touch.h>
#include <SDReader.h>
#include <ambient.h>
#include <sounds.h>
#include <images.h>
//#include <color.h>

#include <dacplayer.h>
#ifdef TFT
    #include <tft.h>
#endif
#ifdef EPAPER
    #include <epaper.h>
#endif

#include <menu.h>



// **** Project code functions here ...
void project_hw() {
 // Output GPIOs


 // Input GPIOs

}


void project_setup() {
  // Start Push Buttons call precedures
    buttons_setup();
    touch_setup();

  // Start SD Card reader
    SDReader_setup();

  // Start Ambient devices
    //ambient_setup();
    //ambient_get_data();

  // Start TFT device
    display_setup();

  // Start Player device
    player_setup();

  // Color Managament Service
    //color_setup();

  // Start MENU
    menu_setup();
    //display_drawtime();
    //display_powerOff();

}

void project_loop() {
  // Ambient handing
    //if (TIMER >0) if ((millis() - 3500) % (TIMER * 60000) < 5) ambient_data();      // TIMER bigger than zero on div or dog bites!!

  // Player handling
    player_loop();

  // Color handling
    //color_loop();

  // MENU handling
    touch_loop();
    menu_loop();
}
