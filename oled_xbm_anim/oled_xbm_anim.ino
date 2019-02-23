/*
 * OLED Animation Example with hackster.io logo
 * 
 */

#include <Wire.h> //I2C
#include <U8g2lib.h>
#include <AsyncDelay.h>
#include "logo.h"

AsyncDelay tick;
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);  // Adafruit ESP8266/32u4/ARM Boards + FeatherWing OLED
//U8G2_SH1107_64X128_F_4W_HW_SPI u8g2(U8G2_R3, /* cs=*/ 14, /* dc=*/ 27, /* reset=*/ 33);
const int FPS = 1000 / 30; //30 FPS
bool animation_direction = false;
int animation_state = 0;

void setup() {
  u8g2.begin();
  tick.start(FPS, AsyncDelay::MILLIS);
}

void loop() {
  if (tick.isExpired()) {
    drawAnimation();
    if (animation_direction) {
      animation_state--;
    } else {
      animation_state++;
    }

    if (animation_state == 5) {
      animation_direction = true;
    }

    if (animation_state == 0) {
      animation_direction = false;
    }
    tick.repeat();
  }
}

void drawAnimation() {
  u8g2.firstPage();
  do {
    switch (animation_state) {
      case 0:
        u8g2.drawXBMP(0, 0, logo_width, logo_height, logo_1);
        break;
      case 1:
        u8g2.drawXBMP(0, 0, logo_width, logo_height, logo_2);
        break;
      case 2:
        u8g2.drawXBMP(0, 0, logo_width, logo_height, logo_3);
        break;
      case 3:
        u8g2.drawXBMP(0, 0, logo_width, logo_height, logo_4);
        break;
      case 4:
        u8g2.drawXBMP(0, 0, logo_width, logo_height, logo_5);
        break;
      case 5:
        u8g2.drawXBMP(0, 0, logo_width, logo_height, logo_6);
        break;
    }
  } while ( u8g2.nextPage() );
}
