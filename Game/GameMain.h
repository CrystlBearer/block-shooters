#pragma once
#ifndef START_MENU_H_INCLUDED
#define START_MENU_H_INCLUDED
#include "Objects.h"

typedef enum { // This will be used to create a menu and determine if the player would like to continue, pause, or stop the game.
	PLAY,
	MENU,
	STOP
} Game_State; 

int start_menu(); //Prototype for the start menu
void render_bg( // Prototype for clearing the background by rendering the background color
	SDL_Renderer * render,
	Uint8         r,
	Uint8         g,
	Uint8         b,
	Uint8         a);
bool init(); // This is used to create the game window and renderer
Game_State game_loop(); // This is the game loop to continuously render
Game_State show_menu();
void close(); // This will clean up all the windows and renderers before exiting the program

#endif
