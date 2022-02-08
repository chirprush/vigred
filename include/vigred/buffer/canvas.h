#pragma once

#include <stdlib.h>
#include <vigred/util/rect.h>
#include <vigred/util/color.h>
#include <vigred/event/key.h>
#include <vigred/event/click.h>
#include <vigred/buffer/buffer.h>
#include <vigred/widget/view.h>
#include <vigred/window.h>

typedef struct vi_canvas_rect {
	vi_rect rect;
	vi_color color;
} vi_canvas_rect;

typedef struct vi_canvas_buffer {
	const vi_canvas_rect *rects;
	size_t length;
} vi_canvas_buffer;

vi_canvas_buffer *vi_canvas_buffer_new(const vi_canvas_rect *rects, size_t length);
vi_buffer *vi_canvas_buffer_new_buffer(const vi_canvas_rect *rects, size_t length);
void vi_canvas_buffer_free(vi_buffer *buffer);

void vi_canvas_buffer_render(const vi_buffer *buffer, vi_state *state, vi_view *view, vi_buffer_render_opts opts);
void vi_canvas_buffer_on_key(const vi_buffer *buffer, vi_state *state, vi_key key);
void vi_canvas_buffer_on_click(const vi_buffer *buffer, vi_state *state, vi_click click);
