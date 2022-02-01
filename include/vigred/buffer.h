#pragma once

#include <vigred/rect.h>
#include <vigred/event/key.h>
#include <vigred/view.h>
#include <vigred/state.h>

struct vi_buffer;

typedef void (*vi_buffer_render_func)(const struct vi_buffer *, vi_state *, vi_view *);
typedef void (*vi_buffer_on_key_func)(const struct vi_buffer *, vi_state *, vi_key);
typedef void (*vi_buffer_free_func)(struct vi_buffer *);

typedef struct vi_buffer_vtable {
	vi_buffer_render_func render;
	vi_buffer_on_key_func on_key;
	vi_buffer_free_func free;
} vi_buffer_vtable;

typedef struct vi_buffer {
	const vi_buffer_vtable *vtable;
	void *internal;
} vi_buffer;

vi_buffer *vi_buffer_new(const vi_buffer_vtable *vtable, void *internal);
void vi_buffer_free(vi_buffer *buffer);

void vi_buffer_render(const vi_buffer *buffer, vi_state *state, vi_view *view);
void vi_buffer_on_key(const vi_buffer *buffer, vi_state *state, vi_key key);
