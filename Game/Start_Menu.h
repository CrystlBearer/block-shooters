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
bool init();
bool game_loop(Game_State * state);
void clear();
void close();

#endif
