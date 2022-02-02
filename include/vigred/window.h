#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdint.h>
#include <stdbool.h>
#include <vigred/util/rect.h>
#include <vigred/util/color.h>
#include <vigred/util/font.h>

typedef struct vi_window {
	SDL_Window *win;
	SDL_Renderer *renderer;
	int32_t w;
	int32_t h;
	bool running;
} vi_window;

vi_window *vi_window_new(void);
void vi_window_free(vi_window *win);

// We don't have to pass pointers here because the struct is
// relatively small and it allows for the use of brace initializers
// and vi_color_from_hex which is much more friendly
void vi_window_draw_clear(vi_window *win, vi_color color);
void vi_window_draw_present(vi_window *win);

void vi_window_draw_rect(vi_window *win, vi_color color, vi_rect rect);

// TODO: Maybe in the future we can abstract away the TTF_Font to a
// vi_font type, which would we could also use for a font store
// (vi_font_store). This way, you don't have to create a font and free
// it everytime yourself. In addition, this font could have functions
// for text metrics and such.
void vi_window_draw_text(vi_window *win, vi_color color, vi_vec pos, const vi_font *font, const char *text);
