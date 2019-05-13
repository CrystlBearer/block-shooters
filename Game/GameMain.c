#include "GameMain.h" // This will include the Dependencies.h file, Objects.h, and sl.h header files

const int WINDOW_WIDTH_GAME = 600; // This will be the fixed size of the window's width
const int WINDOW_HEIGHT_GAME = 480; // This will be the fixed size of the window's height
const short OBJECT_WIDTH = 60; // This is the width of all enemies and users in game
const short OBJECT_HEIGHT = 40; // This is the height of all enemies and users in the game
const short BULLET_WIDTH = 20;
const short BULLET_HEIGHT = 20; // Width height for projectiles

int score = 0;
short users_bullet_counter = 0;


SDL_Event event; // This is used to detect user's actions
Uint32 total_milliseconds;

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
		state = MENU;
		do {
			switch (state) {
				case PLAY:
					state = game_loop();
					break;
				case MENU:
					state = show_menu();
					break;
				default:
					state = STOP;
					break;
			}
		} while (state != STOP);
		close(); // Clean up 
		return 0;
	}
}





/*
* This will display the main menu with the texts
* @return select {Game_State} This will have game state enum to determine to continue the game or exit
*/
Game_State show_menu() {
	puts("Entering Main Menu...");
	SDL_Color menuColor = { 255,255,255 };
	SDL_Surface * text_title = TTF_RenderText_Solid(font,"Block Shooters",menuColor);
	SDL_Texture * texture_text_title = SDL_CreateTextureFromSurface(render, text_title);

	SDL_Surface * text_option1 = TTF_RenderText_Solid(font2, "Press 1 to Play", menuColor);
	SDL_Texture * texture_text_option1 = SDL_CreateTextureFromSurface(render, text_option1);

	SDL_Surface * text_option2 = TTF_RenderText_Solid(font2, "Press Q to Quit", menuColor);
	SDL_Texture * texture_text_option2 = SDL_CreateTextureFromSurface(render, text_option2);

	SDL_Surface * credits = TTF_RenderText_Solid(font2, "David     Jordan    Vivian", menuColor);
	SDL_Texture * texture_text_credits = SDL_CreateTextureFromSurface(render, credits);

	if (texture_text_title == NULL) {
		printf_s("FILE: %s >> LINE: %d >> Title texture creation error!\n", __FILE__,__LINE__ );
		exit(EXIT_FAILURE);
	}

	if (texture_text_option1 == NULL) {
		printf_s("FILE: %s >> LINE: %d >> Text option (1) creation error!\n", __FILE__, __LINE__ );
		exit(EXIT_FAILURE);
	}

	if (texture_text_option2 == NULL) {
		printf_s("FILE: %s >> LINE: %d >> Text option (2) creation error!\n", __FILE__, __LINE__ );
		exit(EXIT_FAILURE);
	}

	if (texture_text_credits == NULL) {
		printf_s("FILE: %s >> LINE: %d >> Text option (2) creation error!\n", __FILE__, __LINE__);
		exit(EXIT_FAILURE);
	}

	

	const SDL_Rect title_src = { 0, 0, 20*WINDOW_WIDTH_GAME,WINDOW_HEIGHT_GAME }; // Pure guess work of what the values are here but bigger the less skewed it'll look if the dest is smaller
	const SDL_Rect title_dest = { 50, 30, (4*WINDOW_WIDTH_GAME)/5,WINDOW_HEIGHT_GAME >> 2 }; //This will stretch to fill the rectangle
	
	const SDL_Rect option1_src = { 0, 0, 20 * WINDOW_WIDTH_GAME,WINDOW_HEIGHT_GAME };
	const SDL_Rect option1_dest = { (1*WINDOW_WIDTH_GAME)/5, 200, WINDOW_WIDTH_GAME >> 1,WINDOW_HEIGHT_GAME >> 3 };
	
	const SDL_Rect option2_src = { 0, 0, 20 * WINDOW_WIDTH_GAME,WINDOW_HEIGHT_GAME };
	const SDL_Rect option2_dest = { (1*WINDOW_WIDTH_GAME)/5, 250, WINDOW_WIDTH_GAME >> 1,WINDOW_HEIGHT_GAME >> 3 };

	const SDL_Rect credits_src = { 0, 0, 20 * WINDOW_WIDTH_GAME,WINDOW_HEIGHT_GAME };
	const SDL_Rect credits_dest = { (1 * WINDOW_WIDTH_GAME) / 5, WINDOW_HEIGHT_GAME-(WINDOW_HEIGHT_GAME/20), WINDOW_WIDTH_GAME >> 1,WINDOW_HEIGHT_GAME / 20 };

	SDL_FreeSurface(text_title); //Frees the surface from the original text
	SDL_FreeSurface(text_option1);
	SDL_FreeSurface(text_option2);
	SDL_FreeSurface(credits);
	SDL_SetRenderTarget(render, texture_text_title); // this allows this texture to be rendered
	SDL_SetRenderTarget(render, texture_text_option1);
	SDL_SetRenderTarget(render, texture_text_option2);
	SDL_SetRenderTarget(render, texture_text_credits);


	Game_State select = MENU;
	bool quit = false;
	render_bg(render, 0, 14, 20, 10);
	SDL_RenderCopy(render, texture_text_title, &title_src, &title_dest);
	SDL_RenderCopy(render, texture_text_option1, &option1_src, &option1_dest);
	SDL_RenderCopy(render, texture_text_option2, &option2_src, &option2_dest);
	SDL_RenderCopy(render, texture_text_option2, &option2_src, &option2_dest);
	SDL_RenderCopy(render, texture_text_credits, &credits_src, &credits_dest);
	SDL_RenderPresent(render); //This will render all the shapes into the canvas

	while (!quit) { // Event loop for the game
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) { //User requests to exit
				puts("Exiting window...");
				quit = true;
				select = STOP;
			}
			else if (event.type == SDL_KEYDOWN) { //https://wiki.libsdl.org/SDL_EventType?highlight=%28%5CbCategoryEnum%5Cb%29%7C%28CategoryEvents%29
				switch (event.key.keysym.sym) {
				case SDLK_1:
					select = PLAY;
					quit = true;
					break;
				case SDLK_q:
					select = STOP;
					quit = true;
					break;
				}
			}
		}
	}
	return select;
}


