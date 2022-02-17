#include <stdio.h>
#include <vigred/event/key.h>
#include <vigred/widget/widget.h>
#include <vigred/state.h>

void plugin_init(vi_state *state) {
	(void)state;
	printf("Hello from a plugin!\n");
}

void plugin_key(vi_state *state, vi_key key) {
	if (key.mod == VI_MOD_CTRL && key.key == 'j') {
		state->selected = vi_widget_find_id(state->ui, "anon");
	}
}

void plugin_close(vi_state *state) {
	(void)state;
	printf("Bye from a plugin!\n");
}
