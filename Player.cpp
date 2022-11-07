#include "Player.h"

Player::Player(float x, float y) {
	position = { x, y };
	direction = { 0, 0 };


}

void Player::load() {


}

void Player::update(const Uint8* state, float deltaTime) {
	if (state[SDL_SCANCODE_UP]) {
		direction.setY(-1.0f);
		//std::cout << "Keyboard: UP \n";
	}
	else if (state[SDL_SCANCODE_DOWN]) {
		direction.setY(1.0f);
		//std::cout << "Keyboard: DOWN \n";
	}
	else direction.setY(0.0f);

	if (state[SDL_SCANCODE_RIGHT]) {
		direction.setX(1.0f);
		//std::cout << "Keyboard: RIGHT \n";
	}
	else if (state[SDL_SCANCODE_LEFT]) {
		direction.setX(-1.0f);
		//std::cout << "Keyboard: LEFT \n";
	}
	else direction.setX(0.0f);

	myVector movement = direction.normalize();
	movement.ScalarMultiply(deltaTime * speed);
	position.Add(movement);

	// top and left borders
	if (position.getX() < 0) position.setX(0);
	if (position.getY() < 0) position.setY(0);

	// right and down borders
	//if (position.getX() > map->columns * 40 - 40) { position.setX(map->columns * 40 - 40); std::cout << "here comes border"; }
	//if (position.getY() > map->rows * 40 - 40) position.setY(map->rows * 40 - 40);

}