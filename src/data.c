#include "data.h"

// Cache all data
static GColor s_background, s_tie, s_collar;


static void write_defaults() {
  s_background = GColorWhite;
  s_tie = GColorCyan;
  s_collar = GColorDarkGray;
  data_deinit();
}

void data_init() {
  
  // Nuke previus version settings
  if(!persist_exists(V_1_1)) {
    persist_write_bool(V_1_1, true);
  
  
    persist_delete(BACKGROUND_KEY);
    persist_delete(TIE_KEY);
    persist_delete(COLLAR_KEY);

    write_defaults();
  } else {
    s_background = (GColor){ .argb = persist_read_int(BACKGROUND_KEY) };
    s_tie = (GColor){ .argb = persist_read_int(TIE_KEY) };
    s_collar = (GColor){ .argb = persist_read_int(COLLAR_KEY) };
  }
}

void data_deinit() {
  // Store current values
  persist_write_int(BACKGROUND_KEY, s_background.argb);
  persist_write_int(TIE_KEY, s_tie.argb);
  persist_write_int(COLLAR_KEY, s_collar.argb);
}

GColor data_get_background_color() {
#if defined(PBL_COLOR)
  return s_background;
#else
  return GColorWhite;
#endif
}

GColor data_get_tie_color() {
#if defined(PBL_COLOR)
  return s_tie;
#else
  return GColorCyan;
#endif
}

GColor data_get_collar_color() {
#if defined(PBL_COLOR)
  return s_collar;
#else
  return GColorDarkGray;
#endif
}

void data_set_background_color(GColor color) {
  s_background = color;
}

void data_set_tie_color(GColor color) {
  s_tie = color;
}

void data_set_collar_color(GColor color) {
  s_collar = color;
}


