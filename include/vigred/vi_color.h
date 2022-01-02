#pragma once

#include <stdint.h>

typedef struct vi_color {
	uint8_t r, g, b;
} vi_color;

vi_color vi_color_from_hex(uint32_t color);
