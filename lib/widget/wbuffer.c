#include <stdio.h>
#include <stdlib.h>
#include <vigred/util/rect.h>
#include <vigred/event/key.h>
#include <vigred/event/click.h>
#include <vigred/event/scroll.h>
#include <vigred/buffer/buffer.h>
#include <vigred/widget/view.h>
#include <vigred/widget/widget.h>
#include <vigred/state.h>

#include <vigred/widget/wbuffer.h>

const vi_widget_vtable wbuffer_vtable = {
	.resize = vi_wbuffer_resize,
	.render = vi_wbuffer_render,
	.on_key = vi_wbuffer_on_key,
	.on_click = vi_wbuffer_on_click,
	.scroll = vi_wbuffer_scroll,
	.free = vi_wbuffer_free,
};

vi_wbuffer *vi_wbuffer_new(vi_buffer *buffer) {
	// TODO: Add widget resizing
	// Ideally we should just be able to make a tree of nested widgets
	// and then call resize on it.
	vi_view *view = vi_view_new((vi_rect) {(vi_vec) {0, 0}, 300, 300});
	vi_wbuffer *wbuffer = malloc(sizeof(vi_wbuffer));
	wbuffer->view = view;
	wbuffer->buffer = buffer;
	return wbuffer;
}

vi_widget *vi_wbuffer_new_widget(vi_buffer *buffer) {
	vi_wbuffer *wbuffer = vi_wbuffer_new(buffer);
	vi_widget *widget = vi_widget_new(&wbuffer_vtable, wbuffer);
	return widget;
}

void vi_wbuffer_free(vi_widget *widget) {
	vi_wbuffer *wbuffer = widget->internal;
	vi_view_free(wbuffer->view);
	free(wbuffer);
}

void vi_wbuffer_resize(const vi_widget *widget, vi_state *state, vi_rect bounds) {
	(void)state;
	vi_wbuffer *wbuffer = widget->internal;
	vi_view_resize(wbuffer->view, bounds);
}

void vi_wbuffer_render(const vi_widget *widget, vi_state *state) {
	vi_wbuffer *wbuffer = widget->internal;
	vi_buffer_render(wbuffer->buffer, state, wbuffer->view);
	vi_view_render(wbuffer->view, state->win);
}

void vi_wbuffer_on_key(const vi_widget *widget, vi_state *state, vi_key key) {
	vi_wbuffer *wbuffer = widget->internal;
	vi_buffer_on_key(wbuffer->buffer, state, key);
}

void vi_wbuffer_on_click(const vi_widget *widget, vi_state *state, vi_click click) {
	vi_wbuffer *wbuffer = widget->internal;
	vi_buffer_on_click(wbuffer->buffer, state, click);
}

void vi_wbuffer_scroll(const vi_widget *widget, vi_state *state, vi_scroll scroll) {
	(void)widget;
	(void)state;
	printf("vi_scroll { dir: (%d, %d) }\n", scroll.dir.x, scroll.dir.y);
}