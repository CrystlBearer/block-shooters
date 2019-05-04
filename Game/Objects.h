#pragma once
#ifndef OBJECTS_H_INCLUDED
#define OBECTS_H_INCLUDED
#include "Dependencies.h"

void render_shape(SDL_Rect * shape, SDL_Renderer * render);
bool move_shape(SDL_Rect * shape, int x, int y);


#endif
