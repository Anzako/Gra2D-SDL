#include "Map.h"
#include "TextureManager.h"
#include <fstream>

Map::Map(int rowNum, int colNum, int screenWidth, int screenHeight, int tileSize) {
	dirt = TextureManager::loadTexture("assets/dirt.png");
	grass = TextureManager::loadTexture("assets/grass.png");
	water = TextureManager::loadTexture("assets/water.png");
	brick = TextureManager::loadTexture("assets/brick.png");
	floor = TextureManager::loadTexture("assets/floor.png");

	rows = rowNum;
	columns = colNum;
	sWidth = screenWidth;
	sHeight = screenHeight;
	tSize = tileSize;

	map = new int*[rows];
	for (int i = 0; i < rows; i++)
		map[i] = new int[columns];

	loadMap();
	src = { 0, 0, tSize, tSize};
	dest = { 0, 0, tSize, tSize};
}

void Map::loadMap() {
	int number;
	std::ifstream mapFile("mapFile.txt");
	if (!mapFile.is_open()) {
		std::cout << "duapa" << " \n";
	} else {
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < columns; col++) {
				mapFile >> number;
				map[row][col] = number;
			}
		}
	}
	
	mapFile.close();
}

void Map::drawMap(int cameraX, int cameraY) {
	int type = 0;
	int cameraTileX = cameraX / tSize;
	int cameraTileY = cameraY / tSize;

	for (int row = 0; row < (int)(sHeight / tSize) + 1; row++) {
		for (int col = 0; col < (int)(sWidth / tSize) + 1; col++) {
			if (row + cameraTileY == rows || col + cameraTileX == columns) {
				break;
			} else type = map[row + cameraTileY][col + cameraTileX];

			dest.x = col * tSize - (cameraX - cameraTileX * tSize);
			dest.y = row * tSize - (cameraY - cameraTileY * tSize);

			switch (type) {
				case 0:
					TextureManager::drawTile(grass, src, dest);
					break;
				case 1:
					TextureManager::drawTile(water, src, dest);
					break;
				case 2:
					TextureManager::drawTile(dirt, src, dest);
					break;
				case 3:
					TextureManager::drawTile(brick, src, dest);
					break;
				case 4:
					TextureManager::drawTile(floor, src, dest);
					break;
			}
		}
	}
}

