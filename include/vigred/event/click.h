#pragma once

#include <SDL2/SDL.h>
#include <stdint.h>
#include <vigred/rect.h>

typedef enum vi_mouse_button {
	VI_MOUSE_NOP,
	VI_MOUSE_LEFT,
	VI_MOUSE_RIGHT
} vi_mouse_button;

typedef enum vi_mouse_state {
	VI_MOUSE_PRESS,
	VI_MOUSE_RELEASE
} vi_mouse_state;

typedef struct vi_click {
	vi_mouse_button button;
	vi_mouse_state state;
	vi_vec pos;
} vi_click;

vi_click vi_click_from_sdl(SDL_MouseButtonEvent button);
