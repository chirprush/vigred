#include <stdio.h>
#include <vigred/state.h>

void plugin_init(vi_state *state) {
	(void)state;
	printf("Hello from a plugin!\n");
}
