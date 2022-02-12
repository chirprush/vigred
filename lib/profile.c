#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#include <vigred/profile.h>

vi_profile *vi_profile_new() {
	vi_profile *profile = malloc(sizeof(vi_profile));
	const char *home = getenv("HOME");
	const char *config_part = "/.config/vigred/";
	profile->config_path = calloc(strlen(home) + strlen(config_part) + 1, sizeof(char));
	strcat(profile->config_path, home);
	strcat(profile->config_path, config_part);
	return profile;
}

void vi_profile_free(vi_profile *profile) {
	free(profile->config_path);
	free(profile);
}

static void vi_state_load_plugin(vi_state *state, const char *path) {
	void *handle = dlopen(path, RTLD_LAZY);
	if (handle == NULL) {
		return;
	}
	vi_plugin_init_func init;
	// Kinda ugly, but -Werror=pedantic will complain unless we do this
	*(void **)(&init) = dlsym(handle, "plugin_init");
	if (init != NULL) {
		init(state);
	}
	dlclose(handle);
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
