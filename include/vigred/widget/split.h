#pragma once

#include <stdbool.h>
#include <vigred/widget/widget.h>

typedef struct vi_split {
	vi_widget *left;
	vi_widget *right;
	float sep;
	bool vertical;
} vi_split;

vi_split *vi_split_new(vi_widget *left, vi_widget *right, float sep, bool vertical);
vi_widget *vi_split_new_widget(vi_widget *left, vi_widget *right, float sep, bool vertical);

void vi_split_free(vi_widget *widget);

void vi_split_resize(struct vi_widget *widget, vi_state *state, vi_rect bounds);
void vi_split_render(const struct vi_widget *widget, vi_state *state);
void vi_split_on_key(const struct vi_widget *widget, vi_state *state, vi_key key);
void vi_split_on_click(const struct vi_widget *widget, vi_state *state, vi_click click);
void vi_split_scroll(const struct vi_widget *widget, vi_state *state, vi_scroll scroll);
