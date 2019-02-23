#include <Wire.h> //I2C
#include <U8g2lib.h>
#include <AsyncDelay.h>
#include "mario_cannon.h"

AsyncDelay tick;
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

const int OLED_WIDTH = 128;
const int OLED_HEIGHT = 32;
const int FPS = 1000 / 30;
const int X = 3;
int pos_x = 0;
int pos_y = 0;

void setup() {
  Serial.begin(9600);
  u8g2.begin();
  tick.start(FPS, AsyncDelay::MILLIS);
}

void loop() {
  if (tick.isExpired()) {
    drawAnimation();
    pos_x = pos_x + X;
    if (pos_x > OLED_WIDTH + cannon_width) {
      pos_x = -cannon_width;
    }
    tick.repeat();
  }
}

void drawAnimation() {
  u8g2.firstPage();
  do {
    u8g2.drawXBMP(pos_x, pos_y, cannon_width, cannon_height, mario_cannon);
  } while ( u8g2.nextPage() );
}
