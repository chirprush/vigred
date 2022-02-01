#include <SDL2/SDL.h>
#include <vigred/scroll.h>

vi_scroll vi_scroll_from_sdl(SDL_MouseWheelEvent wheel) {
	vi_scroll scroll = {0};
	scroll.dir.x = wheel.x;
	// As the origin of rendering is the top-left, it makes more sense
	// that scrolling down results in a positive y
	scroll.dir.y = -wheel.y;
	return scroll;
}
