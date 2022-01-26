#include <stdio.h>
#include <stdlib.h>
#include <vigred/rect.h>
#include <vigred/color.h>
#include <vigred/font.h>
#include <vigred/window.h>
#include <vigred/state.h>
#include <vigred/buffer.h>
#include <vigred/byte_buffer.h>

const vi_buffer_vtable byte_buffer_vtable = {
	vi_byte_buffer_render,
	vi_byte_buffer_on_key,
	vi_byte_buffer_free
};

vi_byte_buffer *vi_byte_buffer_new(const char *text) {
	vi_byte_buffer *byte_buffer = malloc(sizeof(vi_byte_buffer));
	byte_buffer->text = text;
	byte_buffer->pos = (vi_vec) {0, 0};
	return byte_buffer;
}

vi_buffer *vi_byte_buffer_new_buffer(const char *text) {
	vi_byte_buffer *byte_buffer = vi_byte_buffer_new(text);
	vi_buffer *buffer = vi_buffer_new(&byte_buffer_vtable, byte_buffer);
	return buffer;
}

void vi_byte_buffer_free(vi_buffer *buffer) {
	vi_byte_buffer *byte_buffer = buffer->internal;
	free(byte_buffer);
}

void vi_byte_buffer_render(const vi_buffer *buffer, vi_state *state) {
	vi_byte_buffer *byte_buffer = buffer->internal;
	const vi_font *font = vi_font_store_ensure_font(state->font_store, "/usr/share/fonts/truetype/noto/NotoSansMono-Regular.ttf", 15);
	vi_color fg = vi_color_from_hex(0xffffffff);
	vi_window_draw_text(state->win, fg, byte_buffer->pos, font, byte_buffer->text);
	byte_buffer->pos.x++;
	byte_buffer->pos.y++;
}

void vi_byte_buffer_on_key(const vi_buffer *buffer, vi_state *state, vi_key key) {
	(void)buffer;
	(void)state;
	char *repr = vi_key_show(key);
	printf("key: %s\n", repr);
	free(repr);
}
