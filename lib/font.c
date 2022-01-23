#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <stdint.h>
#include <vigred/font.h>

vi_font *vi_font_new(const char *font_path, uint32_t size) {
	vi_font *font = malloc(sizeof(vi_font));
	font->font = TTF_OpenFont(font_path, size);
	font->font_path = font_path;
	font->size = size;
	return font;
}

void vi_font_free(vi_font *font) {
	TTF_CloseFont(font->font);
	free(font);
}

vi_vec vi_font_metrics(const vi_font *font, const char *text) {
	vi_vec metrics = {0};
	TTF_SizeText(font->font, text, &metrics.x, &metrics.y);
	return metrics;
}

vi_font_store *vi_font_store_new(void) {
	vi_font_store *store = malloc(sizeof(vi_font_store));
	store->fonts = NULL;
	store->length = 0;
	store->capacity = 0;
	return store;
}

void vi_font_store_free(vi_font_store *store) {
	for (uint32_t i = 0; i < store->length; ++i) {
		vi_font_free(store->fonts[i]);
	}
	free(store->fonts);
	free(store);
}

const vi_font *vi_font_store_ensure_font(vi_font_store *store, const char *font_path, uint32_t size) {
	for (uint32_t i = 0; i < store->length; ++i) {
		if (strcmp(store->fonts[i]->font_path, font_path) == 0 &&
			store->fonts[i]->size == size) {
			return store->fonts[i];
		}
	}
	if (store->length >= store->capacity) {
		uint32_t new_capacity = store->capacity + 8;
		store->fonts = realloc(store->fonts, new_capacity * sizeof(vi_font *));
	}
	vi_font *font = vi_font_new(font_path, size);
	store->fonts[store->length] = font;
	store->length++;
	return font;
}
