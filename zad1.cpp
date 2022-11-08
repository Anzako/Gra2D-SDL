#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "headers/myVector.h"
#include "headers/Game.h"

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;

Game* game = nullptr;
const Uint8* state = SDL_GetKeyboardState(NULL);

int main(int argc, char* args[])
{
	game = new Game(SCREEN_WIDTH, SCREEN_HEIGHT);

	if (!game->init("gameWindow", false))
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!game->loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			bool quit = false;
			while (!quit)
			{
				if (game->update()) quit = true;
			}
		}
	}
	game->close();
	return 0;
}

