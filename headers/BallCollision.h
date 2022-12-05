#pragma once
#include "Ball.h"
#include "iostream"
#include "vector"

class BallCollision {
private:
	std::vector<Ball> balls;
	int sWidth;
	int sHeight;

public:
	BallCollision(int width, int height, int numberOfBalls);
	~BallCollision();

	void drawAll(SDL_Renderer* renderer);
	void MoveAll(bool separated, bool ballCollide, double deltaTime);
	void generateBalls(int numberOfBalls, float radius);
	void collideBorders();
	void collideWithBalls(bool separation, bool ballCollide);
};