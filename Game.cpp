#include "headers/Game.h"
#include "headers/GameObject.h"
#include "headers/TextureManager.h"
#include "headers/Map.h"
#include "headers/Player.h"

Map* map;
Player* player1;
Player* player2;

SDL_Renderer* Game::gRenderer = nullptr;

const int JOYSTICK_DEAD_ZONE = 8000;
SDL_Joystick* gGameController = NULL;

Game::Game(int width, int height) {
	// delta time
	NOW = SDL_GetPerformanceCounter();
	LAST = 0;
	deltaTime = 0;

	ScreenWidth = width;
	ScreenHeight = height;
	TileSize = 40;
	//int mapWidth;		dodac
	//int maHeight;

	directionPlayer1 = { 0, 0 };
	directionPlayer2 = { 0, 0 };
}

Game::~Game() {}

bool Game::init(const char* title, bool fullscreen) {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}
		if (SDL_NumJoysticks() < 1)
		{
			printf("Warning: No joysticks connected!\n");
		}
		else
		{
			//Load joystick
			gGameController = SDL_JoystickOpen(0);
			if (gGameController == NULL)
			{
				printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
			}
		}

		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
		map = new Map(25, 30, ScreenWidth, ScreenHeight, 40);
		player1 = new Player(0, 0, 0.5, "assets/draco.png", map->columns * 40, map->rows * 40);
		player2 = new Player(30, 30, 0.5, "assets/draco.png", map->columns * 40, map->rows * 40);
	}

	return success;
}


bool Game::loadMedia() {
	bool success = true;

	/*brom = new GameObject("brom.png", 0, 200, 200, 200);
	if (brom == NULL)
	{
		printf("Failed to load texture image!\n");
		success = false;
	}*/

	return success;
}

void drawCircle(SDL_Renderer* renderer, int x, int y, int radius, SDL_Color color)
{
	//Renderer is set to draw in given color.
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	//And in those loops we draw a point in every pixel that belongs to the circle.
	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w; // horizontal offset
			int dy = radius - h; // vertical offset
			//It would be a filled square, if we wouldn't check if the point lies within the circle boundaries.
			if ((dx * dx + dy * dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(renderer, x + dx, y + dy);
			}
		}
	}
}

bool Game::update() {
	bool quit = false;
	SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);

	LAST = NOW;
	NOW = SDL_GetPerformanceCounter();
	deltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

	while (SDL_PollEvent(&e) != 0)
	{
		// update keyboard state
		if (e.type == SDL_QUIT)
		{
			quit = true;
		}
		else if (e.type == SDL_JOYAXISMOTION)
		{
			//Motion on controller 0
			if (e.jaxis.which == 0)
			{
				//X axis motion
				if (e.jaxis.axis == 0)
				{
					if (e.jaxis.value < -JOYSTICK_DEAD_ZONE)
					{
						directionPlayer2.setX(-1.0f);
					}
					else if (e.jaxis.value > JOYSTICK_DEAD_ZONE)
					{
						directionPlayer2.setX(1.0f);
					}
					else
					{
						directionPlayer2.setX(0.0f);
					}
				}
				//Y axis motion
				else if (e.jaxis.axis == 1)
				{
					if (e.jaxis.value < -JOYSTICK_DEAD_ZONE)
					{
						directionPlayer2.setY(-1.0f);
					}
					else if (e.jaxis.value > JOYSTICK_DEAD_ZONE)
					{
						directionPlayer2.setY(1.0f);
					}
					else
					{
						directionPlayer2.setY(0.0f);
					}
				}
			}
		}

		const Uint8* state = SDL_GetKeyboardState(NULL);
		if (SDL_GetMouseState(&mouseX, &mouseY)) {
			//std::cout << "Mouse X position: " << mouseX << "  |  Mouse Y position: " << mouseY << "\n";
		}

		if (state[SDL_SCANCODE_UP]) {
			directionPlayer1.setY(-1.0f);
			std::cout << "Keyboard: UP \n";
		}
		else if (state[SDL_SCANCODE_DOWN]) {
			directionPlayer1.setY(1.0f);
			std::cout << "Keyboard: DOWN \n";
		}
		else directionPlayer1.setY(0.0f);

		if (state[SDL_SCANCODE_RIGHT]) {
			directionPlayer1.setX(1.0f);
			std::cout << "Keyboard: RIGHT \n";
		}
		else if (state[SDL_SCANCODE_LEFT]) {
			directionPlayer1.setX(-1.0f);
			std::cout << "Keyboard: LEFT \n";
		}
		else directionPlayer1.setX(0.0f);
	}

	// --------------------------- CAMERA -----------------------------------
	// camera track the player
	cameraRect.x = player1->getPosition().getX() - ScreenWidth / 2;
	cameraRect.y = player1->getPosition().getY() - ScreenHeight / 2;

	// camera stop tracking when comes to end of map
	if (cameraRect.x < 0) cameraRect.x = 0;
	if (cameraRect.y < 0) cameraRect.y = 0;
	if (cameraRect.x > map->columns * 40 - ScreenWidth) cameraRect.x = map->columns * 40 - ScreenWidth;
	if (cameraRect.y > map->rows * 40 - ScreenHeight) cameraRect.y = map->rows * 40 - ScreenHeight;

	SDL_RenderClear(gRenderer);
	map->drawMap(cameraRect.x, cameraRect.y);

	// Player 1 display on screen
	player1->update(directionPlayer1, (float)deltaTime);
	player1->draw(cameraRect.x, cameraRect.y);

	player2->update(directionPlayer2, (float)deltaTime);
	player2->draw(cameraRect.x, cameraRect.y);

	SDL_RenderPresent(gRenderer);
	return quit;
}


void Game::close()
{
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	SDL_JoystickClose(gGameController);
	gGameController = NULL;

	IMG_Quit();
	SDL_Quit();
}