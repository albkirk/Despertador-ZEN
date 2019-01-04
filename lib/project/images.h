#ifndef BITMAPS_H
#define BITMAPS_H

//Bell icon size: 16W*16H
const unsigned char bell [] PROGMEM = {
0x01, 0x80, 0x03, 0xc0, 0x0f, 0xf0, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x3f, 0xfc, 0x3f, 0xfc,
0x3f, 0xfc, 0x3f, 0xfc, 0x3f, 0xfc, 0x7f, 0xfe, 0x7f, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0x3f, 0xfc,
};

//wifi icon size: 20W*15H px
const unsigned char wifi_icon [] PROGMEM = {
0x01, 0x68, 0x00,
0x07, 0xfe, 0x00,
0x1f, 0xff, 0x80,
0x7f, 0x0f, 0xe0,
0x78, 0x01, 0xe0,
0x70, 0x00, 0xe0,
0x00, 0xf0, 0x00,
0x03, 0xfc, 0x00,
0x07, 0xfe, 0x00,
0x07, 0x0e, 0x00,
0x02, 0x00, 0x00,
0x00, 0x00, 0x00,
0x00, 0x60, 0x00,
0x00, 0x70, 0x00,
0x00, 0x60, 0x00
};

//battery icon size: 20W*15H px
const unsigned char battery_icon [] PROGMEM = {
0x00, 0x00, 0x00,
0x00, 0x00, 0x00,
0x00, 0x00, 0x00,
0xff, 0xff, 0x80,
0xff, 0xc1, 0x80,
0xff, 0xc1, 0xe0,
0xff, 0xc1, 0xe0,
0xff, 0xc1, 0xe0,
0xff, 0xc1, 0xe0,
0xff, 0xc1, 0xe0,
0xff, 0xc1, 0x80,
0xff, 0xff, 0x80,
0x00, 0x00, 0x00,
0x00, 0x00, 0x00,
0x00, 0x00, 0x00
};

//user_icon Size: 15W*15H px
const unsigned char user_icon [] PROGMEM = {
0x03, 0x80,
0x0f, 0xe0,
0x0f, 0xe0,
0x1f, 0xf0,
0x1f, 0xf0,
0x1f, 0xf0,
0x0f, 0xe0,
0x0f, 0xe0,
0x03, 0x80,
0x38, 0x38,
0x7f, 0xfc,
0x7f, 0xfc,
0xff, 0xfe,
0xff, 0xfe,
0xff, 0xfe
};

#endif
