#include "headers/myVector.h"
#include <iostream>

myVector::myVector()
{
	x = 0.0f;
	y = 0.0f;
}

myVector::myVector(float x, float y)
{
	this->x = x;
	this->y = y;
}

float myVector::getX()
{
	return this->x;
}

float myVector::getY()
{
	return this->y;
}

void myVector::setX(float x)
{
	this->x = x;
}

void myVector::setY(float y)
{
	this->y = y;
}

void myVector::Coordinates()
{
	std::cout << "x: " << this->x << "    y: " << this->y << "\n";
}

myVector& myVector::Add(const myVector& vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}
	
myVector& myVector::Subtract(const myVector& vec) 
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

myVector& myVector::Subtract(const myVector& vec1, const myVector& vec2) {
	float x = vec1.x - vec2.x;
	float y = vec1.y - vec2.y;

	myVector wektor = {x, y};
	return wektor;
}

myVector& myVector::ScalarMultiply(float scalar)
{
	this->x *= scalar;
	this->y *= scalar;

	return *this;
}

myVector& myVector::Multiply(const myVector& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

myVector& myVector::Divide(const myVector& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}

myVector& myVector::ScalarDivide(float scalar)
{
	this->x /= scalar;
	this->y /= scalar;

	return *this;
}

float myVector::length()
{
	return sqrt(this->x * this->x + this->y * this->y);
}

myVector& myVector::normalize()
{
	float len = length();
	if (len == 0.0f)
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}
	else {
		this->x /= len;
		this->y /= len;
	}
	
	
	return *this;
}

bool myVector::Equals(const myVector& vec1, const myVector& vec2) {
	return (vec1.x == vec2.x && vec1.y == vec2.y);
}