#pragma once
#include <SDL_image.h>
#include <iostream>
#include "myVector.h"
#include "Player.h"

class Game {
public:
	Game(int width, int height);
	~Game();

	bool init(const char* title, bool fullscreen);
	bool loadMedia();

	void handleEvents();
	bool update();
	bool running() { return isRunning; };
	void render();
	void close();
	void clean();

	static SDL_Renderer* gRenderer;
	SDL_Rect cameraRect = { 0, 0, 1000, 800};

private:
	bool isRunning = false;
	int cnt = 0;
	SDL_Window* gWindow = NULL;
	int ScreenWidth;
	int ScreenHeight;
	int TileSize;
	SDL_Event e;

	// delta time
	Uint64 NOW;
	Uint64 LAST;
	double deltaTime;

	// ----------------------------------- || -----------------------------------------

	Player* player;

	double player1_Speed;

	// vectors
	myVector position;
	myVector directionPlayer;

	int mouseX, mouseY;
	SDL_Color circleColor;
	

};