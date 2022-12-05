#include "headers/Ball.h"

SDL_Color color = { 255, 255, 0, 255 };

Ball::Ball(float x, float y, float Vx, float Vy, float radius) {
	Position = { x, y };
	Movement = { Vx, Vy };
	Radius = radius;
	Speed = 0.9;
}

void Ball::update(double delta) {
	Movement = Movement.ScalarMultiply((float)delta * Speed).normalize();
	Position.Add(Movement);
}

void Ball::draw(SDL_Renderer* renderer) {
	//Renderer is set to draw in given color.
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	//And in those loops we draw a point in every pixel that belongs to the circle.
	for (int w = 0; w < Radius * 2; w++)
	{
		for (int h = 0; h < Radius * 2; h++)
		{
			int dx = Radius - w; // horizontal offset
			int dy = Radius - h; // vertical offset
			//It would be a filled square, if we wouldn't check if the point lies within the circle boundaries.
			if ((dx * dx + dy * dy) <= (Radius * Radius))
			{
				SDL_RenderDrawPoint(renderer, Position.getX() + dx, Position.getY() + dy);
			}
		}
	}
}

myVector Ball::getPosition() {
	return this->Position;
}

myVector Ball::getMovement() {
	return this->Movement;
}

void Ball::setMovementX(float x) {
	this->Movement.setX(x);
}

void Ball::setMovementY(float y) {
	this->Movement.setY(y);
}

float Ball::getRadius() {
	return this->Radius;
}

void Ball::setPositionX(float x) {
	this->Position.setX(x);
}

void Ball::setPositionY(float y) {
	this->Position.setY(y);
}

float Ball::getPositionX() {
	return getPosition().getX();
}

float Ball::getPositionY() {
	return this->Position.getY();
}
