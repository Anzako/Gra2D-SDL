#pragma once
#include "myVector.h"
#include <SDL_image.h>
#include <iostream>
#include "PlayerColider.h"

class Player {
public:
	Player(myVector position, float speed, const char* texName, int width, int height, PlayerColider* kolider);
	void load();
	void update(myVector direction, float deltaTime);
	void draw(float cameraX, float cameraY);
	void setPositionX(float x);
	void setPositionY(float y);
	void setPosition(myVector wektor);
	myVector getPosition();
	bool isMoving();
	bool getCollisionType();
	float getWidth();
	float getHeight();
	float getRadius();
	void addPosition(myVector wektor);

private:
	float speed;
	myVector position;
	myVector movement;
	PlayerColider* colider;
	const char* textureName;
	int mapWidth;
	int mapHeight;
};
