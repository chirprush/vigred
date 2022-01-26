#pragma once

#include <vigred/window.h>
#include <vigred/font.h>

typedef struct vi_state {
	vi_window *win;
	vi_font_store *font_store;
} vi_state;

vi_state *vi_state_new(void);
void vi_state_free(vi_state *state);