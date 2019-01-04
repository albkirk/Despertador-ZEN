//  - - - libraries
#include <math.h>

//  - - -  Constants
// BEEP PIN
#define SPEAKER_PIN 25
#ifndef pi
#define pi 3.1415926
#endif


//  - - -  Variables  - - -
byte last_Vol=8;
byte min_ampl=0;        // Max is 8 bits - 1 Byte
byte max_ampl=255;      // Max is 8 bits - 1 Byte
bool speaker_on=false;

//  - - -  Functions  - - -
void player_mute() {
    digitalWrite(SPEAKER_PIN, 127);
}

void player_fadeout(byte amplitude = 127, int sample_rate = 22500) {
    unsigned int delay_interval = ((unsigned long)1000000/sample_rate);
    if (amplitude > 127) {
        for(byte fadeout=amplitude; fadeout>=127; fadeout--) {
            dacWrite(SPEAKER_PIN, fadeout);
            delayMicroseconds(delay_interval);
        }
    }
    else {
        for(byte fadeout=amplitude; fadeout<=127; fadeout++) {
            dacWrite(SPEAKER_PIN, fadeout);
            delayMicroseconds(delay_interval);
        }

    }
}

void player_tone(float freq, float tempo, byte ampl=config.Volume, byte bpm=120, int spl_rate = 22500) {
    ampl = ampl/100.0*(max_ampl - min_ampl)/2;     // To convert volume [0-100%] to amplitude [0-128]
    unsigned int delay_intv = ((unsigned long)1000000/spl_rate);
    if (ampl > 128) ampl = 128;
    if (ampl < 0) ampl = 0;
    for (size_t t = 0; t < (tempo * 60 / bpm * spl_rate); t++) {
    //for (size_t t = 0; t < 10; t++) {
        dacWrite(SPEAKER_PIN, ((ampl * sin(2*pi*freq*t*delay_intv*0.000001))+127));
        //Serial.print(" " + String((ampl * sin(2*pi*freq*t*delay_intv*0.000001))+127));
        delayMicroseconds(delay_intv);
    }
    player_fadeout((ampl*sin(2*pi*freq*tempo*60/bpm*spl_rate*delay_intv*0.000001))+127, spl_rate);
}

void player_beep(int ntimes = 2) {
    for (size_t i = 0; i < ntimes; i++) {
        player_tone(A6, 1.0/8);
        player_tone(0, 1.0/4);
        //player_tone(0, 120);
    }
}

void player_music(const uint8_t* music_data, int sample_rate=22500) {
    unsigned long length = strlen((char*)music_data);
    unsigned int delay_interval = ((unsigned long)1000000/sample_rate);
    if(config.Volume != 0) {
        for(int i=0; i<length; i++) {
            dacWrite(SPEAKER_PIN, (byte)music_data[i]/config.Volume/100.0);
            delayMicroseconds(delay_interval);
        }

        for(int fadeout= (byte)music_data[length-1]/config.Volume/100.0; fadeout>=0; fadeout--) {
            dacWrite(SPEAKER_PIN, fadeout);
            delayMicroseconds(delay_interval);
        }
    }
}

void player_setup() {
    player_beep(3);
    //player_music(startup_sound, 22500);

}


void player_loop() {
    /*if (last_Volume != config.Volume) {
        myDFPlayer.Volume(config.Volume);  //Set volume value [0~100%].
    }*/
    /*
    if(A_STATUS == true) player_tone(C4, 1);
    if(B_STATUS == true) player_tone(D4, 1);
    if(C_STATUS == true) player_tone(E4, 1);
    */
}