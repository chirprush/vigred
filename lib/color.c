#include <SDL2/SDL.h>
#include <stdint.h>
#include <vigred/window.h>
#include <vigred/color.h>

vi_color vi_color_from_hex(uint32_t color) {
	vi_color c = {0};
	c.r = color >> 24 & 0xFF;
	c.g = color >> 16 & 0xFF;
	c.b = color >>  8 & 0xFF;
	c.a = color >>  0 & 0xFF;
	return c;
}
