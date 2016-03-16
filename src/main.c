#include <pebble.h>

#include "data.h"
#include "comm.h"
#include "window.h"


/****************************************************/

static Window *s_main_window;

static void init() {
  data_init();
  const uint32_t buffer_size = 256;
  comm_init(buffer_size, buffer_size);

  main_window_push();
}

static void deinit() {
  // Destroy Window
  data_deinit();
  comm_deinit();
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}