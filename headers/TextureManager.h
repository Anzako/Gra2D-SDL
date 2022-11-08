#pragma once

#include "Game.h"

class TextureManager {
public:
	static SDL_Texture* loadTexture(const char* path);
	static void drawTile(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest, Uint8 alpha);
};
