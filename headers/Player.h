#pragma once
#include "myVector.h"
#include <SDL_image.h>
#include <iostream>

class Player {
public:
	Player(float x, float y);
	void load();
	void update(const Uint8* state, float deltaTime);
	void draw();

private:
	float speed;
	myVector position;
	myVector direction;


};
