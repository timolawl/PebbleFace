#pragma once

#include <pebble.h>

#include "data.h"

#include "window.h"

void comm_init(uint32_t inbox, uint32_t outbox);

void comm_deinit();