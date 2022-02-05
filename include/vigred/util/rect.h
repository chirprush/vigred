#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef struct vi_vec {
	int32_t x, y;
} vi_vec;

vi_vec vi_vec_sub(vi_vec pos, vi_vec offset);

typedef struct vi_rect {
	vi_vec pos;
	int32_t w, h;
} vi_rect;

bool vi_rect_contains(vi_rect rect, vi_vec pos);
