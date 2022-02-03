#include <stdlib.h>
#include <vigred/state.h>
#include <vigred/event/key.h>
#include <vigred/event/click.h>
#include <vigred/event/scroll.h>

#include <vigred/widget/widget.h>

vi_widget *vi_widget_new(const vi_widget_vtable *vtable, void *internal) {
	vi_widget *widget = malloc(sizeof(vi_widget));
	widget->vtable = vtable;
	widget->internal = internal;
	return widget;
}

void vi_widget_free(vi_widget *widget) {
	widget->vtable->free(widget);
	free(widget);
}

void vi_widget_render(const struct vi_widget *widget, vi_state *state) {
	widget->vtable->render(widget, state);
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
