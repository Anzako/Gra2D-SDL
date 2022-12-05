#include "headers/BallCollision.h"

BallCollision::BallCollision(int width, int height, int numberOfBalls) {
	sWidth = width;
	sHeight = height;
	srand((unsigned)time(NULL));
	generateBalls(numberOfBalls, 20);
}


void BallCollision::generateBalls(int numberOfBalls, float radius) {
	for (int i = 0; i < numberOfBalls; i++) {
		float randomX = radius + rand() % (sWidth - (int)radius);
		float randomY = radius + rand() % (sHeight - (int)radius);
		float randomVx = -100 + rand() % 200;
		float randomVy = -100 + rand() % 200;
		Ball ball = { randomX, randomY, randomVx, randomVy , radius };
		balls.push_back(ball);
	}
}

void BallCollision::drawAll(SDL_Renderer* renderer) {
	for (int i = 0; i < balls.size(); i++) {
		balls.at(i).draw(renderer);
	}
}

void BallCollision::MoveAll(bool separated, bool ballCollide, double deltaTime) {
	
	for (int i = 0; i < balls.size(); i++) {
		balls.at(i).update(deltaTime);
	}
	collideWithBalls(separated, ballCollide);
	collideBorders();
}

void BallCollision::collideBorders() {
	for (int i = 0; i < balls.size(); i++) {
		float x = balls.at(i).getPositionX();
		float y = balls.at(i).getPositionY();
		float r = balls.at(i).getRadius();
		if (x - r < 0) {
			balls.at(i).setMovementX(abs(balls.at(i).getMovement().getX()));
		}
		else if (x + r >= sWidth) {
			balls.at(i).setMovementX(-abs(balls.at(i).getMovement().getX()));
		}
		if (y - r < 0) {
			balls.at(i).setMovementY(abs(balls.at(i).getMovement().getY()));
		}
		else if (y + r >= sHeight) {
			balls.at(i).setMovementY(-abs(balls.at(i).getMovement().getY()));
		}
	}

}

void BallCollision::collideWithBalls(bool separation, bool ballCollide) {
	for (int i = 0; i < balls.size(); i++) {
		for (int j = balls.size() - 1; j > i; j--) {
			if (i != j) {
				float left = pow(balls.at(j).getPositionX() - balls.at(i).getPositionX(), 2);
				float right = pow(balls.at(j).getPositionY() - balls.at(i).getPositionY(), 2);
				float distance = sqrt(left + right);
				
				if (distance < balls.at(i).getRadius() + balls.at(j).getRadius()) {
					float overlap = 0.5f * (distance - balls.at(i).getRadius() - balls.at(j).getRadius());
					float newX = overlap
						* (balls.at(i).getPositionX() - balls.at(j).getPositionX()) / distance;
					float newY = overlap
						* (balls.at(i).getPositionY() - balls.at(j).getPositionY()) / distance;

					if (separation) {
						balls.at(i).setPositionX(balls.at(i).getPositionX() - newX);

						balls.at(i).setPositionY(balls.at(i).getPositionY() - newY);

						balls.at(j).setPositionX(balls.at(j).getPositionX() + newX);

						balls.at(j).setPositionY(balls.at(j).getPositionY() + newY);
					}

					if (ballCollide) {
						/*float Vx1 = balls.at(i).getMovement().getX();
						float Vy1 = balls.at(i).getMovement().getY();
						float Vx2 = balls.at(j).getMovement().getX();
						float Vy2 = balls.at(j).getMovement().getY();
						balls.at(i).setMovementX(-Vx1 - 2 * (Vx1 * newX + Vy1 * newY) * newX);
						balls.at(i).setMovementY(-Vy1 - 2 * (Vx1 * newX + Vy1 * newY) * newY);

						balls.at(j).setMovementX(-Vx2 + 2 * (Vx2 * newX + Vy2 * newY) * newX);
						balls.at(j).setMovementY(-Vy2 + 2 * (Vx2 * newX + Vy2 * newY) * newY);
*/
						float Vx1 = balls.at(j).getMovement().getX();
						float Vy1 = balls.at(j).getMovement().getY();
						float Vx2 = balls.at(i).getMovement().getX();
						float Vy2 = balls.at(i).getMovement().getY();

						//tangent 
						float tx = -newX;
						float ty = -newY;

						float dpTan1 = Vx1 * tx + Vy1 * ty;
						float dpTan2 = Vx2 * tx + Vy2 * ty;


						balls.at(i).setMovementX(tx * dpTan1);
						balls.at(i).setMovementY(ty * dpTan1);

						balls.at(j).setMovementX(tx * dpTan2);
						balls.at(j).setMovementY(ty * dpTan2);
					}
					
				}
			

			}

		}
	}
}