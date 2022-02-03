#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <vigred/util/rect.h>
#include <vigred/util/color.h>
#include <vigred/event/key.h>
#include <vigred/event/click.h>
#include <vigred/event/scroll.h>
#include <vigred/buffer/anon.h>
#include <vigred/buffer/buffer.h>
#include <vigred/widget/widget.h>
#include <vigred/widget/wbuffer.h>
#include <vigred/window.h>
#include <vigred/state.h>

#define DELTA_TIME (1000 / 144)

int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;
	vi_state *state = vi_state_new();
	if (!state) {
		return -1;
	}
	vi_color bg = vi_color_from_hex(0x282c34ff);
	vi_buffer *buffer = vi_anon_buffer_new_buffer("Hello, World!");
	vi_widget *widget = vi_wbuffer_new_widget(buffer);
	vi_widget_resize(widget, state, (vi_rect) {(vi_vec) {20, 20}, state->win->w - 40, state->win->h - 40});
	SDL_Event e;
	while (state->win->running) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				state->win->running = 0;
				break;
			case SDL_KEYDOWN: {
				vi_key key = vi_key_from_sdl(e.key.keysym);
				vi_widget_on_key(widget, state, key);
				break;
			}
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEBUTTONDOWN: {
				vi_click click = vi_click_from_sdl(e.button);
				vi_widget_on_click(widget, state, click);
				break;
			}
			case SDL_MOUSEWHEEL: {
				vi_scroll scroll = vi_scroll_from_sdl(e.wheel);
				vi_widget_scroll(widget, state, scroll);
				break;
			}
			case SDL_WINDOWEVENT:
				if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
					state->win->w = e.window.data1;
					state->win->h = e.window.data2;
				}
				vi_widget_resize(widget, state, (vi_rect) {(vi_vec) {20, 20}, state->win->w - 40, state->win->h - 40});
				break;
			}
		}
		vi_window_draw_clear(state->win, bg);
		vi_widget_render(widget, state);
		vi_window_draw_present(state->win);
		SDL_Delay(DELTA_TIME);
	}
	vi_buffer_free(buffer);
	vi_widget_free(widget);
	vi_state_free(state);
	return 0;
}