/*
 * Initializes all objects in the game
 * @return true {bool}
 */
bool initialize_objects() {
	left_wall.x = 0;
	left_wall.y = 0;
	left_wall.w = 1;
	left_wall.h = WINDOW_HEIGHT_GAME;
	
	right_wall.x = WINDOW_WIDTH_GAME-1;
	right_wall.y = 0;
	right_wall.w = 1;
	right_wall.h = WINDOW_HEIGHT_GAME;

	upper_wall.x = 0;
	upper_wall.y = 1;
	upper_wall.w = WINDOW_WIDTH_GAME;
	upper_wall.h = 1;

	lower_wall.x = 0;
	lower_wall.y = WINDOW_HEIGHT_GAME - 1;
	lower_wall.w = WINDOW_WIDTH_GAME;
	lower_wall.h = 1;

	user.x = WINDOW_WIDTH_GAME / 2;
	user.y = WINDOW_HEIGHT_GAME - OBJECT_HEIGHT - 20;
	user.w = OBJECT_WIDTH;
	user.h = OBJECT_HEIGHT;
	user_object = malloc(sizeof(Object) * 1); // This is used to update the user's character position of all four corners (Found in Objects.h and Objects.c)
	
	
	enemy.x = WINDOW_WIDTH_GAME / 2;
	enemy.y = 20;
	enemy.w = OBJECT_WIDTH;
	enemy.h = OBJECT_HEIGHT;
	enemy_object = malloc(sizeof(Object) * 1);

	set_object(user_object, &user); // Initializing the values in Objects.c
	set_object(enemy_object, &enemy);

	user_bullet.x = user.x + (OBJECT_WIDTH / 3);
	user_bullet.y = user.y;
	user_bullet.w = BULLET_WIDTH;
	user_bullet.h = BULLET_HEIGHT;

	user_bullet_object = malloc(sizeof(Object) * 1);
	set_object(user_bullet_object, &user_bullet);

	enemy_bullet.x = enemy.x + (OBJECT_WIDTH / 3);
	enemy_bullet.y = enemy.y + (OBJECT_HEIGHT / 2);
	enemy_bullet.w = BULLET_WIDTH;
	enemy_bullet.h = BULLET_HEIGHT;
	enemy_bullet_object = malloc(sizeof(Object) * 1);
	set_object(enemy_bullet_object, &enemy_bullet);
	return true;
}



