#pragma once

#include <vigred/util/font.h>
#include <vigred/window.h>

struct vi_widget;

typedef struct vi_state {
	vi_window *win;
	vi_font_store *font_store;
	// TODO: Maybe abstract these two fields into a separate struct?
	struct vi_widget *ui;
	const struct vi_widget *selected;
} vi_state;

vi_state *vi_state_new(void);
void vi_state_free(vi_state *state);
