#pragma once

#include <vigred/util/rect.h>
#include <vigred/event/key.h>
#include <vigred/event/click.h>
#include <vigred/event/scroll.h>
#include <vigred/buffer/buffer.h>
#include <vigred/widget/view.h>
#include <vigred/widget/widget.h>
#include <vigred/state.h>

typedef struct vi_wbuffer {
	vi_view *view;
	vi_buffer *buffer;
} vi_wbuffer;

vi_wbuffer *vi_wbuffer_new(vi_buffer *buffer);
vi_widget *vi_wbuffer_new_widget(const char *id, vi_buffer *buffer);

void vi_wbuffer_free(vi_widget *widget);

void vi_wbuffer_resize(vi_widget *widget, vi_state *state, vi_rect bounds);
void vi_wbuffer_render(const vi_widget *widget, vi_state *state);
vi_widget *vi_wbuffer_find_id(vi_widget *widget, const char *id);
void vi_wbuffer_on_key(const vi_widget *widget, vi_state *state, vi_key key);
void vi_wbuffer_on_click(const vi_widget *widget, vi_state *state, vi_click click);
void vi_wbuffer_scroll(const vi_widget *widget, vi_state *state, vi_scroll scroll);
