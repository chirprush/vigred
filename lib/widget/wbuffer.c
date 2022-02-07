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
	.find_id = vi_wbuffer_find_id,
	.on_key = vi_wbuffer_on_key,
	.on_click = vi_wbuffer_on_click,
	.scroll = vi_wbuffer_scroll,
	.free = vi_wbuffer_free,
};

vi_wbuffer *vi_wbuffer_new(vi_buffer *buffer) {
	vi_view *view = vi_view_new((vi_rect) {0});
	vi_wbuffer *wbuffer = malloc(sizeof(vi_wbuffer));
	wbuffer->view = view;
	wbuffer->buffer = buffer;
	return wbuffer;
}

vi_widget *vi_wbuffer_new_widget(const char *id, vi_buffer *buffer) {
	vi_wbuffer *wbuffer = vi_wbuffer_new(buffer);
	vi_widget *widget = vi_widget_new(id, &wbuffer_vtable, (vi_rect) {0}, wbuffer);
	return widget;
}

void vi_wbuffer_free(vi_widget *widget) {
	vi_wbuffer *wbuffer = widget->internal;
	vi_view_free(wbuffer->view);
	free(wbuffer);
}

void vi_wbuffer_resize(vi_widget *widget, vi_state *state, vi_rect bounds) {
	(void)state;
	vi_wbuffer *wbuffer = widget->internal;
	vi_view_resize(wbuffer->view, bounds);
}

void vi_wbuffer_render(const vi_widget *widget, vi_state *state) {
	vi_wbuffer *wbuffer = widget->internal;
	vi_color bg = vi_color_from_hex(0x181c24ff);
	if (widget == state->selected) {
		bg.r += 7;
		bg.g += 7;
		bg.b += 7;
	}
	vi_view_draw_clear(wbuffer->view, bg);
	vi_buffer_render(wbuffer->buffer, state, wbuffer->view);
	vi_view_render(wbuffer->view, state->win);
}

vi_widget *vi_wbuffer_find_id(vi_widget *widget, const char *id) {
	// vi_widget already checks for the current widget, but not the
	// internal, so we can somewhat cleanly return NULL here.
	(void)widget;
	(void)id;
	return NULL;
}

void vi_wbuffer_on_key(const vi_widget *widget, vi_state *state, vi_key key) {
	vi_wbuffer *wbuffer = widget->internal;
	vi_buffer_on_key(wbuffer->buffer, state, key);
}

void vi_wbuffer_on_click(const vi_widget *widget, vi_state *state, vi_click click) {
	vi_wbuffer *wbuffer = widget->internal;
	click.pos = vi_vec_sub(click.pos, widget->bounds.pos);
	vi_buffer_on_click(wbuffer->buffer, state, click);
	// It's sort of awkward to set the selected widget manually like
	// this, but I'm not really sure what to do otherwise.
	state->selected = widget;
}

void vi_wbuffer_scroll(const vi_widget *widget, vi_state *state, vi_scroll scroll) {
	(void)widget;
	(void)state;
	printf("vi_scroll { dir: (%d, %d) }\n", scroll.dir.x, scroll.dir.y);
}
