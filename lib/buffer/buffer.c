#include <stdlib.h>
#include <vigred/util/rect.h>
#include <vigred/event/key.h>
#include <vigred/event/click.h>
#include <vigred/widget/view.h>
#include <vigred/window.h>

#include <vigred/buffer/buffer.h>

vi_buffer *vi_buffer_new(const vi_buffer_vtable *vtable, void *internal) {
	vi_buffer *buffer = malloc(sizeof(vi_buffer));
	buffer->vtable = vtable;
	buffer->internal = internal;
	return buffer;
}

void vi_buffer_free(vi_buffer *buffer) {
	buffer->vtable->free(buffer);
	free(buffer);
}

void vi_buffer_render(const vi_buffer *buffer, vi_state *state, vi_view *view, vi_buffer_render_opts opts) {
	buffer->vtable->render(buffer, state, view, opts);
}

void vi_buffer_on_key(const vi_buffer *buffer, vi_state *state, vi_key key) {
	buffer->vtable->on_key(buffer, state, key);
}

void vi_buffer_on_click(const vi_buffer *buffer, vi_state *state, vi_click click) {
	buffer->vtable->on_click(buffer, state, click);
}
