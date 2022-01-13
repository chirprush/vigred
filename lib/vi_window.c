#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <vigred/vi_window.h>
#include <vigred/vi_rect.h>
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
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_ALLOW_HIGHDPI
	);
	if (!win->win) {
		fprintf(stderr, "SDL_Error: %s\n", SDL_GetError());
		free(win);
		return NULL;
	}
	win->renderer = SDL_CreateRenderer(win->win, -1, SDL_RENDERER_ACCELERATED);
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

void vi_window_draw_clear(vi_window *win, vi_color color) {
	SDL_SetRenderDrawColor(win->renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(win->renderer);
}

void vi_window_draw_present(vi_window *win) {
	SDL_RenderPresent(win->renderer);
}

void vi_window_draw_rect(vi_window *win, vi_color color, vi_rect rect) {
	SDL_Rect sdl_rect = {rect.pos.x, rect.pos.y, rect.w, rect.h};
	SDL_SetRenderDrawColor(win->renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(win->renderer, &sdl_rect);
}

void vi_window_draw_text(vi_window *win, vi_color color, vi_vec pos, TTF_Font *font, const char *text) {
	SDL_Color fg = {color.r, color.g, color.b, color.a};
	SDL_Surface *surface = TTF_RenderText_Blended(font, text, fg);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(win->renderer, surface);
	SDL_Rect dest;
	dest.x = pos.x;
	dest.y = pos.y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(win->renderer, texture, NULL, &dest);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}
