#pragma once
#include "Game.h"

class GameObject {
	
public:
	GameObject(const char* texturesheet, int x, int y, int width, int height);
	~GameObject();

	void Update(myVector* wektor);
	void Render();
	void Render(double angle, SDL_Point* center, SDL_RendererFlip flip);
	void Destroy();

private:
	int xPos;
	int yPos;
	int width;
	int height;

	SDL_Texture* objTexture;
	SDL_Rect destRect;
};
