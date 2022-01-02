#pragma once

#include <SDL2/SDL.h>
#include <stdint.h>
#include "vi_color.h"

typedef struct vi_window {
	SDL_Window *win;
	SDL_Renderer *renderer;
	int32_t w;
	int32_t h;
	uint8_t running;
} vi_window;

vi_window *vi_window_new(void);
void vi_window_free(vi_window *win);

void vi_window_draw_clear(vi_window *win, const vi_color *color);
void vi_window_draw_present(vi_window *win);
