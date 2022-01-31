#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <vigred/key.h>

vi_key vi_key_from_sdl(SDL_Keysym keysym) {
	bool shift = keysym.mod & KMOD_SHIFT;
	bool ctrl = keysym.mod & KMOD_CTRL;
	bool meta = keysym.mod & KMOD_ALT;
	bool hyper = keysym.mod & KMOD_GUI;
	uint8_t mod_part = 0;
	if (ctrl) {
		mod_part |= VI_MOD_CTRL;
	}
	if (meta) {
		mod_part |= VI_MOD_META;
	}
	if (hyper) {
		mod_part |= VI_MOD_HYPER;
	}
	if (shift) {
		switch (keysym.sym) {
		case SDLK_SPACE: return (vi_key) {mod_part | VI_MOD_SHIFT, ' '};
		case SDLK_ESCAPE: return (vi_key) {mod_part | VI_MOD_SHIFT, SPECIAL_KEY_MASK | VI_KBD_ESC};
		case SDLK_TAB: return (vi_key) {mod_part | VI_MOD_SHIFT, SPECIAL_KEY_MASK | VI_KBD_TAB};
		case SDLK_RETURN: return (vi_key) {mod_part | VI_MOD_SHIFT, SPECIAL_KEY_MASK | VI_KBD_RET};
		case SDLK_BACKSPACE: return (vi_key) {mod_part | VI_MOD_SHIFT, SPECIAL_KEY_MASK | VI_KBD_BSP};
		case SDLK_a: return (vi_key) {mod_part, 'A'};
		case SDLK_b: return (vi_key) {mod_part, 'B'};
		case SDLK_c: return (vi_key) {mod_part, 'C'};
		case SDLK_d: return (vi_key) {mod_part, 'D'};
		case SDLK_e: return (vi_key) {mod_part, 'E'};
		case SDLK_f: return (vi_key) {mod_part, 'F'};
		case SDLK_g: return (vi_key) {mod_part, 'G'};
		case SDLK_h: return (vi_key) {mod_part, 'H'};
		case SDLK_i: return (vi_key) {mod_part, 'I'};
		case SDLK_j: return (vi_key) {mod_part, 'J'};
		case SDLK_k: return (vi_key) {mod_part, 'K'};
		case SDLK_l: return (vi_key) {mod_part, 'L'};
		case SDLK_m: return (vi_key) {mod_part, 'M'};
		case SDLK_n: return (vi_key) {mod_part, 'N'};
		case SDLK_o: return (vi_key) {mod_part, 'O'};
		case SDLK_p: return (vi_key) {mod_part, 'P'};
		case SDLK_q: return (vi_key) {mod_part, 'Q'};
		case SDLK_r: return (vi_key) {mod_part, 'R'};
		case SDLK_s: return (vi_key) {mod_part, 'S'};
		case SDLK_t: return (vi_key) {mod_part, 'T'};
		case SDLK_u: return (vi_key) {mod_part, 'U'};
		case SDLK_v: return (vi_key) {mod_part, 'V'};
		case SDLK_w: return (vi_key) {mod_part, 'W'};
		case SDLK_x: return (vi_key) {mod_part, 'X'};
		case SDLK_y: return (vi_key) {mod_part, 'Y'};
		case SDLK_z: return (vi_key) {mod_part, 'Z'};
		case SDLK_0: return (vi_key) {mod_part, ')'};
		case SDLK_1: return (vi_key) {mod_part, '!'};
		case SDLK_2: return (vi_key) {mod_part, '@'};
		case SDLK_3: return (vi_key) {mod_part, '#'};
		case SDLK_4: return (vi_key) {mod_part, '$'};
		case SDLK_5: return (vi_key) {mod_part, '%'};
		case SDLK_6: return (vi_key) {mod_part, '^'};
		case SDLK_7: return (vi_key) {mod_part, '&'};
		case SDLK_8: return (vi_key) {mod_part, '*'};
		case SDLK_9: return (vi_key) {mod_part, '('};
		case SDLK_BACKQUOTE: return (vi_key) {mod_part, '~'};
		case SDLK_COMMA: return (vi_key) {mod_part, '<'};
		case SDLK_PERIOD: return (vi_key) {mod_part, '>'};
		case SDLK_SLASH: return (vi_key) {mod_part, '?'};
		case SDLK_SEMICOLON: return (vi_key) {mod_part, ':'};
		case SDLK_QUOTE: return (vi_key) {mod_part, '"'};
		case SDLK_LEFTBRACKET: return (vi_key) {mod_part, '{'};
		case SDLK_RIGHTBRACKET: return (vi_key) {mod_part, '}'};
		case SDLK_BACKSLASH: return (vi_key) {mod_part, '|'};
		case SDLK_MINUS: return (vi_key) {mod_part, '_'};
		case SDLK_EQUALS: return (vi_key) {mod_part, '+'};
		}
	} else {
		switch (keysym.sym) {
		case SDLK_SPACE: return (vi_key) {mod_part, ' '};
		case SDLK_ESCAPE: return (vi_key) {mod_part, SPECIAL_KEY_MASK | VI_KBD_ESC};
		case SDLK_TAB: return (vi_key) {mod_part, SPECIAL_KEY_MASK | VI_KBD_TAB};
		case SDLK_RETURN: return (vi_key) {mod_part, SPECIAL_KEY_MASK | VI_KBD_RET};
		case SDLK_BACKSPACE: return (vi_key) {mod_part, SPECIAL_KEY_MASK | VI_KBD_BSP};
		case SDLK_a: return (vi_key) {mod_part, 'a'};
		case SDLK_b: return (vi_key) {mod_part, 'b'};
		case SDLK_c: return (vi_key) {mod_part, 'c'};
		case SDLK_d: return (vi_key) {mod_part, 'd'};
		case SDLK_e: return (vi_key) {mod_part, 'e'};
		case SDLK_f: return (vi_key) {mod_part, 'f'};
		case SDLK_g: return (vi_key) {mod_part, 'g'};
		case SDLK_h: return (vi_key) {mod_part, 'h'};
		case SDLK_i: return (vi_key) {mod_part, 'i'};
		case SDLK_j: return (vi_key) {mod_part, 'j'};
		case SDLK_k: return (vi_key) {mod_part, 'k'};
		case SDLK_l: return (vi_key) {mod_part, 'l'};
		case SDLK_m: return (vi_key) {mod_part, 'm'};
		case SDLK_n: return (vi_key) {mod_part, 'n'};
		case SDLK_o: return (vi_key) {mod_part, 'o'};
		case SDLK_p: return (vi_key) {mod_part, 'p'};
		case SDLK_q: return (vi_key) {mod_part, 'q'};
		case SDLK_r: return (vi_key) {mod_part, 'r'};
		case SDLK_s: return (vi_key) {mod_part, 's'};
		case SDLK_t: return (vi_key) {mod_part, 't'};
		case SDLK_u: return (vi_key) {mod_part, 'u'};
		case SDLK_v: return (vi_key) {mod_part, 'v'};
		case SDLK_w: return (vi_key) {mod_part, 'w'};
		case SDLK_x: return (vi_key) {mod_part, 'x'};
		case SDLK_y: return (vi_key) {mod_part, 'y'};
		case SDLK_z: return (vi_key) {mod_part, 'z'};
		case SDLK_0: return (vi_key) {mod_part, '0'};
		case SDLK_1: return (vi_key) {mod_part, '1'};
		case SDLK_2: return (vi_key) {mod_part, '2'};
		case SDLK_3: return (vi_key) {mod_part, '3'};
		case SDLK_4: return (vi_key) {mod_part, '4'};
		case SDLK_5: return (vi_key) {mod_part, '5'};
		case SDLK_6: return (vi_key) {mod_part, '6'};
		case SDLK_7: return (vi_key) {mod_part, '7'};
		case SDLK_8: return (vi_key) {mod_part, '8'};
		case SDLK_9: return (vi_key) {mod_part, '9'};
		case SDLK_BACKQUOTE: return (vi_key) {mod_part, '`'};
		case SDLK_COMMA: return (vi_key) {mod_part, ','};
		case SDLK_PERIOD: return (vi_key) {mod_part, '.'};
		case SDLK_SLASH: return (vi_key) {mod_part, '/'};
		case SDLK_SEMICOLON: return (vi_key) {mod_part, ';'};
		case SDLK_QUOTE: return (vi_key) {mod_part, '\''};
		case SDLK_LEFTBRACKET: return (vi_key) {mod_part, '['};
		case SDLK_RIGHTBRACKET: return (vi_key) {mod_part, ']'};
		case SDLK_BACKSLASH: return (vi_key) {mod_part, '\\'};
		case SDLK_MINUS: return (vi_key) {mod_part, '-'};
		case SDLK_EQUALS: return (vi_key) {mod_part, '='};
		}
	}
	return (vi_key) {0, SPECIAL_KEY_MASK | VI_KBD_NOP};
}

