#pragma once
#ifndef OBJECTS_H_INCLUDED
#define OBECTS_H_INCLUDED
#include "Dependencies.h"



/*
 * This default coordinates for SDL is the top left corner of the object
 * The other values are for checking collision and boundaries later on
 */
typedef struct object {
	SDL_Rect * shape;
	int top_left_x;
	int top_left_y;
	int top_right_x;
	int top_right_y;
	int bottom_left_x;
	int bottom_left_y;
	int bottom_right_x;
	int bottom_right_y;
} Object;


//typedef struct object * Object_ptr;

void render_shape(
	SDL_Rect * shape, 
	SDL_Renderer * render, 
	Uint8         r,
	Uint8         g,
	Uint8         b,
	Uint8         a
);

bool move_shape(
	SDL_Rect * shape,
	Object * object,
	int x, 
	int y
);

bool set_object(
	Object * object,
	SDL_Rect * shape
);

bool update_object(Object * object);





#endif
