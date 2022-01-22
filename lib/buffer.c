#include <stdlib.h>
#include <vigred/rect.h>
#include <vigred/window.h>
#include <vigred/buffer.h>


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

void vi_buffer_render(const vi_buffer *buffer, vi_window *win) {
	buffer->vtable->render(buffer, win);
}