/*
* This will start the game loop and begin interactivity between the player 
* @param finished {int *} 
* @return true {bool}
*/
Game_State game_loop() {
	void render_score(Uint32);
	void render_objects(SDL_Rect *[]);
	SDL_Rect * objects[8];
	Uint32 start;
	Uint32 end;
	Game_State state = MENU;
	initialize_objects();
	objects[0] = &user_bullet;
	objects[1] = &enemy_bullet;
	objects[2] = &user;
	objects[3] = &enemy;
	objects[4] = &left_wall;
	objects[5] = &right_wall;
	objects[6] = &upper_wall;
	objects[7] = &lower_wall;

	bool userCanShoot = true;
	bool enemyCanShoot = true;
	bool quit = false; // This will quit the program if the user exits
	
	puts("Starting the render loop...");
	start = SDL_GetTicks();
	while (!quit) { //While application is runnin
		while (SDL_PollEvent(&event) != 0) { //This is our event loop
			if (event.type == SDL_QUIT) { //User requests to exit
				puts("Exiting Game Window...");
				state = STOP;
				quit = true;
			} else if (event.type == SDL_KEYDOWN) { //https://wiki.libsdl.org/SDL_EventType?highlight=%28%5CbCategoryEnum%5Cb%29%7C%28CategoryEvents%29
				switch (event.key.keysym.sym) {
					case SDLK_a:
						move_shape(&user, user_object, -(OBJECT_WIDTH), 0);
						move_shape(&user_bullet, user_bullet_object, -(OBJECT_WIDTH), 0);
						break;
					case SDLK_d:
						move_shape(&user, user_object, (OBJECT_WIDTH), 0);
						move_shape(&user_bullet, user_bullet_object, OBJECT_WIDTH, 0);
						break;
					case SDLK_s:
						puts("PRESSED S!");
						if (userCanShoot == true) {
							move_shape(&user_bullet, user_bullet_object, 0, -(BULLET_HEIGHT));
							userCanShoot = false;
						}
						break;
					case SDLK_j:
						move_shape(&enemy, enemy_object, -(OBJECT_WIDTH), 0);
						move_shape(&enemy_bullet, user_bullet_object, -(OBJECT_WIDTH), 0);
						break;
					case SDLK_k:
						puts("PRESSED K!");
						if (userCanShoot == true) {
							move_shape(&enemy_bullet, user_bullet_object, 0, (BULLET_HEIGHT));
							enemyCanShoot = false;
						}
						break;
					case SDLK_l:
						move_shape(&enemy, enemy_object, (OBJECT_WIDTH), 0);
						move_shape(&enemy_bullet, user_bullet_object, OBJECT_WIDTH, 0);
						break;
					case SDLK_q:
						puts("Returning to main menu...");
						state = MENU;
						quit = true;
					default:
						break;
				}
			}
		}

		if (userCanShoot == false) {
			move_shape(&user_bullet, user_bullet_object, 0, -(BULLET_HEIGHT));
		}
		
		if (enemyCanShoot == false) {
			move_shape(&enemy_bullet, enemy_bullet_object, 0, (BULLET_HEIGHT));
		}

		if (SDL_HasIntersection(&lower_wall, &enemy_bullet)) {
			enemy_bullet.x = enemy.x + (OBJECT_WIDTH / 3);
			enemy_bullet.y = enemy.y;
			enemyCanShoot = true;
		}
		if (SDL_HasIntersection(&upper_wall, &user_bullet)) {
			user_bullet.x = user.x + (OBJECT_WIDTH / 3);
			user_bullet.y = user.y;
			userCanShoot = true;
		}

		if (SDL_HasIntersection(&enemy, &user_bullet)) {
			end = SDL_GetTicks();
			puts("User bullet hit the enemy!");
			break;
		}

		if (SDL_HasIntersection(&user, &enemy_bullet)) {
			end = SDL_GetTicks();
			puts("Enemy bullet hit the user!");
			break;
		}

		render_bg(render, 0x00, 0x00, 0x00, 0x00); //this will clear the window of all objects
		render_objects(objects);
		SDL_RenderPresent(render); //This will render all the shapes into the canvas
	}


	//Rendering the score board...
	total_milliseconds = end - start;
	render_score(total_milliseconds);
	Sleep(2500); // To let the users see the score
	free(user_object);
	free(enemy_object);
	free(user_bullet_object);
	free(enemy_bullet_object);
	return state;
}


