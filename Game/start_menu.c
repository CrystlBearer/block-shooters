#include "Start_Menu.h" //This will include the Dependencies.h file, Objects.h, and sl.h header files


const int WINDOW_WIDTH_GAME = 600; //This will be the fixed size of the window's width
const int WINDOW_HEIGHT_GAME = 480; //This will be the fixed size of the window's height

const short OBJECT_WIDTH = 50; //This is the width of all objects in game
const short OBJECT_HEIGHT = 30; //This is the height of all objects in the game

/*
* This will bring up the start menu and call the game loop
* @return {int}
*/
int start_menu() {
	bool initialize = init(); // This will create the window and renderer
	if (initialize == false) {  // If creation fails, program will exit with code -1
		return -1;
	}
	else {
		Game_State state; // The game state is initialized (will need to implement start menu later)
		state = CONTINUE;
		game_loop(&state); // This will run the function game loop to take in user input
		return 0;
	}
}


/*
* This will start the game loop and begin interactivity between the player 
* @param finished {int *} 
* @return {bool}
*/
bool game_loop(Game_State * state) {
	SDL_Rect user = { 0,WINDOW_HEIGHT_GAME-OBJECT_HEIGHT,OBJECT_WIDTH,OBJECT_HEIGHT}; // This initializes the user's character 
	Object * user_object = malloc(sizeof(Object)); // This is used to update the user's character position of all four corners (Found in Objects.h and Objects.c)
	SDL_Event event;
	set_object(user_object, &user); // Initializing the values in Objects.c
	bool quit = false; // This will quit the program if the user exits
	//bool goRight = true;

	puts("Starting the render loop...");
	while (!quit) { //While application is runnin
		while (SDL_PollEvent(&event) != 0) { //This is our event loop
			if (event.type == SDL_QUIT) { //User requests to exit
				puts("Exiting window...");
				quit = true;
			}
			else if (event.type == SDL_KEYDOWN) {//https://wiki.libsdl.org/SDL_EventType?highlight=%28%5CbCategoryEnum%5Cb%29%7C%28CategoryEvents%29
				switch (event.key.keysym.sym) {
				case SDLK_a:
					move_shape(&user, user_object, -25, 0);
					break;
				case SDLK_d:
					move_shape(&user, user_object, 25, 0);
					break;
				default:
					break;
				}
			}
		}
		render_bg(render, 0x00, 0x00, 0x00, 0x00); //this will clear the window of all objects
		render_shape(&user,render, 192, 16, 16, 255); //this will draw the shape, but will not render
		SDL_RenderPresent(render); //This will render all the shapes into the canvas
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
		window = SDL_CreateWindow("Block Shooters", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH_GAME, WINDOW_HEIGHT_GAME, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("File: %s << Line: %d SDL_CreateWindow Error: %s\n", __FILE__, __LINE__, SDL_GetError());
			exit(EXIT_FAILURE);
		}

		render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (render == NULL) {
			printf("File: %s << Line: %d SDL_CreateRenderer Error: %s\n", __FILE__, __LINE__, SDL_GetError());
			exit(EXIT_FAILURE);
		}
	}

	return true;

}



/*
 * This will render the background with black, or what ever value is assigned to
 * the rgba.
 */
void render_bg(
	SDL_Renderer * render,
	Uint8         r,
	Uint8         g,
	Uint8         b,
	Uint8         a
) {
	SDL_SetRenderDrawColor(render, r, g, b, a);
	SDL_RenderClear(render);
}




/*
 * This will clean up processes before quitting
 */
void close() {
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
}