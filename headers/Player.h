#pragma once
#include "myVector.h"
#include <SDL_image.h>
#include <iostream>
#include "PlayerColider.h"
#include "Map.h"

class Player {
public:
	Player(myVector position, float speed, const char* texName, int mWidth, int mHeight, PlayerColider* kolider);
	void load();
	void update(myVector direction, float deltaTime);
	void draw(float cameraX, float cameraY);
	void updateParameters(int mWidth, int mHeight);
	bool checkCollision(Map map);
	bool isOnGround(Map map);

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
	void setMovement(myVector wektor);
	float getSpeed();


private:
	float speed;
	float jumpHeight;
	float distanceToPeak;

	myVector position;
	myVector movement;
	PlayerColider* colider;
	const char* textureName;
	int mapWidth;
	int mapHeight;
};
