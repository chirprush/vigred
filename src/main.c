#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vigred/buffer.h>
#include <vigred/byte_buffer.h>
#include <vigred/window.h>
#include <vigred/color.h>

#define DELTA_TIME (1000 / 144)

int main(int argc, char *argv[]) {
	(void)argc;
	(void)argv;
	vi_window *win = vi_window_new();
	if (!win) {
		return -1;
	}
	vi_color bg = vi_color_from_hex(0x282c34ff);
	// vi_color fg = vi_color_from_hex(0xffffffff);
	vi_buffer *buffer = vi_byte_buffer_new_buffer("Hello, World!");
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
		vi_window_draw_clear(win, bg);
		vi_buffer_render(buffer, win);
		vi_window_draw_present(win);
		SDL_Delay(DELTA_TIME);
	}
	vi_buffer_free(buffer);
	vi_window_free(win);
	return 0;
}
