#pragma once

#include <vigred/event/key.h>
#include <vigred/event/click.h>
#include <vigred/event/scroll.h>
#include <vigred/state.h>

typedef void (*vi_plugin_init_func)(vi_state *);
typedef void (*vi_plugin_key_func)(vi_state *, vi_key);
typedef void (*vi_plugin_click_func)(vi_state *, vi_click);
typedef void (*vi_plugin_scroll_func)(vi_state *, vi_scroll);
typedef void (*vi_plugin_close_func)(vi_state *);

typedef struct vi_plugin {
	void *handle;
	vi_plugin_init_func init_func;
	vi_plugin_key_func key_func;
	vi_plugin_click_func click_func;
	vi_plugin_scroll_func scroll_func;
	vi_plugin_close_func close_func;
} vi_plugin;

vi_plugin *vi_plugin_new(
	void *handle,
	vi_plugin_init_func init_func,
	vi_plugin_key_func key_func,
	vi_plugin_click_func click_func,
	vi_plugin_scroll_func scroll_func,
	vi_plugin_close_func close_func
);

void vi_plugin_free(vi_plugin *plugin);
