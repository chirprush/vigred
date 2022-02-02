#pragma once

#include <stdint.h>

typedef struct vi_vec {
	int32_t x, y;
} vi_vec;

typedef struct vi_rect {
	vi_vec pos;
	int32_t w, h;
} vi_rect;
