#include <U8g2lib.h>
#include "logo.h"

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

//I2C SSD1306 128x32 (search U8g2 examples for other display)
//U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

//SPI SSD1306 128x64
U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 9, /* dc=*/ 10, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  u8g2.begin(); //Start Screen
  drawLogo();
}

void loop() {
  drawLogo();
}

void drawLogo() {

  //u8g2 can be a little weird to use at first
  //But (as I understand it) this allows you to do other task while it draws your text/images
  u8g2.firstPage();
  do {
    u8g2.drawXBMP(0, 0, arduino_width, arduino_height, arduino); //arduino
    //u8g2.drawXBMP(0, 16, hackster_width, hackster_height, hackster); //hackster
    //u8g2.drawXBMP(0, 0, heliox_width, heliox_height, heliox); //heliox
    //u8g2.drawXBMP(0, 0, lagrottedubarbu_width, lagrottedubarbu_height, lagrottedubarbu); //lagrottedubarbu
    //u8g2.drawXBMP(32, 0, mrbidouille_width, mrbidouille_height, mrbidouille); //mrbidouille
    //u8g2.drawXBMP(40, 0, poulains_width, poulains_height, poulains); //poulains
    //u8g2.drawXBMP(64, 32, youtube_width, youtube_height, youtube); //youtube
  } while ( u8g2.nextPage() );
}
