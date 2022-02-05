#include <stdlib.h>
#include <stdbool.h>
#include <vigred/util/rect.h>
#include <vigred/widget/widget.h>
#include <vigred/widget/split.h>

const vi_widget_vtable vi_split_vtable = {
	.resize = vi_split_resize,
	.render = vi_split_render,
	.on_key = vi_split_on_key,
	.on_click = vi_split_on_click,
	.scroll = vi_split_scroll,
	.free = vi_split_free
};

vi_split *vi_split_new(vi_widget *left, vi_widget *right, float sep, bool vertical) {
	vi_split *split = malloc(sizeof(vi_split));
	split->left = left;
	split->right = right;
	split->sep = sep;
	split->vertical = vertical;
	return split;
}

vi_widget *vi_split_new_widget(vi_widget *left, vi_widget *right, float sep, bool vertical) {
	vi_split *split = vi_split_new(left, right, sep, vertical);
	vi_widget *widget = vi_widget_new(&vi_split_vtable, split);
	return widget;
}

void vi_split_free(vi_widget *widget) {
	vi_split *split = widget->internal;
	vi_widget_free(split->left);
	vi_widget_free(split->right);
	free(split);
}

void vi_split_resize(const struct vi_widget *widget, vi_state *state, vi_rect bounds) {
	vi_split *split = widget->internal;
	if (split->vertical) {
		int32_t w = (int32_t)(bounds.w * split->sep);
		vi_widget_resize(split->left, state, (vi_rect) {bounds.pos, w, bounds.h});
		vi_widget_resize(split->right, state, (vi_rect) {(vi_vec) {bounds.pos.x + w, bounds.pos.y}, bounds.w - w, bounds.h});
	} else {
		int32_t h = (int32_t)(bounds.h * split->sep);
		vi_widget_resize(split->left, state, (vi_rect) {bounds.pos, bounds.w, h});
		vi_widget_resize(split->right, state, (vi_rect) {(vi_vec) {bounds.pos.x, bounds.pos.y + h}, bounds.w, bounds.h - h});
	}
}

void vi_split_render(const struct vi_widget *widget, vi_state *state) {
	vi_split *split = widget->internal;
	vi_widget_render(split->left, state);
	vi_widget_render(split->right, state);
}

void vi_split_on_key(const struct vi_widget *widget, vi_state *state, vi_key key) {
	vi_split *split = widget->internal;
	vi_widget_on_key(split->left, state, key);
	vi_widget_on_key(split->right, state, key);
}

void vi_split_on_click(const struct vi_widget *widget, vi_state *state, vi_click click) {
	(void)widget;
	(void)state;
	(void)click;
}

void vi_split_scroll(const struct vi_widget *widget, vi_state *state, vi_scroll scroll) {
	vi_split *split = widget->internal;
	vi_widget_scroll(split->left, state, scroll);
	vi_widget_scroll(split->right, state, scroll);
}
