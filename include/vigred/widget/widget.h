#pragma once

#include <vigred/util/rect.h>
#include <vigred/event/key.h>
#include <vigred/event/click.h>
#include <vigred/event/scroll.h>
#include <vigred/state.h>

struct vi_widget;

typedef void (*vi_widget_resize_func)(struct vi_widget *, vi_state *, vi_rect);
typedef void (*vi_widget_render_func)(const struct vi_widget *, vi_state *);
typedef void (*vi_widget_on_key_func)(const struct vi_widget *, vi_state *, vi_key);
typedef void (*vi_widget_on_click_func)(const struct vi_widget *, vi_state *, vi_click);
typedef void (*vi_widget_scroll_func)(const struct vi_widget *, vi_state *, vi_scroll);
typedef void (*vi_widget_free_func)(struct vi_widget *);

typedef struct vi_widget_vtable {
	vi_widget_resize_func resize;
	vi_widget_render_func render;
	vi_widget_on_key_func on_key;
	vi_widget_on_click_func on_click;
	vi_widget_scroll_func scroll;
	vi_widget_free_func free;
} vi_widget_vtable;

typedef struct vi_widget {
	const vi_widget_vtable *vtable;
	vi_rect bounds;
	void *internal;
} vi_widget;

vi_widget *vi_widget_new(const vi_widget_vtable *vtable, vi_rect bounds, void *internal);
void vi_widget_free(vi_widget *widget);

void vi_widget_resize(struct vi_widget *widget, vi_state *state, vi_rect bounds);
void vi_widget_render(const struct vi_widget *widget, vi_state *state);
void vi_widget_on_key(const struct vi_widget *widget, vi_state *state, vi_key key);
void vi_widget_on_click(const struct vi_widget *widget, vi_state *state, vi_click click);
void vi_widget_scroll(const struct vi_widget *widget, vi_state *state, vi_scroll scroll);
