#pragma once

#include <vigred/util/rect.h>
#include <vigred/event/key.h>
#include <vigred/event/click.h>
#include <vigred/buffer/buffer.h>
#include <vigred/widget/view.h>
#include <vigred/window.h>

typedef struct vi_anon_buffer {
	const char *text;
	vi_vec pos;
} vi_anon_buffer;

vi_anon_buffer *vi_anon_buffer_new(const char *text);
vi_buffer *vi_anon_buffer_new_buffer(const char *text);
void vi_anon_buffer_free(vi_buffer *buffer);

void vi_anon_buffer_render(const vi_buffer *buffer, vi_state *state, vi_view *view, vi_buffer_render_opts opts);
void vi_anon_buffer_on_key(const vi_buffer *buffer, vi_state *state, vi_key key);
void vi_anon_buffer_on_click(const vi_buffer *buffer, vi_state *state, vi_click click);
