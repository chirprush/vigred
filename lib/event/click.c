#include <SDL2/SDL.h>
#include <stdint.h>
#include <vigred/util/rect.h>

#include <vigred/event/click.h>

vi_click vi_click_from_sdl(SDL_MouseButtonEvent button) {
	vi_click click = {0};
	switch (button.button) {
	case SDL_BUTTON_LEFT:
		click.button = VI_MOUSE_LEFT;
		break;
	case SDL_BUTTON_RIGHT:
		click.button = VI_MOUSE_RIGHT;
		break;
	default:
		click.button = VI_MOUSE_NOP;
		// If there is a mouse press event that we don't handle or
		// record, make the event a no op. This is meant to be
		// ignored.
		return click;
	}
	switch (button.state) {
	case SDL_PRESSED:
		click.state = VI_MOUSE_PRESS;
		break;
	case SDL_RELEASED:
		click.state = VI_MOUSE_RELEASE;
		break;
	}
	click.pos.x = button.x;
	click.pos.y = button.y;
	return click;
}
