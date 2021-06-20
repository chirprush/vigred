#ifndef _VIGRED_COLOR_H
#define _VIGRED_COLOR_H

#include "vigred_window.h"

typedef struct vi_color {
	int r, g, b;
} vi_color;

vi_color vi_color_from_hex(int color);

#endif // _VIGRED_COLOR_H
