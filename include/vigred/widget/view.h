#pragma once

#include <SDL2/SDL.h>
#include <vigred/util/rect.h>
#include <vigred/window.h>

typedef struct vi_view {
	vi_rect bounds;
	SDL_Surface *render_surface;
} vi_view;

vi_view *vi_view_new(vi_rect bounds);
void vi_view_free(vi_view *view);

void vi_view_resize(vi_view *view, vi_rect bounds);

void vi_view_render(vi_view *view, vi_window *win);

void vi_view_draw_clear(vi_view *view, vi_color color);
void vi_view_draw_rect(vi_view *view, vi_color color, vi_rect rect);
void vi_view_draw_text(vi_view *view, vi_color color, vi_vec pos, const vi_font *font, const char *text);
