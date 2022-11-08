#include "headers/GameObject.h"
#include "headers/TextureManager.h"

GameObject::GameObject(const char* texturesheet, int x, int y, int w, int h) {
	objTexture = TextureManager::loadTexture(texturesheet);

	xPos = x;
	yPos = y;
	width = w;
	height = h;
	destRect = { xPos, yPos, width, height };
}

void GameObject::Update(myVector* wektor) {
	destRect = { (int)wektor->getX(), (int)wektor->getY(), width, height};

}

void GameObject::Render() {
	SDL_RenderCopy(Game::gRenderer, objTexture, NULL, &destRect);
}

void GameObject::Destroy() {
	SDL_DestroyTexture(objTexture);
}