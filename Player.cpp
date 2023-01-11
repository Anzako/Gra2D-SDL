#include "headers/Player.h"
#include "headers/TextureManager.h"

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

Player::Player(myVector wektor, float Speed, const char* texName, int mWidth, int mHeight, PlayerColider* kolider) {
	position = wektor;
	movement = { 0, 0 };
	textureName = texName;
	mapWidth = mWidth;
	mapHeight = mHeight;
	colider = kolider;

	speed = Speed;
}

void Player::load() {


}

float Player::getSpeed() {
	return speed;
}

void Player::update(myVector direction, float deltaTime) {
	//movement = direction.normalize();
	//movement.ScalarMultiply(deltaTime * speed);
	position.Add(direction);

	// top and left borders
	if (position.getX() < 0) position.setX(0);
	if (position.getY() < 0) position.setY(0);

	// right and down borders
	if (position.getX() > mapWidth - 40)  position.setX(mapWidth - 40);
	if (position.getY() > mapHeight - 40) position.setY(mapHeight - 40);

	// borders for players not to go away from screen
}

void Player::draw(float cameraX, float cameraY) {
	SDL_Rect player1Rect = { position.getX() - cameraX, position.getY() - cameraY, 40, 40 };
	SDL_Rect src = { 0, 0, 40, 40 };
	SDL_Texture* texture = TextureManager::loadTexture(textureName);
	TextureManager::drawTile(texture, src, player1Rect, 255);
}

void Player::updateParameters(int mWidth, int mHeight) {
	mapWidth = mWidth;
	mapHeight = mHeight;
}

myVector Player::getPosition() {
	return position;
}

void Player::setPositionX(float x) {
	this->position.setX(x);
}

void Player::setPositionY(float y) {
	this->position.setY(y);
}

void Player::setPosition(myVector wektor) {
	this->position.setX(wektor.getX());
	this->position.setY(wektor.getY());
}

void Player::setMovement(myVector wektor) {
	this->movement = wektor;
}

bool Player::isMoving() {
	bool move = true;
	if (movement.getX() == 0 && movement.getY() == 0) {
		move = false;
	}
	return move;
}

//bool Player::isOnGround(Map map) {
//	int tileX = position.getX() / map.tSize;
//	int tileY = position.getY() / map.tSize;
//	std::cout << position.getX() << " " << tileX << " \n";
//	if (map.getTileNumber(tileX, tileY + 1) == 3) {
//		std::cout << "Dotykasz ziemi \n";
//	} else std::cout << "nie dotykasz ziemi \n";
//	//std::cout << (int)(39 / 40) + " \n";
//	return true;
//}

bool Player::checkCollision(Map map) {
	int type = 0;
	bool isOnGround = false;

	for (int row = 0; row < map.rows; row++) {
		for (int col = 0; col < map.columns; col++) {
			type = map.getTileNumber(row, col);
			float playerX = position.getX();
			float playerY = position.getY();
			float tileX = col * map.tSize;
			float tileY = row * map.tSize;
			if (type == 3 || type == 1 || type == 4 || type == 2) {
				if (!getCollisionType()) {

					float left = playerX + getWidth() - tileX;
					float right = tileX + map.tSize - playerX;
					float top = playerY + getHeight() - tileY;
					float bottom = tileY + map.tSize - playerY;
				
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
						else {
							separatedX = 0;
							if (separatedY == -top) {
								isOnGround = true;
							}
						}
						

						myVector wektor = { separatedX, separatedY };
						addPosition(wektor);
					}
				}
				if (getCollisionType()) {
					float radius = getRadius();
					float centerX = playerX + radius;
					float centerY = playerY + radius;

					myVector playerWektor = { centerX, centerY };
					myVector rectWektor = { clamp(tileX, tileX + map.tSize, centerX),
						clamp(tileY, tileY + map.tSize, centerY) };

					float distance = myVector::Subtract(playerWektor, rectWektor).length();

					if (distance < radius) {
						/*if (type == 1) {
							return true;
						}*/
						if (myVector::Equals(playerWektor, rectWektor)) {
							float left = rectWektor.getX() - tileX + radius;
							float right = tileX + map.tSize - rectWektor.getX() + radius;
							float top = rectWektor.getY() - tileY + radius;
							float bottom = tileY + map.tSize - rectWektor.getY() + radius;

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
							addPosition(wektor);
						}
						else {
							myVector wektor = myVector::Subtract(playerWektor, rectWektor);
							wektor.ScalarDivide(distance);
							wektor.ScalarMultiply(radius - distance);

							addPosition(wektor);
						}
					}
				}
			}
		}
	}
	return isOnGround;
}

bool Player::getCollisionType() {
	return colider->getColisionType();
}

float Player::getHeight() {
	return this->colider->getHeight();
}

float Player::getWidth() {
	return this->colider->getWidth();
}


float Player::getRadius() {
	return this->colider->getRadius();
}

void Player::addPosition(myVector wektor) {
	this->position.Add(wektor);
}