#ifndef _VIGRED_WINDOW_H
#define _VIGRED_WINDOW_H

#include <SDL2/SDL.h>
#include "vigred_color.h"

typedef struct vi_window {
	SDL_Window *win;
	SDL_Renderer *renderer;
	int w;
	int h;
	int running;
} vi_window;

vi_window *vi_window_new(void);
void vi_window_free(vi_window *win);

void vi_window_draw_clear(vi_window *win, const vi_color *color);
void vi_window_draw_present(vi_window *win);

#endif // _VIGRED_WINDOW_H
