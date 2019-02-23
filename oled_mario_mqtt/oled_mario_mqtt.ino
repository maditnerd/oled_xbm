String MESSAGE_WAIT = "MQTT [...]";
String MESSAGE_END = "MQTT [OK]";
#include <AsyncDelay.h>
#include "mario_anim.h"

AsyncDelay tick;

void setup() {
  Serial.begin(9600);
  tick.start(FPS, AsyncDelay::MILLIS);
}

void loop() {
  if (tick.isExpired()) {
    set_anim_walk();
    while (walk_loop_part) {
      mario_anim_loop();
    }
    set_anim_walk();
    while (walk_loop_part) {
      mario_anim_loop();
    }
    set_anim_jump();
    while (jump_anim) {
      mario_anim_loop();
    }
    tick.repeat();
  }
}
