#ifndef VEC2_H
#define VEC2_H

#include "Rect.h"

class Vec2{
	public:
		double x, y;
	
		Vec2();
		Vec2(double x, double y);
		Vec2(Rect r);

		Vec2 operator+(const Vec2& rhs) const;
		Vec2 operator-(const Vec2& rhs) const;
		Vec2 operator*(const float rhs) const;

		double length();

		void transform(double module, double angle);
		void normalize();

		Vec2 *translate(double dx, double dy);
		Vec2 *rotate(double pAngle);
		Vec2 *rotate(double pAngle, double px, double py);
		
		static double angle(double x, double y);

	private:
};

#endif
