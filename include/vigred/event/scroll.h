#pragma once

#include <SDL2/SDL.h>

#include <vigred/util/rect.h>

typedef struct vi_scroll {
	vi_vec dir;
} vi_scroll;

vi_scroll vi_scroll_from_sdl(SDL_MouseWheelEvent wheel);
