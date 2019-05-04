#include "Objects.h"


/*
* @param shape {SDL_Rect}
* @param render {SDL_Renderer}
*/
void render_shape(SDL_Rect * shape, SDL_Renderer * render) {
		SDL_SetRenderDrawColor(render, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(render);
		SDL_SetRenderDrawColor(render, 192, 16, 16, 255);
		SDL_RenderFillRect(render, shape);
		SDL_RenderDrawRect(render, shape);
		SDL_RenderPresent(render);
}



/*
 * @param shape {SDL_Rect}
 * @param x {int}
 * @param y {int}
*/
bool move_shape(SDL_Rect * shape, int x, int y) {
	return true;
}


