#pragma once
#include "myVector.h"
#include <SDL_image.h>
#include <iostream>

class Player {
public:
	Player(float x, float y, float speed, const char* texName, int width, int height);
	void load();
	void update(myVector direction, float deltaTime, float cameraX, int scaledScreenWidth);
	void draw(float cameraX, float cameraY);
	myVector getPosition();
	bool isMoving();

private:
	float speed;
	myVector position;
	myVector movement;
	const char* textureName;
	int mapWidth;
	int mapHeight;
};
