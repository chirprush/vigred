#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <vigred/event/key.h>
#include <vigred/event/click.h>
#include <vigred/event/scroll.h>
#include <vigred/plugin/plugin.h>

#include <vigred/plugin/profile.h>

vi_profile *vi_profile_new() {
	vi_profile *profile = malloc(sizeof(vi_profile));
	const char *home = getenv("HOME");
	const char *config_part = "/.config/vigred/";
	profile->config_path = calloc(strlen(home) + strlen(config_part) + 1, sizeof(char));
	strcat(profile->config_path, home);
	strcat(profile->config_path, config_part);
	profile->plugins = NULL;
	profile->capacity = 0;
	profile->length = 0;
	return profile;
}

void vi_profile_free(vi_profile *profile) {
	free(profile->config_path);
	if (profile->plugins != NULL) {
		for (size_t i = 0; i < profile->length; ++i) {
			vi_plugin_free(profile->plugins[i]);
		}
		free(profile->plugins);
	}
	free(profile);
}

static void vi_state_load_plugin(vi_state *state, const char *path) {
	vi_profile *profile = state->profile;
	void *handle = dlopen(path, RTLD_LAZY);
	if (handle == NULL) {
		return;
	}
	vi_plugin_init_func init_func;
	vi_plugin_key_func key_func;
	vi_plugin_click_func click_func;
	vi_plugin_scroll_func scroll_func;
	vi_plugin_close_func close_func;
	// Kinda ugly, but -Werror=pedantic will complain unless we do this
	*(void **)(&init_func) = dlsym(handle, "plugin_init");
	*(void **)(&key_func) = dlsym(handle, "plugin_key");
	*(void **)(&click_func) = dlsym(handle, "plugin_click");
	*(void **)(&scroll_func) = dlsym(handle, "plugin_scroll");
	*(void **)(&close_func) = dlsym(handle, "plugin_close");
	vi_plugin *plugin = vi_plugin_new(handle, init_func, key_func, click_func, scroll_func, close_func);
	if (profile->plugins == NULL || profile->length == profile->capacity) {
		profile->capacity += 8;
		profile->plugins = realloc(profile->plugins, profile->capacity * sizeof(vi_plugin *));
	}
	profile->plugins[profile->length] = plugin;
	profile->length++;
}

void vi_state_load_plugins(vi_state *state) {
	vi_profile *profile = state->profile;
	const char *init_part = "init.so";
	char *init_path = calloc(strlen(profile->config_path) + strlen(init_part) + 1, sizeof(char));
	strcat(init_path, profile->config_path);
	strcat(init_path, init_part);
	vi_state_load_plugin(state, init_path);
	free(init_path);
}

void vi_state_init_hook(vi_state *state) {
	vi_profile *profile = state->profile;
	for (size_t i = 0; i < profile->length; ++i) {
		if (profile->plugins[i]->init_func != NULL) {
			profile->plugins[i]->init_func(state);
		}
	}
}

void vi_state_key_hook(vi_state *state, vi_key key) {
	vi_profile *profile = state->profile;
	for (size_t i = 0; i < profile->length; ++i) {
		if (profile->plugins[i]->key_func != NULL) {
			profile->plugins[i]->key_func(state, key);
		}
	}
}

void vi_state_click_hook(vi_state *state, vi_click click) {
	vi_profile *profile = state->profile;
	for (size_t i = 0; i < profile->length; ++i) {
		if (profile->plugins[i]->click_func != NULL) {
			profile->plugins[i]->click_func(state, click);
		}
	}
}

void vi_state_scroll_hook(vi_state *state, vi_scroll scroll) {
	vi_profile *profile = state->profile;
	for (size_t i = 0; i < profile->length; ++i) {
		if (profile->plugins[i]->scroll_func != NULL) {
			profile->plugins[i]->scroll_func(state, scroll);
		}
	}
}

void vi_state_close_hook(vi_state *state) {
	vi_profile *profile = state->profile;
	for (size_t i = 0; i < profile->length; ++i) {
		if (profile->plugins[i]->close_func != NULL) {
			profile->plugins[i]->close_func(state);
		}
	}
}

