#pragma once

#include <vigred/rect.h>
#include <vigred/window.h>

struct vi_buffer;

typedef void (*vi_buffer_render_func)(const struct vi_buffer *, vi_window *);
typedef void (*vi_buffer_free_func)(struct vi_buffer *);

typedef struct vi_buffer_vtable {
	vi_buffer_render_func render;
	vi_buffer_free_func free;
} vi_buffer_vtable;

typedef struct vi_buffer {
	const vi_buffer_vtable *vtable;
	void *internal;
} vi_buffer;

vi_buffer *vi_buffer_new(const vi_buffer_vtable *vtable, void *internal);
void vi_buffer_free(vi_buffer *buffer);

// Eventually, we will remove this window and instead let the buffer
// rendered to a vi_view (the vigred equivalent of a vim window).
void vi_buffer_render(const vi_buffer *buffer, vi_window *win);
