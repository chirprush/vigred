#include <SDL2/SDL.h>
#include "vigred_window.h"
#include "vigred_window_draw.h"

vi_draw_color vi_draw_color_from_hex(int color) {
	vi_draw_color c = {0};
	c.r = color >> 16 & 0xFF;
	c.g = color >>  8 & 0xFF;
	c.b = color >>  0 & 0xFF;
	return c;
}

void vi_window_draw_clear(vi_window *win, const vi_draw_color *color) {
	SDL_SetRenderDrawColor(win->renderer, color->r, color->g, color->b, 255);
	SDL_RenderClear(win->renderer);
}

void vi_window_draw_present(vi_window *win) {
	SDL_RenderPresent(win->renderer);
}