static char *concat_cstr(const char *left, const char *right) {
	size_t total_length = strlen(left) + strlen(right) + 1;
	char *buffer = calloc(total_length, sizeof(char));
	buffer[total_length - 1] = 0;
	strcat(buffer, left);
	strcat(buffer, right);
	return buffer;
}

static char *show_mod(uint8_t mod) {
	char *mod_part = strdup("");
	if (mod & VI_MOD_CTRL) {
		char *new = concat_cstr(mod_part, "C-");
		free(mod_part);
		mod_part = new;
	}
	if (mod & VI_MOD_HYPER) {
		char *new = concat_cstr(mod_part, "H-");
		free(mod_part);
		mod_part = new;
	}
	if (mod & VI_MOD_META) {
		char *new = concat_cstr(mod_part, "M-");
		free(mod_part);
		mod_part = new;
	}
	if (mod & VI_MOD_SHIFT) {
		char *new = concat_cstr(mod_part, "S-");
		free(mod_part);
		mod_part = new;
	}
	return mod_part;
}

static char *char_to_cstr(char c) {
	char *cstr = malloc(2);
	cstr[0] = c;
	cstr[1] = 0;
	return cstr;
}

static char *show_key(uint16_t key) {
	bool special = key & SPECIAL_KEY_MASK;
	if (special) {
		const uint16_t special_key = key ^ SPECIAL_KEY_MASK;
		switch (special_key) {
		case VI_KBD_NOP: return strdup("NOP");
		case VI_KBD_ESC: return strdup("ESC");
		case VI_KBD_TAB: return strdup("TAB");
		case VI_KBD_RET: return strdup("RET");
		case VI_KBD_BSP: return strdup("BSP");
		default:
			fprintf(stderr, "vi_key_show(): [warning] Unrecognized special key sequence (%#04x). Defaulting to NOP\n", special_key);
			return strdup("NOP");
		}
	}
	return char_to_cstr((char)key);
}

char *vi_key_show(vi_key key) {
	char *mod_part = show_mod(key.mod);
	char *key_part = show_key(key.key);
	char *full = concat_cstr(mod_part, key_part);
	free(mod_part);
	free(key_part);
	return full;
}
