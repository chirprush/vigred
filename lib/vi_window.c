#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <vigred/vi_window.h>
#include <vigred/vi_color.h>

vi_window *vi_window_new(void) {
	vi_window *win = malloc(sizeof(vi_window));
	int init = SDL_Init(SDL_INIT_VIDEO);
	if (init < 0) {
		fprintf(stderr, "SDL_Error: %s\n", SDL_GetError());
		free(win);
		return NULL;
	}
	int ttf_init = TTF_Init();
	if (ttf_init < 0) {
		fprintf(stderr, "TTF_Error: %s\n", TTF_GetError());
		free(win);
		return NULL;
	}
	// Get screen size
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);
	int32_t w = (int32_t)(dm.w * 0.8f);
	int32_t h = (int32_t)(dm.h * 0.8f);
	// Create objects
	win->win = SDL_CreateWindow(
		"Vigred",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		w, h,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED
	);
	if (!win->win) {
		fprintf(stderr, "SDL_Error: %s\n", SDL_GetError());
		free(win);
		return NULL;
	}
	win->renderer = SDL_CreateRenderer(win->win, -1, 0);
	if (!win->renderer) {
		fprintf(stderr, "SDL_Error: %s\n", SDL_GetError());
		SDL_DestroyWindow(win->win);
		free(win);
		return NULL;
	}
	// These get set after the resize event is received
	win->w = w;
	win->h = h;
	win->running = 1;
	return win;
}

void vi_window_free(vi_window *win) {
	// Assumes that `win` is using allocated memory from vi_window_new()
	// NOTE: This function should only be called ONCE at the end of the program
	SDL_DestroyWindow(win->win);
	SDL_DestroyRenderer(win->renderer);
	free(win);
	TTF_Quit();
	SDL_Quit();
}

void vi_window_draw_clear(vi_window *win, const vi_color *color) {
	SDL_SetRenderDrawColor(win->renderer, color->r, color->g, color->b, 255);
	SDL_RenderClear(win->renderer);
}

void vi_window_draw_present(vi_window *win) {
	SDL_RenderPresent(win->renderer);
}
