#include <SDL2/SDL.h>
#include "vigred_window.h"
#include "vigred_color.h"

// 60 "fps"
#define DELTA_TIME (1000 / 60)

int main(int argc, char *argv[]) {
	vi_window *win = vi_window_new();
	if (!win) {
		return -1;
	}
	vi_color bg = vi_color_from_hex(0x282c34);
	SDL_Event e;
	while (win->running) {
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_QUIT:
				win->running = 0;
				break;
			case SDL_WINDOWEVENT:
				if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
					win->w = e.window.data1;
					win->h = e.window.data2;
				}
				break;
			}
		}
		vi_window_draw_clear(win, &bg);
		vi_window_draw_present(win);
		SDL_Delay(DELTA_TIME);
	}
	vi_window_free(win);
	return 0;
}
