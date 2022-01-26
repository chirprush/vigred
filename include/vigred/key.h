#pragma once

#include <SDL2/SDL.h>
#include <stdint.h>

typedef enum vi_mod {
	VI_MOD_NONE  = 0,
	VI_MOD_SHIFT = 1 << 0,
	VI_MOD_CTRL  = 1 << 1,
	VI_MOD_META  = 1 << 2,
	VI_MOD_HYPER = 1 << 3,
} vi_mod;

#define SPECIAL_KEY_MASK (1 << 15)

typedef enum vi_special_key {
	VI_NOP,
	VI_ESC,
	VI_TAB,
	VI_RET,
	VI_BSP
} vi_special_key;

typedef struct vi_key {
	uint8_t mod;
	uint16_t key;
} vi_key;

vi_key vi_key_from_sdl(SDL_Keysym keysym);
char *vi_key_show(vi_key key);
