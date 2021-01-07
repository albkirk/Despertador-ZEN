//  - - -  TFT  - - -
#define TFTRotate 1

//  - - -  NeoPixels  - - -
#define NEOPixelsPIN  18 //21         // pin on the ESP32 to connected to the NeoPixels
#define NEOPixelsNUM  8               // Number of NeoPixels LEDs


// **** Project code definition here ...
#include <buttons.h>
#include <touch.h>
#include <SDReader.h>
#include <ambient.h>
#include <sounds.h>
#include <images.h>
#include <color.h>
#include <tft.h>
#include <dacplayer.h>
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
    ambient_setup();
    //ambient_get_data();

  // Start TFT device
    tft_setup();

  // Start Player device
    player_setup();

  // Color Managament Service
    color_setup();

  // Start MENU
    menu_setup();

}

void project_loop() {
  // Ambient handing
    //if (TIMER >0) if ((millis() - 3500) % (TIMER * 60000) < 5) ambient_data();      // TIMER bigger than zero on div or dog bites!!

  // Player handling
    player_loop();

  // Color handling
    color_loop();

  // MENU handling
    touch_loop();
    menu_loop();
}
