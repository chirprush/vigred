#include <stdint.h>
#include <stdbool.h>

#include <vigred/util/rect.h>

vi_vec vi_vec_sub(vi_vec pos, vi_vec offset) {
	return (vi_vec) {pos.x - offset.x, pos.y - offset.y};
}

bool vi_rect_contains(vi_rect rect, vi_vec pos) {
	return pos.x >= rect.pos.x && pos.x <= rect.pos.x + rect.w && pos.y >= rect.pos.y && pos.y <= rect.pos.y + rect.h;
}
