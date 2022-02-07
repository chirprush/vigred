#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <vigred/util/rect.h>
#include <vigred/util/color.h>
#include <vigred/event/key.h>
#include <vigred/event/click.h>
#include <vigred/event/scroll.h>
#include <vigred/buffer/anon.h>
#include <vigred/buffer/buffer.h>
#include <vigred/widget/widget.h>
#include <vigred/widget/wbuffer.h>
#include <vigred/widget/split.h>
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
	vi_buffer *left_buffer = vi_anon_buffer_new_buffer("Left");
	vi_buffer *right_buffer = vi_anon_buffer_new_buffer("Right");
	state->ui = vi_split_new_widget(
		NULL,
		vi_wbuffer_new_widget("left", left_buffer),
		vi_wbuffer_new_widget(NULL, right_buffer),
		0.3,
		true
	);
	vi_widget_resize(state->ui, state, (vi_rect) {(vi_vec) {20, 20}, state->win->w - 40, state->win->h - 40});
	state->selected = vi_widget_find_id(state->ui, "left");
	SDL_Event e;
	while (state->win->running) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				state->win->running = 0;
				break;
			case SDL_KEYDOWN: {
				vi_key key = vi_key_from_sdl(e.key.keysym);
				if (state->selected) {
					vi_widget_on_key(state->selected, state, key);
				}
				break;
			}
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEBUTTONDOWN: {
				vi_click click = vi_click_from_sdl(e.button);
				if (vi_rect_contains(state->ui->bounds, click.pos)) {
					vi_widget_on_click(state->ui, state, click);
				} else {
					state->selected = NULL;
				}
				break;
			}
			case SDL_MOUSEWHEEL: {
				vi_scroll scroll = vi_scroll_from_sdl(e.wheel);
				if (state->selected) {
					vi_widget_scroll(state->selected, state, scroll);
				}
				break;
			}
			case SDL_WINDOWEVENT:
				if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
					state->win->w = e.window.data1;
					state->win->h = e.window.data2;
				}
				vi_widget_resize(state->ui, state, (vi_rect) {(vi_vec) {20, 20}, state->win->w - 40, state->win->h - 40});
				break;
			}
		}
		vi_window_draw_clear(state->win, bg);
		vi_widget_render(state->ui, state);
		vi_window_draw_present(state->win);
		SDL_Delay(DELTA_TIME);
	}
	vi_buffer_free(left_buffer);
	vi_buffer_free(right_buffer);
	vi_state_free(state);
	return 0;
}
