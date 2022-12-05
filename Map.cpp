#include "headers/Map.h"
#include "headers/TextureManager.h"
#include <fstream>

float clamp(float min, float max, float value) {
	if (value < min) {
		return min;
	}
	else if (value > max) {
		return max;
	}
	else {
		return value;
	}
}

Map::Map(int rowNum, int colNum, int screenWidth, int screenHeight, int tileSize) {
	dirt = TextureManager::loadTexture("../assets/dirt.png");
	grass = TextureManager::loadTexture("../assets/grass.png");
	water = TextureManager::loadTexture("../assets/water.png");
	brick = TextureManager::loadTexture("../assets/brick.png");
	floor = TextureManager::loadTexture("../assets/floor.png");

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
	std::ifstream mapFile("../assets/mapFile.txt");
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
					TextureManager::drawTile(grass, src, dest, NULL);
					break;
				case 1:
					TextureManager::drawTile(water, src, dest, NULL);
					break;
				case 2:
					TextureManager::drawTile(dirt, src, dest, NULL);
					break;
				case 3:
					TextureManager::drawTile(brick, src, dest, NULL);
					break;
				case 4:
					TextureManager::drawTile(floor, src, dest, NULL);
					break;
			}
		}
	}
}


void Map::checkCollision(Player* player) {
	int type = 0;
	//int cameraTileX = cameraX / tSize;
	//int cameraTileY = cameraY / tSize;
	//int width = sWidth / scale;
	//int height = sHeight / scale;

	for (int row = 0; row < rows; row++) {
		for (int col = 0; col < columns; col++) {
			type = map[row][col];
			float playerX = player->getPosition().getX();
			float playerY = player->getPosition().getY();
			float tileX = col * tSize;
			float tileY = row * tSize;
			if (type == 3) {
				if (!player->getCollisionType()) {
					float left = playerX + player->getWidth() - tileX;
					float right = tileX + tSize - playerX;
					float top = playerY + player->getHeight() - tileY;
					float bottom = tileY + tSize - playerY;
					//if (playerX + player->getWidth() > tileX && playerX < tileX + tSize
						//&& playerY + player->getHeight() > tileY && playerY < tileY + tSize) {
					if (left > 0 && right > 0 && top > 0 && bottom > 0) {
						float separatedX;
						float separatedY;

						if (left < right) {
							separatedX = -left;
						}
						else {
							separatedX = right;
						}

						if (top < bottom) {
							separatedY = -top;
						}
						else {
							separatedY = bottom;
						}

						if (abs(separatedX) < abs(separatedY)) {
							separatedY = 0;
						}
						else separatedX = 0;
					
						myVector wektor = { separatedX, separatedY };
						player->addPosition(wektor);
					}
				}
				if (player->getCollisionType()) {
					float radius = player->getRadius();
					float centerX = playerX + radius;
					float centerY = playerY + radius;

					myVector playerWektor = { centerX, centerY };
					myVector rectWektor = { clamp(tileX, tileX + tSize, centerX),
						clamp(tileY, tileY + tSize, centerY) };

					float distance = myVector::Subtract(playerWektor, rectWektor).length();

					if (distance < radius) {
						if (myVector::Equals(playerWektor, rectWektor)) {
							float left = rectWektor.getX() - tileX + radius;
							float right = tileX + tSize - rectWektor.getX() + radius;
							float top = rectWektor.getY() - tileY + radius;
							float bottom = tileY + tSize - rectWektor.getY() + radius;

							float separatedX;
							float separatedY;

							if (left < right) {
								separatedX = -left;
							}
							else {
								separatedX = right;
							}

							if (top < bottom) {
								separatedY = -top;
							}
							else {
								separatedY = bottom;
							}

							if (abs(separatedX) < abs(separatedY)) {
								separatedY = 0;
							}
							else separatedX = 0;

							myVector wektor = { separatedX, separatedY };
							wektor.Coordinates();
							player->addPosition(wektor);
						}
						else {
							myVector wektor = myVector::Subtract(playerWektor, rectWektor);
							wektor.ScalarDivide(distance);
							wektor.ScalarMultiply(radius - distance);
							
							player->addPosition(wektor);
						}

					}

					


				}

				
			}
		}
	}
}

