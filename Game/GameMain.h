#pragma once
#ifndef START_MENU_H_INCLUDED
#define START_MENU_H_INCLUDED
#include "Objects.h"

typedef enum { // This will be used to create a menu and determine if the player would like to continue, pause, or stop the game.
	PLAY,
	MENU,
	STOP
} Game_State; 

int start_menu(int*,int*); //Prototype for the start menu
void render_bg( // Prototype for clearing the background by rendering the background color
	SDL_Renderer * render,
	Uint8         r,
	Uint8         g,
	Uint8         b,
	Uint8         a
);

bool init(); // This is used to create the game window and renderer
Game_State game_loop(); // This is the game loop to continuously render
Game_State show_menu();
bool initialize_objects();
void close(); // This will clean up all the windows and renderers before exiting the program

SDL_Rect left_wall;
SDL_Rect right_wall;
SDL_Rect upper_wall;
SDL_Rect lower_wall;

SDL_Rect user; // This initializes the user's character 
Object * user_object; // This is used to update the user's character position of all four corners (Found in Objects.h and Objects.c)


SDL_Rect enemy; // This initializes the user's character 
Object * enemy_object;

SDL_Rect user_bullet;
Object * user_bullet_object;
SDL_Rect enemy_bullet;
Object * enemy_bullet_object;



#endif
