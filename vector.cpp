#include "vector.h"

using namespace MyOGLProg;

Vector::Vector(void)
{
	this->x = this->y = this->z = 0.0;
}

Vector::Vector(float x, float y, float z)
{
	this->x = x; this->y = y; this->z = z;
}

Vector::Vector(Position& start, Position& end)
{
	//initialise this vector from two positions
	this->x = end.x - start.x;
	this->y = end.y - start.y;
	this->z = end.z - start.z;
}

Vector Vector::addTo(const Vector &other) const
{
	//add this vector to other and return the result
	Vector result;
	//your code here
	result.x = other.x + this->x;
    result.y = other.y + this->y;
	result.z = other.z + this->z;
	return result;
}

Vector Vector::subtractFrom(const Vector &other) const
{
	//subtract this vector from other and return the result
	Vector result;
	//your code here
	result.x = other.x - this ->x;
	result.y = other.y - this ->y;
	result.z = other.z - this ->z;
	return result;
}
		
float Vector::getMagnitude(void) const
{
	//get the length of the vector
	float result;
	//result = sqrt((x*x) + (y*y) + (z*z));
	return result;
}

void Vector::setMagnitude(const float m)
{
	//set the length of the vector
	//your code here
	
}
	
float Vector::getDotProduct(const Vector &other) const
{
	//return the dot product between this vector and other
	float result;
	//your code here
	float x = other.x + this->x;
	float y = other.y + this->y;
	float z = other.z + this->z;
	result =  x +  y +  z;
	return result;
}

Vector Vector::getCrossProduct(const Vector &other) const
{
	//return the cross product between this vector and other
	Vector result;
	//your code here
	result.x = (other.z * this->y) - (this->z * other.y);
	result.y = (other.x * this->z) - (this->x * other.z);
	result.z = (other.y * this->x) - (this->y * other.x);
	return result;
}

void Vector::normalise(void)
{
	//normalise this vector (set its length to 1)
	//your code here
}

