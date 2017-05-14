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

void Vec2::transform(double module, double pAngle){
	x = module * cos(pAngle);
	y = module * sin(pAngle);
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

Vec2 *Vec2::rotate(double pAngle){
	double new_x = x * cos(pAngle) - y * sin(pAngle);
	double new_y = x * sin(pAngle) + y * cos(pAngle);

	Vec2 *newVec = new Vec2(new_x, new_y);

	return newVec;
}

Vec2 *Vec2::rotate(double pAngle, double px, double py){
	Vec2 *newVec = translate(-px, -py);

	newVec = newVec->rotate(pAngle);
	newVec = newVec->translate(px, py);

	return newVec;
}

double Vec2::angle(double x, double y){
	return atan2(y, x);
}
