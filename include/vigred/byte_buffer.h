#pragma once

#include <SDL2/SDL_ttf.h>
#include <vigred/window.h>
#include <vigred/buffer.h>

const vi_buffer_vtable byte_buffer_vtable;

typedef struct vi_byte_buffer {
	const char *text;
	TTF_Font *font;
} vi_byte_buffer;

vi_byte_buffer *vi_byte_buffer_new(const char *text);
vi_buffer *vi_byte_buffer_new_buffer(const char *text);
void vi_byte_buffer_free(vi_buffer *buffer);

void vi_byte_buffer_render(const vi_buffer *buffer, vi_window *win);

