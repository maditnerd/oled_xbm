#include <Wire.h> //I2C
#include <U8g2lib.h>
#include "mario.h"
#include "mario_tiles.h"

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

const int MARIO_FRAMERATE_WALK = 2;
const int MARIO_FRAMERATE_JUMP = 2;
const int PIPE_X = 112;
const int PIPE_Y = 20;

bool display_mario = false;
bool display_pipe = false;

int mario_x = 0;
int mario_y = 16;
int mario_anim = 0;
int mario_current_framerate = 0;

bool is_jumping = false;
bool jump_up = false;
bool jump_down = false;
bool jump_finish = false;
bool jump_anim = false;

bool walk_part = false;
bool jump_part = false;
bool enter_pipe_part = false;
bool walk_loop_part = false;

void mario() {
  if (display_mario) {
    switch (mario_anim) {
      case 0:
        u8g2.drawXBMP(mario_x, mario_y, mario_w, mario_h, mario_idle);
        break;
      case 1:
        u8g2.drawXBMP(mario_x, mario_y, mario_w, mario_h, mario_walk1);
        break;
      case 2:
        u8g2.drawXBMP(mario_x, mario_y, mario_w, mario_h, mario_walk2);
        break;
      case 3:
        u8g2.drawXBMP(mario_x, mario_y, mario_w, mario_h, mario_jump1);
        break;
      case 4:
        u8g2.drawXBMP(mario_x, mario_y, mario_w, mario_h, mario_jump2);
        break;
    }
  }
}

void pipe() {
  if (display_pipe) {
    u8g2.drawXBMP(PIPE_X, PIPE_Y, mario_w, mario_h, mario_pipe);
  }
}

void text() {
  u8g2.setFont(u8g2_font_unifont_t_latin);
  u8g2.setCursor(0, 14);
  if (walk_loop_part) {
    u8g2.println(MESSAGE_WAIT);
  } else {
    u8g2.println(MESSAGE_END);
  }
}

void draw() {
  u8g2.firstPage();
  do {
    mario();
    pipe();
    text();
  } while ( u8g2.nextPage() );
}

void mario_walk() {
  if (mario_current_framerate == MARIO_FRAMERATE_WALK) {
    mario_anim++;
    mario_current_framerate = 0;
  }
  mario_current_framerate++;

  if (mario_anim == 3) {
    mario_anim = 0;
  }
}

void mario_jump() {

  if (is_jumping) {

    if (mario_current_framerate == MARIO_FRAMERATE_JUMP) {
      mario_anim++;
      mario_current_framerate = 0;
    }
    mario_current_framerate++;

    if (mario_anim == 5) {
      mario_anim = 4;
      is_jumping = false;
    }
  }
}

void start_screen() {
  u8g2.begin();
}

void set_anim_walk() {
  start_screen();
  display_mario = true;
  display_pipe = false;

  mario_x = 0;
  mario_y = 16;
  mario_anim = 0;
  mario_current_framerate = 0;

  is_jumping = false;
  jump_up = false;
  jump_down = false;
  jump_finish = false;

  walk_part = false;
  jump_part = false;
  enter_pipe_part = false;
  walk_loop_part = true;
  jump_anim = false;
}

void set_anim_jump() {
  display_mario = true;
  display_pipe = true;

  mario_x = 0;
  mario_y = 16;
  mario_anim = 0;
  mario_current_framerate = 0;

  is_jumping = false;
  jump_up = false;
  jump_down = false;
  jump_finish = false;

  walk_part = true;
  jump_part = false;
  enter_pipe_part = false;
  walk_loop_part = false;
  jump_anim = true;
}

void mario_anim_loop() {
  draw();

  if (walk_loop_part) {
    mario_x++;
    mario_walk();

    if (mario_x == 128) {
      set_anim_jump();
      //mario_x = 0;
    }
  }

  if (walk_part) {
    if (mario_x <= 96) {
      mario_x = mario_x + 1;
      mario_walk();
    }

    if (mario_x == 91) {
      walk_part = false;
      jump_up = true;
      jump_part = true;
      mario_anim = 3;
    }
  }
  if (jump_part) {
    //Serial.println(mario_anim);
    if (!jump_finish) {
      mario_jump();
      if (jump_up) {
        if (mario_y >= 0) {
          mario_y--;
          mario_x++;
        }
        if (mario_y == 0) {
          jump_down = true;
          jump_up = false;
        }
      }
      if (jump_down) {
        if (mario_y <= 16) {
          mario_y++;
          mario_x++;
        }
        if (mario_y == 4) {
          jump_down = false;
          mario_anim = 0;
          jump_finish = true;
          enter_pipe_part = true;
        }
      }
    }
  }

  if (enter_pipe_part) {
    mario_y++;
    if (mario_y == 64) {
      enter_pipe_part = false;
      jump_anim = false;
    }
  }

}