/*
 * Render objects
 * @param total_milliseconds {Uint32} Time it took to end the game in milliseconds
 */
void render_objects(SDL_Rect * objects[]) {
	render_shape(objects[0], render, 255, 251, 0, 0);
	render_shape(objects[1], render, 85, 255, 0, 0);
	render_shape(objects[2], render, 0, 0, 255, 0); //this will draw the shape, but will not render
	render_shape(objects[3], render, 192, 16, 16, 255);
	render_shape(objects[4], render, 192, 16, 16, 255);
	render_shape(objects[5], render, 192, 16, 16, 255);
	render_shape(objects[6], render, 192, 16, 16, 255);
	render_shape(objects[7], render, 192, 16, 16, 255);
}



/*
 * Render scores after player hits the other player
 * @param total_milliseconds {Uint32} Time it took to end the game in milliseconds
 */
void render_score(Uint32 total_milliseconds) {
	char buffer[50];
	sprintf_s(buffer, 50, "%d", total_milliseconds);
	SDL_Color textColor = { 255,255,255 };
	SDL_Surface * text = TTF_RenderText_Solid(font, buffer, textColor);
	SDL_Texture * texture_text = SDL_CreateTextureFromSurface(render, text);

	if (texture_text == NULL) {
		printf_s("FILE: %s >> LINE: %d >> Title texture creation error!\n", __FILE__, __LINE__);
		exit(EXIT_FAILURE);
	}
	const SDL_Rect score_src = { 0, 0, 20 * WINDOW_WIDTH_GAME,WINDOW_HEIGHT_GAME }; // Pure guess work of what the values are here but bigger the less skewed it'll look if the dest is smaller
	const SDL_Rect score_dest = { 50, 150, (4 * WINDOW_WIDTH_GAME) / 5,WINDOW_HEIGHT_GAME >> 2 }; //This will stretch to fill the rectangle
	SDL_FreeSurface(text);
	SDL_SetRenderTarget(render, texture_text); // this allows this texture to be rendered
	SDL_RenderCopy(render, texture_text, &score_src, &score_dest);
	SDL_RenderPresent(render);
}






/* 
 * Initiate the game and start the window and renderer
 * @return true {bool}
 */
bool init() {

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("File: %s << Line: %d SDL_Init Error: %s\n", __FILE__, __LINE__, SDL_GetError());
		exit(EXIT_FAILURE);
	}


	if (TTF_Init() < 0) {
		printf("File: %s << Line: %d TTF_Init Error: %s\n", __FILE__, __LINE__, TTF_GetError());
		exit(EXIT_FAILURE);
	}

	font = TTF_OpenFont("./font/Blox2.ttf", 80);
	font2 = TTF_OpenFont("./font/ArcadeClassic.ttf", 80);

	if (!font) {
		printf_s("TTF_OpenFont: %s\n", TTF_GetError());
	}

	if (!font2) {
		printf_s("TTF_OpenFont: %s\n", TTF_GetError());
	}
	
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
	
	return true;

}







/*
 * Render the background with black, or what ever value is assigned to
 * the rgba.
 * @param render {SDL_Renderer} The initialized renderer to draw on the canvas
 * @param r,g,b,a {Uint8} The color values 
 * @return {void}
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
 * Clean up SDL renderer and window before quitting
 * @return {void}
 */
void close() {
	TTF_CloseFont(font);
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);

	font = NULL;
	render = NULL;
	window = NULL;
	
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}