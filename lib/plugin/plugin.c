#include <stdlib.h>
#include <dlfcn.h>
#include <vigred/event/key.h>
#include <vigred/event/click.h>
#include <vigred/event/scroll.h>
#include <vigred/state.h>

#include <vigred/plugin/plugin.h>

vi_plugin *vi_plugin_new(
	void *handle,
	vi_plugin_init_func init_func,
	vi_plugin_key_func key_func,
	vi_plugin_click_func click_func,
	vi_plugin_scroll_func scroll_func,
	vi_plugin_close_func close_func
) {
	vi_plugin *plugin = malloc(sizeof(vi_plugin));
	plugin->handle = handle;
	plugin->init_func = init_func;
	plugin->key_func = key_func;
	plugin->click_func = click_func;
	plugin->scroll_func = scroll_func;
	plugin->close_func = close_func;
	return plugin;
}

void vi_plugin_free(vi_plugin *plugin) {
	dlclose(plugin->handle);
	free(plugin);
}
