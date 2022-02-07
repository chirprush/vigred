#include <string.h>
#include <stdlib.h>
#include <vigred/util/rect.h>
#include <vigred/event/key.h>
#include <vigred/event/click.h>
#include <vigred/event/scroll.h>
#include <vigred/state.h>

#include <vigred/widget/widget.h>

vi_widget *vi_widget_new(const char *id, const vi_widget_vtable *vtable, vi_rect bounds, void *internal) {
	vi_widget *widget = malloc(sizeof(vi_widget));
	widget->id = id;
	widget->vtable = vtable;
	widget->bounds = bounds;
	widget->internal = internal;
	return widget;
}

void vi_widget_free(vi_widget *widget) {
	widget->vtable->free(widget);
	free(widget);
}

void vi_widget_resize(struct vi_widget *widget, vi_state *state, vi_rect bounds) {
	widget->vtable->resize(widget, state, bounds);
	widget->bounds = bounds;
}

void vi_widget_render(const struct vi_widget *widget, vi_state *state) {
	widget->vtable->render(widget, state);
}

vi_widget *vi_widget_find_id(struct vi_widget *widget, const char *id) {
	if (widget->id != NULL && id != NULL && strcmp(id, widget->id) == 0) {
		return widget;
	}
	return widget->vtable->find_id(widget, id);
}

void vi_widget_on_key(const struct vi_widget *widget, vi_state *state, vi_key key) {
	widget->vtable->on_key(widget, state, key);
}

void vi_widget_on_click(const struct vi_widget *widget, vi_state *state, vi_click click) {
	widget->vtable->on_click(widget, state, click);
}

void vi_widget_scroll(const struct vi_widget *widget, vi_state *state, vi_scroll scroll) {
	widget->vtable->scroll(widget, state, scroll);
}
