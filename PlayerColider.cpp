#include "headers/PlayerColider.h"

PlayerColider::PlayerColider(float width, float height) {
	this->width = width;
	this->height = height;
	isCircle = false;
}

PlayerColider::PlayerColider(float radius) {
	this->radius = radius;
	isCircle = true;
}

float PlayerColider::getHeight() {
	return this->height;
}

float PlayerColider::getWidth() {
	return this->width;
}

float PlayerColider::getRadius() {
	return this->radius;
}

bool PlayerColider::getColisionType() {
	return this->isCircle;
}