#include "Vec2.h"

#include <cmath>
#include <cstdio>

Vec2::Vec2(){
	x = 0;
	y = 0;
}

Vec2::Vec2(double pX, double pY){
	x = pX;
	y = pY;
}

double Vec2::length(){
	return hypot(x, y);
}

void Vec2::normalize(){
	double len = length();

	x /= len;
	y /= len;

	length();
}

Vec2 *Vec2::translate(double dx, double dy){
	Vec2 *newVec = new Vec2(x + dx, y + dy);

	return newVec;
}

Vec2 *Vec2::rotate(double angle){
	double new_x = x * cos(angle) - y * sin(angle);
	double new_y = x * sin(angle) + y * cos(angle);

	Vec2 *newVec = new Vec2(new_x, new_y);

	return newVec;
}

Vec2 *Vec2::rotate(double angle, double px, double py){
	Vec2 *newVec = translate(-px, -py);

	newVec = newVec->rotate(angle);
	newVec = newVec->translate(px, py);

	return newVec;
}
