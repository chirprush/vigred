#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <vigred/rect.h>
#include <vigred/color.h>
#include <vigred/key.h>
#include <vigred/click.h>
#include <vigred/scroll.h>
#include <vigred/buffer.h>
#include <vigred/view.h>
#include <vigred/anon_buffer.h>
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
	vi_view *view = vi_view_new((vi_rect) {(vi_vec) {state->win->w / 2- 300, state->win->h / 2 - 300}, 600, 600});
	vi_buffer *buffer = vi_anon_buffer_new_buffer("Hello, World!");
	SDL_Event e;
	while (state->win->running) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				state->win->running = 0;
				break;
			case SDL_KEYDOWN: {
				vi_key key = vi_key_from_sdl(e.key.keysym);
				vi_buffer_on_key(buffer, state, key);
				break;
			}
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEBUTTONDOWN: {
				vi_click click = vi_click_from_sdl(e.button);
				printf("vi_click { button: %d, state: %d, pos: (%d, %d) }\n", click.button, click.state, click.pos.x, click.pos.y);
				break;
			}
			case SDL_MOUSEWHEEL: {
				vi_scroll scroll = vi_scroll_from_sdl(e.wheel);
				printf("vi_scroll { dir: (%d, %d) }\n", scroll.dir.x, scroll.dir.y);
				break;
			}
			case SDL_WINDOWEVENT:
				if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
					state->win->w = e.window.data1;
					state->win->h = e.window.data2;
				}
				break;
			}
		}
		vi_window_draw_clear(state->win, bg);
		vi_buffer_render(buffer, state, view);
		vi_view_render(view, state->win);
		vi_window_draw_present(state->win);
		SDL_Delay(DELTA_TIME);
	}
	vi_buffer_free(buffer);
	vi_view_free(view);
	vi_state_free(state);
	return 0;
}
