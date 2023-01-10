#pragma once
#include "Game.h"

class Map {
public:
	Map(int rowNum, int colNum, int screenWidth, int screenHeight, int tileSize, const char* fileName);
	Map();
	~Map();

	int rows, columns;
	int sWidth, sHeight;
	int tSize;
	void loadMap(const char* file);
	void drawMap(int cameraX, int cameraY, float scale);
	myVector getObjective();
	int getTileNumber(int x, int y);

private:
	SDL_Rect src, dest;

	SDL_Texture* underground;
	SDL_Texture* grass;
	SDL_Texture* water;
	SDL_Texture* brick;
	SDL_Texture* floor;
	SDL_Texture* stone;
	SDL_Texture* fence;
	SDL_Texture* cloud;
	SDL_Texture* sun;

	int **map;

	myVector objectivePosition;
};
