/*
 * OLED Hackter.io Logo Example
 * 
 */

#include <Wire.h> //I2C
#include <U8g2lib.h>
#include "logo.h"

//I2C SSD1306 128x32 (search U8g2 examples for other display)
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void setup() {
  u8g2.begin(); //Start Screen
  drawLogo();
}

void loop() {
}

void drawLogo() {

  //u8g2 can be a little weird to use at first
  //But (as I understand it) this allows you to do other task while it draws your text/images
  u8g2.firstPage();
  do {
    u8g2.drawXBMP(0, 0, logo_width, logo_height, logo); //X, Y, Size_X, Size_Y, data
  } while ( u8g2.nextPage() );
}
