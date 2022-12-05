#pragma once
#include "headers/myVector.h"
#include <SDL_image.h>
#include <iostream>

class Ball {
public:
	Ball(float x, float y, float Vx, float Vy, float radius);
	void update(double delta);
	void draw(SDL_Renderer* renderer);
	myVector getPosition();
	float getPositionX();
	float getPositionY();
	myVector getMovement();
	void setPositionX(float x);
	void setPositionY(float y);
	void setMovementX(float x);
	void setMovementY(float y);
	float getRadius();

private:
	myVector Position;
	myVector Movement;
	float Radius;
	float Speed;
};