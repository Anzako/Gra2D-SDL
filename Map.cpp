#include "headers/Map.h"
#include "headers/TextureManager.h"
#include <fstream>

Map::Map(int rowNum, int colNum, int screenWidth, int screenHeight, int tileSize, const char* fileName) {
	underground = TextureManager::loadTexture("../assets/underground.png");
	grass = TextureManager::loadTexture("../assets/grass.png");
	water = TextureManager::loadTexture("../assets/water.png");
	brick = TextureManager::loadTexture("../assets/brick.png");
	floor = TextureManager::loadTexture("../assets/floor.png");
	stone = TextureManager::loadTexture("../assets/stone.png");

	rows = rowNum;
	columns = colNum;
	sWidth = screenWidth;
	sHeight = screenHeight;
	tSize = tileSize;

	map = new int*[rows];
	for (int i = 0; i < rows; i++)
		map[i] = new int[columns];

	loadMap(fileName);
	src = { 0, 0, tSize, tSize};
	dest = { 0, 0, tSize, tSize};
}

Map::Map() {
}

Map::~Map()
{
}

myVector Map::getObjective() {
	return objectivePosition;
}

void Map::loadMap(const char* file) {
	int number;
	std::ifstream mapFile(file);
	if (!mapFile.is_open()) {
		std::cout << "Plik mapy nie zostal otwarty" << " \n";
	} else {
		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < columns; col++) {
				mapFile >> number;
				map[row][col] = number;
				if (number == 1) {
					objectivePosition = { (float)col * tSize, (float)row * tSize };
				}
			}
		}
	}
	
	mapFile.close();
}

int Map::getTileNumber(int x, int y) {
	return map[x][y];
}

void Map::drawMap(int cameraX, int cameraY, float scale) {
	int type = 0;
	int cameraTileX = cameraX / tSize;
	int cameraTileY = cameraY / tSize;
	int width = sWidth / scale;
	int height = sHeight / scale;

	for (int row = 0; row < (int)(height / tSize) + 2; row++) {
		for (int col = 0; col < (int)(width / tSize) + 2; col++) {
			if (row + cameraTileY >= rows || col + cameraTileX >= columns || row + cameraTileY < 0 || col + cameraTileX < 0) {
				break;
			} else type = map[row + cameraTileY][col + cameraTileX];

			dest.x = col * tSize - (cameraX - cameraTileX * tSize);
			dest.y = row * tSize - (cameraY - cameraTileY * tSize);

			switch (type) {
				case 0:
					break;
				case 1:
					TextureManager::drawTile(grass, src, dest, NULL);
					break;
				case 2:
					TextureManager::drawTile(underground, src, dest, NULL);
					break;
				case 3:
					TextureManager::drawTile(brick, src, dest, NULL);
					break;
				case 4:
					TextureManager::drawTile(stone, src, dest, NULL);
					break;

			}
		}
	}
}


