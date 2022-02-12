#pragma once

#include <vigred/util/font.h>
#include <vigred/window.h>

#define VI_SCROLL_SPEED 50

struct vi_profile;
struct vi_widget;

typedef struct vi_state {
	vi_window *win;
	vi_font_store *font_store;
	struct vi_profile *profile;
	// TODO: Maybe abstract these two fields into a separate struct?
	struct vi_widget *ui;
	const struct vi_widget *selected;
} vi_state;

vi_state *vi_state_new(void);
void vi_state_free(vi_state *state);
