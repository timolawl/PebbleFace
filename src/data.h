#pragma once

#include <pebble.h>

typedef enum {

  BACKGROUND_KEY = 0,
  COLLAR_KEY,
  TIE_KEY
} DataKey;


typedef enum {
  V_1_0 = 100,    // When settings need nuking
  V_1_1 = 101
} VersionKeys;


void data_init();
void data_deinit();

GColor data_get_background_color();
GColor data_get_tie_color();
GColor data_get_collar_color();

void data_set_background_color(GColor color);
void data_set_tie_color(GColor color);
void data_set_collar_color(GColor color);
