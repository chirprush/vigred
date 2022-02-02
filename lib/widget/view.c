#include <SDL2/SDL.h>
#include <stdlib.h>

#include <vigred/widget/view.h>

vi_view *vi_view_new(vi_rect bounds) {
	vi_view *view = malloc(sizeof(vi_view));
	view->bounds = bounds;
	view->render_surface = SDL_CreateRGBSurface(0, bounds.w, bounds.h, 32, 0, 0, 0, 0);
	return view;
}

void vi_view_free(vi_view *view) {
	SDL_FreeSurface(view->render_surface);
	free(view);
}

void vi_view_render(vi_view *view, vi_window *win) {
	SDL_Texture *texture = SDL_CreateTextureFromSurface(win->renderer, view->render_surface);
	SDL_Rect bounds;
	bounds.x = view->bounds.pos.x;
	bounds.y = view->bounds.pos.y;
	bounds.w = view->bounds.w;
	bounds.h = view->bounds.h;
	SDL_RenderCopy(win->renderer, texture, NULL, &bounds);
	SDL_DestroyTexture(texture);
}

void vi_view_draw_clear(vi_view *view, vi_color color) {
	SDL_FillRect(
		view->render_surface,
		NULL,
		SDL_MapRGBA(
			view->render_surface->format,
			color.r,
			color.g,
			color.b,
			color.a
		)
	);
}

void vi_view_draw_rect(vi_view *view, vi_color color, vi_rect rect) {
	SDL_Rect r;
	r.x = rect.pos.x;
	r.y = rect.pos.y;
	r.w = rect.w;
	r.h = rect.h;
	SDL_FillRect(
		view->render_surface,
		&r,
		SDL_MapRGBA(
			view->render_surface->format,
			color.r,
			color.g,
			color.b,
			color.a
		)
	);
}

void vi_view_draw_text(vi_view *view, vi_color color, vi_vec pos, const vi_font *font, const char *text) {
	SDL_Color fg = {color.r, color.g, color.b, color.a};
	SDL_Surface *surface = TTF_RenderUTF8_Blended(font->font, text, fg);
	SDL_Rect dest;
	dest.x = pos.x;
	dest.y = pos.y;
	dest.w = surface->w;
	dest.h = surface->h;
	SDL_BlitSurface(surface, NULL, view->render_surface, &dest);
	SDL_FreeSurface(surface);
}
