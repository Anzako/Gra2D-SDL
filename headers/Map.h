#pragma once
#include "Game.h"
#include "Player.h"

class Map {
public:
	Map(int rowNum, int colNum, int screenWidth, int screenHeight, int tileSize);
	~Map();

	int rows, columns;
	int sWidth, sHeight;
	int tSize;
	void loadMap();
	void drawMap(int cameraX, int cameraY, float scale);
	bool checkCollision(Player* player);

private:
	SDL_Rect src, dest;

	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;
	SDL_Texture* brick;
	SDL_Texture* floor;
	int **map;
};
