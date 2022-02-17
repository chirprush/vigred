#pragma once

#include <vigred/event/key.h>
#include <vigred/event/click.h>
#include <vigred/event/scroll.h>
#include <vigred/plugin/plugin.h>
#include <vigred/state.h>

// In the future, we'll probably have to actually make a proper path
// object.
typedef struct vi_profile {
	char *config_path;
	vi_plugin **plugins;
	size_t capacity;
	size_t length;
} vi_profile;

vi_profile *vi_profile_new();
void vi_profile_free(vi_profile *profile);

void vi_state_load_plugins(vi_state *state);

void vi_state_init_hook(vi_state *state);
void vi_state_key_hook(vi_state *state, vi_key key);
void vi_state_click_hook(vi_state *state, vi_click click);
void vi_state_scroll_hook(vi_state *state, vi_scroll scroll);
void vi_state_close_hook(vi_state *state);
