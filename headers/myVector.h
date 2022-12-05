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

	myVector& Add(const myVector& vec);
	myVector& Subtract(const myVector& vec);
	myVector& Multiply(const myVector& vec);
	myVector& ScalarMultiply(float scalar);
	myVector& Divide(const myVector& vec);
	myVector& ScalarDivide(float scalar);
	static myVector& Subtract(const myVector& vec1, const myVector& vec2);
	static bool Equals(const myVector& vec1, const myVector& vec2);
	float length();
	myVector& normalize();
};
