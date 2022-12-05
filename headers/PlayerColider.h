#pragma once


class PlayerColider {
private:
	float width;
	float height;
	float radius;
	bool isCircle;

public:
	PlayerColider(float width, float height);
	PlayerColider(float radius);

	float getHeight();
	float getWidth();
	float getRadius();
	bool getColisionType();
};