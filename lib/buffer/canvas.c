#include <stdlib.h>
#include <vigred/util/color.h>
#include <vigred/event/key.h>
#include <vigred/event/click.h>
#include <vigred/buffer/buffer.h>
#include <vigred/widget/view.h>

#include <vigred/buffer/canvas.h>

const vi_buffer_vtable canvas_buffer_vtable = {
	.render = vi_canvas_buffer_render,
	.on_key = vi_canvas_buffer_on_key,
	.on_click = vi_canvas_buffer_on_click,
	.free = vi_canvas_buffer_free
};

vi_canvas_buffer *vi_canvas_buffer_new(const vi_canvas_rect *rects, size_t length) {
	vi_canvas_buffer *canvas_buffer = malloc(sizeof(vi_canvas_buffer));
	canvas_buffer->rects = rects;
	canvas_buffer->length = length;
	return canvas_buffer;
}

vi_buffer *vi_canvas_buffer_new_buffer(const vi_canvas_rect *rects, size_t length) {
	vi_canvas_buffer *canvas_buffer = vi_canvas_buffer_new(rects, length);
	vi_buffer *buffer = vi_buffer_new(&canvas_buffer_vtable, canvas_buffer);
	return buffer;
}

void vi_canvas_buffer_free(vi_buffer *buffer) {
	vi_canvas_buffer *canvas_buffer = buffer->internal;
	free(canvas_buffer);
}

void vi_canvas_buffer_render(const vi_buffer *buffer, vi_state *state, vi_view *view, vi_buffer_render_opts opts) {
	(void)state;
	(void)opts;
	vi_canvas_buffer *canvas_buffer = buffer->internal;
	for (size_t i = 0; i < canvas_buffer->length; ++i) {
		vi_rect bounds = canvas_buffer->rects[i].rect;
		if (bounds.pos.y + bounds.h >= opts.scroll.y) {
			bounds.pos.y -= opts.scroll.y;
			vi_view_draw_rect(view, canvas_buffer->rects[i].color, bounds);
		}
	}
}

void vi_canvas_buffer_on_key(const vi_buffer *buffer, vi_state *state, vi_key key) {
	(void)buffer;
	(void)state;
	(void)key;
}

void vi_canvas_buffer_on_click(const vi_buffer *buffer, vi_state *state, vi_click click) {
	(void)buffer;
	(void)state;
	(void)click;
}
