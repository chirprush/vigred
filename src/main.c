#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <vigred/color.h>
#include <vigred/buffer.h>
#include <vigred/key.h>
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
			case SDL_WINDOWEVENT:
				if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
					state->win->w = e.window.data1;
					state->win->h = e.window.data2;
				}
				break;
			}
		}
		vi_window_draw_clear(state->win, bg);
		vi_buffer_render(buffer, state);
		vi_window_draw_present(state->win);
		SDL_Delay(DELTA_TIME);
	}
	vi_buffer_free(buffer);
	vi_state_free(state);
	return 0;
}
