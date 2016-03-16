#include <pebble.h>

#include "data.h"
#include "comm.h"
#include "window.h"

static Window *s_main_window;
static TextLayer *s_time_layer, *s_date_layer;  // for the time, date


//static Layer *s_canvas_layer;  // for the circle
static Layer *s_path_layer;  // for paths

// 144 x 168
// 180 x 180

//static BitmapLayer *s_background_layer;
//static GBitmap *s_background_bitmap;

static GFont s_time_font, s_date_font;

// GPath describes the shape
static GPath *s_path;  // tie triangle
static GPath *s_path2;  //left piece
static GPath *s_path3;  //right piece
static GPath *s_path4;  //tie piece

static GPathInfo PATH_INFO = {
  .num_points = 3,
  .points = (GPoint[]) { {90, 90}, {70, 70}, {110, 70} }
};

static GPathInfo PATH_INFO2 = {
  .num_points = 4,
  .points = (GPoint[]) { {90, 90}, {50, 90}, {30, 70}, {70, 70} }
};

static GPathInfo PATH_INFO3 = {
  .num_points = 4,
  .points = (GPoint[]) { {90, 90}, {130, 90}, {150, 70}, {110, 70} }
};

static GPathInfo PATH_INFO4 = {
  .num_points = 4,
  .points = (GPoint[]) { {90, 155}, {75, 135}, {90, 90}, {105, 135} }
};


/****************************************************/

static void update_time() {
  // Get a tm structure
  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);

  // Write the current hours and minutes into a buffer
  static char s_buffer[8];
  strftime(s_buffer, sizeof(s_buffer), clock_is_24h_style() ?
                                          "%H:%M" : "%I:%M", tick_time);

  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer, s_buffer+(('0' == s_buffer[0]?1:0)));
  
  
  // Copy date into buffer from tm structure
  static char date_buffer[16];
  strftime(date_buffer, sizeof(date_buffer), "%b        -%d-", tick_time);
  
  // Show the date
  text_layer_set_text(s_date_layer, date_buffer);

  
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}


/*
static void canvas_update_proc(Layer *this_layer, GContext *ctx) {
  GRect bounds = layer_get_bounds(this_layer);

  // Get the center of the screen (non full-screen)
  GPoint center = GPoint(bounds.size.w / 2, (bounds.size.h / 2));

  // Draw the 'loop' of the 'P'
  graphics_context_set_fill_color(ctx, GColorCyan);
  graphics_fill_circle(ctx, center, 90);
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_circle(ctx, center, 85);

  // Draw the 'stalk'
 // graphics_context_set_fill_color(ctx, GColorBlack);
 // graphics_fill_rect(ctx, GRect(32, 40, 5, 100), 0, GCornerNone);
  
}

*/


static void gpath_update_proc(Layer *layer, GContext *ctx) {
  // Set the color using RGB values
  
  /***************stroke (color/width) currently does not work with paths **********/ 
 
  graphics_context_set_fill_color(ctx, data_get_tie_color());
  // Draw the filled shape in above color
  gpath_draw_filled(ctx, s_path);
  gpath_draw_filled(ctx, s_path4);
  
  graphics_context_set_fill_color(ctx, data_get_collar_color());
  gpath_draw_filled(ctx, s_path2);
  gpath_draw_filled(ctx, s_path3);
    
 
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_context_set_stroke_width(ctx, 5);
  
  gpath_draw_outline(ctx, s_path);
  gpath_draw_outline(ctx, s_path2);
  gpath_draw_outline(ctx, s_path3);
  gpath_draw_outline(ctx, s_path4);
  
}


/****************************************************/


void reload_config() {  
  // Colors
  window_set_background_color(s_main_window, data_get_background_color());
  layer_set_update_proc(s_path_layer, gpath_update_proc);
  
  layer_mark_dirty(s_path_layer);

}


/****************************************************/


static void main_window_load(Window *window) {
  // Get information about the Window
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);

  // Create Canvas Layer
//  s_canvas_layer = layer_create(GRect(0, 0, window_bounds.size.w, window_bounds.size.h));
 // layer_add_child(window_layer, s_canvas_layer);

  // Set the update_proc
//  layer_set_update_proc(s_canvas_layer, canvas_update_proc);
  
  
  // Create GPath object
  s_path = gpath_create(&PATH_INFO);
  s_path2 = gpath_create(&PATH_INFO2);
  s_path3 = gpath_create(&PATH_INFO3);
  s_path4 = gpath_create(&PATH_INFO4);
  
  gpath_move_to(s_path, GPoint(0, 10));
  gpath_move_to(s_path2, GPoint(0, 10));
  gpath_move_to(s_path3, GPoint(0, 10));
  gpath_move_to(s_path4, GPoint(0, 10));

  // Create Layer that the path will be drawn on
  s_path_layer = layer_create(window_bounds);
  layer_set_update_proc(s_path_layer, gpath_update_proc);
  layer_add_child(window_layer, s_path_layer);
  
  
  
  // Create GBitmap
 // s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BACKGROUND);

  // Create BitmapLayer to display the GBitmap
 // s_background_layer = bitmap_layer_create(window_bounds);

  // Set the bitmap onto the layer and add to the window
 // bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
 // layer_add_child(window_layer, bitmap_layer_get_layer(s_background_layer));

  
  
  // Create date TextLayer
  s_date_layer = text_layer_create(GRect(0, 110, 180, 40));
  text_layer_set_text_color(s_date_layer, GColorBlack);
  text_layer_set_background_color(s_date_layer, GColorClear);
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentCenter);
  
  s_date_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ISTOK_WEB_16));

  text_layer_set_font(s_date_layer, s_date_font);

  
  // Add to Window
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_date_layer));
  
  
  
  // Create the time TextLayer with specific bounds
  s_time_layer = text_layer_create(GRect(0, PBL_IF_ROUND_ELSE(25, 52), window_bounds.size.w, 50));
 //     GRect(0, PBL_IF_ROUND_ELSE(58, 52), window_bounds.size.w, 50));

  // Improve the layout to be more like a watchface
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);
  //********************Removed this************************//
//  text_layer_set_text(s_time_layer, "00:00");
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

  // Create GFont
  s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_MONTSERRAT_40));

  // Apply to TextLayer
  text_layer_set_font(s_time_layer, s_time_font);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
}

/****************************************************/

static void main_window_unload(Window *window) {
  
  // destroy date textlayer
  text_layer_destroy(s_date_layer);
  
  // Destroy time TextLayer
  text_layer_destroy(s_time_layer);
  
  
  // Unload date GFont
  fonts_unload_custom_font(s_date_font);
  
  // Unload time GFont
  fonts_unload_custom_font(s_time_font);

  // Destroy GBitmap
 // gbitmap_destroy(s_background_bitmap);

  // Destroy BitmapLayer
//  bitmap_layer_destroy(s_background_layer);
  
  // Destroy layer and path
  layer_destroy(s_path_layer);
  gpath_destroy(s_path);
  gpath_destroy(s_path2);
  gpath_destroy(s_path3);
  gpath_destroy(s_path4);
  
  // Destroy Canvas Layer
//  layer_destroy(s_canvas_layer);
  
}



void main_window_push() {
   // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set the background color
  window_set_background_color(s_main_window, GColorWhite);

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);

  // Make sure the time is displayed from the start
  update_time();

  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);

}

