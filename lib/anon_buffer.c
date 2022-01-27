#include <stdio.h>
#include <stdlib.h>
#include <vigred/rect.h>
#include <vigred/color.h>
#include <vigred/font.h>
#include <vigred/window.h>
#include <vigred/view.h>
#include <vigred/state.h>
#include <vigred/buffer.h>
#include <vigred/anon_buffer.h>

const vi_buffer_vtable anon_buffer_vtable = {
	vi_anon_buffer_render,
	vi_anon_buffer_on_key,
	vi_anon_buffer_free
};

vi_anon_buffer *vi_anon_buffer_new(const char *text) {
	vi_anon_buffer *anon_buffer = malloc(sizeof(vi_anon_buffer));
	anon_buffer->text = text;
	anon_buffer->pos = (vi_vec) {0, 0};
	return anon_buffer;
}

vi_buffer *vi_anon_buffer_new_buffer(const char *text) {
	vi_anon_buffer *anon_buffer = vi_anon_buffer_new(text);
	vi_buffer *buffer = vi_buffer_new(&anon_buffer_vtable, anon_buffer);
	return buffer;
}

void vi_anon_buffer_free(vi_buffer *buffer) {
	vi_anon_buffer *anon_buffer = buffer->internal;
	free(anon_buffer);
}

void vi_anon_buffer_render(const vi_buffer *buffer, vi_state *state, vi_view *view) {
	vi_anon_buffer *anon_buffer = buffer->internal;
	const vi_font *font = vi_font_store_ensure_font(state->font_store, "/usr/share/fonts/truetype/noto/NotoSansMono-Regular.ttf", 15);
	vi_color bg = vi_color_from_hex(0x181c24ff);
	vi_color fg = vi_color_from_hex(0xffffffff);
	vi_view_draw_clear(view, bg);
	vi_view_draw_text(view, fg, anon_buffer->pos, font, anon_buffer->text);
	anon_buffer->pos.x++;
	anon_buffer->pos.y++;
}

void vi_anon_buffer_on_key(const vi_buffer *buffer, vi_state *state, vi_key key) {
	(void)buffer;
	(void)state;
	char *repr = vi_key_show(key);
	printf("key: %s\n", repr);
	free(repr);
}
