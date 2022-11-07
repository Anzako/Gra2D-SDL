#include "Game.h"
#include "GameObject.h"
#include "TextureManager.h"
#include "Map.h"

Map* map;

SDL_Renderer* Game::gRenderer = nullptr;

Game::Game(int width, int height) {
	// delta time
	NOW = SDL_GetPerformanceCounter();
	LAST = 0;
	deltaTime = 0;

	ScreenWidth = width;
	ScreenHeight = height;
	TileSize = 40;

	// ----------------------------------- || -----------------------------------------

	player1_Speed = 0.6;
	position = { 20, 20 };
	directionPlayer = { 0, 0 };
	circleColor = { 94, 114, 0, 127 };
}

Game::~Game() {}

bool Game::init(const char* title, bool fullscreen) {
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
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

		const Uint8* state = SDL_GetKeyboardState(NULL);
		if (SDL_GetMouseState(&mouseX, &mouseY)) {
			//std::cout << "Mouse X position: " << mouseX << "  |  Mouse Y position: " << mouseY << "\n";
		}

		if (state[SDL_SCANCODE_UP]) {
			directionPlayer.setY(-1.0f);
			std::cout << "Keyboard: UP \n";
		}
		else if (state[SDL_SCANCODE_DOWN]) {
			directionPlayer.setY(1.0f);
			std::cout << "Keyboard: DOWN \n";
		}
		else directionPlayer.setY(0.0f);

		if (state[SDL_SCANCODE_RIGHT]) {
			directionPlayer.setX(1.0f);
			std::cout << "Keyboard: RIGHT \n";
		}
		else if (state[SDL_SCANCODE_LEFT]) {
			directionPlayer.setX(-1.0f);
			std::cout << "Keyboard: LEFT \n";
		}
		else directionPlayer.setX(0.0f);
	}
	
	// ------------------------- MOVEMENT --------------------------------------

	myVector movement = directionPlayer.normalize();
	movement.ScalarMultiply((float)deltaTime * (float)player1_Speed);
	position.Add(movement);

	// top and left borders
	if (position.getX() < 0) position.setX(0);
	if (position.getY() < 0) position.setY(0);

	// right and down borders
	if (position.getX() > map->columns * 40 - 40) position.setX(map->columns * 40 - 40);
	if (position.getY() > map->rows * 40 - 40) position.setY(map->rows * 40 - 40);
	

	// --------------------------- CAMERA -----------------------------------
	// camera track the player
	cameraRect.x = position.getX() - ScreenWidth / 2;
	cameraRect.y = position.getY() - 400;

	// camera stop tracking when comes to end of map
	if (cameraRect.x < 0) cameraRect.x = 0;
	if (cameraRect.y < 0) cameraRect.y = 0;
	if (cameraRect.x > map->columns * 40 - ScreenWidth) cameraRect.x = map->columns * 40 - ScreenWidth;
	if (cameraRect.y > map->rows * 40 - ScreenHeight) cameraRect.y = map->rows * 40 - ScreenHeight;
	

	SDL_RenderClear(gRenderer);
	map->drawMap(cameraRect.x, cameraRect.y);
	// Player
	SDL_Rect player1Rect = { position.getX() - cameraRect.x, position.getY() - cameraRect.y, 40, 40 };
	SDL_Rect src = { 0, 0, 40, 40 };
	SDL_Texture* draco = TextureManager::loadTexture("assets/draco.png");
	
	TextureManager::drawTile(draco, src, player1Rect);

	// kolo
	//drawCircle(gRenderer, mouseX, mouseY, 40, circleColor);

	SDL_RenderPresent(gRenderer);
	return quit;
}


void Game::close()
{
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}