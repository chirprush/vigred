#include <SDL2/SDL.h>
#include <stdint.h>
#include <vigred/vi_window.h>
#include <vigred/vi_color.h>

vi_color vi_color_from_hex(uint32_t color) {
	vi_color c = {0};
	c.r = color >> 16 & 0xFF;
	c.g = color >>  8 & 0xFF;
	c.b = color >>  0 & 0xFF;
	return c;
}
