#pragma once

#include <vigred/state.h>

// If we want to add a close function and such, we need to store
// individual plugin objects.
typedef void (*vi_plugin_init_func)(vi_state *);

// In the future, we'll probably have to actually make a proper path
// object.
typedef struct vi_profile {
	char *config_path;
} vi_profile;

vi_profile *vi_profile_new();
void vi_profile_free(vi_profile *profile);

void vi_state_load_plugins(vi_state *state);
