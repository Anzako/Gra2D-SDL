#pragma once

class myVector
{
private:
	float x;
	float y;

public:
	myVector();
	myVector(float x, float y);

	float getX();
	float getY();
	void setX(float x);
	void setY(float y);

	void Coordinates();
	myVector& ScalarMultiply(float scalar);
	myVector& Add(const myVector& vec);
	myVector& Subtract(const myVector& vec);
	myVector& Multiply(const myVector& vec);
	myVector& Divide(const myVector& vec);

	float length();
	myVector& normalize();
};
