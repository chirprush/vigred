#pragma once

#include <SDL2/SDL_ttf.h>
#include <stdint.h>
#include <vigred/rect.h>

typedef struct vi_font {
	TTF_Font *font;
	const char *font_path;
	uint32_t size;
} vi_font;

vi_font *vi_font_new(const char *font_path, uint32_t size);
void vi_font_free(vi_font *font);

vi_vec vi_font_metrics(const vi_font *font, const char *text);

typedef struct vi_font_store {
	vi_font **fonts;
	uint32_t length;
	uint32_t capacity;
} vi_font_store;

vi_font_store *vi_font_store_new(void);
void vi_font_store_free(vi_font_store *store);

const vi_font *vi_font_store_ensure_font(vi_font_store *store, const char *font_path, uint32_t size);
