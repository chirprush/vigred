#include <vigred/window.h>
#include <vigred/font.h>
#include <vigred/state.h>

vi_state *vi_state_new(void) {
	vi_state *state = malloc(sizeof(vi_state));
	state->win = vi_window_new();
	if (state->win == NULL) {
		free(state);
		return NULL;
	}
	state->font_store = vi_font_store_new();
	if (state->font_store == NULL) {
		vi_window_free(state->win);
		free(state);
		return NULL;
	}
	return state;
}

void vi_state_free(vi_state *state) {
	vi_font_store_free(state->font_store);
	vi_window_free(state->win);
	free(state);
}
