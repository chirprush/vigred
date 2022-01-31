#pragma once

#include <SDL2/SDL_ttf.h>
#include <stdint.h>
#include <stdbool.h>
#include <vigred/rect.h>

typedef enum vi_font_style {
	VI_FONT_NORMAL        = 0,
	VI_FONT_BOLD          = 1 << 0,
	VI_FONT_ITALIC        = 1 << 1,
	VI_FONT_UNDERLINE     = 1 << 2,
	VI_FONT_STRIKETHROUGH = 1 << 3
} vi_font_style;

typedef struct vi_font {
	TTF_Font *font;
	const char *font_path;
	uint32_t size;
	uint8_t style;
} vi_font;

vi_font *vi_font_new(const char *font_path, uint32_t size);
void vi_font_free(vi_font *font);

void vi_font_clear_style(vi_font *font);
void vi_font_set_style(vi_font *font, uint8_t style);

vi_vec vi_font_metrics(const vi_font *font, const char *text);

typedef struct vi_font_store {
	vi_font **fonts;
	uint32_t length;
	uint32_t capacity;
} vi_font_store;

vi_font_store *vi_font_store_new(void);
void vi_font_store_free(vi_font_store *store);

vi_font *vi_font_store_ensure_font(vi_font_store *store, const char *font_path, uint32_t size);
