#pragma once
#ifndef START_MENU_H_INCLUDED
#define START_MENU_H_INCLUDED
#include "Objects.h"
#include "Dependencies.h"


typedef enum {
	CONTINUE,
	PAUSE,
	STOP
} Game_State;

int start_menu();
void render_bg(
	SDL_Renderer * render,
	Uint8         r,
	Uint8         g,
	Uint8         b,
	Uint8         a);
bool init();
bool game_loop(Game_State * state);
void close();

#endif
