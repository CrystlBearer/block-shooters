#include "Objects.h"

/*
 * @param shape {SDL_Rect}
 * @param render {SDL_Renderer}
 * @param r,g,b,a {Uint8} These are the values for the color of the shape
 * This will draw the object onto the canvas
 */
void render_shape(
	SDL_Rect * shape, 
	SDL_Renderer * render, 
	Uint8         r,
	Uint8         g,
	Uint8         b,
	Uint8         a
) {
		SDL_SetRenderDrawColor(render, r, g, b, a);
		SDL_RenderFillRect(render, shape);
		SDL_RenderDrawRect(render, shape);
}



/*
This will set the size of the objects to check for boundaries 
*/
bool set_object(Object * object, SDL_Rect * shape) {
	//puts("Do you make it here");
	object->shape = shape;
	object->top_left_x = shape->x;
	object->top_left_y = shape->y;
	object->top_right_x = ( object->top_left_x ) + shape->w ;
	object->top_right_y = (object->top_left_y);
	object->bottom_left_x = (object->top_left_x);
	object->bottom_left_y = (object->top_left_y) + shape->h;
	object->bottom_right_x = ( object->top_left_x ) + shape->w;
	object->bottom_right_y = (object->top_left_y) + shape->h;
	return true;
}





/*
 * This will move the object and update the values of coordinates of the object
 * @param shape {SDL_Rect}
 * @param x {int}
 * @param y {int}
*/
bool move_shape(SDL_Rect * shape, Object * object, int x, int y) {
	shape->x += x;
	shape->y += y;
	update_object(object);
	return true;
}





/*
 Updating an object's coordinates of the four corners
 */
bool update_object(Object * object) {
	object->top_left_x = (object->shape)->x;
	object->top_left_y = (object->shape)->y;

	object->top_right_x = (object->top_left_x) + (object->shape)->w;
	object->top_right_y = (object->top_left_y);

	object->bottom_left_x = (object->top_left_x);
	object->bottom_left_y = (object->top_left_y) + (object->shape)->h;

	object->bottom_right_x = (object->top_left_x) + (object->shape)->w;
	object->bottom_right_y = (object->top_left_y) + (object->shape)->h;
	return true;
}


