#ifndef _VIGRED_WINDOW_DRAW_H
#define _VIGRED_WINDOW_DRAW_H

#include "vigred_window.h"

typedef struct vi_draw_color {
	int r, g, b;
} vi_draw_color;

vi_draw_color vi_draw_color_from_hex(int color);

void vi_window_draw_clear(vi_window *win, const vi_draw_color *color);
void vi_window_draw_present(vi_window *win);

#endif // _VIGRED_WINDOW_DRAW_H
