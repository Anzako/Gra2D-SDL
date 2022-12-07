#include "headers/Player.h"
#include "headers/TextureManager.h"

Player::Player(float x, float y, float Speed, const char* texName, int width, int height, PlayerColider* kolider) {
	position = { x, y };
	movement = { 0, 0 };
	textureName = texName;
	speed = Speed;
	mapWidth = width;
	mapHeight = height;
	colider = kolider;
}

void Player::load() {


}

void Player::update(myVector direction, float deltaTime) {
	movement = direction.normalize();
	movement.ScalarMultiply(deltaTime * speed);
	position.Add(movement);

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
	TextureManager::drawTile(texture, src, player1Rect, 126);
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

bool Player::isMoving() {
	bool move = true;
	if (movement.getX() == 0 && movement.getY() == 0) {
		move = false;
	}
	return move;
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