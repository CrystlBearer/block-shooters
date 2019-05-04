#include "Start_Menu.h"


const int WINDOW_WIDTH_GAME = 600;
const int WINDOW_HEIGHT_GAME = 480;

/*
* This will bring up the start menu and call the game loop
* @return {int}
*/
int start_menu() {
	bool initialize = init();
	if (initialize == false) {
		return -1;
	}
	else {
		Game_State state;
		state = CONTINUE;
		game_loop(&state);
		return 0;
	}
}



/*
* This will start the game loop and begin interactivity between the player 
* @param finished {int *} 
* @return {bool}
*/
bool game_loop(Game_State * state) {
	SDL_Rect ship = { 0,WINDOW_HEIGHT_GAME / 2,40,30 };
	bool quit = false;
	bool goRight = true;
	SDL_Event event;

	puts("Starting the render loop");
	while (!quit) { //While application is runnin
		while (SDL_PollEvent(&event) != 0) { //This is our event loop
			if (event.type == SDL_QUIT) { //User requests suit
				puts("Exiting window...");
				quit = true;
			}
		}

		clear();
		render_shape(&ship,render);
		SDL_RenderPresent(render);
		if (goRight) {
			ship.x += 5;
		}
		else {
			ship.x -= 5;
		}

		if (ship.x == WINDOW_WIDTH_GAME) {
			goRight = false;
		}
		else if (ship.x == 0) {
			goRight = true;
		}
	}
	return true;
}


/* 
 * This will initiate the game and start the window and renderer
 * @return void
 */
bool init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("File: %s << Line: %d SDL_Init Error: %s\n", __FILE__, __LINE__, SDL_GetError());
		exit(EXIT_FAILURE);
	}
	else {
		window = SDL_CreateWindow("Block Shooters", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH_GAME, WINDOW_HEIGHT_GAME, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("File: %s << Line: %d SDL_CreateWindow Error:", __FILE__, __LINE__, SDL_GetError());
			exit(EXIT_FAILURE);
		}

		render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (render == NULL) {
			printf("File: %s << Line: %d SDL_CreateRenderer Error:", __FILE__, __LINE__, SDL_GetError());
			exit(EXIT_FAILURE);
		}
	}

	return true;

}


/*
* This will clear the screen with the background color(Black at the moment)
*/
void clear() {
	SDL_SetRenderDrawColor(render, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(render);
}


/*
This will clean up processes before quitting
*/
void close() {
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
}