#include <pebble.h>
#include "comm.h"

static void inbox_received_handler(DictionaryIterator *iter, void *context) {

#if defined(PBL_COLOR)
  Tuple *bg_tuple = dict_find(iter, BACKGROUND_KEY);
  if(bg_tuple) {
    data_set_background_color(GColorFromHEX(bg_tuple->value->int32));
  }
  
  Tuple *tg_tuple = dict_find(iter, TIE_KEY);
  if(tg_tuple) {
    data_set_tie_color(GColorFromHEX(tg_tuple->value->int32));
  }
  
  Tuple *cg_tuple = dict_find(iter, COLLAR_KEY);
  if(cg_tuple) {
    data_set_collar_color(GColorFromHEX(cg_tuple->value->int32));
  }  
#endif

  reload_config();
}

void comm_init(uint32_t inbox, uint32_t outbox) {
  app_message_register_inbox_received(inbox_received_handler);
  app_message_open(inbox, outbox);
}

void comm_deinit() { }


