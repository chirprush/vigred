#include <stdlib.h>
#include <vigred/rect.h>
#include <vigred/color.h>
#include <vigred/window.h>
#include <vigred/buffer.h>
#include <vigred/byte_buffer.h>

const vi_buffer_vtable byte_buffer_vtable = {
	vi_byte_buffer_render,
	vi_byte_buffer_free
};

vi_byte_buffer *vi_byte_buffer_new(const char *text) {
	vi_byte_buffer *byte_buffer = malloc(sizeof(vi_byte_buffer));
	byte_buffer->text = text;
	byte_buffer->font = TTF_OpenFont("/usr/share/fonts/truetype/noto/NotoSansMono-Regular.ttf", 16);
	return byte_buffer;
}

vi_buffer *vi_byte_buffer_new_buffer(const char *text) {
	vi_byte_buffer *byte_buffer = vi_byte_buffer_new(text);
	vi_buffer *buffer = vi_buffer_new(&byte_buffer_vtable, byte_buffer);
	return buffer;
}

void vi_byte_buffer_free(vi_buffer *buffer) {
	vi_byte_buffer *byte_buffer = buffer->internal;
	TTF_CloseFont(byte_buffer->font);
	free(byte_buffer);
}

void vi_byte_buffer_render(const vi_buffer *buffer, vi_window *win) {
	const vi_byte_buffer *byte_buffer = buffer->internal;
	vi_color fg = vi_color_from_hex(0xffffffff);
	vi_vec pos = {0, 0};
	vi_window_draw_text(win, fg, pos, byte_buffer->font, byte_buffer->text);
}
