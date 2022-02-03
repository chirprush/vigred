#include <stdio.h>
#include <stdlib.h>
#include <vigred/util/rect.h>
#include <vigred/util/color.h>
#include <vigred/util/font.h>
#include <vigred/event/key.h>
#include <vigred/event/click.h>
#include <vigred/widget/view.h>
#include <vigred/buffer/buffer.h>
#include <vigred/window.h>
#include <vigred/state.h>

#include <vigred/buffer/anon.h>

const vi_buffer_vtable anon_buffer_vtable = {
	.render = vi_anon_buffer_render,
	.on_key = vi_anon_buffer_on_key,
	.on_click = vi_anon_buffer_on_click,
	.free = vi_anon_buffer_free
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
	vi_font *font = vi_font_store_ensure_font(state->font_store, "/usr/share/fonts/truetype/noto/NotoSansMono-Regular.ttf", 50);
	vi_font_set_style(font, VI_FONT_ITALIC | VI_FONT_UNDERLINE);
	vi_color bg = vi_color_from_hex(0x181c24ff);
	vi_color fg = vi_color_from_hex(0xffffffff);
	vi_view_draw_clear(view, bg);
	vi_view_draw_text(view, fg, anon_buffer->pos, font, anon_buffer->text);
	// anon_buffer->pos.x++;
	// anon_buffer->pos.y++;
}

void vi_anon_buffer_on_key(const vi_buffer *buffer, vi_state *state, vi_key key) {
	(void)buffer;
	(void)state;
	char *repr = vi_key_show(key);
	printf("key: %s\n", repr);
	free(repr);
}

void vi_anon_buffer_on_click(const vi_buffer *buffer, vi_state *state, vi_click click) {
	(void)buffer;
	(void)state;
	printf("vi_click { button: %d, state: %d, pos: (%d, %d) }\n", click.button, click.state, click.pos.x, click.pos.y);
}
